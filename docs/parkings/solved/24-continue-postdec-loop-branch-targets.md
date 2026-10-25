# Issue 24 - Link-level-only branch-target diffs: `continue` + post-decrement do-while

**Status: ✅ SOLVED (2026-08-22) - fn_800C2284 promoted, DOL byte-identical.**
The masked draft sweep reported EXACT, yet every promotion failed with
"!!! DOL DIFFERS !!!" on a SINGLE word: one intra-function `bge` whose
displacement differed at LINK. The cause was control-flow shape, not codegen
noise: the original skips the rewrite store on the in-range path (`continue`
semantics), and the loop decrement lives INSIDE the condition
(`while (cnt-- != 0)`), which is what puts `continue`'s jump target on the
latch's `cmpwi`.

## The problem

fn_800C2284 (156B, `.text:0x800C2284-0x800C2320`) is the head function of the
0x800C2xxx angular-integration cluster: it walks `count = u[0x1AC/4]` entries
of a 480-byte array (base pointer reloaded each iteration from `obj+0x2F0`),
integrates `nv = vel - dt*0.5*pos; na = dt*nv + ang`, stores `na`, wraps the
angle into `[0, 200*pi]` by +-`100*pi`, stores the wrapped value, and loops
with a post-decremented counter.

Original tail (want): the tail stores the integrated angle, compares it against the high constant (628.3185f, 200*pi) and branches to the second test when at or below it, otherwise subtracts the 314.1593f (100*pi) constant and takes the shared-store branch. The second test compares against 0.0f with a branch-to-latch-head on the in-range path that skips the rewrite store, while the below-range path adds the constant back and falls into the shared rewrite store. The latch then tests the pre-decrement count, advances the base by the 480-byte stride, decrements the counter, and loops back, falling through to the return when done.

Compiled draft (got) was identical except ONE word: the `bge` at 0x800C2300
targeted `0x800c2308` (the store) instead of `0x800c230c` (the latch) - i.e.
the in-range path stored the unmodified angle instead of skipping the store.

## Why every tool said "EXACT"

`tools/test_wip_drafts.py` / `tools/diff_near.py` compare object bytes with
relocation masking: intra-function branches are `R_PPC_REL14/REL24`
relocations whose raw field is masked out (AGENTS.md section 4o warns about
exactly this). A draft whose ONLY defect is a branch landing on the wrong
block therefore scores 100% masked and still breaks the DOL at link. The
masked verdict is NECESSARY but not SUFFICIENT; only
`cmp orig/G2TE52/sys/main.dol build/G2TE52/main.dol` after the real link is
proof.

## Diagnosis recipe (works for any masked-EXACT / DOL-DIFFERS case)

```sh
cp src/wip/fn_X.c src/fn_X.c                       # manual registration
tools/venv/bin/python tools/add_gen_leaves.py      # splits.txt + configure.py
python3 configure.py --dtk tools/dtk --ninja tools/ninja --compilers build/compilers
rm -f build/G2TE52/main.elf build/G2TE52/main.dol
tools/ninja build/G2TE52/main.dol
cmp orig/G2TE52/sys/main.dol build/G2TE52/main.dol \
  || tools/venv/bin/python tools/cmp_dols.py orig/G2TE52/sys/main.dol build/G2TE52/main.dol
```

`tools/cmp_dols.py` prints differing words WITH virtual addresses - here it
pinpointed `file 0xBF300 vaddr 0x800c2300` and showed want `bge 0x800c230c` /
got `bge 0x800c2308`. One differing branch word = block-layout problem: find
what the want target block DOES that the got target doesn't (here: skip a
store), then find the C statement whose presence/absence moves that block.

## First fix attempt (wrong)

Adding plain `continue` did NOT match:

```c
if (na > c2)      na -= c3;
else if (na < c4) na += c3;
else                   continue;   // in-range: skip the rewrite store
*(volatile f32 *)&o[0xC/4] = na;
__asm__ volatile ("" ::: "memory");
cnt--;
} while (cnt != -1);
```

Result: `bge` now targeted the `cmpwi r8,-1` TEST only (skipping the stride
AND the decrement) and the latch emitted `addi r8,-1; cmpwi r8,-1` (test on
POST-decrement value). Reason: in a do-while, `continue` jumps to the
CONDITION EVALUATION POINT, which sits AFTER the body-tail statements
(`cnt--;`). The want's `bge` lands on the `cmpwi` BEFORE both the stride and
the decrement - impossible while the decrement is a separate statement.

## The actual cause (winning source form)

The original source evaluates the decrement AS PART OF THE CONDITION:

```c
do {
    /* ... base reload, loads, integrate ... */
    *(volatile f32 *)&o[0xC/4] = na;        // first store (integrated value)
    if (na > c2)      na -= c3;             // wrap above 200*pi
    else if (na < c4) na += c3;             // wrap below 0
    else              continue;             // in range: SKIP rewrite store
    *(volatile f32 *)&o[0xC/4] = na;        // shared rewrite store
    __asm__ volatile ("" ::: "memory");
} while (cnt-- != 0);
```

Two properties reproduce the want exactly:

1. `else continue;` gives the in-range path a direct edge to the latch,
   sharing the store between the two wrap arms (`b 0x800c2308` + fall-through)
   and skipping it entirely on the third path (`bge` to latch head).
2. `cnt--` inside the condition makes GCC emit the latch as
   `cmpwi r8,0 / addi r11,-480 / addi r8,-1 / bne`: the TEST reads the
   PRE-decrement value, and `continue`'s target (condition start) is the
   `cmpwi` itself - both matching the want byte-for-byte.

With that, the manually registered object linked to a byte-identical DOL;
promoted via the standard loop afterwards.

## Lessons for future drafts

- A single-word link diff that masks clean is almost always a BLOCK-LAYOUT
  difference: something in the want's target block exists/doesn't exist in
  yours. Read the two branch targets' instructions, diff their behavior.
- `continue` in do-while loops targets the condition, not the body tail. Any
  latch bookkeeping (counters, strides) that must execute on the continue
  path has to be part of the condition expression (`cnt-- != 0`,
  `(ptr += stride) < end`, ...) - a trailing `cnt--;` statement is evaluated
  AFTER the continue edge and will desync both the target AND the tested
  value.
- `while (X--) != LIMIT)` is the general form behind the cluster's other
  fixes: the head guard `if (cnt-- == 0) return;` (pre-loop, same
  post-dec-in-test idiom) plus this bottom `while (cnt-- != 0)` cracked the
  0x800C2xxx angular-loop family (see also the fn_800C4734/fn_800C48A0/
  fn_800C47EC promotions from the same round).
- Operational note: during this round, two promote attempts ALSO failed while
  another agent's promotion was mid-flight (shared configure/build state).
  Before debugging your own function, run a plain
  `tools/ninja build/G2TE52/main.dol && cmp ...` on the untouched tree -
  if THAT differs, the tree is polluted; retry once it settles.

## 2026-08-31 additions — duplicate-guard merge + short-circuit layout

Two more masked-EXACT-but-link-different variants of the same class:

### (a) Duplicate-`if` guard merge (fn_80184A2C → PROMOTED)

Tail was two consecutive `if (sp48s.v != 0)` blocks. The original keeps TWO
separate `lwz/cmpwi/beq` guard pairs; ngccc proves the field unchanged and
jump-threads the SECOND guard's `beq` straight to the shared epilogue
(merging both blocks' test), changing one `beq` displacement at link. Fix:
`__asm__("" ::: "memory");` between the two ifs — forces a re-read, the
second guard stays a separate block, DOL byte-identical.

### (b) Short-circuit `&&` branch LAYOUT (fn_80172C44, parked)

`if ((fnA() != 0) && (fnB() == 0)) { fnC(); }` — the semantics match, but the
original emits `beq <fnC-block>` from the A-test (fall into the B test), while
ngccc emits `beq <past-fnC>` + skips; identical 3-block control flow, one
`beq` displacement differs at link. Resisted: `||`-inverted, `!()`-wrapped,
nested-if, goto forms (all normalize to the same layout). Parked at
masked-EXACT; NOT promotable until a shape forces the fnC-block-adjacent
layout.

### (c) 3-way shared tail not merged on all inputs (fn_8019591C, parked — NOT the barrier case)

fn_8019591C ends with `fn_8018CD64(arg0)` as a shared tail reached from ALL
of: (1) first vtable-dispatch guard fail, (2) second vtable-dispatch guard
fail, (3) the `var_r30 == 0` else. The original has one `mr r3,r31; bl
fn_8018CD64` block at 0x80195a90 and ALL THREE branches (beq @0x95960, bne
@0x95980, beq @0x95a6c) point at it. ngccc only merges the LAST input (the
`var_r30 == 0` beq lands correctly on the shared block); the two far-textually-removed
vtable guards come out 8B too long, landing on the epilogue @0x80195a98 and
SKIPPING the shared call. This is distinct from (a): the barrier trick doesn't
apply (guards aren't duplicate ifs; they're two different calls feeding one
merge), and it's distinct from (b) (short-circuit 3-block, not a shared tail).

Resisted (ALL masked-EXACT, ALL link-differ identically on exactly those two
guard branches): single trailing fall-through call; explicit `goto cd64` on
both guards (inverted `== 0` / `!= 0`); else-if chains; duplicated
`fn_8018CD64(...); return;` on each guard path (that one regressed hard to 69
masked diffs — the extra `mr r3,r31` per path changes allocation). Because the
`var_r30 == 0` merge works but the guard merges don't, the differing variable
is ngccc's per-branch distance/layout decision, not our C. Parked as asm in
`src/wip/fn_8019591C.c` with full notes; DOL reverts byte-identical.

### (d) `bl`-heavy bodies with internal forward branches (fn_801FA318, parked)

Masked-EXACT with 9 raw-diff words (internal `bge/beq/bne/blt` + `bl` targets)
— all link-resolved, but the built DOL still differs on ONE internal branch
word. Same diagnosis: control-flow shape, keep parked.

### (e) SOLVED — shared increment block re-entered as FALL-THROUGH (fn_80237604 → PROMOTED)

fn_80237604 (260B) iterates a node list docked by fn_802432A8/fn_80237D14. The
masked draft compiled EXACT except ONE word: retail `beq cr4, 0x80237688`
(falls INTO the count increment block when `arg2&4 == 0`), built emitted
`beq cr4, 0x802376c4` (skipped all increments). Reading retail, the increment
block runs when `!( (arg2&4) && (Get(node).f8 & 0x20) )` — i.e. increments are
UNCONDITIONAL and `arg2&4` only gates the mask-skip. The m2c source had
wrapped ALL of that inside `if (arg2 & 4) { if (!mask) { inc } }`, so ngccc
correctly pointed the false-test at the latch.

Fix (PROMOTED, DOL byte-identical): make the `arg2&4` guard only a
`goto node_next` skip and put the increments OUTSIDE it:

```c
do {
    if (arg2 & 4) {
        s32 n2 = Get(node);
        if (*(s32 *)((char *)n2 + 8) & 0x20)
            goto node_next;              /* skip increments — beq target */
    }
    count1++; count2 += ...; fn_802371CC(...);  /* shared, FALL-THROUGH */
node_next:
    node = *(void **)((char *)node + 0xC);
} while (node != NULL);
```

Key contrast with (c): in (c) the shared block was a CALL reached only via
gotos and the compiler refused to route distant guards at it; here the shared
block is reached by FALL-THROUGH from the guard-false path, so ngccc happily
places it adjacent and points `beq cr4` at it. The winning shape is "guard
early-exits via goto to the latch, shared body stays a fall-through."

### (d-repeat)

General rule reinforced: masked-EXACT is a NECESSARY but not SUFFICIENT
condition for promotion. The promote pipeline's final full-DOL byte-compare
is the only trustworthy gate; a masked 100% with any internal conditional
branch should be link-verified before trusting it.

---

## 2026-09-02 — RELOC-ADDEND METHOD (generalized diagnosis, 2 more members closed)

The masked sweep reports EXACT because raw .o bytes match; a *conditional
branch* whose target is inside the same .text section is RELOC-FILLED
(R_PPC_REL14, section-relative), so two different block layouts can compile
to byte-identical objects and differ only at link time. Diagnosis recipe
that cracked fn_80136CAC and fn_8013A9FC:

1. Promote once and let it revert; run the manual build and binary-diff the
   DOLs (python: walk to first differing file offset, map through the DOL
   header to a .text VA).
2. Compare orig vs built word at the branch: `41820014` vs `41820010` — the
   low 16 bits ARE the target delta; convert to the section-relative addend
   the linker applied (`branch_pc + delta*4 - 4` semantics; just note
   orig/built target offsets).
3. `powerpc-eabi-readelf -r fn_XXXX.o` gives the object's own addend
   (e.g. `.text + 0x60`); the goal is a source shape whose addend equals the
   ORIG target offset.
4. Disassemble the ORIG function region from the DOL (objdump -b binary) and
   read the block at the orig target — the instruction there tells you which
   source statement the beq must skip (a store? a `li`? a whole call?).
5. Restructure the C so that statement sits where the beq must skip it, then
   verify the object's addend moved before re-promoting.

Results:
- **fn_80136CAC** (132B, DVD path helper) — orig beq@0x50 → 0x64 (`li r3,1`):
  call AND the `*(base+0xA8) = 0` store both INSIDE the if, `return 1`
  shared after the if. (Store-after-if links 0x60; call+store+return-1 all
  inside the if links 0x6C.) Promoted, DOL byte-identical.
- **fn_8013A9FC** (188B, script message handler) — orig beq@0x34 → 0x74
  (`li r3,4; b epilogue`): `return 4` EARLY-EXIT inside the bit-test
  branch (beq skips the fn_8013F74C call test); the F74C if is the ELSE
  path of the outer bit-test if. m2c's flattened sibling-ifs links 0x60.
  Promoted, DOL byte-identical.

Still open (masked-EXACT, link-differs, addend-walked but unsolved):
- **fn_8020ACB0** (308B) — SOLVED 2026-09-02, see below.
- **fn_80134E1C, fn_80169070, fn_80172C44** — earlier-generation parks
  (see WIP.md registry rows for per-fn notes).

## SOLVED 2026-09-02 — fn_8020ACB0 (message-dispatch, 308B)

The "2-entry state-machine" reading was itself inverted. Retail disasm
shows ONE tail-merge block at .text+0xDC with THREE entries:
- beq@0x44 / beq@0x5C (hash match 0xA4B7A992 / 0xDA3A5A4D) → 0xDC
- beq@0xCC (0x1C10==0) and the 0x1C0C!=0 fall-through → 0xDC
- the lfs fast path b@0xA4 → 0xE8 (INTO the middle of the merged tail,
  skipping the fn_8020ADE4 call because f1 comes from lbl_802AF380)

The m2c draft's `!= A && != DA` guard skips the send on hash match —
semantic inversion; retail hash-match SENDS. Fix: plain 3-site if/else
with the natural `fn_800CC038(temp_r30,1,0,0,var_f1)` at each site; MWCC
regenerates the merge (308B, 100% masked, all 10 branch addends match).
The earlier goto-rewrite failed only because it wasn't the natural form.
Promoted, DOL byte-identical.

## SOLVED 2026-09-02 — all three members promoted via reloc-addend method

The trio is fully cracked; each had a *different* root cause behind the same
reloc-masked symptom (byte-EXACT object, DOL diff at one branch word):

1. **fn_80172C44** (232B): m2c **inverted the short-circuit** — retail is
   `if (fn_8011BC38() == 0 || fn_8011BC60() == 0) fn_8011CF0C();`. The orig
   `beq@0xEC` addend (`.text+0xFC`) lands *inside* the call; m2c's `&&` form
   skips it. Diagnostic: orig displacement byte 0x10 vs built 0x14, one word.

2. **fn_80169070** (1124B, ScriptLoadFromMemoryCard): the switch **default arm
   was missing** — retail's `b@0x110`/`blt@0x118` both target `.text+0x3C8`
   (the r27 file-handle cleanup block); m2c's default fell through to the
   post-switch join at 0x1D0. Fix: `default: goto cleanup;`. Diagnostic: two
   converging orig targets ≠ any draft target = missing arm.

3. **fn_80134E1C** (852B parser): cross-jump **barrier placement** — the
   `"+r"` barrier pinning the two merged 5/6-case tails must sit BEFORE the
   empty loop, not after; then `bge@0x2AC`'s addend threads directly to the
   shared `add r27,r27,r8` tail (`.text+0x338`) instead of chaining through
   the merged `b`. Swept 5 tail-region variants; barrier-first was the only
   0-wrong-addend form.

Method recap (now fully general): compile → cmp DOLs → decode the differing
branch words as displacements → resolve against BOTH address maps → the
target block tells you which source shape the compiler must emit. Raw .o
displacement fields are linker placeholders; only addends are ground truth.

## 2026-09-06 — NEW MEMBER SOLVED: fn_8000BEEC via the if/return-structured GOTO recipe

fn_8000BEEC (80B state-machine command dispatcher; was parked 85% with
"nested else-if best, flat goto chain 68%, switch 60%") is byte-exact with a
form nobody had tried: an **if/return-structured goto transcription** —

- the compares stay INLINE in want's order (`==1`, `>1`, `==2`, `==5`),
- the two single-call blocks become TRAILING LABELS (`state1:` / `state2:`),
- the inline (no-call) path ends in a bare `return;` so the labels are only
  reachable via the forward gotos,

```c
if (state == 1) goto state1;
if (state > 1) {
    if (state == 2) goto state2;
    if (state == 5) fn_8000BF3C(arg0);
}
return;
state1:
    fn_8000C39C((Unk_76808E8C *)arg0);
    return;
state2:
    fn_8000BF80((Unk_AD12C14B *)arg0);
```

This gives GCC the out-of-line placement want has (compare against 1 with an equal branch to the first label, a less-or-equal branch to the end, compare against 2 with an equal branch to the second label, compare against 5 with a not-equal branch to the end, the first call, a branch to the end, then the two out-of-line call labels each followed by a branch to the end) — 20/20, promoted. Why the earlier "goto chain" failed at 68%: a
FLAT `if (a==1) goto L1; if (a==2) goto L2; if (a==5) ...` removes the
`state > 1` guard, so the compare order no longer matches want's; the
structured form keeps it. Recipe class: "out-of-line call block placement" —
worth trying on other doc-24-family parks where a call block must NOT be
inline (promoted src/fn_8000BEEC.c holds the full example).

## 2026-09-13 — `tools/br_targets.py` is now the FAST front-end for this class

Every earlier entry in this doc needed a full manual rebuild + `cmp_dols.py`
to find the offending branch. `tools/br_targets.py` already resolves the
object's REL14/REL24 relocations the way the linker does (target =
`function_base + symbol_value + addend`) and diffs them against retail's own
branches **without linking**, so it names the exact word and both targets:

```
tools/venv/bin/python tools/br_targets.py 0x80109F18
  0x80109f54: want ('beq', 2148573172) got ('beq', 2148573136)
```

Use it FIRST on any masked-EXACT draft; only fall back to the rebuild recipe
when it reports 0 diffs and the DOL still differs (that is the `fn_8001DFF4`
reloc-target case, not a layout case).

### NEW MEMBER SOLVED — `fn_80109F18` (244B): m2c `if (x != 0) { body }` wrapper vs the original's early `return`

Masked-EXACT, and `br_targets` flagged ONE word: the `beq` at `+0x3C` went to
`+0xB8` (the tail after the body) where retail goes to `+0xDC` (the epilogue).
The draft (m2c) wrapped the whole body in `if (sp8.unk00 != 0) { ...body... }`,
so ngccc naturally branched PAST the body to the tail; retail's `if
(sp8.unk00 == 0) return;` branches to the epilogue. The two forms emit the
**identical linear instruction stream** — only the displacement differs —
which is why the masked score was 100%.

Swap the wrapper for the early-return and both the block layout and the
target match:

```c
fn_8004B03C(&sp8, ..., QB_LENS_FLARE_CONTAINER, 0);
if (sp8.unk00 == 0) {
    return;                 /* beq +0xDC, not +0xB8 */
}
/* ...body... */
lbl_80302C0C = 0;
if (sp8.unk00 != 0) { fn_8009DFC0(sp8.unk00, &sp8); sp8.unk00 = 0; }
```

With `-fno-gcse` (the pre-existing flag) that is 244B masked-EXACT +
`br_targets` 0 diffs; promoted, DOL byte-identical. Note the two forms are NOT
semantically equivalent — the wrapper version runs the tail when `unk00 == 0` —
so this is a real semantic correction, not a cosmetic reshuffle. **When a
`beq` on a `x != 0` guard overshoots the body, suspect the inverted wrapper.**

### `fn_8010284C` (152B) — a br_targets FALSE POSITIVE, not a layout case

This member was refused for two days by a bogus "1 internal-branch difference".`br_targets.body_of()` read only the draft's `// FLAG:` line and did not
mirror `promote_wip.draft_flags()`, so paired-single drafts whose header names
`__ps_t` but omits `-mps-float` were compiled as **scalar** code and then
diffed against PS retail. `br_targets.py` now applies the same
`__ps_t`/`__builtin_ps_` → `-mps-float` auto-flag as the other tools; with that
its single internal `beq` resolves to retail's `+0x8C` and the draft promotes
byte-identical. Any check that compiles a draft MUST use
`promote_wip.draft_flags()` semantics — a check with different flags is
checking a different program.

### Still parked in this family (br_targets-verified, NOT a layout fix)

- `fn_801D2C58` — the doc-50 linker-relaxation member; `br_targets` shows the
  two `blt`/`beq` resolving to `+0x70` instead of retail's out-of-line `+0x12C`.
  Not source-reachable.
- `fn_8001DFF4` — `br_targets` 0 diffs, every offline gate passes, yet the
  linked DOL differs inside its own range: a raw-addr → symbol RELOCATION
  target problem (doc-51), not a layout one.

### 2026-09-13 — `fn_80207430` (264B): masked-100% from a *flag*, still refused

The parked-draft flag matrix (recipe 49b) found this draft reaches a masked
**100.00% (66/66)** under `-fno-schedule-insns2` — up from an honest 95.45%.
`br_targets` still refuses it, and the reason is instructive:

```
0x802074F8 want ('blt', 0x802074E0)  got ('blt', 0x802074DC)
```

Both builds put the walker's pointer init `addi r9, r29, 0xa60` at `+0xAC`.
Retail treats that instruction as the **loop preheader** (reached once, *after*
the `cmpw r11,r10 / bge` guard) so the back-edge targets the following
`lwz r0,0(r9)` at `+0xB0`. ngccc keeps it at the loop top and the back-edge
lands on it at `+0xAC`. So the layout and every opcode match; only the latch
displacement differs, and — unlike the `fn_800C2284` case above — the source
shape that hoists this pointer is the *draft's own barrier*:

```c
for (i = 0; i < count; i++) {
    wp = a0 + 0xA60;
    __asm__ volatile("" : "+r"(wp));      /* <- makes wp loop-carried */
    t = *(s32 *)wp;
    __asm__ volatile("addi %0,%0,4" : "+r"(wp));
    ...
}
```

The `"+r"(wp)` barrier (and the asm increment) is what the draft needs to hold
`r9`, and exactly what stops LICM from sinking the init into the preheader.
Swept init-hoisted-before-the-loop (95.5% — gcc then emits the `addi` *before*
the guard and the `bge`/branch order flips), init-in-loop without the barrier
(same single diff), plain `wp += 4` (60.6%, frame shrinks by 8), and
`((s32 *)(a0 + 0xA60))[i]` index forms (66.7%).
**`br_targets` is doing its job here: without it this draft would look
promotable twice over.** Keep the FLAG line — it is the best-known body — but
do not re-promote without an allocator/loop-pass lever.
