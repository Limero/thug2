# WIP (non-matching) function drafts

Best-guess C for functions that **cannot be matched yet** (parked). Drafts live
in `src/wip/fn_XXXXXXXX.c` and are **not** registered in `splits.txt` /
`configure.py`, so:

> **Why functions are parked:** see `docs/parkings/` — one self-contained doc
> per distinct root-cause issue (FPR frame quirk, regalloc, store scheduling,
> etc.), indexed in `docs/parkings/README.md`.

- the DOL stays **byte-identical** (drafts are never compiled),
- objdiff progress stays **honest** (no object → no match score — writing a
  C stub that *contains* the original asm would compile to identical bytes
  and FAKE a 100% match, which we deliberately do not do),
- the C is versioned, readable, and ready to activate when a blocker is
  solved (`tools/wip.py activate <addr>`).

## Draft generation (2026-08-08)

Two passes:

1. `tools/gen_wip_drafts.py` wrote a draft for **every** unmatched function:
   best-guess C where a leaf pattern is known, otherwise a stub with the
   original disassembly as comments.
2. `tools/fill_wip_drafts.py` ran **m2c** (decomp.me's decompiler, target
   ppc-mwcc-c) on every stub and post-processed the output into standalone C
   that compiles with ngccc (`?`→s32, `->unkN`→byte casts, indirect calls,
   function prototypes stripped, etc.). Drafts where m2c produced no real
   body (FPR-frame quirks, Paired-Single ops, cross-function branches) stayed
   `stub`.

All drafts are inert: never compiled into the DOL, so byte-identity and
objdiff honesty are preserved. Family breakdown:

| family | count | meaning |
| m2c | 2,421 | real best-guess C from m2c (compile + byte-compare to find matches) |
| hand | 26 | hand-reconstructed / special-cased |
| stub | 15 | m2c produced no real body — disasm documented, TODO |
| c | 4 | hand-reconstructed / special-cased |
| gxtev | 3 | (hand/maintained drafts) |
| ps | 2 | (hand/maintained drafts) |
| gx-chan | 2 | (hand/maintained drafts) |
| gxpixel | 2 | (hand/maintained drafts) |
| mwcc | 1 | (hand/maintained drafts) |
| psc-call | 1 | (hand/maintained drafts) |
| Script | 1 | (hand/maintained drafts) |
| scriptcmd | 1 | (hand/maintained drafts) |
| script | 1 | (hand/maintained drafts) |
| vmx | 1 | (hand/maintained drafts) |
| vfprintf | 1 | (hand/maintained drafts) |
| vfiprintf | 1 | (hand/maintained drafts) |
| pow | 1 | (hand/maintained drafts) |
| (untagged) | 76 | drafts whose header carries no `family=` tag |
| **total** | **2,560** | one draft per still-unmatched function |

**2026-08-21 lib cleanup:** removed **721 drafts + 1,406 registry rows** for
functions fully covered by SDK library objects (`libs/dolphin`, `libs/runtime`
→ `src/os|dvd|gx|db|mtx|base|ar|ai|dsp|vi|pad|si|exi|card|ax|runtime/*.o`,
never matched — ranges derived from the link order, validated against SDK
symbols: 10 contiguous runs in 0x8024+ with **0 straddling functions**).
Boundary SDK functions that live in `obj/auto_01_*` gap objects (e.g.
`GXInit`, `GXSetFog`, `GXSetFogRangeAdj`) are **not** lib-covered and keep
their drafts. Also removed 54 stale registry rows (44 for already-promoted
functions, 10 for lib-covered drafts deleted in earlier commits).

M4.13 status: of the 8,990 m2c drafts, **252 still fail to compile** (list
in `/tmp/fail3.txt`) — the rest compile clean and are swept by
`tools/test_wip_drafts.py` (2 were found byte-exact and promoted in M4.13).

**M4.15–M4.17 status: ZERO compile-FAILs.** The remaining failures were
attacked in three waves:

1. **M4.15 (234 → 187):** new batch rules in `tools/fill_wip_drafts.py` for
   the MEMBER/ARROW family that dominated the real distribution (116 of 187
   were `*(s32 *)(X)->unkN` / `**(s32 *)X` / `*(s32 *)(X)(args)` shapes that
   the existing `fix_paren_field` was mangling). Added `fix_deref_arrow`,
   `fix_called_obj`, the double-star rule, multi-word fn-ptr decls, raised
   the `fix_paren_field` iteration cap 8→200, and made the new scan rules
   run AFTER the field rules (they consume the field rules' output).
2. **M4.16 (187 → 74):** `tools/bucket_fail6.py` (full-stderr bucketing —
   `compile_fn` truncates stderr to 200 chars and hid the real errors) +
   more surgical rules (`*(s32 *)X + var`, `&unkspN` offsets).
3. **M4.17 (74 → 65 → 0):** the remaining tail was genuinely unique.
   `tools/errlines.py` compiles the draft file AS-IS (compiler line numbers
   = file line numbers) and shows the exact erroring source line;
   `tools/repair_tail.py` applies per-address compile-only repairs;
   `tools/fix_tail2.py` holds curated per-address FIXES / FIXES2 / COMPUTED
   tables (paren-balanced full-line replacements verified by compiling).
   All 65 unique one-offs were hand-fixed against the actual disassembly
   (e.g. 0x80237A88's stores rewritten from asm; 0x8008076C's row-index
   arithmetic mirrored from the compilable sibling line).

Final sweep (`tools/sweep3.sh`, 8 parallel slices over all 9,259 drafts):
**0 FAIL**, 1 new EXACT promoted (0x80003464), DOL byte-identical,
progress **2157/11,430 (18.87%)**. `src/wip/` now contains **no draft that
fails to compile** — every non-stub draft is swept every round.

**2026-08-31 — fn_800A248C promoted to EXACT (60B, DOL byte-identical).**
Was parked at 66.7% on the `(x == 0)`-with-masked-value xori fold + sibling
block-layout flip. New recipe (mixed leaf-block forms, no asm, no flags):
A-block `if ((t0 ^ 1) != 0) return 1; return 0;` (non-combinable xor blocks
ngccc's xori fold, still canonicalizes to `cmpwi r0,0; li r3,1; beqlr`),
B-block `r = 1; if (t0 != 0) return r; r = 0; return r;` (the r-variable form
is what pins the wanted `[A][B]` + `bne B` layout when both blocks would
otherwise be identical 5-insn constant returns). Full recipe in the draft
header + AGENTS.md §4p-7. The other 0x800A24C8 comparison-switch sibling
(promoted earlier via recipe-100) is adjacent.

**2026-08-31 — fn_8000978C promoted to EXACT (140B, DOL byte-identical).**
Case-insensitive ASCII string compare (stricmp-style); was parked at 82.4%
because the null-check section emitted `cmpwi r11,0; beq` (then-block placed
last) instead of WANT's `bne`-out layout. Fix: the SHORT-CIRCUIT form
`if (c1 == 0 && c2c == 0) return 0;` emits `bne L1; cmpwi r0,0; bne L2; li
r3,0; blr` with L1 = the c2c != 0 → loop check and L2 = the shared return -1
block — exactly WANT's block order; the two `return 1` sites crossjump into
one shared ret-1 block. Recipe in the draft header.

**2026-08-31 — fn_802349F0 promoted to EXACT (112B, DOL byte-identical).**
ScriptLoadParkFromDisk (pack open + file open + transfer). Formerly parked at
89.3% on the recurring `lis;addi` vs `lis;ori` low-half coin (AGENTS
§M5.16.5): the two slice addresses were bare literals `0x802B0A00/08` (fold
to lis+ori and misplace the `li r6,1` arg); referencing the registered rodata
symbols `lbl_802B0A00`/`lbl_802B0A08` (both string symbols in symbols.txt)
flips ngccc to lis+addi in want's exact slot. All 112 bytes match.

**2026-08-31 — masked-EXACT but NOT promotable (link-level divergers, auto-reverted):**
Four drafts report EXACT on the masked sweep yet every promotion fails link-reverify
with `!!! DOL DIFFERS !!!` (promote_wip registers, links, byte-checks, and safe-reverts;
F320/80178888 promote fine through the same path, so these are genuine link traps):
- **fn_80136CAC** (132B, m2c) — call-after-register-ref with two exit paths; draft itself
  already warned `Do not auto-re-promote`.
- **fn_8022AE98** (172B) / **fn_8022AF44** (188B) — adjacent-sibling dense-conditional
  entry (all intra-function bne/beq/b), masked-EXACT but their register link does not
  land identical; both fail alone too (not an interaction).
- **fn_8025CFB4** (72B, cs) — uses `__cvt_fp2unsigned` which BLs to the unregistered
  `lbl_802B1CD8` → `undefined: 'lbl_802B1CD8'` link error (doc-49 batch caveat restated).
All kept in src/wip/ pending a fix (hand-add `lbl_802B1CD8` symbol, or manual asm for
the branch layout). Leave the drafts INERT.

**2026-08-31 — fn_8000F320 promoted to EXACT (60B, DOL byte-identical).**
Stack top-pointer pop (suggested rename StackTopPop): decrements self->0x110
count, clears self+0xd0[count] to -1, rebuilds self->0xcc top as
`count ? self + count*4 + 0xcc : 0`. Was parked at 93.3% (~1/15 original on
a doc-49/doc-46 regalloc coin). Three levers combined to EXACT:
(1) doc-49 NAMED-pointer store `s32 *stack = self+0xd0; stack[count]=-1;`
emits want's indexed `stwx r10,r11,r0`; (2) count pinned to r9
`__asm__("r9")` fixes the prologue + `lwz r9,0x110` reload;
(3) FINAL: tail build must use the UNSIGNED spelling
`count=(s32)((s32)((unsigned)count<<2)+(s32)self+0xcc)` — the signed
`count*4` forms bind self to add's rB (`add r9,r3,r9`) one commutative-
operand rank off want's `add r9,r9,r3`. No asm in the body beyond the
count pin.

**2026-08-31 — fn_80178888 promoted to EXACT (308B, DOL byte-identical).**
Skater-zone frame-list iterator; was parked at 97.4% on a doc-15 li/mr
scheduler swap (want `li r0,0` before `mr r26,r11`, ngccc emitted them
reversed). Root cause: the parked draft's OWN `__asm__("" : "+r"(sp))`
barrier between the frame stores and `iter = (s32)sp;` — deleting the barrier
makes the scheduler emit the exact WANT order (the copy-prop the barrier was
blocking never occurs once the r26 pin is in place). NO asm left in the body.

**2026-10-23 — fn_80152C00 promoted EXACT (208B, DOL byte-identical); the
walker-copy preheader order is a source shape after all.** The r9 pin's empty
`__asm__` barrier must carry the loaded sentinel AND the node pointer as
**inputs** (`"" : "+r"(walker) : "r"(sentinel), "r"(head)`): with the copy as
the only operand the barrier does not hold the load above the copy, and marking
the load `volatile` does not either. The twin fn_80152CD0 has the same walk and
the same barrier form.
automated scan of 157 wip drafts whose WANT has `crclr cr1eq` before a bl,
testing the unprototype recipe (drop the callee's prototype so ngccc emits the
crclr AND — as in fn_80076F8C — the arg scheduling falls into want's order).
Verdict: fn_80076F8C is the only clean case. All other crclr sites already
keep the callee unprototyped/varargs (fn_8021805C, fn_801695A0, fn_8017F614,
fn_80175F38, memcpy sites per fix_crclr_protos/crclr2 harvests). Removing the
prototype from the remaining prototyped varargs callers (fn_800F4F78
147/205, fn_80191CC0, fn_801F3D30, fn_800D478, fn_800771FC, fn_800723F0)
regresses or is a no-op — their diffs are frame/regalloc/prologue order, not
call-shape. fn_80130250/fn_801302F0 (50%, crclr before bl 0x8012CB60) and
fn_8001B5E4 (memcpy with 2 args — structurally wrong) need full redrafts.

**2026-09-02 — 7 new EXACT drafts matched (all left INERT in src/wip/,
not promotable today):**
- **fn_8002D108** (68B) / **fn_80138038** (100B) — zero-init helpers; fixes
  were compiler store-order recipes (want store sequence is a rotate of
  source order).
- **fn_80070BF0 / fn_80070C34 / fn_80069840 / fn_80069890** (68-80B) —
  guarded subobject-method dispatch twins; the m2c drafts passed `sub` as a
  bogus 2nd arg (`mr r4,r9` shifted every tail insn +1); the calls are
  single-arg.
- **fn_8009A6C0** (80B) — list-unlink helper vs global lbl_803018F0; the
  walker advance must volatile-reload `*p` each iteration to reproduce
  want's `lwz r9,0(r9)` (ngccc CSEs it to `mr` + r11 walker otherwise).
- Parked 2 fresh drafts with notes: **fn_8007AC6C** (14/20, callee-saved
  slot coin-flip arg2->r28/result->r29 unreachable in ngccc) and
  **fn_80058184** (20/21, want's u16 `lhz;rlwinm` clear vs ngccc's andi
  fold — tried volatile/read casts, folds every form).
- **fn_8000F9C4** (144B) — doc-49's indexed `lwzx/stwx` rA↔rB slot coin
  SOLVED: index the named in-loop base with a SOURCE-LEVEL byte biv
  (`k += 4`, `*(void**)(arr + k)`) instead of `arr[i]`, plus
  `// FLAG: -fno-gcse` (without it ngccc turns base+k into a walking `lwzu`
  and PEELS the first iteration, 180B). flagdiff 36/36 (100%). Inert —
  .sdata2 +0x40 promotion blocker applies. Doc-49's suggested recipe-99
  `"+r"(arr)` base pin was tried: 8.3%, dead end. Full recipe in draft
  header + doc-49 §2026-09-02.
- **fn_8000F95C** (104B) — doc-49's last member SOLVED (no flags, flagdiff
  26/26): the push RETURNS the pushed object (`void *` + `return obj;` —
  that's what emits want's `mr r11,r3`; a void signature stores from r3 and
  drops a word), and the count increment must REASSIGN `count++` before the
  field store instead of an inline `count + 1` (inline form hoists the addi
  before the stwx). Both recipes in draft header + doc-49 §2026-09-02. Doc
  49 is now fully closed.

**2026-09-02 — doc-47 CLOSED: all members solved with the doc-49 in-body
base lesson** (loop bases/walkers must be NAMED locals DECLARED INSIDE the
for-body, not pre-loop locals / for-header inits — ngccc's LICM then emits
the init below the entry guard in want's slot). Four members this pass:
- **fn_8000C6A0** already promoted EXACT in src/ by the parallel session
  (its winning body IS the in-body-base form);
- **fn_8000C938** (was 32/37, 5 preheader words) → **EXACT 37/37, no flags**:
  two in-body bases `char *b1 = self+0x60; char z = 0; char *b2 = self+
  0xa0;` — the zero VAR between the base decls orders want's `li r11,0`
  between the two addi's (literal `b1[i]=0` puts it last); plus the tail
  call needs its real extern proto (implicit int ⇒ spurious `crclr cr1eq`,
  152B vs 148B);
- **fn_8000FA70** (pool lookup sibling of F9C4; re-drafted 0% → 13/17
  earlier today, then EXACT with the lesson) → **EXACT 17/17, no flags**:
  affine in-body walker `s32 *p = (s32 *)(self + 8 + 4 * i);`
  strength-reduces into want's walker AND reproduces the guard-into-latch
  rotation that resisted ~25 shapes/flags (for-header `p=self+8; p++` =
  13/17; byte-biv = 5.9%);
- **fn_800394CC** (find-first-float-array-index, was 17/20) → **EXACT 20/20,
  no flags**: loaded-base split — pre-loop temp for the `*(self+0x8)` LOAD
  (want loads it first anyway) + IN-BODY decl of the `+0x508` offset base
  (`f32 *arr = (f32 *)(p0 + 0x508);`); the load itself must NOT be in-body
  (per-iteration reload past the in-loop store).
All five EXACTs in wip are inert on the .sdata2 +0x40 promotion blocker.
Doc 47 moved to docs/parkings/solved/ — full recipe + historical dead ends
inside.

**2026-09-02 — doc-47 lesson follow-up sweep: fn_80032610 EXACT (34/34,
no flags).** Element-clear loop with an in-loop vtable dispatch (array at
self+0x40, count self+0x58) — parked today at 30/34 (was attributed to
"doc-15 scheduling" but it is the doc-47 mechanism: walker init
`addi r31,r29,0x40` above vs below the entry guard). The winning variant is
the ELEMENT-INDEXED in-body base (`for (...; i < count; i++) { s32 *arr =
(s32 *)(arg0 + 0x40); ...arr[i]... }`) — ngccc strength-reduces arr[i] into
want's pointer-walker (r31) while self stays in r29 across the in-loop call.
Notably the FA70-style AFFINE in-body form regresses here to 22/34: with
self live after the loop, ngccc decomposes it as self + offset-walker
(`li r30,0x40; lwzx`) instead of want's pointer-walker, cascading the whole
regalloc. Lesson refinement: when the base's object is live past the loop
(and a call is in the body), prefer the const-base + arr[i] element form
over the affine walker form.

**2026-09-02 — 4 more EXACTs from the NEAR sweep (all no-flags, flagdiff-
verified, left INERT in src/wip/):**
- **fn_800A638C** (ScriptObjectExists, 108B, was 26/27) — `cmpwi r3,0` vs
  `or. r3,r3,r3` zero-test coin: SOLVED via return-if structure — m2c's
  shared-`result` shape (`result = f(...); if (result != 0) ... return
  result != 0;`) makes ngccc emit `or.`; `if (a != 0) { if (b != 0)
  return 1; } return 0;` gives want's bare cmpwi for both tests. → 27/27.
- **fn_80076F8C** (252B, was 60/63) — sp8-call-arg order coin (addi
  r3,r1,8 between the mr r27/r26 saves): SOLVED by calling varargs
  fn_80269F4C UNPROTOTYPED (recipe 87/M8.16 — want has crclr cr1eq before
  the bl, which is what the missing proto emits; the unprototyped-call path
  also changes arg scheduling so the buffer-addr addi lands in want's
  slot). The sibling fn_800147E8 call stays prototyped. → 63/63.
- **fn_80136BE4** (DVD path-open, 200B, was 48/50) — `[cmpwi r0,-1][li
  r3,0][beq]` order: SOLVED by placing the default `ret = 0` AFTER the
  `if (temp_r0 == -1) return 0;` early return (ret-before-if and
  direct-return forms both restructure the block; the r3-pin + ret-later
  form matches). → 50/50.
- **fn_80122450** (script-VM s16 trampoline, 88B, was 18/22) — 4 `extsh`
  diffs: SOLVED by declaring the CALLER's params s32 and casting (s16) at
  the call site — ngccc's ABI model treats incoming s16 params as
  already-extended and elides the extsh; an s16 cast of a wider s32 value
  forces sign-extension. → 22/22.
Re-probed without movement: fn_8009A5B4 (2-word li r3/r5-zero-grouping
coin — all shapes/flags/proto forms converge), fn_800C9808, fn_8009FB20,
fn_80161A00, fn_80161F24, fn_80141B08, fn_80136D30 (documented doc-15
scheduler/allocator coins).

**2026-09-02 — fn_80159E20 EXACT + doc-15 arg-setup family re-probe
verdict:** ScriptSkaterExists SOLVED (32/32, no flags) by the positive-if +
separate-returns recipe (see registry row). Re-probed 8 more members of the
arg-setup order family (the ~2-word `mr r3,rX`/`li`/store-vs-`ori` swap at a
single call site): fn_80156220, fn_801587C8, fn_8015BCB4 (twin fn_8015BB78
EXACT — fresh-load arg0 sites match; only reg-sourced-arg0 sites flip),
fn_8015D6B0, fn_80169D64 (+sibling CE4), fn_80169F04, fn_801819E4,
fn_8015B25C. Unified mechanism: WANT's scheduler interleaves other arg
setup / stores INTO the lis→ori const-materialization gap and hoists
call-args above stores, while ngccc emits the lis→ori pair atomically and
pins args to the call — a scheduler-model gap, not source-reachable. All
resist every shape/flag/proto/pin variant; fn_8015A5C8 re-tested with the
matched-codebase `extern char lbl_80305FF8[]` + `*(void**)&lbl` idiom
(no-op, 98.2% — r3-vs-r11 load-target coin stands). No new matches from
this family; parked notes updated.

**2026-09-02 — fn_80130E88 EXACT via guard + do-while peel:** object-id
scan loop (0x80130E88, was 34/38) — the m2c while-with-pre-loop-inits form
put the loop-carried zero inits `[li r8,0; li r10,0]` in the straight-line
preheader BEFORE the entry guard (cmpw r11,r0; bge), want keeps them AFTER
it (first insns of the loop-entry block — MW sinks them below the guard
since only the body uses them). SOLVED by peeling: `if (i < N) { r8 = 0;
r10 = 0; do { body; i++; r10 += 0x2C; } while (i < N); }` (38/38, no
flags). Caution: moving `r10 = 0` INSIDE the plain while body resets the
running stride counter per iteration (semantics change — 17/35); the
inits must sit between the guard and the rotated body. Same placement
family as fn_80136BE4 (default-after-guard) extended to loop-carried
state. Registry row + recipe header updated.

**2026-09-02 — promotion blocker (all new ngccc objects):** every promote
attempt today (single fn, pairs, 7-fn batch) links the DOL with `.sdata2`
shifted exactly **+0x40** (built `_SDA2_BASE_` 0x803D2F80 -> 0x803D2FC0), so
`patch_dol.py`'s BUILT_R2 assert fails and `promote_wip.py` auto-reverts
(DOL stays byte-identical, drafts stay in src/wip/). Prior-session diagnosis:
mwld GC/alignment of the .text tail (post-0x8028C860, GXTransform `.sdata2`
unit + OdemuExi2/DebuggerDriver.o which carries ~0x9AC of dead text but only
~0x280 linked) keeps +0x40 more when ANY new compiled object joins the link
— pre-existing state, not these drafts (0x8000F320/0x80178888 promoted fine
on 08-31 through the same path). Fix would be tail-region surgery (trim/
re-split the borderline unit) so GC stops flipping; not attempted.

**2026-09-12 — random-batch sweep (no-park-note drafts): 2 EXACT promotions
(DOL byte-identical `ff6faeb0…`) + 5 parked with notes.**
- **fn_8005D9F0 (124B) EXACT, promoted** — hash-table ctor (count = 1<<arg1;
  alloc count*0xC; call fn_8005D814 per 0xC slot; set arg0->4/0x8/0x14).
  Recipe: the loop counter `count`/`i` must be **u32** — s32 makes GCC
  synthesize an extra `mr r0,r31` before the `i-- != 0` post-decrement test
  (58% -> 93.5%); and the tail store order is arg0->4, arg0->8, arg0->0x14
  (that spelling produces want's [4][0x14][mr r3][8] interleave).
- **fn_80125480 (100B) EXACT, promoted** — type-0xD node search. The m2c
  goto-CFG lost the block layout; the NESTED-IF shape (`if (p != NULL) { if
  (p->unk2 == 0xD) { for(;;) … } } return p;`) reproduces want's two branches
  into the shared `mr r3,r31` return block; the type byte is a u8 (lbz, not
  the m2c 4-byte read).
- Parked (best body + detailed note in each draft): **fn_80042DE8 93.8%**
  (store-order vs mgr-load rotate, 6 permutations x spellings x flags), **
  fn_800F1448 85.0%** (arg1/arg2 callee-saved home swap r29/r28), **
  fn_800448D0 75.0%** (buffer base r4-vs-r9 allocator coin after a 0x5C-strip;
  byte-indexed buffer accesses), **fn_801C2088 71.4%** (arg0/arg1 home swap +
  lis/mr interleave; needed the f32 field at 0x2C + pad8 FPR dummy), **
  fn_801297E4 65.1%** (f64 threshold compare, pad8 dummy, mr-home order +
  shared-epilogue REL14 layout).

**2026-09-12 — ScriptDoScreenElementMorph (fn_8004CC88, 136B) EXACT,
promoted (DOL byte-identical `ff6faeb0…`).** Screen-element family (promoted
fn_8004CD10/fn_8004D4CC recipe) with two NEW calibrations:
- **Method-record offset field is s16, per-record.** Want loads the dispatch
  offset `lha r3,0x50(r9)` (fn_80070838's twin loads `lha 0x38(r9)`, family
  caller fn_800B6634 loads `lwz`). The record must be typed via a LOCAL
  `typedef struct { char pad[0x50]; s16 unk0x50; s32 fn; }` — the shared
  Unk_C7387A53 fields at those offsets are s32 and emit lwz. These dispatch
  records have mixed-width fields per record; decode each site's load width
  from want before typing.
- **Call-site-dereference of a data-symbol arg.** The QB handle arg must be
  spelled `fn_8004B0E8(&sp8.a, *(s32 *)lbl_80300434, …)` IN the call — a
  named local `s32 hid = *(s32 *)lbl_80300434;` changes scheduling: want's
  `lis r9; lwz r4,0x434(r9)` moves above `mr r30,r3` (the frame arg becomes
  r4 via a stale-home reload path and every word from +0x10 shifts). Same
  lesson family as doc-51 (symbols not literals) but for ARG SPELLING:
  data-symbol args are rematerialized at the call site only when spelled
  there.
- Draft-header gotcha (3rd occurrence): a `// extra_cflags:` header line
  whose prose contains `-O2` gets its tokens harvested as compile flags and
  breaks the sweep — keep flag tokens off prose lines.
- Parked the two siblings probed in the same pass: **fn_80070838 92.1%**
  (same s16-record fix + guard layout + `-fno-schedule-insns`; residual =
  want sinks the 2nd call's `mr r3,r31` below the li r4/r6 arg setups —
  same wall as fn_80156CB0) and **fn_8000E978 58.1%** (count-down latch
  `addic.` vs want's split cmpwi/addi — fn_8000E48C wall confirmed) and
  **fn_801322F8 45.5%** (two-base stwx walker exists but zero/count regs
  color to a different permutation in every init ordering).

**2026-09-14 — random-batch sweep (no-park-note drafts): 17 EXACT promotions
(DOL byte-identical `ff6faeb0…`; PROGRESS 8002 → 8019, 69.773%) + 2 parks.**
New reusable recipe found — **the QB helper arity bug** (worth 10+ fns in the
0x8011xxxx Script zone): m2c drafts call the QB readers as 3-arg
`fn(ctx_less, KEY, &out)` and/or drop the callee prototype entirely, which
costs BOTH the leading ctx register and a spurious `crclr cr1eq`.
Fix = declare the real 4-arg proto `s32 fn_80128228|801284EC|801285A4|801286D0|
80128BF0|80128C80(Unk_2EF06E12 *, s32, s32 *, s32)` AND pass the incoming
`arg0` as the first argument (`fn_Xxx(arg0, KEY, &sp8, 0)`) — several of these
Script commands were `void` in the draft but actually take the ctx as param 1.
Promoted by this recipe: **fn_801159C0, fn_80117470, fn_80234F2C, fn_80118088,
fn_80118184, fn_801188D8, fn_80118934**. Also promoted: **fn_8013AC98,
fn_80131C94, fn_800F4D50, fn_801853A8, fn_801F5C18, fn_80190840** (store
widths + missing prototypes), **fn_80117054** (if/else arms for the
`li r3,1 / bne` shared-tail shape), **fn_80118C54** (raw `0x802FFE98` literal
→ `extern char lbl_802FFE98[]`; doc-51) and **fn_80117C18** (u32 switch +
PER-CASE duplicated stores `lbl_803032D8 = N;` so ngccc crossjumps the `stw`
into a shared block and keeps `li r0,N` per case; the single-store form homes
the value in a callee-saved reg and pre-saves r30).
Parked with notes: **fn_801174B4** (82.9% — arity FIXED this session, residual
is the `&sp8` scratch pointer's r30/r31 color coin; the r30 pin fixes the color
but hoists the `addi` above the first `bl`) and **fn_802347D0** (67.6 → 73.0% —
the four QB broadcasts are BYTE reads (lbz) at o0/2/3 of the s32 at r1+8 and o1
of the u16 at r1+0xC, not m2c's `*(s32 *)(&sp8+k)`; residual = r0/r9 role swap
+ the arg1->0x18 load hoisted above the `sth`).

**2026-09-15 — random sweep: 3 EXACT promotions (fn_800AF9C4 204B,
fn_800DDDC0 64B, fn_80003F54 164B; all DOL byte-identical via promote_wip)
+ 1 semantically-corrected park.**
- **fn_800AF9C4 EXACT + PROMOTED** — was 57.4% with THREE stacked m2c
  defects, all semantic, none scheduling: (1) mixed-width record — fields
  0x54/0x58/0x5C are f32 (want lfs) but shared Unk_C8FEE62D types them s32
  (fn_8004CC88 lesson; fixed with a local per-record typedef); (2) the float
  callees fn_80059380(f32,f32)/fn_80059394(s32,f32,f32) were undeclared →
  crclr + integer-ABI args; (3) NEW arity twist — m2c ARG-INVERSION: the call
  is `fn_8012701C(arg0->unk0x50, 3)` (arg1 = the LOADED FIELD, not arg0);
  want loads 0x50 into r3 before the 0x14 store and the same register feeds
  both the cmpwi and the bl. 57.4 → 96.1 → 100%.
- **fn_800DDDC0 EXACT + PROMOTED** — was 75.0% under `-fno-schedule-insns
  -ffixed-r9`; root cause was NOT scheduling: m2c invented a PHANTOM SECOND
  ARG on the fn-ptr dispatch (`((fn)temp_r9->unk0x24)(obj+off, temp_r9)`).
  Want never writes r4 — the dispatch takes ONE argument (`lwz r9,8(r11);
  lha r9,0x20(r9); add r3,r11,r9; lwz r0,0x24(r9); mtlr; blr`). The bogus
  arg colored the record r4 and forced the -ffixed-r9 hack; with the
  single-arg call the natural coloring is EXACT, flagless (the parked flags
  are dropped). Same m2c phantom-arg family as the fn_8004B0E8 6th-arg and
  fn_800AFA90 lessons.
- **fn_80003F54 EXACT + PROMOTED** — was 75.6% under `-fno-schedule-insns`
  with ALL 10 diff words being ONE frame-size delta (want frame -0x30 vs got
  -0x20; every mismatch a displacement shifted 0x10). Fix: two
  `volatile double` locals add exactly 0x10 of frame headroom and every
  displacement snaps into place — the previously documented doc-15 FPR-color
  wall (want keeps the const in f13, fneg's -sin into f0) resolved
  automatically once the frame matched. Two-dummy placement is order-
  insensitive (both spellings compile identical). 2D rotation-matrix setup
  (sinf/cosf, rodata consts lbl_8028FC70/74). Suggested rename:
  Fn_SetRot2DMatrix.
- **fn_80105FE8 honestly re-parked at 72.2% (26/36, size-exact 144B, no
  flags)** with a SEMANTIC REDRAFT: the old m2c goto-CFG body (69.4%) walked
  the find loop with a pointer advanced by +8 per BYTE index (+32B/element,
  want is +8B) and hoisted the count. Correct decode: find loop re-reads
  unk0xFC4 per iteration, key load is an in-body AFFINE base (arg0+0x20+i*8,
  doc-47 form), hit path is a guarded do-while shift-down copying
  dst[+0x20/+0x24]→dst[+0x18/+0x1C] with j++ between load and store, and the
  tail decrements go through TWO locals. Residual = one coloring cluster:
  want reuses the find-index register r11 as the copy-loop dst walker and
  colors j=r8/a=r9/b=r10; ngccc keeps r11 for i and shifts every copy color
  down one. Resisted: dst as s32*/char*/struct-row, fn-scope vs block-scope
  temps, load-order swap, -fno-schedule-insns{,2} (f2 regresses globally to
  1/36), -O1 (5.6%).
- **fn_80112A94 (ScriptLoadSound) semantically redrafted 81.1 → 96.8%**
  (91/94, size-exact, no flags; parked). Three decode fixes: (1) the sound
  mode flags are ELSE-IF with |= (bit-OR — modes coexist; want's `beq +b`
  skips the second fn_801289E4 probe), not m2c's overwriting assignment
  chain; (2) NEW arity-family lesson — m2c REGROUPED alternating int/f32
  params: fn_8011A2AC is really (void*, void*, s32 mode, f32 vol, s32 type,
  f32 pitch, s32 bank, f32 dropoff) per matched caller fn_8010C86C, so GPRs
  r3..r7 and f1/f2/f3 follow source order (want's lfs offsets f1<-vol,
  f2<-pitch, f3<-dropoff pin the mapping); (3) lbl_80302C34 is a pointer
  VARIABLE (lwz), not char[]. Residual 3 words = doc-15 arg-class
  interleave (r7 hoisted above the GPR mr, fpr loads delayed past it).
- Probed + confirmed-existing parks (no movement): fn_8001B8D0 (stale note
  partially corrected — under -O1 the FBCC calls NOW match; the true residual
  is 12 words of r3-last vs r3-first arg-setup order on ONE E248 site +
  EEE0; every local-variable spelling canonicalizes identically),
  fn_801A2584, fn_8003A9E4, fn_80044EA4, fn_800703D8, fn_801D1210,
  fn_8004C7B0 (+2026-09-15 probe: 8-aligned dummy always wins r1+8 — GCC
  stack-bucket order, not decl order), fn_8021F120, fn_80223FA0,
  fn_8020CAA4, fn_80161420, fn_8020D2E4, fn_80172A90, fn_80054950,
  fn_801A9388, fn_801744B8, fn_800B7D94, fn_8004195C, fn_800D512C.
- Late-session re-verifications (notes current or corrected, no movement):
  fn_8021DAD4 (97.6%, 8-word preheader pair-swap), fn_80245410 (96.7% —
  STALE "EXACT under -mps-float" claim corrected: draft_flags() auto-appends
  the flag for __ps_t bodies, so 96.7% IS the flagged score; walker-web
  spellings all converge), fn_800D5078 (divisor-load hoist coin),
  fn_8018CC18 (97.3%; source-order w/wp swap REGRESSES to 90.4% — GCC
  schedules addi r4 first regardless), fn_800CC358 (doc-15 coin, all branchy
  forms previously measured), fn_80191DBC, fn_800C3C00, fn_8023E9D0,
  fn_80220CC8, fn_8022082C (note refreshed: prologue lis-hoist + msg-store
  interleave, all spellings converge 80.4%), fn_8021FAB4, fn_8021EB8C
  (retry hint CLOSED: peel/merged-predicate spellings 50-54%, body inflates),
  fn_8021D184, fn_800C70A4, fn_800D4E34, fn_8001094C, fn_8004A6A8,
  fn_801A9B1C.
- Swept the float-undeclared-callee defect class (100 drafts calling a
  float-signature promoted fn with no declaration): batch proto-insert
  mostly REVERTS (the m2c bodies also pass int-typed args — the struct
  fields must be retyped per-draft first, fn_800AF9C4 lesson); only
  fn_800B6694 kept a one-proto improvement.

**2026-09-14 (session 2) — continued random sweep: 3 more EXACT promotions
(DOL byte-identical `ff6faeb0…`; PROGRESS 8019 → 8033 after report regen) +
2 new parks + 3 drafts rewritten with semantic fixes.**
Promoted: **fn_8003AB44** (dropped the `var_r3` local → direct `return` from
both arms keeps the result in r3; with a local ngccc homes it in r30 and
pre-saves r30+r31 via stmw), **fn_800A205C** (hoist the loop key
`s32 key = arg1->unk0x4` out of the loop — want loads it once into r7 — and
write `while (i < (u32)arg0->unk0x50)` so the count is RE-READ at the loop
bottom; model the 8-byte record stride at arg0+0x54 and the i*4 global stride
as explicit offsets), **fn_8021F840** (replace the duplicated
`(x==1)==0?0:1` ternary with ONE `s32 v = 1; if (arg0->unk0x48 == 1) v = 0;`,
hoist the `*(s32 *)&lbl_80303148` deref into a local loaded up front, and add
the callee proto to kill `crclr cr1eq`).
New reusable recipes:
- **toggle-flag local** (fn_8021F840): a `0/1` flag that is both stored and
  branched on must be a single local; writing the ternary twice makes ngccc
  compute it arithmetically (`xori/subfic/adde`) instead of the
  `li 1 / cmpwi / bne / li 0` branch form want uses.
- **hoist-loop-invariant-global** (fn_800A205C): when want holds a loaded
  field in a callee-volatile reg across the loop, the source must assign it to
  a local BEFORE the loop; re-reading it in the condition pins it to a
  callee-saved reg + adds the count reload at the wrong place.
- **vtable-dispatch with s16 offset** (fn_80172E64, 41.4 → 71.4%): the real
  signature is `(unused_r3, obj_r4, flag_r5)` — an m2c `(arg1, arg2, arg0)`
  order means the object is wrongly read from r3. The dispatch offset is
  `s16` (lha) and `-fno-schedule-insns` is REQUIRED (default -O2 reorders to
  32%). Residual is the `lwz r9,vt; lha r3,off(r9); lwz r0,fn(r9); mtlr r0`
  color (want r9/r0, ngccc r4/r9).
Rewritten with semantic fixes (parked): **fn_80129A90** (`fn_8012CBA0` takes
an f32 — want emits `lfs f1,4(r31)`; WANT's prologue carries one extra `mr`
copy vs ngccc → 124B vs 104B; the old 51.9% body read the fields as ints),
**fn_8003FED0** (best `while (p->unk0x70 != NULL)` + inline null check at
-O1/-Os = 53.8%; want walks the list in r3, ngccc colors r9 + a spurious
`mr r9,r0`), **fn_8006FA50** (byte stores + ascending order = 68.8%; want
materializes 0x66 first and keeps the [0] store on the `0x6dd8(r11)` lis form
— constant-slot scheduling coin), **fn_8011984C** (64.5 → 67.7% AND
semantically corrected: the base is `lbl_80388C18` + a SEPARATE `addi 0xbf0`
(keep the symbol in a local or ngccc folds the addi away), a
`for (i = 0x80; i != 0; i--)` bdnz loop with -0x18 stride (NOT unrolled), and
the tail stores in the order `lbl_80302C44 = 0;` then
`lbl_80302C3C = lbl_8029D4E4;`).

**2026-09-16 — random-batch sweep (12 no-park-note drafts): 8 EXACT
promotions (DOL byte-identical `ff6faeb0…`) + 2 parks with notes + 4
assessed/parked.**
Promoted (**all DOL-verified byte-identical**): **fn_800B1168** (108B),
**fn_80069EB8** (100B), **fn_800B08A4** (104B, PS), **fn_80078F44** (184B),
**fn_800169FC** (140B), **fn_8000B23C** (268B).  (fn_8009B5F4 184B and
fn_801224A8 64B are the two m2c drafts that were already byte-exact and were
promoted at the start of the session — they had been left inert.)
Landscape shortcut used for the pick: a 16-way Pool over all 1,686 no-park
drafts (`test_wip_drafts.test_one`, per-draft FLAG lines + the issue-01 FPR
dummy + the `__ps_t` -> `-mps-float` rule) scores the whole set in ~27 s.
New reusable recipes:
- **trailing-phantom-arg (2nd flavour)** — fn_80069EB8: m2c appended a
  THIRD argument to the vtable dispatch, which forced `mr r10, r4` in the
  prologue to keep arg1 "live" for the call.  want writes only r3 and `blrl`s
  (r4 still holds arg1 but is never re-set).  Dropping the phantom arg removes
  the copy and the whole body falls into place (15.4% -> 100%).  Same family
  as fn_800DDDC0 / fn_8004B0E8, but the tell here is the dead `mr` of an
  incoming ARG register rather than a bogus arg setup.
- **callee-return-as-pointer (PS)** — fn_800B08A4: the psq_l base is r3 AFTER
  the `bl`, i.e. the helper RETURNS the block to copy.  Declaring it `void`
  and copying from arg1 scores 11.1%; `__ps_t *fn_80057E2C(__ps_t *)` is
  byte-exact.  Also: 4 consecutive `__ps_t` must be a struct member
  (`P4 pair`) for disp-form psq_st.  (m2c emitted bare `0;` for all four
  copies — capstone without PS decoding sees them as data.)
- **`0x802B1D05` is `_ctype_` + 1** — fn_8000B23C: the case table is the
  ALREADY-REGISTERED `_ctype_` (symbols.txt 0x802B1D04, size 0x101) offset by
  one, i.e. classic `_ctype_[(c) + 1]`.  A fresh `lbl_802B1D05` is undefined
  at link time and a raw literal makes ngccc emit `lis+ori` (11.9%, doc-51).
  And the lbzx OPERAND ORDER is source-visible: `_ctype_[c + 1]` gives
  `lbzx r9, table, c` (97.0%, 2 words off); spelling the address with the
  character first — `*(u8 *)(c + (s32)(_ctype_ + 1))` — gives want's
  `lbzx r9, r11, r28`.  The RTL `plus` operand order is a real lever.
- **s32 char accumulator** — fn_8000B23C: `c` must be s32, not s8.  want
  `extsb r11, r0` once and then a bare `addi r11, r11, 0x20`; an s8 `c`
  re-extends after the `+=` (extra extsb, 29%).
- **counter-intuitive source order** — fn_80078F44: want loads `7(r11)` (r29)
  then `6(r11)` (r30).  Writing the u16 assignments [7]-then-[6] emits them
  [6]-first (80.4%); the [6]-first source order emits want's [7]-first
  sequence (100%).  Also: the four shift results must be `u16` (want masks
  every shift with `clrlwi`), the shift COUNTS are bytes (`lbz`, not `lwz`),
  the vtable `fn` field needs a real prototype (`s32 (*fn)(void *)` — an
  old-style `()` emits a spurious `crclr cr1eq` and costs the frame), and the
  arg1 shifts must be computed BEFORE the second dispatch call.
- **per-site type widths vs the shared Unk_* structs** — fn_800169FC:
  m2c typed two 0xC-byte sub-objects as the s32-only Unk_2EF06E12, so six
  `stfs` became `stw` + a stray `fctiwz`.  A local `P3 { f32 a,b,c; }` plus
  REAL f32 externs (lbl_80290BEC / lbl_80290BF0 — both registered) and the
  source store order a,b,c (an a,c,b source 4/8-swaps, 94.3%) makes it
  byte-exact.  Same lesson as fn_8004CC88 / fn_800AF9C4.
Parked with notes (bodies kept as the current best):
- **fn_800ABB34** 92.5% (was 63.7%) — QB_X/Y/Z scale reader; fixed the sp8
  pointer out-param, the 4-arg QB helper arity, the `if (spC == 0)` polarity
  and the `*(f32 *)lbl[]` pointer-form constants (real `extern f32` needed, or
  ngccc materializes the address instead of lis+displacement).  Residual is a
  doc-15 scheduler coin (want issues `stfs w` + `lfs scale` above the first
  `fdivs`; ngccc hoists the load+divide above the store).  All 24 store
  permutations + quotient locals + `-O1/-Os/-O3/-fno-schedule-insns{,2}`
  tried; source order does not reach the scheduler here.
- **fn_8004567C** 76.2% — one dead `mr r0, r4` (want stores through r0; ngccc
  stores r4 directly).  5 spellings incl. volatile/named-temp/char-offset all
  byte-identical; 2 restructurings regress.  Dead-copy class.
- **fn_80176FA8** (300B, 12%), **fn_801D33F4** (2064B, 0.8%), **fn_8001CC70**
  (572B, 8.8%), **fn_80030290** (752B, 14.3%) — first two are m2c-corrupt
  drafts with PS ops (20 / 42) + FPR frames (need doc-06 + issue-01 redrafts);
  last two are source-quality husks (file-scope `static` locals, raw address
  literals, wrong field widths, pool-float literals) needing from-disasm
  redrafts.  Full per-function defect lists are in the draft headers.
False EXACTs identified (NOT promotable — already covered): **fn_8028D494 /
fn_8028D498 / fn_8028DF14 / 18 / 1C / 24 / 2C / 34 / 38** are the odemuexi2
`DBClose`/`DBOpen`/`Vtable0x803089D0` lib units (`main/odemuexi2/*` in
report.json, built from `libs/odemuexi2/src`).  Their empty-function drafts
score 100% on every masked sweep (an empty body IS `blr`) but registering
them as `src/fn_*.c` aborts dtk with "Split … overlaps with previous split".
Park notes added; these 9 should be dropped by the next lib-cleanup pass.

Draft workflow: `tools/test_wip_drafts.py` (optionally `--slice i/m`) compiles
every non-stub draft with the real ngccc command, relocation-masked byte-
compares vs the DOL, and reports **EXACT / NEAR / DIFF / FAIL**; byte-exact
drafts are promoted into the build with `tools/promote_wip.py <addrs>`.

Regenerate stubs with `tools/venv/bin/python tools/gen_wip_drafts.py` and
re-fill with `tools/venv/bin/python tools/fill_wip_drafts.py` (both
idempotent).

**2026-09-09 — screen-element Script pair: 2 EXACT promotions (DOL
byte-identical `ff6faeb0…`; PROGRESS 7618 → 7637 incl. report catch-up).**
Random-batch pick of no-park-note drafts; both are QB_ID lookup + delete
members of the fn_8004B0E8/fn_8009DFC0 screen-element family:
- **ScriptScreenElementExists (fn_8004D4CC, 100B) EXACT, promoted** — the
  m2c draft had m2c's phantom 6th call arg (`0x80290000` rodata-base
  garbage) on fn_8004B0E8 and no prototype (unprototyped call ⇒ crclr +
  arg shuffle). Winning shape: the handle slot is a 16-BYTE struct local
  `struct { s32 a,b,c,d; } sp8` (want frame 0x18 = 8 + 16 locals; plain
  `s32 sp8` gives 0x10), EARLY-RETURN form (`if (sp8.a == 0) return 0;` —
  puts want's shared return-0 block after the ret-1 body), and the &handle
  call-arg must come from a LOCAL `s32 *h = &sp8.a;` assigned INSIDE the
  taken branch. Requires `// FLAG: -fno-expensive-optimizations`: GCC's
  expensive-optimizations pass is what CSEs `&sp8.a` across the two call
  sites into a callee-saved reg (frame shifts 0x18→0x10, every arg reg
  moves). `-fno-gcse` alone does NOT cover it.
- **ScriptSetScreenElementLock (fn_8004CD10, 156B) EXACT, promoted** —
  same recipe plus the doc-36 mirror-direction calibration: with the
  two-call if/else diamond, want computes `addi r4,r1,8` (the &handle for
  the delete call) ABOVE the `lwz;cmpwi;beq` null guard — the C must
  assign `h = &sp8.a;` BETWEEN the if/else and the guard (unconditional
  address birth in source), and then plain -O2 works (no flag: the flag
  disables crossjumping, killing want's shared `li r3,1` tail).
  Both drafts had parked notes describing the WRONG mechanism ("register
  shape coin-flip, needs an idiom that keeps the address un-CSE'd" — the
  fix was the exact opposite: a named local `h` the CSE can home).
- Promotion gotcha (recurring): both are `scope:global` in symbols.txt
  (the .rodata script-command registry references the names) — the first
  promote failed with `undefined: ScriptSetScreenElementLock` until the
  drafts defined the Script* names instead of `fn_8004CD10/8004D4CC`.
- **doc-36 mirror calibration recorded** (see
  `docs/parkings/36-enumerator-fresh-addi-vs-mr.md`): want's
  rematerialize-vs-home choice tracks whether the SOURCE computes the
  address once (unconditional named local) vs per-site; GCC matches that
  as long as expensive-optimizations doesn't invent a second homing.

**2026-09-09 (cont. 2) — random batch: 3 more EXACT promotions (DOL
byte-identical `ff6faeb0…`; PROGRESS 7640 → 7644, 66.510%):**
- **fn_80009EBC (168B) EXACT, promoted** — sorted-list insert with
  `Unk_2EF06E12`-typed node pointers. Recipe: the walk is an UNROTATED
  `for (;;)` with a goto-CFG (`r11 = r9; if (v == -1) r11 = NULL; if
  (r11 == NULL) break;` then the `(s32)r11->unk0x8 <= key` insert test)
  — want's block order (walk block, insert-block placed after, then the
  r8-fallthrough path) falls out of that spelling; naming the r8/r9/r10/r11
  pointer temps explicitly (not collapsing them) keeps want's exact
  rematerialization of `arg0+8`.
- **fn_80127A18 (148B) EXACT, promoted** — node builder: allocates a
  12-byte node (fn_8009F4C4(0x10) / fn_801252BC()), stores the bitfield
  `type:5` at bits 9-15 of the header (rlwimi merge), chains a 12-byte
  payload struct (fn_80128EF4(0xC) / fn_80125000()), stores two f32s.
  Recipe: (1) bitfield member at `s32 pad:9; s32 type:7;` — a plain
  `hdr |= 5 << 9` spelling does NOT produce the rlwimi merge. (2) TWO
  volatile f64 dummies (`_dummy`, `_dummy2`) are required to reproduce
  want's 16 bytes of extra frame (matches the fn_80006350 convention —
  the FPR-spill shadow). (3) Callees fn_801252BC/fn_80125000 stay
  UNPROTOTYPED (no-arg decl) — prototyping them makes GCC set up r3
  junk before the calls that want never emits. (4) The second f32 store
  goes through `((Node2S *)node->unk8)->f8` (re-load node->unk8), not a
  cached node2 pointer — matches want's re-load.
- **fn_80184C50 (104B) EXACT, promoted** — enumerator loop (sibling of
  parked fn_80184BE8). Recipe: the function is VOID — the m2c draft's
  `return arg0 + 4` was a decompiler artifact (the exit path's r3 just
  carries the last B4C0 call's result). Spelling: plain unrotated `while
  (sp8 < fn_80184168(arg0))` with `fn_8018D108(fn_8018B4C0((char
  *)arg0 + 4, &sp8, &spC)); sp8++;` — the single `addi r3,r31,4` in
  want's condition block is purely the B4C0 first argument (CSE'd), NOT
  a return value; the earlier 108-vs-104B delta was the spurious exit
  `addi r3`. All the doc-36 mirror analysis about "fresh addi vs mr"
  resolves to this: there is only ONE arg birth and it serves the call.
- **fn_80131E50 PARKED (75%, 5 words)** — r30/r31 arg-web color flip
  (want r30=arg0/r31=arg1; ngccc insists on the reverse). Frozen after
  ~25 variants: every proto typing, extern-s32 vs extern-char[] lbl
  spelling (the extern-s32 ha/l form DID fix the addressing — cf.
  fn_80233394), local copies, early-return, reversed cond, volatile,
  unprototyped callees, 5 flag levers — all identical 15/20. Full
  analysis in the draft header. The remaining 5 words are 2 data words
  + 3 colored mr/lwz words; words 11/13 are link-time rels.
- **fn_80091CF8 PARKED (55%, size exact)** — compare-of-two-0x58-arrays
  with write-back guards; want is a LEAF (no mflr, saves only r31) with
  11 webs (sumA spills to r31) and IN-LOOP remat of the sum bases
  (`addi r10,r3,0x58` each iteration) + reborn guard bases, while ngccc
  PRE-hoists the bases out of the loop with a copy, shifting every
  color. Full want decode + frozen-lever list in the draft header.
  Caller fn_80091D98 passes it as a callback (void-typed), so only the
  machine shape matters.

**2026-09-09 (cont.) — random batch: 3 more EXACT promotions (DOL
byte-identical `ff6faeb0…`; PROGRESS 7637 → 7640):**
- **fn_800AA9DC (44B) EXACT, promoted** — 4-entry static-table getter;
  same `extern s32[]` element-indexed spelling lesson as promoted sibling
  fn_800AAA08 (indexed extern array, not a pointer deref).
- **fn_8012653C (228B) EXACT, promoted** — hex-record parser feeding a
  2-arg callback. Recipe: (1) return type is VOID — want has no epilogue
  `li r3,0`; the callback's r3 flows through (ngccc materializes 0 on
  fall-off for non-void; that was the last 2-word diff). (2) The callback
  takes TWO args, arg2(v, buf): accumulated hex value + line (a 1-arg
  spelling forces an extra `mr r3` want never emits). (3) `c` is s32
  (NOT s8): one extsb at the load `c = (s8)*p++`, branches rewrite c in
  place — an s8 variable re-extsbs after every assignment. (4) `char
  buf[0x100]` is scoped INSIDE the while body: the back edge re-runs the
  NUL-init (`li r11,0` inside the loop, not hoisted). (5) Digit decode:
  positive else-if chain on (u32)(c-0x30)/(c-0x61)/(c-0x41). (6) Line
  copy: pre-increment do-while (`c2 = *++p`), not post-inc.
- **fn_80138334 (204B) EXACT, promoted** — RLE decoder with capacity
  check (caller fn_8013A398 passes the s32* in/out). Recipe: (1) cmd is
  u8 (NOT s32) — the `n <= cmd` compare must stay cmplw; an s32 cmd
  folds it into signed cmpw + range fold. (2) Arms SWAPPED vs the decomp
  order: `if ((cmd & 0x80) == 0) { literal copy } else { run copy }`
  keeps the literal arm inline (retail layout; decomp's arm order
  inlines the run arm instead). (3) In the literal arm, `out++` comes
  BEFORE the store statement — the scheduler then orders stb before
  src++ (want's order); out++ after the store hoists src++ above the
  stb instead (stuck at 49/51). (4) Run arm: u8 n vs u32 run keeps
  `n < run` unsigned (cmplw); `*dst++ = *src` with no post-inc and
  trailing src++/len--.

**2026-09-07 (cont. 14) — random-batch sweep cont.: 1 more EXACT promotion
(DOL byte-identical `ff6faeb0…`), 1 honest redraft parked:**
- **fn_8002B920 (316B) EXACT, promoted** — float-range checker on
  `(f32)*(s32 *)arg0` (0x43300000/xoris + rodata-bias lfd conversion; the
  m2c draft was a `li r3,0; blr` stub). Winning shape after ~8 A/B rounds:
  NESTED IFS with a result VARIABLE (`result = 0; v = ...; if (v >= farg0)
  { if (v <= farg1) result = 1; } return result;`) — this is what emits
  want's [fcmpu][cror continue-mask][bns bail-to-shared-epilogue] pairs and
  the single shared `li r3,1`; early-return spellings emit per-path fail
  blocks (regress to 42%) and flat `&&` chains get crossjumped away (28%).
  Two calibrations recorded: the outer dispatcher must be spelled
  `if (arg3 != 0)` (want emits `beq` to the arg3==0 block laid out LATER in
  .text — `if (arg3 == 0)` gives `bne` and inverts the layout), and the
  outer range test is always against farg0 with the inner against farg1
  regardless of ascending/descending. Semantics: arg3!=0 → inclusive
  [min,max]; arg3==0 → ascending [lo,hi) / descending (hi,lo].
- **fn_80092DD4 honestly re-parked at 7.7%** — m2c body was corrupted
  (`0;` noise, whole plane scan dropped). Fully redrafted from want: scans
  the lbl_803792E0 record array (0x60-byte records: 5 float4 planes + s32
  counter at record+0x50, record count lbl_803017F4, counter slot indexed
  lbl_803017F0<<2); 5-iteration do-while (mtctr/bdnz) tests
  dot(p,x,y,z)-p[3] >= -arg0[3] via fcmpu + cror cr0un,cr0eq,cr0gt + bso;
  all 5 pass → *(counter) += arg1, return 1. Instruction sequence is now
  1:1 with want (204B, same block layout) — the residual is pure GPR
  coloring (want count→r8 with mr r6,r8 copy + r8 reused as the 0x60
  walker, E0 base→r7, ctr-origin r9=r7+0x50, counter→r11; ngccc insists
  count→r7/no-copy, E0→r11, and attaches +0x50 to the lbl*4 chain).
  Documented levers tried in the draft header; registered-symbol spelling
  is REQUIRED (raw literal folds +0x50 into a lis+ori). doc-06 wall.
- **vtest.py trap found:** `tools/vtest.py` takes a RAW hex addr — passing
  `2B920` (no 0x800 base) silently compares against the wrong DOL region
  and prints a false MATCH. Always pass the full `8002B920` / use
  try_variants.py for A/B scoring.
- fn_801AEBA4 (232B, skinning-blend FPR web, 31%) unworked this round.

**2026-09-07 (cont. 13) — random batch (seed ls|head): 5 EXACT promotions
(DOL byte-identical `ff6faeb0…`), 1 park note corrected:**
- **New recipe — FP param-reuse register pinning (fn_80053D10, 304B):** an
  HSL→RGB sector converter parked at 64.5% on a whole FPR scratch-web
  rotation (quotient f12/divisor f12/1.0 f11/helper-double f10 vs want's
  f1/f0/f12/f11). Root cause: the m2c draft kept `farg0 / lbl` in a FRESH
  temp; want keeps the quotient IN THE PARAMETER REGISTER — the original C
  reassigned the param in place (`farg0 = farg0 / lbl_80292FD8;`). That
  single change pins every downstream scratch reg to want's slots. Same
  lesson as the GPR param-reuse class, now confirmed for FPR coloring.
- **fn_800AAA08 (44B)** — float-table getter: three fixes — the slot is an
  f32 ARRAY load (lfsx), not s32; the `*4` in the m2c sum is the array
  element scale, so the honest form is `arg0 = arg0 + arg1*2 + arg2*4 +
  arg3*8; return lbl_f32array[arg0];` (bit-combined element index); and the
  `extern f32[]` element spelling is what lands want's `lfsx f1, r9, r3`
  (rA=base) — with `extern char[]` + (s32) cast ngccc emits rA=index (a
  one-shot variant of doc-49's rA↔rB slot coin).
- **fn_800780A8 (92B)** — guarded record reader: arg4 is really a u16 *
  (want stores a BYTE as a halfword: lbzx + sth), and the three optional
  outputs are byte reads at +1/+2/+3 of the same 4-byte record (m2c had
  *(s32*) reads at a 16-byte stride). EXACT 23/23.
- **fn_8001EFF4 (72B)** — lbl_80300280 dispatch (fn_801F298 class): declare
  the label as the fn-ptr VARIABLE `extern void (*lbl_80300280)(s32, s32);`
  (raw-literal deref emitted lis+ori+lwz through a 2nd reg + mr) and drop
  m2c's phantom 3rd arg (the fnptr itself). EXACT 18/18.
- **fn_8007B890 (96B)** — 2-float setter: the 0x144/0x148 fields are f32
  slots (want stfs after the 0x43300000 int→double + rodata-bias lfd), not
  s32 (m2c emitted a fctiwz round-trip + stw). Gotcha recorded: the inner
  `*(s32 *)(arg0+8)` pointer must be re-dereferenced per store — a named
  local regresses to 33% (want reloads 8(r3) before each stfs).
- **fn_800CD3A0 re-parked at 94.4% with a CORRECTED note:** the old park
  text ("outer-loop register-role permutation") was stale — under its
  `// FLAG: -fno-schedule-insns2` the roles already match want (dst=r9
  ctr=r10 scan=r11). True residual = 2 words: want's zero-branch emits
  [dst += 0x3C] before [base = arg0+0x68]; ngccc hoists the base addi above
  the dst advance regardless of source order (doc-15 scheduler family).
  Tried: both statement orders, comma-sequencing, char*-typed dst,
  base-after-arg2, direct inline store (77.8%), base-from-dst arithmetic,
  all 4 sched-flag combos (no-flag/-fno-sched-insns regress the copy loop
  to <42%). Ceiling re-confirmed.
- Re-scored from the same random batch (DIFF, unworked): fn_8001EFF4 done
  above; fn_8001EFF4 aside, fn_801AEBA4 (232B), fn_800780A8 done,
  fn_8002B920 (316B), fn_80092DD4 (208B) remain DIFF.

**2026-09-07 (cont. 12) — random-batch sweep (seed ls|shuf): 1 new EXACT
(draft-level), 4 re-drafts parked with notes:**
- **fn_8001DFF4 EXACT 98/98 (392B)** — VM dispatch-table first-call init:
  the doc-51 raw-lit → symbol recipe again. The m2c draft stored 16 raw
  function-address literals (0x8001DBC0 … fn_8001DD04) → lis+ori; want
  materializes each as a SYMBOL ref → lis+addi, and loads the queue pointer
  as the registered .sbss object lbl_803CAF18 (lis-anchor + lwz) instead of
  deref-ing the raw literal. Draft rewritten with `(s32)fn_X` stores +
  `extern void *lbl_803CAF18`. **Promotion reverted by the known .sdata2
  +0x40 link blocker** (new-object class, same as the 09-02 entry; DOL
  restored byte-identical `ff6faeb0…`) — draft kept in src/wip/ with the
  EXACT note, re-promote after tail-region surgery.
- **fn_8028DF98** (80B, 19→45%): 3-way dispatch redrafted — lbl_8025C558
  is a direct `bl` target (registered label = function), not an m2c fn-ptr
  cast; -1 path returns before the call. Park: want's addi+cmplwi+ble vs
  ngccc's cmplwi+bgt unsigned-range canonicalization.
- **fn_8007E984** (100B, 26.7→42.3%): two m2c corruptions fixed — first
  call is fn_8007EC7C(arg0) not (&string), + 3 missing protos (crclr).
  Park: want loads the unk0x30 flag into the call-arg register r3 and
  reuses it (doc-15 arg-liveness coloring) + mtlr-after-lmw epilogue order.
- **fn_80127618** (108B, 40→55.6%): sibling of promoted fn_80127684; the
  `((temp & ~0x7F0000) | 0x40000)` patch must be spelled through the
  BitF2 bitfield union (a:9/mid:7/b:16) to get want's
  `li r9,4; rlwimi r0,r9,0x10,9,0xf` (rlwinm+oris fold otherwise). arg2 is
  a string (fn_801251B4 takes char*). Park: doc-15 arg-setup interleave
  around the fn_801251B4 call.
- **fn_800079D8** (116B, 0→3.4%, needs `// FLAG: -mps-float`): identified —
  vec4 xyz-lerp (ratio lbl_8028FE38, w = lbl_8028FE3C) built in a 16B stack
  local then copied as 2 psq pairs (m2c draft had dropped the struct copy
  and compiled without PS). Park: ngccc hoists arg1's loads min.z-first
  invariant to source order/permutations/-O level/-sched flags; want is
  min.x-first with per-lerp interleave; `mr r11,r3` needs the PS r3-clobber
  barrier idiom (no-asm equivalent unknown). Full notes in draft header.
- **fn_80004404** (58.0%): park note upgraded — want frame 0x60 has 0x30 of
  dead locals (temps all in f27-f31); FPR-frame quirk family confirmed
  (same wall as sinf/cosf siblings 0x80003E0C/03EB0/03F54).
- New tool: `tools/try_variants.py` — heredoc A/B scorer for draft bodies
  (compile + reloc-masked score per variant, no file edits needed).

**2026-09-07 (cont. 11) — corrupted-pool re-matches: 7 EXACT promotions
(DOL byte-identical, `ff6faeb0…`; 6,661 matched, wip pool 3,882):**
- Worked the smallest corrupted (`0;`-noise) drafts by re-matching from
  want listings: 5 compare predicates (fn_80058FB8 GT-vs-rodata,
  fn_800AE234 GE field pair, fn_80132260 ranked-table LE with ==TRUE
  shortcut, fn_8001A994 callee-result GE, fn_8002DE6C 0x2C-gated EQ
  ternary over 0x18/0x20 vs 0x1C) + 2 PS pair-movers
  (fn_800592B8 global-pointer slot copy + tail call, fn_80037BF0
  conditional copy with **base = callee return value**); fn_80036370
  scalar-splat init parked 6/19 on dual-pin coloring.
- **New calibration:** X-form `psq_stx f0,r9+r11` + following D-form comes
  from array-of-struct spelling `arr[i].p0 = x` (16B slots); D-form-only
  from pointer-arithmetic spelling. Cast-literal `*(f32*)0xADDR` for
  rodata f32 reads lands the stub in the wrong section — use
  `extern f32 lbl_…` (want lis+lfs D-form).
- **Tooling gap found:** my_diff.py masks `lis/lwz` label immediates, so a
  wrong `extern` label (lbl_80360C3C vs real lbl_80364C3C) scored EXACT
  standalone but failed the DOL link; promote_wip reverted cleanly
  (removed build.ninja — re-run `python3 configure.py …` then
  `tools/ninja build/G2TE52/main.dol` from repo root to recover).
- PS drafts need `// FLAG: -mps-float` in the draft header for
  test_wip_drafts sweeps; my_diff.py takes the flag on argv.

**2026-09-06 (cont. 10) — PS mag-compare family cracked: 5 EXACT promotions
(DOL byte-identical, `ff6faeb0…`; 6,655 matched, wip pool 3,888):**
- **Family recipe (template = promoted fn_800A11D8 + fn_8015896C):**
  `__builtin_ps_mul/merge00/madd/sum0/rsqrte/res` under `// FLAG: -mps-float`,
  mag extracted via `dot.flt.hi`. New calibration: the compare flavor lives in
  the post-`mfcr` `rlwinm` shift — `return a < b` → `5463effe` (rot 0x1d),
  `a > b` → `5463f7fe` (rot 0x1e), `a == b` → `5463fffe` (rot 0x1f);
  `fabsf(x-c) < eps` emits `fmr`→`fsubs`→`fabs` + the LT word.
- **fn_800A1230 (160B)** |mag−sp8|<eps, **fn_800A12D0 (144B)** mag>sp8,
  **fn_800A1360 (144B)** mag<sp8 — SkaterSpeed script-compare siblings
  (ident: arg0 = skater obj with Unk_130D31C8 PS fields at 0xB8/0xC0, arg1 =
  QB ctx, query 0 default via lbl_80297BBC/BC4/BC8). The corrupted m2c drafts
  hid the PS tails behind `0;` noise + `((u32)0>>N)&1` returns.
- **fn_800A07F0 (104B)** compute-and-report: mag = 1/√(D²+A²) over
  arg0->0xC0/0xB8, then `fn_8012772C(arg2->unk0x18, QB_SPEED, mag)`
  (r3-r5 param assignment; the corrupted draft had dropped 2 of 3 params).
- **fn_80003464 (4B)** empty `blr` leaf — EXACT, promoted.
- **Tools:** new `tools/want_vs_got.py <addr> [flags…]` — padded want-vs-got
  word diff with PS-aware decode (replaces the pasted heredoc).
- **Park:** fn_80005A18 (PS scale-by-inv-len, 120B) — spill structure
  reproduced byte-exact (volatile sp8/sp16 + 3-stage pun chain → frame 0x28
  + stfs→psq_l→ps_mr idiom + dead spills) but want pins dest base in r11 via
  entry `mr r11,r3`; no promoted source produces that prologue (scanned all
  src/*.c) — doc 06 M5.0o/M5.0r GPR-coloring wall.
- **Triaged 482 corrupted (`0;`-noise) drafts → 82 with PS tails**; 79 remain
  (mostly ps_sub dead-spill class — blocked by doc 06; several 300B+).

**2026-09-06 (cont. 9) — two-out-param family + store-rotation probes:**
- **Two-out-param QB-reader family** (fn_80128228 callee): fn_80114BAC /
  fn_80114C20 (A==B predicate twins) and fn_80112274 (light-manager init)
  all park at 78.6–82.8% — want's r29/r30 roles and frame-slot order for the
  two stack outs mirror ours. Both-zeros-first (44.8%), interleaved init
  (42.9%), decl swaps, ptr-locals all tie or regress. Allocator/frame coin,
  no source lever found.
- **fn_800B6CCC 88.0% (up from 84.0)** — light-updater ctor: 1c/20 store
  swap helps; the f32 store at 0x28 rotates one slot vs want (TBAA frees it
  from the integer store list; s32-pun attempt reshuffles r9/r11 and
  regresses to 48%). Parked.
- Doc-51 raw-literal call-arg leftovers (53×fn_8000F320, 15×fn_801282E0 …)
  are already-swept regressors, not new opportunities.

**2026-09-06 (cont. 8) — bulk A/B passes (negative results + park notes):**
- **Blind batch arg-insert keeps 0** (tools/fix_firstarg.py): of 585
  dropped-first-arg candidates, blind `arg0` insertion + proto sync breaks
  compilation in every A/B'd case (type mismatches, non-`arg0` param names,
  nested-call forms). The class is per-case only — confirmed wins this round
  were hand-analyzed (800F054C/8007AC6C).
- **Missing-prototype batch pass keeps 0** (tools/add_missing_protos.py):
  drafts that already compile have complete decl sets; the crclr/crset class
  only bites already-corrupted bodies.
- **fn_80244BC4 (78.8%)** parked as hand-re-match work: the whole tail is a
  register-role rotation (r30/r31/r22/r27 shifted one role) inside a
  156-word paired-single fn — want's loop weight lives in different regs.
- **fn_8004C9C0 (55.8%)** tail-web confirmed: else-init form regresses to
  37%, `||` operand swap to 24/43 with the call block fully re-rolled.
- **Hazard:** two concurrent sweep3.sh runs share /tmp/leaf scratch and
  clobber each other's compiles — always pkill sweeps before starting one.
- fn_80151DF8/fn_80152034 pass fn_80151B80 as a **cast function pointer**
  to fn_800A3778 — not an arity bug; scanner false positive.

**2026-09-06 (cont. 7) — arity cross-check + small-NEAR round: 3 more EXACT
promotions (DOL byte-identical):**
- **fn_800F054C (76B) EXACT, promoted** — QB_LINKS lookup: arg0 passes
  THROUGH to fn_801285A4 as its first arg (dropped-first-arg class) +
  early-return form (return 0 inside the null branch) puts want's `li r3,0`
  after `cmpwi`.
- **fn_80124EC4 (60B) EXACT, promoted** — float-broadcast; missing callee
  prototypes only (crset cr1eq artifact).
- **fn_8007AC6C (80B) EXACT, promoted** — pool-setup: want is
  `temp = fn_80077BAC(fn_80009A44(0x10)); fn_8005BF60(temp, arg1, arg2, 1);`
  — m2c split the nested call, dropped BOTH first args, and fn_80009A44's
  promoted `void` decl is wrong (it returns s32; noted for re-promotion).
- **Bulk arity scanner** (`tools/arity_scan2.py` pattern, in /tmp): compares
  every wip call site against the callee's promoted arity — 472 extra-arg
  and 1,813 fewer-arg hits (incl. 585 dropped-first-arg candidates). Blind
  batch-fix keeps 0 (type/name mismatches); the class needs per-case
  handling like the three above. Many 0-vs-1 hits are multi-line-call regex
  artifacts.
- **Parked:** fn_800AF6F8 87.5% (f32 4th arg via `*(f32*)&unk0x348C` pun —
  unk0x348C is mis-typed s32 in structs.h; r6/r7 vs r4/r5 alloc coin),
  fn_80182C50 73.3% (desc 1550→1554→1548 store order, li/addi pair coin),
  fn_80191E8C 95.1% (hash-first vs obj-first at one call — GCC canonical),
  fn_800A1B5C 95.5%, fn_801A11D0/fn_801A1B2C 90.0%.

**2026-09-06 (cont. 6) — m2c-arg-corruption classes scale to 31 EXACT
promotions (DOL byte-identical `ff6faeb0…`):** the two big classes from this
round generalize across the wip pool:
- **Label-stash + spurious label call-arg (17 promoted)** — 37 drafts had
  `arg0->unkNN = (s32)lbl_X; fn_Y(arg0, (s32)lbl_X);`. want stores the label
  and calls `fn_Y(arg0)` with ONE arg (r3=arg0 stays live; `mr r11,r3` spill
  in want is the giveaway). Fix = drop the 2nd arg AND add a 1-param callee
  prototype (without it ngccc emits `crclr cr1eq` for the unprototyped
  call). Promoted: 80010910 80011EA8 80011F64 80013144 80014B94 8002448C
  80034684 80041F5C 8004F15C 8004F1E0 80055A48 8007D4B0 8009A758 800B6D30
  8010192C 80203EC4 80235190.
- **Phantom 0x80290000 call-arg (6 promoted)** — `fn_801282E0(...,
  0x80290000)` is m2c garbage from the rodata base register; the callee is
  4-arg. Also needs the prototype (`s32 fn_801282E0(Unk_2EF06E12 *, s32,
  f32 *, s32);`) to kill the crclr. Promoted: 800702E0 80070394 80070470
  800705F4 800707F4 800708D0 (all 68B, 17/17).
- **One-off wins:** 800726F8/8007C6BC/800948AC/80205460 (48B label-stash
  quartet, same class), 80058184 (s32-intermediate u16 mask selects rlwinm
  over andi.), 8005742C (vtable dispatch: wrong struct type hid the s16
  `lha` + m2c self-arg; single source var for the call result), 8005F100
  (2-arg unprototyped fnptr dispatch, void-return re-load of arg0), 800A3BDC
  (dropped FIRST call arg + load-before-store order vs `sp8=0`).
- **Parked:** 800A1B5C 95.5% (single stwx operand-order coin), 801A11D0 /
  801A1B2C 90% (twin lfs issue-order), 80013180/80058D80-58E00/8005E948+
  fnptr pool re-scored after arg fix — most are corrupted-body re-match work.
- 8 drafts with corrupted bodies (silent-rc1 class) now compile as honest
  DIFFs at 1-45% after phantom-arg removal.
- **fn_800F054C promotion postscript:** the draft carried m2c's phantom
  `static s32 sp8;` (emits .sbss data → promote_wip SKIPs, "allocatable data
  outside .text") while the real sp8 is a stack local. Deleting the static
  unblocks promotion. Scan wip EXACTs for this before assuming a draft is
  unpromotable.
- Progress: 6,651 matched files (+34 this round), wip pool 3,895 → 3,892.

**2026-09-06 (cont. 5) — small-NEAR sweep + silent-rc1 class solved: 3 EXACT
promotions (DOL byte-identical), 7 FAILs → honest DIFFs:**
- **fn_80025DF8 (52B) EXACT, promoted** — 16-slot pointer-table reservation
  scan (Table16_ReserveSlot): statement ORDER win — the table address must
  be materialized into a named local BEFORE `var_r11 = NULL` (want's `lis
  r9` precedes `li r11,0`); computing it inline after the NULL init folds
  the constant onto r11 instead. The REVERSE of the usual inline-is-better
  rule.
- **fn_80025D0C (68B) EXACT, promoted** — event-push counter bump
  (EventQueue_PushCounted): m2c synthesized a 4th call arg (the incremented
  counter) that want never passes — 3-arg call `fn_80025EA8(tbl, &sp8,
  arg0)` is exact. Promotion gotcha: auto-header said size=72B/end D54 but
  the true boundary is 68B/D50 (next promoted fn starts there); fixed the
  header before promoting.
- **fn_8001F298 (64B) EXACT, promoted** — QB event dispatcher
  (QBEvent_DispatchPacked): the draft declared lbl_80300280 as `char[]`
  and CALLED THE ADDRESS ITSELF; want `lwz r0,0x280(r9)` loads a global
  function-pointer VARIABLE. Correct decl: `extern void (*lbl_80300280)(s32,
  s32, s32);` + explicit deref — also kills the `crclr cr1eq` that ngccc
  emits for calls through unprototyped pointers.
- **silent-rc1 class SOLVED (5 drafts FAIL→DIFF)**: ngccc fails with rc=1
  and ZERO error lines when a call to memset/memcpy/sinf has m2c's phantom
  extra args (2-arg memset(0,n), 2-arg memcpy(dst,n), 9-arg sinf). fn_8007904C
  (memset+memcpy+raw derefs), fn_8007A9F8 (memset 0xFF + 2-arg alloc),
  fn_80103A50 (2× memcpy), fn_80046B90 (9-arg sinf), fn_80089368 (9-arg
  sinf) — all repaired to honest DIFF (~1-19%; corrupted bodies need real
  re-matches, but they now sweep). Grep recipe: any silent-rc1 draft →
  check for memset/memcpy/sinf with wrong arity first.
- Parked with notes: fn_8000E48C/fn_8000E978 twins 56-58% (post-dec loop
  `while (left--)` — ngccc's mr-scratch vs want's folded test; both
  spellings + sched flag probed), fn_8000DDB0 57.9% / fn_8000DDFC 64.7%
  (un-rotated vs rotated loop shape; -fno-loop-rotate doesn't exist in
  this ngccc), fn_80014A5C 61.5% (m2c cr0-save artifact, postdec rewrite
  regresses). Full NEAR tier re-confirmed at previous ceilings.

**2026-09-06 (cont. 4) — full-sweep FLAG-honoring + FAIL taxonomy: 3 EXACT
promotions (DOL byte-identical), 21 drafts un-FAILed, sweep tool fixed:**
- **test_wip_drafts.py now parses per-draft `// FLAG:` lines** (same regex
  as promote_wip.py; global `--extra-cflags` still overrides). This was
  scoring every PS/gcse-flagged draft as FAIL (or masking EXACTs): the
  sweep FAIL count dropped 102 → 60 and **5 masked EXACTs surfaced**.
- **fn_800F3794 (56B) EXACT, promoted** — vtable dispatch
  (SubDispatch_PayloadOffset): the 92.9% park was one misread field — the
  0xA0 slot is read as a direct signed halfword (`lha 0xa0(r9)`), so
  `*(s16 *)((char *)sub + 0xA0)` replaces the `(s16)sub->unk0xA0` cast
  (which loads the low half at 0xa2). Old "li interleave" theory wrong.
- **fn_801F62D8 (280B) EXACT, promoted** — already-flagged `-fno-gcse`
  draft (same class as fn_80109F18's park: stops GCC hoisting &sp8 into a
  saved reg).
- **fn_8023E18C (260B) EXACT, promoted** — `-fno-gcse` draft.
- **EXACT-but-asm, stays parked**: fn_801B5A54 (360B, `bdnz $` self-target
  window + psq asm blocks — promote_wip REFUSEs on the `$` symbol and the
  no-asm policy requires a plain-C loop rewrite first), fn_801D2C58 (316B,
  psq asm blocks), fn_80225E70 (504B, `-mps-float -fno-gcse`, asm blocks),
  fn_80109F18 (244B, known link-level park #24 — auto-revert correctly
  rolled back the batch when it diverged).
- **FAIL taxonomy (102 → 42 final)**: 21 drafts un-FAILed by adding
  `// FLAG: -mps-float` (10 SN_PS_type bucket + 9 needs-mps + 2 stragglers —
  SN_PS_type is an ngccc builtin under -mps-float, no SN_PS.h needed),
  1 memset(0,n)→memset(p,0,n) repair (fn_8009B3B4), 1 4-arg memcpy artifact
  (fn_80039AD4), 1 cosf sig `s32 cosf(s32)`→`f32 cosf(f32)` (fn_8009A8CC,
  still ICE-blocked at any -O — compiler-side, not source), 1 missing
  unk_structs include + FLAG (fn_801F77B8, quat-blend skinning), 1
  self-referential `#define QB_TRIANGLE QB_TRIANGLE` + missing qb include
  (fn_8020773C). Remaining: ~15 ICE-class (expr.c:2802/8297, expmed —
  PS-heavy bodies), 6 GX drafts needing real dolphin/gx.h SDK headers
  (stubs would be misleading — left failing), 1 silent rc=1 (fn_8009A8CC),
  and **fn_800699C8 HANGS ngccc indefinitely** (656B m2c body, compiler
  spins forever — first hang observed; killed mid-sweep, recorded FAIL).
  `promote_wip.py` flag parser already ignores trailing prose after the
  flag list; test_wip_drafts.py was taught the same.
- **NEAR ceilings re-confirmed** (probed, parked): fn_80173D30 99.5%
  (r30 pin load-bearing — removing it costs 15%), fn_801689C8 99.5% (GCC
  const-fold onto r25, documented), fn_8019E770 99.3% (add-operand order,
  both swaps tried), fn_80167E04 98.9% (loop-test register coin; swap/pins
  all regress), fn_801903B8 98.6% (lis/lwz call-site swap, both hoists tie),
  fn_801C5780 65.6% (see the earlier entry). Un-FAILed upgrades: fn_801FC8CC
  91.3% NEAR (PS selector/release fn — want loads both psq pairs then
  stores both; GCC interleaves; both reorderings tie) and fn_801B5BF8
  88.7% NEAR (label-web lis base + psq store interleave).

**2026-09-06 (random sample, seed 20260906) — 4 EXACT promotions (DOL
byte-identical; PROGRESS 7,551 → 7,555) + 1 FAIL repair:**
- **fn_80032934 (116B) EXACT, promoted** — threshold-setter
  (fn_80032934_SetThreshold): want is the EARLY-RETURN form
  (`if (fn_80032A60(arg0) != 2) return 0;` after the default-value reset
  branch) with r31-ONLY save (farg0 in f31, no stmw) and a DIRECT `stfs
  f31,0x60(r31)` — arg0+0x60 is an f32 slot used through the *(f32*)& pun
  (shared Unk_31DE137E mega-class field stays s32; M6.89j eligibility
  excluded the s32/f32 pun pair, so the pun is the correct spelling).
  m2c's fctiwz round-trip (s32 field) + guarded var_r3 form cost the whole
  tail. FPR pad8 dummy inlined in the draft. Arg0 was m2c-mis-typed
  Unk_C7387A53* (no unk0x60) — the callees' real sig is Unk_31DE137E*.
- **fn_8023357C (348B) EXACT, promoted** — pad-direction remap installer
  (RemapPadDirectionButtons): the u32-switch draft was already
  byte-exact under its own `// FLAG: -fno-schedule-insns2` (unflagged sweep
  score 97.7% — only want's re-emitted [cmplw][bgt] after the root equality
  differs). Sweep lesson: test_wip_drafts.py does NOT parse per-draft FLAG
  lines — flagged drafts must be re-verified with --extra-cflags before
  promoting. Old 67.4% PARKED note was stale (earlier form).
- **fn_8008A888 repaired (was FAIL)** — m2c 9-arg sinf corruption
  (register-noise class, same as fn_80083564) + missing sinf/cosf externs
  (implicit-builtin mismatch); want disasm confirms every bl sinf/cosf is
  single-arg (angle in f1). Identified: particle ring/disc renderer
  (DrawParticleRing) — body is paired-single, needs a -mps-float hand-draft
  (doc-06); honestly scored DIFF, now sweepable.
- **fn_80186CE0 (52B) EXACT, promoted** — 2-arg passthrough predicate:
  m2c DROPPED arg1 (register noise — want keeps r3/r4 untouched, `li r5,0`
  is the third arg) and synthesized a 1-arg call with r3=0. Redraft:
  `return fn_801839F0(arg0, arg1, 0) != 0;` (the `!= 0` return spelling
  emits want's `cmpwi; li r3,1; bne; li r3,0` order). Gotcha for future
  promotions: promoted files keep the DRAFT's include lines verbatim — a
  body without `#include "types.h"` compiles standalone (compile_fn
  prepends it) but fails in the build (no prepend), surfacing as a
  link-stage "DOL DIFFERS" that is really a parse error.
- **fn_800ABAF8 (60B) EXACT, promoted** — scavenger-hunt timer restart
  (RestartScavengerTimer): three m2c corruptions — call is 1-ARG (arg2 was
  noise); unk0x3494 is an s32-typed field of the shared Unk_0771A7B9 class
  but want stores the float RAW (stfs) → *(f32 *)& pun on that slot; and the
  SOURCE ORDER is [0x347C flag][0x3494 limit][0x3490 base-copy] — the limit
  store sits between the flag store and the base-time copy, which is what
  lands want's stw/stfs/stfs order (m2c's naive order emitted a 3-store
  rotation at 80%).
- **fn_800F3794 (56B) EXACT, promoted (cont. session)** — the "one word
  left" theory above was wrong: the residual was the 0xA0 slot read.
  want emits `lha r0,0xa0(r9)` — a direct SIGNED HALFWORD load at 0xA0,
  not a cast of the s32 field there (which yields lha 0xa2, the low half).
  Fix: `*(s16 *)((char *)temp_r9 + 0xA0)` byte-exact; promotion
  DOL-identical. Suggested rename SubDispatch_PayloadOffset.
- Parked with upgrades: **fn_8000901C 54.7%** (bit reader — arg0 retyped
  u32* killing all puns; 2x2 order grid confirms m2c's original order is
  best; residual = want's x>>32 UB fold + color web; an earlier 83.0%
  reading here was a stale-/tmp-leaf scoring artifact, corrected), **fn_801C5780 65.6%** (was 62.5; GetTimeSincePhysicsSwitch —
  sched flag helps, inline-anchor variant regresses; ceiling re-confirmed
  this session: single-expression 0x4330...ULL|g form regresses to 31%,
  volatile-anchor externs tie — the rodata-load interleave is stable), **fn_80112860 70.4%**
  (ScriptGetBonePosition — doc-15 family, 3 shapes tie), **fn_80172A90
  93.6%** (turntable handler identified, PS wall stands).
- Mid-tier DIFFs checked, all stand as m2c/register-noise bodies
  (fn_8012xxxx QB family, fn_8022xxxx script VM family, fn_800EFxxx
  particle family): real-logic DIFF bodies needing hand redrafts, not
  one-line fixes.

**2026-09-06 — thunk family + store-order: 7 more EXACT promotions (DOL
byte-identical; PROGRESS 7,539 → 7,546).**
- **arg-forwarding thunk family SOLVED (fn_8001B6A8/6DC/718/754/7C0/87C,
  52-60B each)**: m2c drafted them as `void` helpers calling a fn-ptr with a
  bare constant; want disasm showed r3/r5/r6 PASSTHROUGH (args never
  re-homed), a dispatch constant in r4 (12/8/6/3/2/0), and an unprototyped
  call (crclr cr1eq). Redraft: `s32 fn(s32 a[, s32 b, s32 c]) { return
  (*(s32 (**)())lbl_80300178)(a, CONST[, b, c]); }` — the unprototyped
  pointer-to-fn-ptr spelling reproduces lis/addi@l + crclr + blrl exactly.
  Note: promote_wip batch of 6 initially DOL-DIFFERED — root cause was my
  hand-written 52B range markers on the 3-arg twins (real size 60B) leaving
  stale splits.txt rows; fixed markers + clean registration → identical.
- **fn_800AA0BC (312B) EXACT** — 16-slot name-table init (16x fn_800AA080
  rodata-string installs + counter zeroing at 0x274/0x278). The parked draft
  had the two zero-stores swapped; store order 0x274-before-0x278 is
  load-bearing. Suggested rename: InitNameTableEntries.

**2026-09-06 (cont. 3) — random sweep 100 (seed sw6): 2 EXACT promotions
(DOL byte-identical; PROGRESS 7,549 → 7,551).**
- **fn_8008B354 (140B) EXACT** — LabelObjectCtor-family ctor parked at 72.2%
  on the "crclr-before-fn_80081794 interleave". Root cause was simpler: the
  draft never declared fn_80081794, so the call was implicit (crclr cr1eq).
  Adding `s32 fn_80081794(s32);` → byte-exact. Another M5.22-style
  missing-proto harvest — the crclr census (blrl w/ and w/o 0x4CC63182) is
  the fast screen.
- **fn_8001FEC0 (52B) EXACT** — dispatch-setter through lbl_80300280:
  want has NO crclr → prototyped `(*(s32 (**)(s32))lbl_80300280)(...)`;
  the old draft's unprototyped `(**)()` emitted crclr (57.1). The
  no-crclr members of the 0x80300278/80/88/8C zone are all this shape.
- Mid-tier NEARs checked: fn_80181DA0 97.6 (documented prologue coin),
  fn_80136D30 88.9 (documented magic-number alloc coin) — both stand.
  4 sweep FAILs triaged: fn_8002439C repaired (f32-into-struct-ptr assign
  → (s32) cast), 3 PS drafts under -mps-float (doc-06). Registry rows
  updated for all probes.

**2026-09-06 (cont. 2) — fn-ptr cast sweep over the 0x80300278/80/88/8C
dispatch zone (24 drafts, no new promotions — all real-logic DIFF bodies).**
Census: every want stream in the zone calls through the tables with blrl and
NO crclr → prototyped `(**)(args)` casts. tools/fix_fnptr_calls.py converted
59 raw-literal fn-ptr casts (`0x80300288` → `lbl_80300288`, incl. typed
`(**)(u16,s32,s32)` forms); extern decls injected; conflicting
`extern s32 lbl_80300280` duplicates removed (fn_8001E3CC/E4E8 now compile).
Registry rows re-scored for all 24; fn_80018570 improved 45.6 → 67.6
(raw 0x80302EE4 loop literals → symbols; residual = want's base+offset
OSResumeThread arg (no symbol at 0x8031FB28) + walker role coin).

**2026-09-06 (cont.) — FAIL repairs + dispatch-setter family: 3 more EXACT
promotions (DOL byte-identical; PROGRESS 7,546 → 7,549).**
- **9 of 11 compile-FAIL drafts repaired** — all one class: m2c corruption
  that drops or invents call arguments. sinf()/cosf() zero-arg & 9-arg sites
  (fn_8007141C, fn_80083564, fn_80089E40, fn_8008EDC0, fn_800948E0 — want
  passes the angle in f1, confirmed per-site in want disasm); 1-arg memcpy →
  the real fn_80009A78 realloc path (fn_80077CFC); 4-arg memset (fn_801CCB68);
  zero-arg strlen (fn_800427AC); missing dolphin/SN_PS.h include
  (fn_801B4664, compiles under -mps-float). All now compile + are honestly
  scored (DIFF tier; big bodies with early-garbage — but sweepable).
- **dispatch-setter trio PROMOTED (fn_8001EF84/EFBC/F068)**: call through the
  sdata fn-ptr table lbl_80300288/80. The unprototyped `(**)()` cast emits
  spurious crclr cr1eq (60.0 NEAR); the PROTOTYPED pointer-to-fn-pointer
  `(*(s32 (**)(s32,s32))lbl_...)` is byte-exact — 4th fn-ptr-cast recipe
  variant: (*) = call address, (**)() = load+crclr, (**)(args) = load, no
  crclr. Registry rows updated.

**2026-09-06 — raw-lit→symbol full-tree sweep: 5 more EXACT promotions (DOL
byte-identical; PROGRESS 7,532 → 7,539).** Mechanical application of the
doc-51 recipe (fn_801A9528/fn_80121A78) across the whole wip tree:
`tools/fix_raw_lit.py` rewrote 4,702 raw address literals in 870 drafts to
registered `lbl_*` symbol references (+ `extern char lbl_*[];` decls);
every file then A/B-gated via `tools/ab_raw_lit.py --auto` (compile+score
HEAD body vs patched body; keep iff post >= pre; 368 regressors auto-reverted).
~370 files kept, hash-insert siblings 58.5→85.0, fn_80012AD8 crossed to NEAR
50.0. **5 drafts went straight to EXACT from the patch alone and promoted:**
fn_800150EC (global-node list poll), fn_800553EC (log+forward 8 args), and
QB script-callback trio fn_8020432C (QB_TRIGGER resolve), fn_802053AC
(flag notify), fn_8020686C (QB_CAG_WORKSPACE texture bind). 23 registry
rows updated to the post-patch scores; doc 51 + README index written.

**2026-09-06 — random-sweep session: 4 new EXACT promotions (DOL byte-identical
together with all registry/doc updates; PROGRESS 7,529 → 7,532).**
- **fn_801A9528** (92B) — sub-object reset installing fn_801A94E8 callback;
  the draft passed the callee as a BARE 0x801A94E8 literal (lis+ori) instead
  of the registered symbol reference (lis+addi) — fixing that alone also
  flipped the r29/r30 role swap. Clean no-asm match.
- **fn_8000BEEC** (80B, was parked 85% on doc-24) — NEW RECIPE: the
  if/return-structured goto transcription (compares inline in want's order,
  call blocks as trailing labels, bare `return;` on the inline path) gives
  want's out-of-line call-block placement. Flat goto chain had failed (68%).
  Recipe appended to doc-24.
- **fn_800A4AB4** (140B, was 62.9%) — call is 3-ARG (m2c dropped arg3 =
  this fn's arg1; fn_800A5B64 is (ptr,s32,s32)); doc-47 for-form rotation
  with the single walker in the for-init + count reloaded per eval; entry
  must advance as BYTE steps (`(char *)entry + 0x14`) — a typed
  `entry += 0x14` on Unk_2EF06E12* scaled by 0xcd0 (sizeof) and regressed.
- **fn_80054E40** (84B, was parked 60.9% walk-pointer coin) — doc-02
  recipe: r11 walker pin + `-ffixed-r11`, PLUS single-return while-form
  (keeps want's `li r3,0` epilogue instead of `mr r3,r11`). Recipe appended
  to doc-02.
Parked improvements: fn_800874DC 58.5→85.0 and fn_8000EBF4 58.5→85.0
(hash-insert siblings; byte-scaled indexed store via `char *` base, residual
6-word arg2→r28 home swap = fn_8007AC6C coin); fn_80079464 repaired (dup
decls + 4-arg memcpy → real fn_8026AE28 callee); fn_8009E9F0 probes: the
"missing fn_8009EEAC extern" lead is a REGRESSION (removes crclr but lets
PRE merge the two 0x28 stores, 45.5%); fn_801D1210 97.8% re-probed dead
(literal flip, inline float, __builtin_fabs); fn_801D19E0 = ngccc ICE
expr.c:2802 (__ps_t field via char*).

**2026-09-06 — the LabelObjectCtor "r9/r11 label-address web coin" SOLVED
(not a coin): 5 new EXACT promotions.** fn_80087E18, fn_80088824, fn_8008B994,
fn_8008CFD0 + twin fn_8008C2C0 were parked at 85.7-88.6% on "ngccc
assigns the two rodata label addresses to the reverse register pair
regardless of decl/compute order". Root cause was the HANDLE HOIST
(`handle = lbl_80366478;` named local): the hoisted load competes for the
caller-saved pool and reverses the two label-web colors while keeping want's
slot order — every order/pin/flag probe see-saws. Passing the handle global
INLINE to fn_8005CF80 (no named temp) lets the scheduler split the handle
lis+lwz pair between the two label lis as the original does; natural colors
fall out, all 6 label words match. Also required family-wide: 6-param
signature (prologue saves r6/r7/r8) and BYTE stores at 0x170/0x171 (resp.
0x178/0x179 — stb, not the word-pun). Full recipe in doc-15 §SOLVED MEMBER.
Transferable: see-saw (colors↔order) = hidden competing web, un-hoist
single-use globals before concluding scheduler gap.

**2026-09-16 (q) — random no-park batch: 7 EXACT promotions (DOL byte-identical
`ff6faeb0…`) + 1 tool bug fix + 3 improved parks.**  Picked from the no-park
pool after scoring all 2,994 sweepable + 1,616 parked drafts in parallel.

**promote_wip.py bug (fixed) — two draft-header styles never promoted:**
`promote()` built the body with `txt.split("\n", 1)[1]` + a `^(//.*\n)+` strip.
That (a) ate the `/*` opener of a block-comment header, leaking the comment text
into the C (fn_8000E878: `src/fn_8000E878.c:5: parse error before 'to'`), and
(b) assumed the draft carries its own `#include "types.h"` — but
`gen_leaves.compile_fn` ALWAYS prepends that include, so a draft without it (or
with prototypes above it that already use `s32`) verified EXACT offline and then
failed at link-rebuild (fn_8018F70C: `parse error before 's32'`).  New
`draft_code(txt)` skips leading `//` AND `/* */` comment blocks and prepends the
types.h include when absent.  3 drafts in the corpus start with `/*`; every
offline gate (`test_one`, `score_addrs`, `sb.py`) passed all of them, so this
class was invisible before.

Promoted (all via `tools/promote_wip.py`, full rebuild `cmp`-identical):
**fn_8000E878** (188B hash-table iterator), **fn_801F4D6C** (92B), **fn_8018F70C**
(400B, ScriptGetGoalFlags-style QB reader), **fn_8004C9C0**
(ScriptDestroyScreenElement, 168B), **fn_800F2A48** (144B), **fn_800F2AD8**
(140B), **fn_800A3470** (124B).  The first four were long-parked drafts whose stale
notes claimed 52-67% — later automated passes (struct retyping, protoscale) had
already made them byte-exact; the sweep-only pool hid them because
`sweepable_pool.py`'s parked test is case-sensitive (`^//.*park`), so `// PARKED`
upper-case headers still counted as sweepable — but the 4 real ones had genuinely
no park note.  Worth re-sweeping the uppercase-`PARKED` set occasionally.

**New reusable recipe — s16 vtable adjuster + exact-CFG rotated loop (4 fns):**
The Neversoft dispatch idiom loads the adjuster with `lha` and the function
pointer with `lwz` (`lha r3,0xNN(r9); lwz r0,0xNN+4(r9); add r3,rB,r3; mtlr; blrl`).
The shared `Unk_C7387A53` types those offsets `s32`, so m2c emits `lwz` and the
whole body is off.  A per-record LOCAL typedef with `s16 off;` + `void *fn;` at
the right offsets restores the `lha` (fn_800A3470 61.3→100, fn_800F2A48
66.7→100; also +2.7 on fn_8004ADC8, +3.5 on fn_80125C70).
Second half, for the loop shapes: when want ENTERS THE LOOP AT ITS BOTTOM TEST
(`call; if (v) done; goto bottom; body: ...; bottom: if (call()==0) goto body;`),
a plain `while`/`do` makes ngccc rotate the other way (30.6%) and the m2c
duplicated-call goto shape emits both calls consecutively (69.4%).  The exact
spelling is a forward `goto bottom;` BEFORE the `body:` label plus the back-edge
`if (call() == 0) goto body;` — 100% on both members.  Also: the `return 0` for
the NULL case must be written `if (p != 0) { ... } return 0;` (puts the ret-0
block at the end like want), NOT an early `if (p == 0) return 0;` (inlines it,
28.6%).  Full bodies + notes in the promoted headers and the two solved drafts
(removed by promote).

Improved + parked with notes (best body kept):
- **fn_8004ADC8** 58.7 → 61.3% — same s16 typedef for its two dispatch records;
  residual is a whole-function callee-saved home shift (want r28-r31 vs got
  r27-r30) + the fn_8004B03C arg-setup order.
- **fn_80125CE4** 53.6% (unchanged score, SEMANTICALLY REDRAFTED) — m2c scaled
  the `+2` byte store by 4 and mis-scaled the table reads; corrected to
  `*(s32 *)(arg0 + var_r31)` + a `stb`-width store.  **fn_80125C70** 51.7 → 55.2%
  (same byte-store fix + do-while).  Both parked on the loop entry-guard
  duplication rotation wall.
- **fn_801FA534 / fn_801FA58C** 90.9% — a pure 2-word REGALLOC COIN: the two
  loop-invariant symbol bases get the opposite r29/r30 homes (confirmed in
  `.rela.text`).  ~15 source/proto/cast spellings and 15 flags all leave 90.9
  (or regress); -ffixed-r29/-r30 → 77.3.  Parked pending a two-live-invariant
  allocation recipe.
- **fn_8001094C** 62.5% — the arg0/arg1 callee-saved homes are swapped
  (want r30/r31 vs got r31/r30); 8 body spellings, all 62.5 or worse.

## Park ledger

The pool is large enough that batch selection has to be mechanical rather than
by reading draft headers one at a time. `tools/wip_ledger.py` emits one TSV row
per still-unmatched function — address, size, symbol, draft, recorded score,
the draft's own flags, every `docs/parkings/` issue it quotes **with that doc's
current status**, whether the draft carries a park note, and its state:

```sh
tools/venv/bin/python tools/wip_ledger.py -o build/wip_ledger.tsv --summary
```

The lists it exists to produce:

* `state=remaining`, `doc_status` containing `solved` — the draft was parked on
  a blocker whose recipe is now written down in `docs/parkings/solved/`;
  re-test the recipe before re-deriving the wall.
* `park_note=no` — the draft was never worked (not walled).
* `park_note=no-draft` — no draft exists at all.
* one blocker doc / one zone / one family — the whole population of a wall.

`state=uncounted` is a separate population: the unit has a `source_path` and the
linked DOL is byte-identical, but objdiff scores the function below 100 %, so
the report (and PROGRESS) counts it as unmatched. Its draft was deleted on
promotion, so it otherwise looks like a no-draft park. See
`docs/parkings/92-objdiff-reloc-form-undercount.md` before working one.

Recorded scores are the values written in the draft headers, not fresh
measurements. Re-score with `tools/test_wip_drafts.py`, which honours each
draft's `// FLAG:` line; `tools/score_wip_all.py` does not, so its numbers are
not comparable with the header values.

## Registry

Workflow:

```sh
tools/wip.py list                       # show drafts
tools/wip.py add  <addr> <draft.c>      # register a new draft
tools/wip.py activate <addr>            # temporarily wire it into the build
                                        # (iterate against objdiff; DOL will
                                        #  differ until it matches)
tools/wip.py deactivate <addr>          # unwire back to asm / byte-identity
```

| Function | Addr | Blocker / notes |
|---|---|---|
| fn_80003100 | 0x80003100 | stub |
| fn_80003254 | 0x80003254 | stub |
| fn_80003300 | 0x80003300 | stub |
| fn_80003468 | 0x80003468 | stub |
| fn_80003BE8 | 0x80003BE8 | raw-lit→symbol patch 0.7% (2026-09-06) |
| fn_80003FF8 | 0x80003FF8 | repaired 2026-09-06: m2c sinf 5-arg corruption fixed → compiles; identified axis-frame rotation-matrix builder; DIFF ~50% (PS/FP body hand-draft TODO) |
| fn_80004104 | 0x80004104 | m2c |
| fn_80004518 | 0x80004518 | raw-lit sweep 2026-09-06: 0.0% (DIFF) |
| fn_800048A4 | 0x800048A4 | m2c |
| fn_80004B4C | 0x80004B4C | m2c |
| fn_80005490 | 0x80005490 | raw-lit sweep 2026-09-06: 0.0% (DIFF) |
| fn_80005854 | 0x80005854 | m2c |
| fn_800058CC | 0x800058CC | m2c |
| fn_80005A18 | 0x80005A18 | m2c |
| fn_80005C28 | 0x80005C28 | m2c |
| fn_80005E20 | 0x80005E20 | m2c |
| fn_80005F80 | 0x80005F80 | repaired 2026-09-06: m2c cosf(0x80290000,…) corruption fixed → compiles; identified angle-tolerance decimal check (PS body hand-draft TODO, full disasm in header) |
| fn_80006094 | 0x80006094 | m2c |
| fn_800063E0 | 0x800063E0 | raw-lit sweep 2026-09-06: 0.0% (DIFF) |
| fn_80006AB0 | 0x80006AB0 | m2c |
| fn_80006C64 | 0x80006C64 | raw-lit→symbol patch 0.5% (2026-09-06) |
| fn_800073B0 | 0x800073B0 | m2c |
| fn_80007BFC | 0x80007BFC | m2c |
| fn_800086B0 | 0x800086B0 | m2c |
| fn_80009F64 | 0x80009F64 | m2c |
| fn_8000A868 | 0x8000A868 | m2c |
| fn_8000A990 | 0x8000A990 | raw-lit→symbol patch 3.4% (2026-09-06) |
| fn_8000AF90 | 0x8000AF90 | raw-lit sweep 2026-09-06: 16.2% (DIFF) |
| fn_8000B934 | 0x8000B934 | m2c |
| fn_8000BA88 | 0x8000BA88 | m2c |
| fn_8000BB70 | 0x8000BB70 | m2c |
| fn_8000BC4C | 0x8000BC4C | m2c |
| fn_8000BD04 | 0x8000BD04 | m2c |
| fn_8000C9CC | 0x8000C9CC | raw-lit sweep 2026-09-06: 20.8% (DIFF) |
| fn_8000D478 | 0x8000D478 | m2c |
| fn_8000DC80 | 0x8000DC80 | m2c |
| fn_8000EE70 | 0x8000EE70 | raw-lit→symbol patch 5.6% (2026-09-06) |
| fn_8000FAB4 | 0x8000FAB4 | m2c |
| fn_80010808 | 0x80010808 | m2c |
| fn_80010FA4 | 0x80010FA4 | m2c |
| fn_80011454 | 0x80011454 | m2c |
| fn_800119B4 | 0x800119B4 | m2c |
| fn_80011F94 | 0x80011F94 | m2c |
| fn_800122FC | 0x800122FC | m2c |
| fn_800127E4 | 0x800127E4 | raw-lit→symbol patch 15.2% (2026-09-06) |
| fn_80012948 | 0x80012948 | parked 2026-09-10: 72% (200B exact) — G/H shape: cursor=s32 copy of base via mr, owner/rcp as addi-derived index regs off base symbol, cleanup NULL is pointer-mode zero (no CSE with int 0). Remaining 14 misses are allocator register-numbering (two page materializations + chained addis vs want's single base). |
| fn_80013180 | 0x80013180 | m2c |
| fn_800135A0 | 0x800135A0 | raw-lit sweep 2026-09-06: 15.7% (DIFF) |
| fn_80013860 | 0x80013860 | m2c |
| fn_800145AC | 0x800145AC | m2c |
| fn_80014BC4 | 0x80014BC4 | m2c |
| fn_800151F4 | 0x800151F4 | m2c |
| fn_80015434 | 0x80015434 | m2c |
| fn_80015BDC | 0x80015BDC | raw-lit sweep 2026-09-06: 13.7% (DIFF) |
| fn_80016EDC | 0x80016EDC | m2c |
| fn_80017128 | 0x80017128 | raw-lit sweep 2026-09-06: 2.9% (DIFF) |
| fn_80017480 | 0x80017480 | m2c |
| fn_80017604 | 0x80017604 | parked | Vec3Store-init (fn_8001D440 to lbl_8031E664/E670/E67C): 91.2% exact 136B; only misses are arg-copy fmr chain (want fmr f3,f2; GCC emits fmr f3,f1 from every form, no flag fixes) |
| fn_80017700 | 0x80017700 | m2c |
| fn_800179D0 | 0x800179D0 | m2c |
| fn_80017E20 | 0x80017E20 | fn-ptr-cast sweep 2026-09-06: 7.6% |
| fn_800181A4 | 0x800181A4 | m2c |
| fn_80018834 | 0x80018834 | raw-lit sweep 2026-09-06: 3.8% (DIFF) |
| fn_80018E2C | 0x80018E2C | m2c |
| fn_8001908C | 0x8001908C | m2c |
| fn_80019484 | 0x80019484 | raw-lit sweep 2026-09-06: 18.8% (DIFF) |
| fn_80019E50 | 0x80019E50 | raw-lit sweep 2026-09-06: 2.2% (DIFF) |
| fn_8001ABC4 | 0x8001ABC4 | m2c |
| fn_8001AED8 | 0x8001AED8 | m2c |
| fn_8001BCA8 | 0x8001BCA8 | raw-lit sweep 2026-09-06: 8.5% (DIFF) |
| fn_8001CA68 | 0x8001CA68 | m2c |
| fn_8001CB60 | 0x8001CB60 | m2c |
| fn_8001D4FC | 0x8001D4FC | PARKED deep-recon |
| fn_8001D668 | 0x8001D668 | m2c |
| fn_8001D814 | 0x8001D814 | m2c |
| fn_8001E5DC | 0x8001E5DC | fn-ptr-cast sweep 2026-09-06: 18.4% |
| fn_8001E6F0 | 0x8001E6F0 | fn-ptr-cast sweep 2026-09-06: 25.3% |
| fn_8001FBCC | 0x8001FBCC | fn-ptr-cast sweep 2026-09-06: 20.0% |
| fn_800200D8 | 0x800200D8 | m2c |
| fn_8002062C | 0x8002062C | raw-lit sweep 2026-09-06: 10.0% (DIFF) |
| fn_80020834 | 0x80020834 | raw-lit sweep 2026-09-06: 2.9% (DIFF) |
| fn_800211D8 | 0x800211D8 | m2c |
| fn_800224B8 | 0x800224B8 | m2c |
| fn_80022A34 | 0x80022A34 | m2c |
| fn_80024774 | 0x80024774 | m2c |
| fn_80024A40 | 0x80024A40 | m2c |
| fn_80024AC4 | 0x80024AC4 | raw-lit sweep 2026-09-06: 4.1% (DIFF) |
| fn_80024DA8 | 0x80024DA8 | m2c |
| fn_80025010 | 0x80025010 | raw-lit sweep 2026-09-06: 3.0% (DIFF) |
| fn_800252C0 | 0x800252C0 | m2c |
| fn_8002532C | 0x8002532C | raw-lit sweep 2026-09-06: 4.3% (DIFF) |
| fn_800254EC | 0x800254EC | m2c |
| fn_80026140 | 0x80026140 | raw-lit sweep 2026-09-06: 1.4% (DIFF) |
| fn_800264FC | 0x800264FC | raw-lit sweep 2026-09-06: 7.6% (DIFF) |
| fn_80026670 | 0x80026670 | m2c |
| fn_8002684C | 0x8002684C | parked | deep-reconstruction: draft 44.6% (592B vs 568B); want = -0x20 frame/4 saved regs, andis. bit-test, u16 field loads, arg0+0x1C linked-list splice + flag cascade; draft middle structurally divergent |
| fn_80026D34 | 0x80026D34 | raw-lit sweep 2026-09-06: 1.3% (DIFF) |
| fn_80027720 | 0x80027720 | m2c |
| fn_80029A30 | 0x80029A30 | raw-lit sweep 2026-09-06: 1.1% (DIFF) |
| fn_8002A3E0 | 0x8002A3E0 | m2c |
| fn_8002AFB0 | 0x8002AFB0 | raw-lit sweep 2026-09-06: 2.5% (DIFF) |
| fn_8002BC78 | 0x8002BC78 | m2c |
| fn_8002BF34 | 0x8002BF34 | m2c |
| fn_8002C128 | 0x8002C128 | m2c |
| fn_8002C638 | 0x8002C638 | raw-lit sweep 2026-09-06: 1.4% (DIFF) |
| fn_8002CDE4 | 0x8002CDE4 | stub |
| fn_8002D728 | 0x8002D728 | m2c |
| fn_8002E3A8 | 0x8002E3A8 | m2c |
| fn_8002F4E0 | 0x8002F4E0 | m2c |
| fn_8002F9C4 | 0x8002F9C4 | m2c |
| fn_8002FC8C | 0x8002FC8C | m2c |
| fn_8002FFA8 | 0x8002FFA8 | m2c |
| fn_80030750 | 0x80030750 | m2c |
| fn_80030B1C | 0x80030B1C | m2c |
| fn_800313BC | 0x800313BC | m2c |
| fn_80031748 | 0x80031748 | m2c |
| fn_80031AF0 | 0x80031AF0 | m2c |
| fn_80031CEC | 0x80031CEC | m2c |
| fn_80032ACC | 0x80032ACC | m2c |
| fn_80032FB4 | 0x80032FB4 | m2c |
| fn_800340C4 | 0x800340C4 | m2c |
| fn_80034300 | 0x80034300 | m2c |
| fn_80034A28 | 0x80034A28 | m2c |
| fn_80034A90 | 0x80034A90 | m2c |
| fn_80034EB4 | 0x80034EB4 | m2c |
| fn_80035A98 | 0x80035A98 | m2c |
| fn_80035E14 | 0x80035E14 | m2c |
| fn_800363BC | 0x800363BC | m2c |
| fn_80036578 | 0x80036578 | raw-lit sweep 2026-09-06: 11.2% (DIFF) |
| fn_80036970 | 0x80036970 | m2c |
| fn_80037CF4 | 0x80037CF4 | raw-lit sweep 2026-09-06: 1.7% (DIFF) |
| fn_800381F0 | 0x800381F0 | raw-lit sweep 2026-09-06: 1.1% (DIFF) |
| fn_80038C04 | 0x80038C04 | m2c |
| fn_8003951C | 0x8003951C | m2c |
| fn_80039AD4 | 0x80039AD4 | m2c |
| fn_8003AFC8 | 0x8003AFC8 | m2c |
| fn_8003BAAC | 0x8003BAAC | m2c |
| fn_8003C2AC | 0x8003C2AC | m2c |
| fn_8003D664 | 0x8003D664 | m2c |
| fn_8003D868 | 0x8003D868 | m2c |
| fn_8003DBC0 | 0x8003DBC0 | raw-lit sweep 2026-09-06: 1.8% (DIFF) |
| fn_8003EF58 | 0x8003EF58 | m2c |
| fn_8003F208 | 0x8003F208 | m2c |
| fn_8003F360 | 0x8003F360 | m2c |
| fn_8003FE18 | 0x8003FE18 | m2c |
| fn_80040090 | 0x80040090 | m2c |
| CScreenElement_SetMorph | 0x80040734 | m2c |
| fn_80040BE8 | 0x80040BE8 | m2c |
| fn_800414B0 | 0x800414B0 | m2c |
| fn_80041564 | 0x80041564 | raw-lit sweep 2026-09-06: 8.3% (DIFF) |
| fn_800419C0 | 0x800419C0 | m2c |
| fn_80041AC0 | 0x80041AC0 | m2c |
| fn_80041D08 | 0x80041D08 | m2c |
| fn_80042924 | 0x80042924 | m2c |
| fn_80042F44 | 0x80042F44 | m2c |
| fn_800438E8 | 0x800438E8 | m2c |
| fn_80043B28 | 0x80043B28 | m2c |
| fn_80043EE8 | 0x80043EE8 | m2c |
| fn_80044110 | 0x80044110 | m2c |
| fn_80044614 | 0x80044614 | raw-lit sweep 2026-09-06: 17.3% (DIFF) |
| fn_800447B4 | 0x800447B4 | m2c |
| fn_80044D98 | 0x80044D98 | raw-lit sweep 2026-09-06: 10.5% (DIFF) |
| fn_800458E4 | 0x800458E4 | m2c |
| fn_80045DC8 | 0x80045DC8 | raw-lit sweep 2026-09-06: 14.0% (DIFF) |
| fn_80046440 | 0x80046440 | raw-lit sweep 2026-09-06: 8.0% (DIFF) |
| fn_80046B90 | 0x80046B90 | m2c |
| fn_80047DFC | 0x80047DFC | m2c |
| fn_8004A4D8 | 0x8004A4D8 | m2c |
| fn_8004B314 | 0x8004B314 | m2c |
| fn_8004B798 | 0x8004B798 | m2c |
| fn_8004BEB0 | 0x8004BEB0 | m2c |
| fn_8004BFE4 | 0x8004BFE4 | m2c |
| fn_8004C110 | 0x8004C110 | m2c |
| fn_8004C458 | 0x8004C458 | m2c |
| fn_8004C66C | 0x8004C66C | m2c |
| fn_8004CEA4 | 0x8004CEA4 | m2c |
| fn_8004E0B4 | 0x8004E0B4 | m2c |
| fn_8004E900 | 0x8004E900 | m2c |
| fn_8004EAC0 | 0x8004EAC0 | m2c |
| fn_8004FA18 | 0x8004FA18 | m2c |
| fn_80050720 | 0x80050720 | m2c |
| fn_80050868 | 0x80050868 | m2c |
| fn_80052248 | 0x80052248 | m2c |
| fn_80053834 | 0x80053834 | raw-lit sweep 2026-09-06: 9.3% (DIFF) |
| fn_80054048 | 0x80054048 | m2c |
| fn_800554D8 | 0x800554D8 | m2c |
| fn_80055EEC | 0x80055EEC | m2c |
| fn_80056B1C | 0x80056B1C | raw-lit sweep 2026-09-06: 5.4% (DIFF) |
| fn_80059048 | 0x80059048 | m2c |
| fn_8005955C | 0x8005955C | raw-lit sweep 2026-09-06: 3.3% (DIFF) |
| fn_800596E4 | 0x800596E4 | m2c |
| fn_800598C8 | 0x800598C8 | m2c |
| fn_80059C18 | 0x80059C18 | m2c |
| fn_8005A114 | 0x8005A114 | m2c |
| fn_8005A180 | 0x8005A180 | m2c |
| fn_8005A3AC | 0x8005A3AC | raw-lit sweep 2026-09-06: 3.1% (DIFF) |
| fn_8005A7E8 | 0x8005A7E8 | m2c |
| fn_8005AC44 | 0x8005AC44 | m2c |
| fn_8005AEC4 | 0x8005AEC4 | m2c |
| fn_8005B11C | 0x8005B11C | m2c |
| fn_8005B68C | 0x8005B68C | raw-lit sweep 2026-09-06: 2.6% (DIFF) |
| fn_8005BDAC | 0x8005BDAC | raw-lit sweep 2026-09-06: 2.7% (DIFF) |
| fn_8005E08C | 0x8005E08C | m2c |
| fn_8005FA84 | 0x8005FA84 | raw-lit sweep 2026-09-06: 15.4% (DIFF) |
| fn_8005FD68 | 0x8005FD68 | m2c |
| fn_80060984 | 0x80060984 | m2c |
| fn_80060D5C | 0x80060D5C | m2c |
| fn_8006167C | 0x8006167C | m2c |
| fn_80061720 | 0x80061720 | m2c |
| fn_800620EC | 0x800620EC | m2c |
| fn_80062BE8 | 0x80062BE8 | m2c |
| fn_80062F10 | 0x80062F10 | m2c |
| fn_800637C0 | 0x800637C0 | m2c |
| fn_800639E8 | 0x800639E8 | m2c |
| fn_80064294 | 0x80064294 | m2c |
| fn_80064540 | 0x80064540 | raw-lit sweep 2026-09-06: 1.2% (DIFF) |
| fn_80064640 | 0x80064640 | m2c |
| fn_80065220 | 0x80065220 | raw-lit sweep 2026-09-06: 10.1% (DIFF) |
| fn_800660F8 | 0x800660F8 | raw-lit sweep 2026-09-06: 0.3% (DIFF) |
| fn_800669D0 | 0x800669D0 | m2c |
| fn_80066EB0 | 0x80066EB0 | m2c |
| fn_8006821C | 0x8006821C | PARKED 16.9% (hand rebuild 2026-09-11): draw-order comparator (dist² cam→B − cam→A, ps-vectorized, tiebreak u8+0x12C), structure FULLY decoded in draft header; residual = PS arm-scheduling wall (docs/parkings/06 M5.0r wall #2), 20+ shapes all 12/71 |
| fn_80068338 | 0x80068338 | raw-lit sweep 2026-09-06: 5.1% (DIFF) |
| fn_80068B58 | 0x80068B58 | m2c |
| fn_80068C7C | 0x80068C7C | raw-lit sweep 2026-09-06: 0.0% (DIFF) |
| fn_80068F70 | 0x80068F70 | raw-lit sweep 2026-09-06: 3.0% (DIFF) |
| fn_800691AC | 0x800691AC | m2c |
| fn_800699C8 | 0x800699C8 | m2c |
| fn_80069F74 | 0x80069F74 | m2c |
| fn_8006A3E0 | 0x8006A3E0 | m2c |
| fn_8006A6F0 | 0x8006A6F0 | m2c |
| fn_8006AF2C | 0x8006AF2C | raw-lit sweep 2026-09-06: 0.2% (DIFF) |
| fn_8006B5FC | 0x8006B5FC | m2c |
| fn_8006BD88 | 0x8006BD88 | raw-lit sweep 2026-09-06: 8.3% (DIFF) |
| fn_8006BF04 | 0x8006BF04 | m2c |
| fn_8006CB8C | 0x8006CB8C | m2c |
| fn_8006D564 | 0x8006D564 | m2c |
| fn_8006E000 | 0x8006E000 | m2c |
| fn_8006E2FC | 0x8006E2FC | raw-lit sweep 2026-09-06: 2.1% (DIFF) |
| fn_8006E860 | 0x8006E860 | raw-lit sweep 2026-09-06: 2.9% (DIFF) |
| fn_80070138 | 0x80070138 | m2c |
| fn_8007141C | 0x8007141C | repaired 2026-09-06: m2c sinf() zero-arg corruption repaired — now compiles; DIFF tier (0.4%) |
| fn_80071F48 | 0x80071F48 | m2c |
| fn_80072BE8 | 0x80072BE8 | m2c |
| fn_80072E4C | 0x80072E4C | m2c |
| fn_80073594 | 0x80073594 | m2c |
| fn_80073A5C | 0x80073A5C | m2c |
| fn_80075978 | 0x80075978 | m2c |
| fn_80076778 | 0x80076778 | m2c |
| fn_800768A8 | 0x800768A8 | m2c |
| fn_80078104 | 0x80078104 | m2c |
| fn_800784E0 | 0x800784E0 | m2c |
| fn_80078740 | 0x80078740 | m2c |
| fn_8007899C | 0x8007899C | m2c |
| fn_80078C5C | 0x80078C5C | m2c |
| fn_80079464 | 0x80079464 | repaired 2026-09-06: dup static decls removed + 4-arg memcpy → real callee fn_8026AE28(dst,src,len) (bl 0x8026ae28 w/ crclr cr1eq) → compiles; DIFF-tier |
| fn_80079A50 | 0x80079A50 | m2c |
| fn_80079E8C | 0x80079E8C | m2c |
| fn_8007A044 | 0x8007A044 | m2c |
| fn_8007A108 | 0x8007A108 | m2c |
| fn_8007A334 | 0x8007A334 | raw-lit sweep 2026-09-06: 0.7% (DIFF) |
| fn_8007ADB8 | 0x8007ADB8 | raw-lit sweep 2026-09-06: 1.8% (DIFF) |
| fn_8007BE24 | 0x8007BE24 | m2c |
| fn_8007C148 | 0x8007C148 | raw-lit sweep 2026-09-06: 10.1% (DIFF) |
| fn_8007C39C | 0x8007C39C | raw-lit sweep 2026-09-06: 2.7% (DIFF) |
| fn_8007C6F0 | 0x8007C6F0 | m2c |
| fn_8007D5C4 | 0x8007D5C4 | raw-lit sweep 2026-09-06: 11.3% (DIFF) |
| fn_8007E030 | 0x8007E030 | m2c |
| fn_8007E1C8 | 0x8007E1C8 | m2c |
| fn_8007ED94 | 0x8007ED94 | m2c |
| fn_8007EFE0 | 0x8007EFE0 | m2c |
| fn_8007F318 | 0x8007F318 | m2c |
| fn_8007F980 | 0x8007F980 | m2c |
| fn_8007FBEC | 0x8007FBEC | raw-lit sweep 2026-09-06: 7.1% (DIFF) |
| fn_8007FF34 | 0x8007FF34 | m2c |
| fn_80080538 | 0x80080538 | m2c |
| fn_800806E4 | 0x800806E4 | m2c |
| fn_800808EC | 0x800808EC | m2c |
| fn_80080A84 | 0x80080A84 | m2c |
| fn_80080E5C | 0x80080E5C | m2c |
| fn_8008144C | 0x8008144C | m2c |
| fn_80081D9C | 0x80081D9C | m2c |
| fn_80081EC8 | 0x80081EC8 | raw-lit sweep 2026-09-06: 1.0% (DIFF) |
| fn_8008279C | 0x8008279C | m2c |
| fn_80082D8C | 0x80082D8C | m2c |
| fn_80082F38 | 0x80082F38 | m2c |
| fn_800834E0 | 0x800834E0 | m2c |
| fn_80083564 | 0x80083564 | repaired 2026-09-06: m2c sinf/cosf arity corruption repaired (3 sites; want f1-arg calls confirmed in disasm) — now compiles; DIFF tier (0.2%) |
| fn_80085394 | 0x80085394 | raw-lit sweep 2026-09-06: 2.7% (DIFF) |
| fn_8008573C | 0x8008573C | raw-lit sweep 2026-09-06: 0.1% (DIFF) |
| fn_80086B84 | 0x80086B84 | m2c |
| fn_80086D90 | 0x80086D90 | m2c |
| fn_8008757C | 0x8008757C | m2c |
| fn_80087704 | 0x80087704 | m2c |
| fn_80087EEC | 0x80087EEC | m2c |
| fn_800888F8 | 0x800888F8 | m2c |
| fn_80089368 | 0x80089368 | m2c |
| fn_80089E40 | 0x80089E40 | repaired 2026-09-06: m2c sinf 9-arg corruption repaired — now compiles; DIFF tier (0.8%) |
| fn_8008A888 | 0x8008A888 | REPAIRED 2026-09-06 (was FAIL): m2c 9-arg sinf corruption fixed (want is single-arg, angle in f1 per-site) + sinf/cosf externs; identified particle ring/disc renderer (palette-lerped RGBA + sin/cos rotation matrix + 2N-vertex triangle fan via fn_8001F0A0/F0F8/F1D4/F0F4); DIFF ~large-body — needs -mps-float PS hand-draft (doc-06). Suggested rename DrawParticleRing |

| fn_8008B428 | 0x8008B428 | raw-lit sweep 2026-09-06: 0.2% (DIFF) |
| fn_8008BA68 | 0x8008BA68 | raw-lit sweep 2026-09-06: 1.3% (DIFF) |
| fn_8008C394 | 0x8008C394 | m2c |
| fn_8008D0A4 | 0x8008D0A4 | raw-lit sweep 2026-09-06: 1.3% (DIFF) |
| fn_8008D93C | 0x8008D93C | raw-lit sweep 2026-09-06: 0.7% (DIFF) |
| fn_8008EDC0 | 0x8008EDC0 | repaired 2026-09-06: m2c sinf 9-arg corruption repaired — now compiles; DIFF tier (0.1%) |
| fn_800903F0 | 0x800903F0 | raw-lit sweep 2026-09-06: 1.4% (DIFF) |
| fn_80090958 | 0x80090958 | raw-lit sweep 2026-09-06: 0.0% (DIFF) |
| fn_80090D00 | 0x80090D00 | m2c |
| fn_800914C4 | 0x800914C4 | raw-lit sweep 2026-09-06: 2.9% (DIFF) |
| fn_80091DD4 | 0x80091DD4 | m2c |
| fn_80091E98 | 0x80091E98 | raw-lit sweep 2026-09-06: 0.0% (DIFF) |
| fn_80092154 | 0x80092154 | m2c |
| fn_80092F30 | 0x80092F30 | m2c |
| fn_80093084 | 0x80093084 | m2c |
| fn_800931C8 | 0x800931C8 | m2c |
| fn_80093CB8 | 0x80093CB8 | m2c |
| fn_80094010 | 0x80094010 | m2c |
| fn_800948E0 | 0x800948E0 | repaired 2026-09-06: m2c cosf 5-arg + (void*)-cast corruption repaired — now compiles; DIFF tier (0.2%) |
| fn_800953CC | 0x800953CC | m2c |
| fn_800955AC | 0x800955AC | m2c |
| fn_800964EC | 0x800964EC | m2c |
| fn_80096884 | 0x80096884 | m2c |
| fn_80096F20 | 0x80096F20 | raw-lit sweep 2026-09-06: 1.4% (DIFF) |
| fn_80097500 | 0x80097500 | raw-lit sweep 2026-09-06: 1.2% (DIFF) |
| fn_80097E48 | 0x80097E48 | raw-lit sweep 2026-09-06: 7.5% (DIFF) |
| fn_800988B4 | 0x800988B4 | raw-lit sweep 2026-09-06: 3.1% (DIFF) |
| fn_80098F84 | 0x80098F84 | m2c |
| fn_8009955C | 0x8009955C | m2c |
| fn_800997BC | 0x800997BC | m2c |
| fn_80099B2C | 0x80099B2C | raw-lit sweep 2026-09-06: 7.5% (DIFF) |
| fn_8009A8CC | 0x8009A8CC | m2c |
| fn_8009B3B4 | 0x8009B3B4 | m2c |
| fn_8009BAEC | 0x8009BAEC | m2c |
| fn_8009BC98 | 0x8009BC98 | m2c |
| fn_8009D3D8 | 0x8009D3D8 | raw-lit sweep 2026-09-06: 9.0% (DIFF) |
| fn_8009E004 | 0x8009E004 | m2c |
| fn_8009FF50 | 0x8009FF50 | m2c |
| fn_800A0564 | 0x800A0564 | m2c |
| fn_800A0AA8 | 0x800A0AA8 | m2c |
| fn_800A0D8C | 0x800A0D8C | raw-lit sweep 2026-09-06: 1.8% (DIFF) |
| fn_800A0E6C | 0x800A0E6C | m2c |
| fn_800A0F2C | 0x800A0F2C | m2c |
| fn_800A0FFC | 0x800A0FFC | m2c |
| fn_800A1C18 | 0x800A1C18 | m2c |
| fn_800A1DF8 | 0x800A1DF8 | m2c |
| fn_800A2B0C | 0x800A2B0C | m2c |
| fn_800A2D10 | 0x800A2D10 | m2c |
| fn_800A2EE0 | 0x800A2EE0 | m2c |
| fn_800A3778 | 0x800A3778 | m2c |
| fn_800A3E28 | 0x800A3E28 | m2c |
| fn_800A4078 | 0x800A4078 | m2c |
| fn_800A456C | 0x800A456C | m2c |
| fn_800A473C | 0x800A473C | m2c |
| fn_800A4C28 | 0x800A4C28 | m2c |
| fn_800A54AC | 0x800A54AC | raw-lit sweep 2026-09-06: 3.8% (DIFF) |
| fn_800A5E8C | 0x800A5E8C | m2c |
| fn_800A6048 | 0x800A6048 | raw-lit sweep 2026-09-06: 6.5% (DIFF) |
| fn_800A734C | 0x800A734C | m2c |
| fn_800A738C | 0x800A738C | m2c |
| fn_800A74A8 | 0x800A74A8 | m2c |
| fn_800A7B40 | 0x800A7B40 | m2c |
| fn_800A7E30 | 0x800A7E30 | m2c |
| fn_800A8328 | 0x800A8328 | m2c |
| fn_800A85A0 | 0x800A85A0 | m2c |
| fn_800A86E0 | 0x800A86E0 | m2c |
| fn_800A8D9C | 0x800A8D9C | m2c |
| fn_800A9200 | 0x800A9200 | raw-lit sweep 2026-09-06: 0.0% (DIFF) |
| fn_800A9298 | 0x800A9298 | raw-lit sweep 2026-09-06: 4.3% (DIFF) |
| fn_800A95EC | 0x800A95EC | m2c |
| fn_800A970C | 0x800A970C | m2c |
| fn_800A9E80 | 0x800A9E80 | m2c |
| fn_800AA1F4 | 0x800AA1F4 | m2c |
| fn_800AB528 | 0x800AB528 | m2c |
| fn_800ABD08 | 0x800ABD08 | m2c |
| fn_800AC884 | 0x800AC884 | m2c |
| fn_800AC93C | 0x800AC93C | m2c |
| fn_800ACAB0 | 0x800ACAB0 | m2c |
| fn_800ACC2C | 0x800ACC2C | m2c |
| fn_800AD750 | 0x800AD750 | m2c |
| fn_800AD890 | 0x800AD890 | m2c |
| fn_800AE250 | 0x800AE250 | m2c |
| fn_800AE8C4 | 0x800AE8C4 | parked | triaged: draft 456B vs want 336B (120B over!) — m2c over-expanded, deep reconstruction needed |
| fn_800AEBCC | 0x800AEBCC | m2c |
| fn_800AF6F8 | 0x800AF6F8 | m2c |
| fn_800B0A08 | 0x800B0A08 | raw-lit sweep 2026-09-06: 4.5% (DIFF) |
| fn_800B16FC | 0x800B16FC | raw-lit sweep 2026-09-06: 0.6% (DIFF) |
| fn_800B250C | 0x800B250C | m2c |
| fn_800B2748 | 0x800B2748 | raw-lit sweep 2026-09-06: 4.3% (DIFF) |
| fn_800B34E4 | 0x800B34E4 | m2c |
| fn_800B48D4 | 0x800B48D4 | raw-lit sweep 2026-09-06: 3.6% (DIFF) |
| fn_800B6578 | 0x800B6578 | m2c |
| fn_800B6694 | 0x800B6694 | m2c |
| fn_800B6A88 | 0x800B6A88 | m2c |
| fn_800B6B58 | 0x800B6B58 | m2c |
| fn_800B6FCC | 0x800B6FCC | m2c |
| fn_800B77A0 | 0x800B77A0 | m2c |
| fn_800B7F08 | 0x800B7F08 | m2c |
| fn_800B8178 | 0x800B8178 | m2c |
| fn_800B9FB4 | 0x800B9FB4 | m2c |
| fn_800BA0D8 | 0x800BA0D8 | raw-lit sweep 2026-09-06: 0.3% (DIFF) |
| fn_800BA704 | 0x800BA704 | m2c |
| fn_800BA9C8 | 0x800BA9C8 | m2c |
| fn_800BB02C | 0x800BB02C | m2c |
| fn_800BB738 | 0x800BB738 | raw-lit sweep 2026-09-06: 0.0% (DIFF) |
| fn_800BB9BC | 0x800BB9BC | m2c |
| fn_800BBEDC | 0x800BBEDC | m2c |
| fn_800BBFF8 | 0x800BBFF8 | m2c |
| fn_800BC968 | 0x800BC968 | m2c |
| fn_800BCE9C | 0x800BCE9C | raw-lit sweep 2026-09-06: 0.9% (DIFF) |
| fn_800BD518 | 0x800BD518 | m2c |
| fn_800BD770 | 0x800BD770 | m2c |
| fn_800BDAD4 | 0x800BDAD4 | m2c |
| fn_800BE020 | 0x800BE020 | m2c |
| fn_800BE410 | 0x800BE410 | m2c |
| fn_800BE854 | 0x800BE854 | m2c |
| fn_800BF7C8 | 0x800BF7C8 | m2c |
| fn_800C02E8 | 0x800C02E8 | m2c |
| fn_800C11AC | 0x800C11AC | m2c |
| fn_800C1538 | 0x800C1538 | m2c |
| fn_800C1E60 | 0x800C1E60 | m2c |
| fn_800C2320 | 0x800C2320 | m2c |
| fn_800C2AB0 | 0x800C2AB0 | m2c |
| fn_800C333C | 0x800C333C | m2c |
| fn_800C3A24 | 0x800C3A24 | raw-lit sweep 2026-09-06: 1.3% (DIFF) |
| fn_800C3CFC | 0x800C3CFC | m2c |
| fn_800C3E48 | 0x800C3E48 | raw-lit sweep 2026-09-06: 0.6% (DIFF) |
| fn_800C40DC | 0x800C40DC | raw-lit sweep 2026-09-06: 0.0% (DIFF) |
| fn_800C4414 | 0x800C4414 | m2c |
| fn_800C4560 | 0x800C4560 | m2c |
| fn_800C494C | 0x800C494C | m2c |
| fn_800C4B08 | 0x800C4B08 | raw-lit sweep 2026-09-06: 5.0% (DIFF) |
| fn_800C4E78 | 0x800C4E78 | raw-lit sweep 2026-09-06: 0.3% (DIFF) |
| fn_800C65C4 | 0x800C65C4 | m2c |
| fn_800C6860 | 0x800C6860 | raw-lit sweep 2026-09-06: 1.0% (DIFF) |
| fn_800C6EC0 | 0x800C6EC0 | m2c |
| fn_800C7234 | 0x800C7234 | m2c |
| fn_800C750C | 0x800C750C | m2c |
| fn_800C7E6C | 0x800C7E6C | m2c |
| fn_800C8110 | 0x800C8110 | m2c |
| fn_800C8390 | 0x800C8390 | m2c |
| fn_800C8948 | 0x800C8948 | m2c |
| fn_800C8D0C | 0x800C8D0C | m2c |
| fn_800C9A38 | 0x800C9A38 | m2c |
| fn_800C9E18 | 0x800C9E18 | m2c |
| fn_800CA01C | 0x800CA01C | m2c |
| fn_800CA1A8 | 0x800CA1A8 | m2c |
| fn_800CA534 | 0x800CA534 | raw-lit sweep 2026-09-06: 0.3% (DIFF) |
| fn_800CADFC | 0x800CADFC | m2c |
| fn_800CB24C | 0x800CB24C | m2c |
| fn_800CB914 | 0x800CB914 | m2c |
| fn_800CBA5C | 0x800CBA5C | m2c |
| fn_800CBCB4 | 0x800CBCB4 | m2c |
| fn_800CBF00 | 0x800CBF00 | m2c |
| fn_800CC358 | 0x800CC358 | m2c |
| fn_800CC3E0 | 0x800CC3E0 | m2c |
| fn_800CD150 | 0x800CD150 | m2c |
| fn_800CD8E4 | 0x800CD8E4 | m2c |
| fn_800CDCD8 | 0x800CDCD8 | m2c |
| fn_800CDECC | 0x800CDECC | m2c |
| fn_800CE4C4 | 0x800CE4C4 | raw-lit sweep 2026-09-06: 0.8% (DIFF) |
| fn_800CFAFC | 0x800CFAFC | m2c |
| fn_800D024C | 0x800D024C | m2c |
| fn_800D03DC | 0x800D03DC | m2c |
| fn_800D12DC | 0x800D12DC | m2c |
| fn_800D3248 | 0x800D3248 | m2c |
| fn_800D3974 | 0x800D3974 | m2c |
| fn_800D3C44 | 0x800D3C44 | m2c |
| fn_800D498C | 0x800D498C | m2c |
| fn_800D4E34 | 0x800D4E34 | m2c |
| fn_800D6030 | 0x800D6030 | m2c |
| fn_800D69A0 | 0x800D69A0 | m2c |
| fn_800D6FF0 | 0x800D6FF0 | m2c |
| fn_800D7270 | 0x800D7270 | m2c |
| fn_800D7328 | 0x800D7328 | m2c |
| fn_800D77FC | 0x800D77FC | m2c |
| fn_800D80F8 | 0x800D80F8 | m2c |
| fn_800D81F0 | 0x800D81F0 | raw-lit sweep 2026-09-06: 4.8% (DIFF) |
| fn_800D871C | 0x800D871C | m2c |
| fn_800D8908 | 0x800D8908 | m2c |
| fn_800D955C | 0x800D955C | m2c |
| fn_800D9960 | 0x800D9960 | m2c |
| fn_800D9B38 | 0x800D9B38 | m2c |
| fn_800D9DB0 | 0x800D9DB0 | m2c |
| fn_800DA6AC | 0x800DA6AC | m2c |
| fn_800DAA58 | 0x800DAA58 | m2c |
| fn_800DAC74 | 0x800DAC74 | m2c |
| fn_800DAFE4 | 0x800DAFE4 | m2c |
| fn_800DB484 | 0x800DB484 | m2c |
| fn_800DB79C | 0x800DB79C | raw-lit sweep 2026-09-06: 7.2% (DIFF) |
| fn_800DBB74 | 0x800DBB74 | m2c |
| fn_800DC484 | 0x800DC484 | m2c |
| fn_800DC680 | 0x800DC680 | raw-lit sweep 2026-09-06: 6.0% (DIFF) |
| fn_800DC868 | 0x800DC868 | m2c |
| fn_800DC9BC | 0x800DC9BC | m2c |
| fn_800DCBD4 | 0x800DCBD4 | m2c |
| fn_800DCE58 | 0x800DCE58 | m2c |
| fn_800DD1F0 | 0x800DD1F0 | m2c |
| fn_800DD3E8 | 0x800DD3E8 | m2c |
| fn_800DD9E8 | 0x800DD9E8 | m2c |
| fn_800DDAF0 | 0x800DDAF0 | m2c |
| fn_800DE63C | 0x800DE63C | m2c |
| fn_800DE6FC | 0x800DE6FC | raw-lit sweep 2026-09-06: 26.0% (DIFF) |
| fn_800DED84 | 0x800DED84 | m2c |
| fn_800DEEC4 | 0x800DEEC4 | m2c |
| fn_800DF004 | 0x800DF004 | m2c |
| fn_800DF164 | 0x800DF164 | m2c |
| fn_800DF24C | 0x800DF24C | raw-lit sweep 2026-09-06: 8.6% (DIFF) |
| fn_800DF924 | 0x800DF924 | raw-lit sweep 2026-09-06: 21.7% (DIFF) |
| fn_800DFB64 | 0x800DFB64 | m2c |
| fn_800E021C | 0x800E021C | m2c |
| fn_800E08C4 | 0x800E08C4 | m2c |
| fn_800E0C40 | 0x800E0C40 | m2c |
| fn_800E2514 | 0x800E2514 | m2c |
| fn_800E270C | 0x800E270C | m2c |
| fn_800E28F8 | 0x800E28F8 | m2c |
| fn_800E2958 | 0x800E2958 | m2c |
| fn_800E29B8 | 0x800E29B8 | m2c |
| fn_800E2A18 | 0x800E2A18 | m2c |
| fn_800E2A70 | 0x800E2A70 | m2c |
| fn_800E2AC8 | 0x800E2AC8 | m2c |
| fn_800E30F8 | 0x800E30F8 | m2c |
| fn_800E3628 | 0x800E3628 | m2c |
| fn_800E3C9C | 0x800E3C9C | raw-lit sweep 2026-09-06: 1.3% (DIFF) |
| fn_800E4314 | 0x800E4314 | m2c |
| fn_800E4794 | 0x800E4794 | m2c |
| fn_800E4990 | 0x800E4990 | m2c |
| fn_800E4AE8 | 0x800E4AE8 | m2c |
| fn_800E4F90 | 0x800E4F90 | m2c |
| fn_800E5198 | 0x800E5198 | m2c |
| fn_800E53FC | 0x800E53FC | m2c |
| fn_800E5EFC | 0x800E5EFC | raw-lit sweep 2026-09-06: 12.1% (DIFF) |
| fn_800E5FE4 | 0x800E5FE4 | raw-lit sweep 2026-09-06: 0.6% (DIFF) |
| fn_800E6A08 | 0x800E6A08 | raw-lit sweep 2026-09-06: 2.2% (DIFF) |
| fn_800E7120 | 0x800E7120 | m2c |
| fn_800E74B4 | 0x800E74B4 | m2c |
| fn_800E76B4 | 0x800E76B4 | raw-lit sweep 2026-09-06: 5.5% (DIFF) |
| fn_800E7C0C | 0x800E7C0C | m2c |
| fn_800E8060 | 0x800E8060 | m2c |
| fn_800E8AA4 | 0x800E8AA4 | m2c |
| fn_800E8E0C | 0x800E8E0C | m2c |
| fn_800E90F8 | 0x800E90F8 | m2c |
| fn_800E94C0 | 0x800E94C0 | raw-lit sweep 2026-09-06: 1.8% (DIFF) |
| fn_800E9D50 | 0x800E9D50 | m2c |
| fn_800E9F8C | 0x800E9F8C | m2c |
| fn_800EA190 | 0x800EA190 | raw-lit sweep 2026-09-06: 11.4% (DIFF) |
| fn_800EA2CC | 0x800EA2CC | m2c |
| fn_800EA3D0 | 0x800EA3D0 | m2c |
| fn_800EA4D8 | 0x800EA4D8 | m2c |
| fn_800EA7D0 | 0x800EA7D0 | m2c |
| fn_800EA994 | 0x800EA994 | m2c |
| fn_800EAD24 | 0x800EAD24 | m2c |
| fn_800EB040 | 0x800EB040 | raw-lit sweep 2026-09-06: 4.5% (DIFF) |
| fn_800EB268 | 0x800EB268 | m2c |
| fn_800EB8F8 | 0x800EB8F8 | m2c |
| fn_800EBA28 | 0x800EBA28 | m2c |
| fn_800EBC20 | 0x800EBC20 | m2c |
| fn_800EC22C | 0x800EC22C | m2c |
| fn_800EC63C | 0x800EC63C | m2c |
| fn_800EC8C4 | 0x800EC8C4 | raw-lit sweep 2026-09-06: 4.1% (DIFF) |
| fn_800ECE30 | 0x800ECE30 | m2c |
| fn_800EDB3C | 0x800EDB3C | m2c |
| fn_800EE0B8 | 0x800EE0B8 | m2c |
| fn_800EE7B0 | 0x800EE7B0 | m2c |
| fn_800EED54 | 0x800EED54 | m2c |
| fn_800EF4CC | 0x800EF4CC | parked 2026-09-10: 88.9% (72B exact) — structure cracked: *(s64*)(base+8)=0 materializes the 3 distinct zero halves, QB store written first rotates to want order [0,8,C,4], base symbol is 0x80380000 with 0x98 in disps. Last 2 misses = pure scheduler tie-break (li r10 vs ori hoist). |
| fn_800F0224 | 0x800F0224 | m2c |
| fn_800F06A8 | 0x800F06A8 | m2c |
| fn_800F0870 | 0x800F0870 | raw-lit sweep 2026-09-06: 0.5% (DIFF) |
| fn_800F1C34 | 0x800F1C34 | m2c |
| fn_800F2E00 | 0x800F2E00 | m2c |
| fn_800F2F98 | 0x800F2F98 | m2c |
| fn_800F3D7C | 0x800F3D7C | raw-lit sweep 2026-09-06: 30.2% (DIFF) |
| fn_800F429C | 0x800F429C | raw-lit sweep 2026-09-06: 17.3% (DIFF) |
| fn_800F4450 | 0x800F4450 | NEAR 77.6%: doloop CTR strength-reduction — WANT addic.+bne bottom-test, ngccc 3.9.3 always emits mtctr+bdnz for the 3-iter copy loop (13 loop shapes tried). Protos fixed the original 8.8%. |
| fn_800F47F8 | 0x800F47F8 | raw-lit sweep 2026-09-06: 10.4% (DIFF) |
| fn_800F4F78 | 0x800F4F78 | m2c |
| fn_800F5F8C | 0x800F5F8C | m2c |
| fn_800F6AD0 | 0x800F6AD0 | m2c |
| fn_800F6DE0 | 0x800F6DE0 | m2c |
| fn_800F6FF8 | 0x800F6FF8 | m2c |
| fn_800F7280 | 0x800F7280 | raw-lit sweep 2026-09-06: 0.3% (DIFF) |
| fn_800F76E8 | 0x800F76E8 | raw-lit sweep 2026-09-06: 0.1% (DIFF) |
| fn_800F8858 | 0x800F8858 | m2c |
| fn_800F94FC | 0x800F94FC | m2c |
| fn_800F9808 | 0x800F9808 | m2c |
| fn_800F9B1C | 0x800F9B1C | m2c |
| fn_800FA000 | 0x800FA000 | m2c |
| fn_800FABC0 | 0x800FABC0 | raw-lit sweep 2026-09-06: 0.7% (DIFF) |
| fn_800FAE1C | 0x800FAE1C | m2c |
| fn_800FB1A8 | 0x800FB1A8 | m2c |
| fn_800FB5B8 | 0x800FB5B8 | m2c |
| fn_800FBB14 | 0x800FBB14 | m2c |
| fn_800FBED4 | 0x800FBED4 | m2c |
| fn_800FC374 | 0x800FC374 | m2c |
| fn_800FC884 | 0x800FC884 | m2c |
| fn_800FCAA4 | 0x800FCAA4 | m2c |
| fn_800FCF18 | 0x800FCF18 | m2c |
| fn_800FD074 | 0x800FD074 | m2c |
| fn_800FD198 | 0x800FD198 | m2c |
| fn_800FD2D0 | 0x800FD2D0 | m2c |
| fn_800FD388 | 0x800FD388 | m2c |
| fn_800FD59C | 0x800FD59C | m2c |
| fn_800FD698 | 0x800FD698 | m2c |
| fn_800FD81C | 0x800FD81C | m2c |
| fn_800FD9A8 | 0x800FD9A8 | m2c |
| fn_800FDC50 | 0x800FDC50 | m2c |
| fn_800FDE38 | 0x800FDE38 | m2c |
| fn_800FE27C | 0x800FE27C | m2c |
| fn_800FE42C | 0x800FE42C | m2c |
| fn_800FE8D8 | 0x800FE8D8 | m2c |
| fn_800FF030 | 0x800FF030 | m2c |
| fn_800FF478 | 0x800FF478 | m2c |
| fn_800FFB58 | 0x800FFB58 | m2c |
| fn_800FFE78 | 0x800FFE78 | m2c |
| fn_8010048C | 0x8010048C | m2c |
| fn_80100F08 | 0x80100F08 | m2c |
| fn_80101350 | 0x80101350 | m2c |
| fn_801017C8 | 0x801017C8 | m2c |
| fn_801019C4 | 0x801019C4 | m2c |
| fn_80101B80 | 0x80101B80 | m2c |
| fn_80101C80 | 0x80101C80 | m2c |
| fn_80102444 | 0x80102444 | m2c |
| fn_80102B1C | 0x80102B1C | m2c |
| fn_80102DB0 | 0x80102DB0 | m2c |
| fn_80102E8C | 0x80102E8C | m2c |
| fn_80103044 | 0x80103044 | m2c |
| fn_80103470 | 0x80103470 | m2c |
| fn_80103678 | 0x80103678 | raw-lit sweep 2026-09-06: 0.0% (DIFF) |
| fn_80103A50 | 0x80103A50 | m2c |
| fn_80103BC4 | 0x80103BC4 | m2c |
| fn_80103D18 | 0x80103D18 | m2c |
| fn_80103F10 | 0x80103F10 | m2c |
| fn_8010411C | 0x8010411C | m2c |
| fn_801041E4 | 0x801041E4 | m2c |
| fn_80104408 | 0x80104408 | m2c |
| fn_80104668 | 0x80104668 | m2c |
| fn_80105C74 | 0x80105C74 | m2c |
| fn_80105CE8 | 0x80105CE8 | m2c |
| fn_80106608 | 0x80106608 | m2c |
| fn_8010672C | 0x8010672C | m2c |
| fn_80106AD4 | 0x80106AD4 | m2c |
| fn_801072A4 | 0x801072A4 | m2c |
| fn_801074FC | 0x801074FC | m2c |
| fn_80107B20 | 0x80107B20 | m2c |
| fn_80107D7C | 0x80107D7C | raw-lit sweep 2026-09-06: 3.5% (DIFF) |
| fn_80108230 | 0x80108230 | m2c |
| fn_80108C40 | 0x80108C40 | m2c |
| fn_80108F94 | 0x80108F94 | m2c |
| fn_801090B8 | 0x801090B8 | m2c |
| fn_80109798 | 0x80109798 | raw-lit sweep 2026-09-06: 5.3% (DIFF) |
| fn_80109CF8 | 0x80109CF8 | m2c |
| fn_8010A00C | 0x8010A00C | m2c |
| fn_8010B0AC | 0x8010B0AC | m2c |
| fn_8010B7EC | 0x8010B7EC | m2c |
| fn_8010B920 | 0x8010B920 | m2c |
| fn_8010BC58 | 0x8010BC58 | m2c |
| fn_8010C8BC | 0x8010C8BC | m2c |
| fn_8010CC40 | 0x8010CC40 | m2c |
| fn_8010D340 | 0x8010D340 | m2c |
| fn_8010F4F0 | 0x8010F4F0 | m2c |
| fn_8010F5E0 | 0x8010F5E0 | m2c |
| fn_8011036C | 0x8011036C | m2c |
| fn_801106B0 | 0x801106B0 | m2c |
| fn_80110B84 | 0x80110B84 | m2c |
| fn_801112BC | 0x801112BC | m2c |
| fn_80111380 | 0x80111380 | m2c |
| fn_801115FC | 0x801115FC | m2c |
| fn_801118C8 | 0x801118C8 | m2c |
| fn_80111BE0 | 0x80111BE0 | m2c |
| fn_801123AC | 0x801123AC | m2c |
| fn_80112860 | 0x80112860 | PARKED 70.4% (2026-09-06): QB ScriptGetBonePosition (id resolve -> bone lookup -> skeleton attach -> pos fetch -> QB_X/Y/Z writes); 3 shapes tie; residual = doc-15 arg-setup family (fn_800CA01C output-arg addi placement + node r31-vs-r29 color) — scheduler-model gap, not source-reachable |
| fn_80112C0C | 0x80112C0C | m2c |
| fn_8011334C | 0x8011334C | m2c |
| fn_80113528 | 0x80113528 | raw-lit sweep 2026-09-06: 20.5% (DIFF) |
| fn_80113CC4 | 0x80113CC4 | m2c |
| fn_80114448 | 0x80114448 | m2c |
| fn_80114D08 | 0x80114D08 | m2c |
| fn_80114F40 | 0x80114F40 | m2c |
| fn_8011562C | 0x8011562C | m2c |
| fn_80115E3C | 0x80115E3C | m2c |
| fn_80116518 | 0x80116518 | raw-lit sweep 2026-09-06: 14.7% (DIFF) |
| fn_801168CC | 0x801168CC | m2c |
| fn_80116EC0 | 0x80116EC0 | m2c |
| fn_80118334 | 0x80118334 | m2c |
| fn_80118A84 | 0x80118A84 | raw-lit sweep 2026-09-06: 22.2% (DIFF) |
| fn_80119B24 | 0x80119B24 | m2c |
| fn_80119C38 | 0x80119C38 | raw-lit sweep 2026-09-06: 12.4% (DIFF) |
| fn_8011A2AC | 0x8011A2AC | m2c |
| fn_8011AACC | 0x8011AACC | raw-lit sweep 2026-09-06: 4.6% (DIFF) |
| fn_8011ADD4 | 0x8011ADD4 | m2c |
| fn_8011BEFC | 0x8011BEFC | m2c |
| fn_8011C164 | 0x8011C164 | m2c |
| fn_8011C418 | 0x8011C418 | m2c |
| fn_8011C6F8 | 0x8011C6F8 | m2c |
| fn_8011C820 | 0x8011C820 | m2c |
| fn_8011CAF0 | 0x8011CAF0 | m2c |
| fn_8011CBFC | 0x8011CBFC | m2c |
| fn_8011CD70 | 0x8011CD70 | m2c |
| fn_8011D870 | 0x8011D870 | m2c |
| fn_8011E9A0 | 0x8011E9A0 | m2c |
| fn_8011EF98 | 0x8011EF98 | m2c |
| fn_8011F590 | 0x8011F590 | m2c |
| fn_8011FB4C | 0x8011FB4C | raw-lit sweep 2026-09-06: 1.9% (DIFF) |
| fn_8011FDD0 | 0x8011FDD0 | m2c |
| fn_801204CC | 0x801204CC | m2c |
| fn_80120B44 | 0x80120B44 | m2c |
| fn_80120D14 | 0x80120D14 | m2c |
| fn_80121D80 | 0x80121D80 | m2c |
| fn_801229CC | 0x801229CC | m2c |
| fn_80122C40 | 0x80122C40 | m2c |
| fn_80123408 | 0x80123408 | m2c |
| fn_8012399C | 0x8012399C | raw-lit sweep 2026-09-06: 22.2% (DIFF) |
| fn_80123BE0 | 0x80123BE0 | raw-lit sweep 2026-09-06: 2.6% (DIFF) |
| fn_80124110 | 0x80124110 | m2c |
| fn_80124478 | 0x80124478 | m2c |
| fn_80125600 | 0x80125600 | m2c |
| fn_801263A0 | 0x801263A0 | m2c |
| fn_80126808 | 0x80126808 | m2c |
| fn_80126A30 | 0x80126A30 | m2c |
| fn_80128B48 | 0x80128B48 | m2c |
| fn_80129068 | 0x80129068 | m2c |
| fn_801297E4 | 0x801297E4 | m2c |
| fn_80129EA0 | 0x80129EA0 | m2c |
| fn_8012A260 | 0x8012A260 | m2c |
| fn_8012A958 | 0x8012A958 | m2c |
| fn_8012B454 | 0x8012B454 | m2c |
| fn_8012B7C8 | 0x8012B7C8 | m2c |
| fn_8012BFD8 | 0x8012BFD8 | m2c |
| fn_8012CD84 | 0x8012CD84 | m2c |
| fn_8012D190 | 0x8012D190 | raw-lit sweep 2026-09-06: 0.0% (DIFF) |
| fn_8012D62C | 0x8012D62C | raw-lit sweep 2026-09-06: 0.8% (DIFF) |
| fn_8012DC0C | 0x8012DC0C | m2c |
| fn_8012DF78 | 0x8012DF78 | m2c |
| fn_8012E228 | 0x8012E228 | m2c |
| fn_8012E970 | 0x8012E970 | m2c |
| fn_8012F68C | 0x8012F68C | m2c |
| fn_8012F948 | 0x8012F948 | m2c |
| fn_8012FDC0 | 0x8012FDC0 | raw-lit sweep 2026-09-06: 6.2% (DIFF) |
| fn_801303B4 | 0x801303B4 | m2c |
| fn_80130598 | 0x80130598 | m2c |
| fn_80132458 | 0x80132458 | raw-lit sweep 2026-09-06: 1.7% (DIFF) |
| fn_80135170 | 0x80135170 | m2c |
| fn_801354B4 | 0x801354B4 | m2c |
| fn_80135E4C | 0x80135E4C | m2c |
| fn_80136888 | 0x80136888 | m2c |
| fn_80137434 | 0x80137434 | raw-lit sweep 2026-09-06: 14.5% (DIFF) |
| fn_80137CF8 | 0x80137CF8 | m2c |
| fn_80137F30 | 0x80137F30 | m2c |
| fn_8013809C | 0x8013809C | m2c |
| fn_80138BA0 | 0x80138BA0 | m2c |
| fn_8013928C | 0x8013928C | m2c |
| fn_80139450 | 0x80139450 | m2c |
| fn_80139510 | 0x80139510 | m2c |
| fn_801396A4 | 0x801396A4 | m2c |
| fn_80139BDC | 0x80139BDC | m2c |
| fn_80139EF4 | 0x80139EF4 | raw-lit sweep 2026-09-06: 0.7% (DIFF) |
| fn_8013A398 | 0x8013A398 | m2c |
| fn_8013A508 | 0x8013A508 | raw-lit sweep 2026-09-06: 8.8% (DIFF) |
| fn_8013AE40 | 0x8013AE40 | m2c |
| fn_8013B130 | 0x8013B130 | m2c |
| fn_8013B76C | 0x8013B76C | m2c |
| fn_8013B8FC | 0x8013B8FC | m2c |
| fn_8013BB68 | 0x8013BB68 | m2c |
| fn_8013BC8C | 0x8013BC8C | m2c |
| fn_8013BD50 | 0x8013BD50 | m2c |
| fn_8013BF38 | 0x8013BF38 | m2c |
| fn_8013C548 | 0x8013C548 | m2c |
| fn_8013C6F0 | 0x8013C6F0 | m2c |
| fn_8013C950 | 0x8013C950 | m2c |
| fn_8013CC84 | 0x8013CC84 | m2c |
| fn_8013DA08 | 0x8013DA08 | m2c |
| fn_8013DC7C | 0x8013DC7C | m2c |
| fn_8013E364 | 0x8013E364 | m2c |
| fn_8013EA38 | 0x8013EA38 | m2c |
| fn_8013ED3C | 0x8013ED3C | m2c |
| fn_8013F1A4 | 0x8013F1A4 | m2c |
| fn_8013F3D0 | 0x8013F3D0 | m2c |
| fn_8013F818 | 0x8013F818 | m2c |
| fn_8013FA3C | 0x8013FA3C | m2c |
| fn_801403D8 | 0x801403D8 | m2c |
| fn_801410E0 | 0x801410E0 | m2c |
| fn_80141C54 | 0x80141C54 | m2c |
| fn_80141FAC | 0x80141FAC | m2c |
| fn_801427A4 | 0x801427A4 | m2c |
| fn_80143258 | 0x80143258 | m2c |
| fn_801440DC | 0x801440DC | raw-lit sweep 2026-09-06: 5.7% (DIFF) |
| fn_80145610 | 0x80145610 | raw-lit sweep 2026-09-06: 1.8% (DIFF) |
| fn_80145C14 | 0x80145C14 | raw-lit sweep 2026-09-06: 8.7% (DIFF) |
| fn_80146EC8 | 0x80146EC8 | m2c |
| fn_8014DD04 | 0x8014DD04 | m2c |
| fn_8014DDFC | 0x8014DDFC | m2c |
| fn_8014E114 | 0x8014E114 | m2c |
| fn_8014F338 | 0x8014F338 | m2c |
| fn_8015080C | 0x8015080C | m2c |
| fn_80150B94 | 0x80150B94 | m2c |
| fn_80151DF8 | 0x80151DF8 | m2c |
| fn_80152034 | 0x80152034 | m2c |
| fn_80152220 | 0x80152220 | m2c |
| fn_8015307C | 0x8015307C | m2c |
| fn_80153844 | 0x80153844 | m2c |
| fn_801547DC | 0x801547DC | m2c |
| fn_80155AA4 | 0x80155AA4 | m2c |
| fn_80155FF8 | 0x80155FF8 | m2c |
| fn_801562A0 | 0x801562A0 | raw-lit sweep 2026-09-06: 7.6% (DIFF) |
| fn_80156658 | 0x80156658 | m2c |
| fn_80156CB0 | 0x80156CB0 | m2c |
| fn_80156EBC | 0x80156EBC | m2c |
| fn_80157248 | 0x80157248 | m2c |
| fn_801575E0 | 0x801575E0 | m2c |
| fn_80158B7C | 0x80158B7C | m2c |
| fn_80158C2C | 0x80158C2C | m2c |
| fn_80158EC8 | 0x80158EC8 | m2c |
| fn_80159078 | 0x80159078 | m2c |
| fn_801596D4 | 0x801596D4 | m2c |
| fn_80159894 | 0x80159894 | m2c |
| fn_80159A48 | 0x80159A48 | m2c |
| fn_8015AE3C | 0x8015AE3C | m2c |
| fn_8015B698 | 0x8015B698 | m2c |
| fn_8015D4E4 | 0x8015D4E4 | m2c |
| fn_8015DD90 | 0x8015DD90 | m2c |
| fn_8015E868 | 0x8015E868 | m2c |
| fn_8015F308 | 0x8015F308 | m2c |
| fn_8015F96C | 0x8015F96C | m2c |
| fn_801609DC | 0x801609DC | m2c |
| fn_80160CEC | 0x80160CEC | m2c |
| fn_80161608 | 0x80161608 | m2c |
| fn_80161880 | 0x80161880 | m2c |
| fn_801622D4 | 0x801622D4 | m2c |
| fn_801628FC | 0x801628FC | m2c |
| fn_80162AC4 | 0x80162AC4 | m2c |
| fn_80162CB4 | 0x80162CB4 | m2c |
| fn_80163100 | 0x80163100 | m2c |
| fn_801634A8 | 0x801634A8 | m2c |
| fn_8016376C | 0x8016376C | m2c |
| fn_80163BC8 | 0x80163BC8 | m2c |
| fn_80163E3C | 0x80163E3C | m2c |
| fn_801644F4 | 0x801644F4 | m2c |
| fn_80164ABC | 0x80164ABC | m2c |
| fn_80166640 | 0x80166640 | m2c |
| fn_80167408 | 0x80167408 | m2c |
| fn_80167818 | 0x80167818 | m2c |
| fn_80168298 | 0x80168298 | m2c |
| fn_801695A0 | 0x801695A0 | m2c |
| fn_8016A480 | 0x8016A480 | raw-lit sweep 2026-09-06: 11.1% (DIFF) |
| fn_8016AB1C | 0x8016AB1C | m2c |
| fn_8016AEC4 | 0x8016AEC4 | m2c |
| fn_8016C348 | 0x8016C348 | m2c |
| fn_8016CD30 | 0x8016CD30 | m2c |
| fn_8016D470 | 0x8016D470 | m2c |
| fn_8016DAC0 | 0x8016DAC0 | m2c |
| fn_8016E0D8 | 0x8016E0D8 | m2c |
| fn_8016E1B4 | 0x8016E1B4 | m2c |
| fn_8016E32C | 0x8016E32C | m2c |
| fn_8016F69C | 0x8016F69C | m2c |
| fn_8016F820 | 0x8016F820 | m2c |
| fn_80170064 | 0x80170064 | m2c |
| fn_80170444 | 0x80170444 | m2c |
| fn_80170670 | 0x80170670 | m2c |
| fn_80170930 | 0x80170930 | m2c |
| fn_80170FB4 | 0x80170FB4 | m2c |
| fn_80171288 | 0x80171288 | m2c |
| fn_80171958 | 0x80171958 | raw-lit sweep 2026-09-06: 7.2% (DIFF) |
| fn_80172A90 | 0x80172A90 | PARKED @93.6% flagged (2026-09-06, unchanged): skater-state turntable/decay handler identified (state-list walk + net-king gate + fn_800144C8 scale + 2^52-bias diff -> fn_80173C5C); tail sched1 interleave needs -mps-float PS hand-draft (doc-06/doc-15) |
| fn_80172ED4 | 0x80172ED4 | m2c |
| fn_80173024 | 0x80173024 | m2c |
| fn_80173538 | 0x80173538 | m2c |
| fn_801740D8 | 0x801740D8 | m2c |
| fn_80174814 | 0x80174814 | m2c |
| fn_80174B14 | 0x80174B14 | m2c |
| fn_801751B8 | 0x801751B8 | m2c |
| fn_80175690 | 0x80175690 | m2c |
| fn_80175AFC | 0x80175AFC | m2c |
| fn_80175F38 | 0x80175F38 | m2c |
| fn_80176B78 | 0x80176B78 | m2c |
| fn_80177610 | 0x80177610 | m2c |
| fn_8017792C | 0x8017792C | m2c |
| fn_80177D1C | 0x80177D1C | m2c |
| fn_80177F38 | 0x80177F38 | m2c |
| fn_80178520 | 0x80178520 | m2c |
| fn_801786EC | 0x801786EC | m2c |
| fn_80178A28 | 0x80178A28 | m2c |
| fn_801792D4 | 0x801792D4 | m2c |
| fn_8017981C | 0x8017981C | m2c |
| fn_8017A3F8 | 0x8017A3F8 | m2c |
| fn_8017AC00 | 0x8017AC00 | m2c |
| fn_8017B094 | 0x8017B094 | m2c |
| fn_8017B390 | 0x8017B390 | m2c |
| fn_8017B444 | 0x8017B444 | m2c |
| fn_8017B7EC | 0x8017B7EC | m2c |
| fn_8017BB28 | 0x8017BB28 | m2c |
| fn_8017C1A8 | 0x8017C1A8 | m2c |
| fn_8017C2CC | 0x8017C2CC | m2c |
| fn_8017C8F4 | 0x8017C8F4 | m2c |
| fn_8017E1EC | 0x8017E1EC | m2c |
| fn_8017E4C8 | 0x8017E4C8 | m2c |
| fn_8017E6A4 | 0x8017E6A4 | m2c |
| fn_8017EF1C | 0x8017EF1C | m2c |
| fn_8017F614 | 0x8017F614 | m2c |
| fn_8017FC8C | 0x8017FC8C | m2c |
| fn_80180390 | 0x80180390 | m2c |
| fn_801805DC | 0x801805DC | m2c |
| fn_801808C8 | 0x801808C8 | m2c |
| fn_80180A50 | 0x80180A50 | raw-lit sweep 2026-09-06: 10.4% (DIFF) |
| fn_80180C44 | 0x80180C44 | m2c |
| fn_80181014 | 0x80181014 | m2c |
| fn_80181300 | 0x80181300 | m2c |
| fn_801815EC | 0x801815EC | m2c |
| fn_801819E4 | 0x801819E4 | m2c |
| fn_80181DA0 | 0x80181DA0 | m2c |
| fn_8018223C | 0x8018223C | m2c |
| fn_80182558 | 0x80182558 | m2c |
| fn_801826E8 | 0x801826E8 | m2c |
| fn_80184170 | 0x80184170 | m2c |
| fn_801842C0 | 0x801842C0 | m2c |
| fn_801860B8 | 0x801860B8 | raw-lit sweep 2026-09-06: 5.5% (DIFF) |
| fn_80187C14 | 0x80187C14 | m2c |
| fn_8018B6F8 | 0x8018B6F8 | m2c |
| fn_8018C080 | 0x8018C080 | m2c |
| fn_8018C580 | 0x8018C580 | m2c |
| fn_8018CAF4 | 0x8018CAF4 | m2c |
| fn_8018CC18 | 0x8018CC18 | m2c |
| fn_8018DFE0 | 0x8018DFE0 | m2c |
| fn_8018EF54 | 0x8018EF54 | m2c |
| fn_8018F2EC | 0x8018F2EC | m2c |
| fn_8018FAE8 | 0x8018FAE8 | m2c |
| fn_801903B8 | 0x801903B8 | m2c |
| fn_80190ACC | 0x80190ACC | m2c |
| fn_80191260 | 0x80191260 | m2c |
| fn_801919C0 | 0x801919C0 | raw-lit sweep 2026-09-06: 14.4% (DIFF) |
| fn_80191CC0 | 0x80191CC0 | m2c |
| fn_80192854 | 0x80192854 | m2c |
| fn_80192D24 | 0x80192D24 | m2c |
| fn_801937EC | 0x801937EC | raw-lit sweep 2026-09-06: 3.9% (DIFF) |
| fn_80194988 | 0x80194988 | NEAR 94.2% hand — callee-saved register-home rotation (r18-23 shuffle), allocator artifact. draft notes |
| fn_80194DD4 | 0x80194DD4 | m2c |
| fn_80195B14 | 0x80195B14 | m2c |
| fn_80196ACC | 0x80196ACC | m2c |
| fn_80196EF8 | 0x80196EF8 | m2c |
| fn_801979CC | 0x801979CC | m2c |
| fn_80197DB8 | 0x80197DB8 | m2c |
| fn_80198D70 | 0x80198D70 | m2c |
| fn_801996BC | 0x801996BC | m2c |
| fn_8019A49C | 0x8019A49C | m2c |
| fn_8019AA88 | 0x8019AA88 | m2c |
| fn_8019B2A0 | 0x8019B2A0 | m2c |
| fn_8019B84C | 0x8019B84C | raw-lit sweep 2026-09-06: 17.2% (DIFF) |
| fn_8019BD3C | 0x8019BD3C | m2c |
| fn_8019D00C | 0x8019D00C | m2c |
| fn_8019D62C | 0x8019D62C | m2c |
| fn_8019D7FC | 0x8019D7FC | m2c |
| fn_8019DCE8 | 0x8019DCE8 | m2c |
| fn_8019DF10 | 0x8019DF10 | m2c |
| fn_8019E194 | 0x8019E194 | m2c |
| fn_8019EB40 | 0x8019EB40 | m2c |
| fn_8019F090 | 0x8019F090 | m2c |
| fn_8019FB9C | 0x8019FB9C | m2c |
| fn_8019FC70 | 0x8019FC70 | m2c |
| fn_801A058C | 0x801A058C | m2c |
| fn_801A0824 | 0x801A0824 | m2c |
| fn_801A0A28 | 0x801A0A28 | m2c |
| fn_801A128C | 0x801A128C | m2c |
| fn_801A1998 | 0x801A1998 | m2c |
| fn_801A1C7C | 0x801A1C7C | m2c |
| fn_801A3ABC | 0x801A3ABC | m2c |
| fn_801A3E4C | 0x801A3E4C | m2c |
| fn_801A46F8 | 0x801A46F8 | m2c |
| fn_801A4B88 | 0x801A4B88 | m2c |
| fn_801A59B4 | 0x801A59B4 | m2c |
| fn_801A6984 | 0x801A6984 | raw-lit sweep 2026-09-06: 6.7% (DIFF) |
| fn_801A71DC | 0x801A71DC | m2c |
| fn_801A77EC | 0x801A77EC | m2c |
| fn_801A8A6C | 0x801A8A6C | m2c |
| fn_801A8E5C | 0x801A8E5C | m2c |
| fn_801A920C | 0x801A920C | m2c |
| fn_801AA2D4 | 0x801AA2D4 | m2c |
| fn_801AACA4 | 0x801AACA4 | m2c |
| fn_801AB08C | 0x801AB08C | m2c |
| fn_801ABDB0 | 0x801ABDB0 | m2c |
| fn_801AD5DC | 0x801AD5DC | m2c |
| fn_801AE11C | 0x801AE11C | m2c |
| fn_801AE4CC | 0x801AE4CC | m2c |
| fn_801AE5A4 | 0x801AE5A4 | m2c |
| fn_801AE688 | 0x801AE688 | m2c |
| fn_801AEBA4 | 0x801AEBA4 | m2c |
| fn_801AFA18 | 0x801AFA18 | m2c |
| fn_801B1278 | 0x801B1278 | m2c |
| fn_801B17E4 | 0x801B17E4 | m2c |
| fn_801B1D00 | 0x801B1D00 | m2c |
| fn_801B2B10 | 0x801B2B10 | raw-lit sweep 2026-09-06: 11.8% (DIFF) |
| fn_801B36FC | 0x801B36FC | m2c |
| fn_801B3EE8 | 0x801B3EE8 | m2c |
| fn_801B4278 | 0x801B4278 | raw-lit sweep 2026-09-06: 4.0% (DIFF) |
| fn_801B4664 | 0x801B4664 | repaired 2026-09-06: missing dolphin/SN_PS.h include added (was parse-error FAIL) — now compiles; DIFF tier; still parked on doc-06/15/28 walls (2.0 -mps-float%) |
| fn_801B4BD0 | 0x801B4BD0 | m2c |
| fn_801B4E84 | 0x801B4E84 | m2c |
| fn_801B52D0 | 0x801B52D0 | m2c |
| fn_801B56C8 | 0x801B56C8 | m2c |
| fn_801B5BF8 | 0x801B5BF8 | hand; 2026-09-06: 88.7% NEAR (label-web + psq interleave residual, un-FAILed via FLAG) |
| fn_801B5EE8 | 0x801B5EE8 | m2c |
| fn_801B6A60 | 0x801B6A60 | raw-lit sweep 2026-09-06: 0.0% (FAIL) |
| fn_801B6F8C | 0x801B6F8C | m2c |
| fn_801B7484 | 0x801B7484 | m2c |
| fn_801B7A90 | 0x801B7A90 | m2c |
| fn_801B82F0 | 0x801B82F0 | m2c |
| fn_801B8DE0 | 0x801B8DE0 | m2c |
| fn_801B9444 | 0x801B9444 | m2c |
| fn_801B9FD0 | 0x801B9FD0 | raw-lit sweep 2026-09-06: 2.3% (DIFF) |
| fn_801BA464 | 0x801BA464 | m2c |
| fn_801BBAE0 | 0x801BBAE0 | m2c |
| fn_801BED44 | 0x801BED44 | m2c |
| fn_801BEE7C | 0x801BEE7C | m2c |
| fn_801BF5B8 | 0x801BF5B8 | m2c |
| fn_801C0BA0 | 0x801C0BA0 | m2c |
| fn_801C0C94 | 0x801C0C94 | m2c |
| fn_801C0FF4 | 0x801C0FF4 | m2c |
| fn_801C1364 | 0x801C1364 | m2c |
| fn_801C17F4 | 0x801C17F4 | m2c |
| fn_801C1C30 | 0x801C1C30 | m2c |
| fn_801C211C | 0x801C211C | m2c |
| fn_801C23E8 | 0x801C23E8 | m2c |
| fn_801C2870 | 0x801C2870 | m2c |
| fn_801C2B04 | 0x801C2B04 | m2c |
| fn_801C30FC | 0x801C30FC | m2c |
| fn_801C4228 | 0x801C4228 | m2c |
| fn_801C4F98 | 0x801C4F98 | m2c |
| fn_801C5C0C | 0x801C5C0C | m2c |
| fn_801C5F4C | 0x801C5F4C | raw-lit sweep 2026-09-06: 3.5% (DIFF) |
| fn_801C66B4 | 0x801C66B4 | m2c |
| fn_801C6B00 | 0x801C6B00 | m2c |
| fn_801C6F88 | 0x801C6F88 | m2c |
| fn_801C7ABC | 0x801C7ABC | m2c |
| fn_801C7FF0 | 0x801C7FF0 | m2c |
| fn_801C84E8 | 0x801C84E8 | m2c |
| fn_801C8DEC | 0x801C8DEC | m2c |
| fn_801C9464 | 0x801C9464 | m2c |
| fn_801C9F40 | 0x801C9F40 | m2c |
| fn_801CA5C8 | 0x801CA5C8 | m2c |
| fn_801CA970 | 0x801CA970 | m2c |
| fn_801CB0C4 | 0x801CB0C4 | SN_PS include confirmed; DIFF 2.5% under -mps-float (doc-06 park) |
| fn_801CB7B8 | 0x801CB7B8 | m2c |
| fn_801CBBD0 | 0x801CBBD0 | m2c |
| fn_801CBC78 | 0x801CBC78 | m2c |
| fn_801CC75C | 0x801CC75C | m2c |
| fn_801CCB68 | 0x801CCB68 | repaired 2026-09-06: m2c memset 4-arg corruption repaired — now compiles; DIFF tier (5.6%) |
| fn_801CD414 | 0x801CD414 | m2c |
| fn_801CDE9C | 0x801CDE9C | m2c |
| fn_801CE098 | 0x801CE098 | m2c |
| fn_801CE3E4 | 0x801CE3E4 | m2c |
| fn_801CE918 | 0x801CE918 | m2c |
| fn_801CEB2C | 0x801CEB2C | m2c |
| fn_801CEE28 | 0x801CEE28 | m2c |
| fn_801CF0E4 | 0x801CF0E4 | raw-lit sweep 2026-09-06: 0.0% (DIFF) |
| fn_801CF7F8 | 0x801CF7F8 | m2c |
| fn_801CF9B0 | 0x801CF9B0 | m2c |
| fn_801CFBE8 | 0x801CFBE8 | m2c |
| fn_801D0214 | 0x801D0214 | m2c |
| fn_801D0900 | 0x801D0900 | m2c |
| fn_801D0EF8 | 0x801D0EF8 | m2c |
| fn_801D17E4 | 0x801D17E4 | m2c |
| fn_801D19E0 | 0x801D19E0 | FAIL: ngccc ICE expr.c:2802 on __ps_t field access through char* ptr (obj->unk0xC0) — doc-06; needs proper __ps_t-typed member or union, not a cast |
| fn_801D1B3C | 0x801D1B3C | m2c |
| fn_801D2D94 | 0x801D2D94 | m2c |
| fn_801D2F40 | 0x801D2F40 | m2c |
| fn_801D30E0 | 0x801D30E0 | m2c |
| fn_801D33F4 | 0x801D33F4 | m2c |
| fn_801D3C04 | 0x801D3C04 | m2c |
| fn_801D3D18 | 0x801D3D18 | m2c |
| fn_801D488C | 0x801D488C | m2c |
| fn_801D4D74 | 0x801D4D74 | m2c |
| fn_801D5058 | 0x801D5058 | m2c |
| fn_801D59F8 | 0x801D59F8 | m2c |
| fn_801D60F4 | 0x801D60F4 | m2c |
| fn_801D62AC | 0x801D62AC | m2c |
| fn_801D657C | 0x801D657C | m2c |
| fn_801D6810 | 0x801D6810 | m2c |
| fn_801D7528 | 0x801D7528 | m2c |
| fn_801D8748 | 0x801D8748 | raw-lit sweep 2026-09-06: 0.7% (DIFF) |
| fn_801D8BA0 | 0x801D8BA0 | m2c |
| fn_801D99B4 | 0x801D99B4 | m2c |
| fn_801DA420 | 0x801DA420 | m2c |
| fn_801DA88C | 0x801DA88C | raw-lit sweep 2026-09-06: 0.4% (DIFF) |
| fn_801DB148 | 0x801DB148 | m2c |
| fn_801DB310 | 0x801DB310 | m2c |
| fn_801DB820 | 0x801DB820 | m2c |
| fn_801DBCAC | 0x801DBCAC | m2c |
| fn_801DCD50 | 0x801DCD50 | m2c |
| fn_801DD184 | 0x801DD184 | m2c |
| fn_801DDA34 | 0x801DDA34 | m2c |
| fn_801DE248 | 0x801DE248 | raw-lit sweep 2026-09-06: 1.1% (DIFF) |
| fn_801DE50C | 0x801DE50C | raw-lit sweep 2026-09-06: 1.6% (DIFF) |
| fn_801DE8BC | 0x801DE8BC | m2c |
| fn_801DEADC | 0x801DEADC | m2c |
| fn_801DFE50 | 0x801DFE50 | m2c |
| fn_801E0974 | 0x801E0974 | m2c |
| fn_801E1224 | 0x801E1224 | m2c |
| fn_801E1A3C | 0x801E1A3C | m2c |
| fn_801E1D30 | 0x801E1D30 | m2c |
| fn_801E2624 | 0x801E2624 | m2c |
| fn_801E2BD4 | 0x801E2BD4 | raw-lit sweep 2026-09-06: 0.3% (DIFF) |
| fn_801E3128 | 0x801E3128 | m2c |
| fn_801E3B94 | 0x801E3B94 | m2c |
| fn_801E3D70 | 0x801E3D70 | m2c |
| fn_801E3FB0 | 0x801E3FB0 | ngccc ICE (expr.c:2802) under -mps-float too — doc-06 PS park confirmed |
| fn_801E4178 | 0x801E4178 | m2c |
| fn_801E5B18 | 0x801E5B18 | m2c |
| fn_801E6440 | 0x801E6440 | raw-lit sweep 2026-09-06: 0.7% (DIFF) |
| fn_801E6F54 | 0x801E6F54 | m2c |
| fn_801E72F0 | 0x801E72F0 | m2c |
| fn_801E8E04 | 0x801E8E04 | m2c |
| fn_801E97CC | 0x801E97CC | m2c |
| fn_801EB624 | 0x801EB624 | DIFF 17.2% under -mps-float (doc-06 park) |
| fn_801EBDD8 | 0x801EBDD8 | m2c |
| fn_801ED130 | 0x801ED130 | m2c |
| fn_801ED5F0 | 0x801ED5F0 | m2c |
| fn_801EDD7C | 0x801EDD7C | m2c |
| fn_801EE5AC | 0x801EE5AC | m2c |
| fn_801EF44C | 0x801EF44C | m2c |
| fn_801EF828 | 0x801EF828 | m2c |
| fn_801EFE18 | 0x801EFE18 | m2c |
| fn_801F203C | 0x801F203C | m2c |
| fn_801F21A8 | 0x801F21A8 | m2c |
| fn_801F23F0 | 0x801F23F0 | m2c |
| fn_801F2AE0 | 0x801F2AE0 | m2c |
| fn_801F36B0 | 0x801F36B0 | m2c |
| fn_801F3A1C | 0x801F3A1C | m2c |
| fn_801F3D30 | 0x801F3D30 | m2c |
| fn_801F4858 | 0x801F4858 | m2c |
| fn_801F4C88 | 0x801F4C88 | m2c |
| fn_801F4F88 | 0x801F4F88 | m2c |
| fn_801F50B0 | 0x801F50B0 | m2c |
| fn_801F5374 | 0x801F5374 | m2c |
| fn_801F5A0C | 0x801F5A0C | m2c |
| fn_801F5B38 | 0x801F5B38 | m2c |
| fn_801F5CC0 | 0x801F5CC0 | m2c |
| fn_801F5E44 | 0x801F5E44 | m2c |
| fn_801F6EC8 | 0x801F6EC8 | m2c |
| fn_801F7608 | 0x801F7608 | m2c |
| fn_801F77B8 | 0x801F77B8 | m2c |
| fn_801F7B04 | 0x801F7B04 | m2c |
| fn_801F7FEC | 0x801F7FEC | m2c |
| fn_801F8250 | 0x801F8250 | m2c |
| fn_801F8430 | 0x801F8430 | m2c |
| fn_801F8768 | 0x801F8768 | raw-lit sweep 2026-09-06: 3.1% (DIFF) |
| fn_801F8C14 | 0x801F8C14 | m2c |
| fn_801F8DA8 | 0x801F8DA8 | m2c |
| fn_801F9C64 | 0x801F9C64 | m2c |
| fn_801FA1EC | 0x801FA1EC | m2c |
| fn_801FA74C | 0x801FA74C | m2c |
| fn_801FB6B4 | 0x801FB6B4 | m2c |
| fn_801FBF90 | 0x801FBF90 | m2c |
| fn_801FC8CC | 0x801FC8CC | PS hand-draft 2026-09-06: 91.3% (NEAR; psq interleave + label-web residual) |
| fn_801FCA3C | 0x801FCA3C | m2c |
| fn_801FD238 | 0x801FD238 | m2c |
| fn_801FDC38 | 0x801FDC38 | m2c |
| fn_801FDE4C | 0x801FDE4C | m2c |
| fn_801FDFAC | 0x801FDFAC | m2c |
| fn_801FECF8 | 0x801FECF8 | m2c |
| fn_801FEF08 | 0x801FEF08 | m2c |
| fn_801FF1D4 | 0x801FF1D4 | m2c |
| fn_801FF57C | 0x801FF57C | m2c |
| fn_801FFEE8 | 0x801FFEE8 | raw-lit sweep 2026-09-06: 2.8% (DIFF) |
| fn_80200264 | 0x80200264 | m2c |
| fn_802003A0 | 0x802003A0 | m2c |
| fn_80200628 | 0x80200628 | raw-lit sweep 2026-09-06: 0.9% (DIFF) |
| fn_80200DA0 | 0x80200DA0 | m2c |
| fn_802011B8 | 0x802011B8 | m2c |
| fn_80201CCC | 0x80201CCC | m2c |
| fn_80202654 | 0x80202654 | m2c |
| fn_8020309C | 0x8020309C | raw-lit sweep 2026-09-06: 9.7% (DIFF) |
| fn_802032CC | 0x802032CC | m2c |
| fn_80203574 | 0x80203574 | m2c |
| fn_80203698 | 0x80203698 | m2c |
| fn_802038C8 | 0x802038C8 | m2c |
| fn_80203BB8 | 0x80203BB8 | raw-lit sweep 2026-09-06: 22.0% (DIFF) |
| fn_80203F90 | 0x80203F90 | m2c |
| fn_80204294 | 0x80204294 | m2c |
| fn_80204550 | 0x80204550 | m2c |
| fn_80204928 | 0x80204928 | m2c |
| fn_80204E30 | 0x80204E30 | m2c |
| fn_80205668 | 0x80205668 | m2c |
| fn_80205DE8 | 0x80205DE8 | m2c |
| fn_802063D0 | 0x802063D0 | m2c |
| fn_80206658 | 0x80206658 | m2c |
| fn_80207990 | 0x80207990 | raw-lit sweep 2026-09-06: 3.1% (DIFF) |
| fn_802093E8 | 0x802093E8 | m2c |
| fn_8020A0F4 | 0x8020A0F4 | m2c |
| fn_8020B280 | 0x8020B280 | m2c |
| fn_8020CDF0 | 0x8020CDF0 | raw-lit sweep 2026-09-06: 6.0% (DIFF) |
| fn_8020D1F4 | 0x8020D1F4 | m2c |
| fn_8020D530 | 0x8020D530 | m2c |
| fn_8020D764 | 0x8020D764 | m2c |
| fn_8020E014 | 0x8020E014 | m2c |
| fn_8020ED80 | 0x8020ED80 | raw-lit sweep 2026-09-06: 5.8% (DIFF) |
| fn_8020F078 | 0x8020F078 | m2c |
| fn_8020F1D4 | 0x8020F1D4 | m2c |
| fn_8020F5F8 | 0x8020F5F8 | m2c |
| fn_8020F938 | 0x8020F938 | m2c |
| fn_8020FB80 | 0x8020FB80 | m2c |
| fn_802101D0 | 0x802101D0 | m2c |
| fn_80210438 | 0x80210438 | m2c |
| fn_802109D8 | 0x802109D8 | raw-lit sweep 2026-09-06: 2.4% (DIFF) |
| fn_80210D10 | 0x80210D10 | m2c |
| fn_80210F58 | 0x80210F58 | m2c |
| fn_802113EC | 0x802113EC | raw-lit sweep 2026-09-06: 3.0% (DIFF) |
| fn_8021187C | 0x8021187C | m2c |
| fn_80211B70 | 0x80211B70 | m2c |
| fn_80211E5C | 0x80211E5C | m2c |
| fn_80211FE8 | 0x80211FE8 | m2c |
| fn_80212490 | 0x80212490 | m2c |
| fn_80212C54 | 0x80212C54 | m2c |
| fn_80212F20 | 0x80212F20 | m2c |
| fn_80213318 | 0x80213318 | m2c |
| fn_802134A0 | 0x802134A0 | raw-lit sweep 2026-09-06: 0.3% (DIFF) |
| fn_80213E48 | 0x80213E48 | m2c |
| fn_80213FA8 | 0x80213FA8 | m2c |
| fn_80214308 | 0x80214308 | m2c |
| fn_802144B8 | 0x802144B8 | m2c |
| fn_80214690 | 0x80214690 | m2c |
| fn_80214A30 | 0x80214A30 | m2c |
| fn_80214C90 | 0x80214C90 | m2c |
| fn_80214E24 | 0x80214E24 | m2c |
| fn_80214FF0 | 0x80214FF0 | m2c |
| fn_802151B0 | 0x802151B0 | m2c |
| fn_8021546C | 0x8021546C | m2c |
| fn_80215C30 | 0x80215C30 | m2c |
| fn_80215F28 | 0x80215F28 | raw-lit sweep 2026-09-06: 6.0% (DIFF) |
| fn_80216980 | 0x80216980 | m2c |
| fn_80216E24 | 0x80216E24 | m2c |
| fn_80217234 | 0x80217234 | m2c |
| fn_80217488 | 0x80217488 | m2c |
| fn_802183E0 | 0x802183E0 | m2c |
| fn_80218564 | 0x80218564 | m2c |
| fn_80218EB0 | 0x80218EB0 | m2c |
| fn_80219134 | 0x80219134 | m2c |
| fn_80219B18 | 0x80219B18 | m2c |
| fn_8021A910 | 0x8021A910 | m2c |
| fn_8021B574 | 0x8021B574 | m2c |
| fn_8021B6C8 | 0x8021B6C8 | m2c |
| fn_8021B9E8 | 0x8021B9E8 | m2c |
| fn_8021BC54 | 0x8021BC54 | m2c |
| fn_8021C1B4 | 0x8021C1B4 | m2c |
| fn_8021C4FC | 0x8021C4FC | m2c |
| fn_8021C9B8 | 0x8021C9B8 | m2c |
| fn_8021CDA0 | 0x8021CDA0 | m2c |
| fn_8021CEC0 | 0x8021CEC0 | m2c |
| fn_8021D184 | 0x8021D184 | m2c |
| fn_8021D2C4 | 0x8021D2C4 | m2c |
| fn_8021DAD4 | 0x8021DAD4 | m2c |
| fn_8021E18C | 0x8021E18C | m2c |
| fn_8021EB8C | 0x8021EB8C | m2c |
| fn_8021ED5C | 0x8021ED5C | raw-lit sweep 2026-09-06: 9.4% (DIFF) |
| fn_8021EEF4 | 0x8021EEF4 | parked (2026-09-21: rebuilt — 12B record not 0x44B Unk_59AB5482, fn_80219698(arg0), 2-arg fn_8019915C; residual = want keeps one extra live entry-address pseudo) |
| fn_8021F120 | 0x8021F120 | m2c |
| fn_8021FAB4 | 0x8021FAB4 | m2c |
| fn_8021FE30 | 0x8021FE30 | m2c |
| fn_802201BC | 0x802201BC | raw-lit sweep 2026-09-06: 6.8% (DIFF) |
| fn_8022053C | 0x8022053C | m2c |
| fn_8022082C | 0x8022082C | m2c |
| fn_80220CC8 | 0x80220CC8 | m2c |
| fn_80220DF0 | 0x80220DF0 | m2c |
| fn_80221618 | 0x80221618 | m2c |
| fn_802221E8 | 0x802221E8 | m2c |
| fn_802227E0 | 0x802227E0 | m2c |
| fn_80223448 | 0x80223448 | m2c |
| fn_80223C68 | 0x80223C68 | m2c |
| fn_80224E28 | 0x80224E28 | m2c |
| fn_8022527C | 0x8022527C | raw-lit sweep 2026-09-06: 1.0% (DIFF) |
| fn_802266AC | 0x802266AC | m2c |
| fn_802268C0 | 0x802268C0 | m2c |
| fn_80227024 | 0x80227024 | m2c |
| fn_802273FC | 0x802273FC | m2c |
| fn_80227794 | 0x80227794 | m2c |
| fn_802288E0 | 0x802288E0 | raw-lit sweep 2026-09-06: 1.0% (DIFF) |
| fn_80229404 | 0x80229404 | m2c |
| fn_80229A70 | 0x80229A70 | m2c |
| fn_80229E18 | 0x80229E18 | m2c |
| fn_8022A21C | 0x8022A21C | m2c |
| fn_8022B75C | 0x8022B75C | m2c |
| fn_8022B8E8 | 0x8022B8E8 | m2c |
| fn_8022BB14 | 0x8022BB14 | m2c |
| fn_8022BBD0 | 0x8022BBD0 | m2c |
| fn_8022BD5C | 0x8022BD5C | m2c |
| fn_8022C8E0 | 0x8022C8E0 | m2c |
| fn_8022D3F4 | 0x8022D3F4 | m2c |
| fn_8022D910 | 0x8022D910 | m2c |
| fn_8022E028 | 0x8022E028 | PARKED 2026-09-21: 30.2% best; doc-28 CR-liveness (mfcr/mcrf cr4/bne cr4 across 4 calls) + merged RMW + dropped 4th call |
| fn_8022E5B4 | 0x8022E5B4 | m2c |
| fn_8022EA0C | 0x8022EA0C | m2c |
| fn_8022F1F0 | 0x8022F1F0 | m2c |
| fn_8022F840 | 0x8022F840 | m2c |
| fn_80230308 | 0x80230308 | m2c |
| fn_802305B0 | 0x802305B0 | m2c |
| fn_80230774 | 0x80230774 | m2c |
| fn_80230CCC | 0x80230CCC | m2c |
| fn_80231284 | 0x80231284 | m2c |
| fn_80232A40 | 0x80232A40 | m2c |
| fn_802340AC | 0x802340AC | m2c |
| fn_80234444 | 0x80234444 | raw-lit sweep 2026-09-06: 3.8% (DIFF) |
| fn_80234588 | 0x80234588 | raw-lit sweep 2026-09-06: 38.1% (DIFF) |
| fn_80234864 | 0x80234864 | m2c |
| fn_802359A4 | 0x802359A4 | m2c |
| fn_80235A9C | 0x80235A9C | m2c |
| fn_80235D70 | 0x80235D70 | raw-lit sweep 2026-09-06: 7.2% (DIFF) |
| fn_80235FA8 | 0x80235FA8 | m2c |
| fn_80236260 | 0x80236260 | m2c |
| fn_802366E4 | 0x802366E4 | raw-lit sweep 2026-09-06: 1.6% (DIFF) |
| fn_80236FE4 | 0x80236FE4 | m2c |
| fn_802371CC | 0x802371CC | m2c |
| fn_80237454 | 0x80237454 | m2c |
| fn_80237708 | 0x80237708 | m2c |
| fn_802377C8 | 0x802377C8 | m2c |
| fn_80237A88 | 0x80237A88 | m2c |
| fn_80237D14 | 0x80237D14 | m2c |
| fn_80238024 | 0x80238024 | m2c |
| fn_8023821C | 0x8023821C | m2c |
| fn_80238314 | 0x80238314 | m2c |
| fn_8023869C | 0x8023869C | m2c |
| fn_802389D0 | 0x802389D0 | m2c |
| fn_80238AC0 | 0x80238AC0 | m2c |
| fn_80238C40 | 0x80238C40 | m2c |
| fn_80238D28 | 0x80238D28 | raw-lit sweep 2026-09-06: 1.6% (DIFF) |
| fn_802392F0 | 0x802392F0 | m2c |
| fn_802394F8 | 0x802394F8 | m2c |
| fn_80239604 | 0x80239604 | m2c |
| fn_802399E8 | 0x802399E8 | m2c |
| fn_80239ECC | 0x80239ECC | m2c |
| fn_80239FAC | 0x80239FAC | raw-lit sweep 2026-09-06: 7.5% (DIFF) |
| fn_8023A158 | 0x8023A158 | m2c |
| fn_8023A7B8 | 0x8023A7B8 | m2c |
| fn_8023A8A0 | 0x8023A8A0 | raw-lit sweep 2026-09-06: 3.9% (DIFF) |
| fn_8023B1B8 | 0x8023B1B8 | m2c |
| fn_8023B364 | 0x8023B364 | raw-lit sweep 2026-09-06: 10.3% (DIFF) |
| fn_8023B6F0 | 0x8023B6F0 | m2c |
| fn_8023B830 | 0x8023B830 | m2c |
| fn_8023BBC0 | 0x8023BBC0 | m2c |
| fn_8023C0EC | 0x8023C0EC | m2c |
| fn_8023C6A4 | 0x8023C6A4 | m2c |
| fn_8023C84C | 0x8023C84C | m2c |
| fn_8023CEFC | 0x8023CEFC | m2c |
| fn_8023D22C | 0x8023D22C | m2c |
| fn_8023DC38 | 0x8023DC38 | m2c |
| fn_8023DE60 | 0x8023DE60 | m2c |
| fn_8023E33C | 0x8023E33C | m2c |
| fn_8023E43C | 0x8023E43C | m2c |
| fn_8023E724 | 0x8023E724 | m2c |
| fn_8023E9D0 | 0x8023E9D0 | m2c |
| fn_8023EC64 | 0x8023EC64 | m2c |
| fn_8023F07C | 0x8023F07C | raw-lit sweep 2026-09-06: 3.4% (DIFF) |
| fn_8023FC44 | 0x8023FC44 | raw-lit sweep 2026-09-06: 5.4% (DIFF) |
| fn_802401C8 | 0x802401C8 | m2c |
| fn_802403AC | 0x802403AC | m2c |
| fn_802404A8 | 0x802404A8 | m2c |
| fn_80240DC0 | 0x80240DC0 | m2c |
| fn_80240F6C | 0x80240F6C | m2c |
| fn_80241804 | 0x80241804 | m2c |
| fn_80241AA4 | 0x80241AA4 | m2c |
| fn_80241F00 | 0x80241F00 | m2c |
| fn_80242590 | 0x80242590 | m2c |
| fn_80242734 | 0x80242734 | m2c |
| fn_802428BC | 0x802428BC | m2c |
| fn_80242B2C | 0x80242B2C | m2c |
| fn_80242D60 | 0x80242D60 | m2c |
| fn_80242F80 | 0x80242F80 | m2c |
| fn_802434B0 | 0x802434B0 | m2c |
| fn_80243638 | 0x80243638 | m2c |
| fn_80243924 | 0x80243924 | m2c |
| fn_8024402C | 0x8024402C | m2c |
| fn_8024420C | 0x8024420C | m2c |
| fn_802442A8 | 0x802442A8 | m2c |
| fn_802444D0 | 0x802444D0 | parked | all m2c call-artifacts fixed (fn_80238964 0-arg, fn_802416F8(fn_802432A0(n)) chain, fn_802424AC 3-arg, byte store, {s32;u16} sp18 typedef); 20% exact 276B — GCC 2.95 slot order hard-wall: want sp10@0x10/sp18@0x18, GCC emits sp18@0x10/sp10@0x18 regardless of decl order/store form; cascades into all reg numbers |
| fn_802445E8 | 0x802445E8 | m2c |
| fn_80244A20 | 0x80244A20 | m2c |
| fn_80244E48 | 0x80244E48 | m2c |
| fn_802451A4 | 0x802451A4 | m2c |
| fn_80245318 | 0x80245318 | m2c |
| fn_80249B70 | 0x80249B70 | m2c |
| fn_80249E04 | 0x80249E04 | m2c |
| fn_80249F70 | 0x80249F70 | m2c |
| fn_8024A0B0 | 0x8024A0B0 | m2c |
| fn_8024A438 | 0x8024A438 | m2c |
| fn_8024AEF0 | 0x8024AEF0 | m2c |
| fn_8024B208 | 0x8024B208 | m2c |
| fn_8024B690 | 0x8024B690 | m2c |
| fn_8024BA9C | 0x8024BA9C | m2c |
| fn_8024C144 | 0x8024C144 | m2c |
| fn_8024C624 | 0x8024C624 | m2c |
| fn_8024C970 | 0x8024C970 | m2c |
| fn_8024CCC8 | 0x8024CCC8 | m2c |
| fn_8024D6B0 | 0x8024D6B0 | m2c |
| fn_8024DD84 | 0x8024DD84 | m2c |
| fn_8024E2C8 | 0x8024E2C8 | m2c |
| fn_8024EAF4 | 0x8024EAF4 | m2c |
| fn_8024EBD8 | 0x8024EBD8 | m2c |
| fn_8024ECD0 | 0x8024ECD0 | m2c |
| fn_8024EF18 | 0x8024EF18 | m2c |
| fn_8024F2AC | 0x8024F2AC | m2c |
| fn_8024F4B0 | 0x8024F4B0 | m2c |
| fn_8024F65C | 0x8024F65C | m2c |
| fn_8024F9CC | 0x8024F9CC | m2c |
| fn_8024FE30 | 0x8024FE30 | m2c |
| fn_802502C0 | 0x802502C0 | m2c |
| fn_8025085C | 0x8025085C | m2c |
| fn_80250900 | 0x80250900 | m2c |
| fn_8025097C | 0x8025097C | m2c |
| fn_80250A1C | 0x80250A1C | m2c |
| fn_80250AC4 | 0x80250AC4 | m2c |
| fn_80250E24 | 0x80250E24 | m2c |
| fn_80250EAC | 0x80250EAC | m2c |
| fn_80250F2C | 0x80250F2C | m2c |
| fn_802511DC | 0x802511DC | m2c |
| fn_80251490 | 0x80251490 | m2c |
| fn_802518D8 | 0x802518D8 | m2c |
| fn_80251A88 | 0x80251A88 | m2c |
| fn_80251B70 | 0x80251B70 | m2c |
| fn_80251EEC | 0x80251EEC | m2c |
| fn_80252554 | 0x80252554 | m2c |
| fn_80252864 | 0x80252864 | m2c |
| fn_80252D7C | 0x80252D7C | m2c |
| fn_80252EC8 | 0x80252EC8 | m2c |
| fn_80253060 | 0x80253060 | m2c |
| fn_80253694 | 0x80253694 | m2c |
| fn_80253DBC | 0x80253DBC | m2c |
| fn_80253FF4 | 0x80253FF4 | m2c |
| fn_802548F8 | 0x802548F8 | m2c |
| fn_80254CEC | 0x80254CEC | m2c |
| fn_80254E80 | 0x80254E80 | m2c |
| fn_80254FA8 | 0x80254FA8 | m2c |
| fn_802551C8 | 0x802551C8 | m2c |
| fn_802556C4 | 0x802556C4 | m2c |
| fn_80255E34 | 0x80255E34 | m2c |
| fn_80256020 | 0x80256020 | m2c |
| fn_802561E0 | 0x802561E0 | m2c |
| fn_80256458 | 0x80256458 | m2c |
| fn_80256AD0 | 0x80256AD0 | m2c |
| fn_80256D3C | 0x80256D3C | m2c |
| fn_802575CC | 0x802575CC | m2c |
| fn_80257704 | 0x80257704 | m2c |
| fn_8025784C | 0x8025784C | m2c |
| fn_80257948 | 0x80257948 | m2c |
| fn_80257A08 | 0x80257A08 | m2c |
| fn_80257CC4 | 0x80257CC4 | m2c |
| fn_80257D7C | 0x80257D7C | m2c |
| fn_80257E48 | 0x80257E48 | m2c |
| fn_80257F04 | 0x80257F04 | m2c |
| fn_80258254 | 0x80258254 | m2c |
| fn_802584C0 | 0x802584C0 | m2c |
| fn_802585EC | 0x802585EC | m2c |
| fn_80258880 | 0x80258880 | m2c |
| fn_80258938 | 0x80258938 | m2c |
| fn_80258B78 | 0x80258B78 | m2c |
| fn_80258EAC | 0x80258EAC | m2c |
| fn_80259194 | 0x80259194 | m2c |
| fn_802592A4 | 0x802592A4 | m2c |
| fn_80259374 | 0x80259374 | m2c |
| fn_802595F4 | 0x802595F4 | m2c |
| fn_8025985C | 0x8025985C | m2c |
| fn_80259B6C | 0x80259B6C | m2c |
| fn_80259DF8 | 0x80259DF8 | raw-lit sweep 2026-09-06: 0.8% (DIFF) |
| fn_8025A258 | 0x8025A258 | m2c |
| fn_8025A348 | 0x8025A348 | raw-lit sweep 2026-09-06: 40.0% (DIFF) |
| fn_8025A3AC | 0x8025A3AC | m2c |
| fn_8025A610 | 0x8025A610 | stub |
| fn_8025A6FC | 0x8025A6FC | raw-lit sweep 2026-09-06: 0.0% (DIFF) |
| fn_8025A728 | 0x8025A728 | raw-lit sweep 2026-09-06: 0.0% (DIFF) |
| fn_8025A768 | 0x8025A768 | m2c |
| fn_8025A7F8 | 0x8025A7F8 | m2c |
| fn_8025A894 | 0x8025A894 | stub |
| fn_8025AC18 | 0x8025AC18 | stub |
| fn_8025AD64 | 0x8025AD64 | m2c |
| fn_8025AEEC | 0x8025AEEC | stub |
| fn_8025AF18 | 0x8025AF18 | m2c |
| fn_80269F4C | 0x80269F4C | m2c |
| fn_8026A07C | 0x8026A07C | m2c |
| fn_8026B6DC | 0x8026B6DC | m2c |
| fn_8026BC98 | 0x8026BC98 | m2c |
| fn_8026BD70 | 0x8026BD70 | m2c |
| fn_8026D288 | 0x8026D288 | m2c |
| fn_8026E750 | 0x8026E750 | m2c |
| fn_8026EAAC | 0x8026EAAC | m2c |
| fn_8026F2CC | 0x8026F2CC | m2c |
| fn_8026F55C | 0x8026F55C | m2c |
| fn_8026FD2C | 0x8026FD2C | m2c |
| fn_8026FF40 | 0x8026FF40 | m2c |
| fn_8027060C | 0x8027060C | m2c |
| fn_80270858 | 0x80270858 | m2c |
| fn_80270A84 | 0x80270A84 | m2c |
| fn_80270D9C | 0x80270D9C | m2c |
| fn_802712F0 | 0x802712F0 | m2c |
| fn_802715E4 | 0x802715E4 | m2c |
| fn_80271948 | 0x80271948 | m2c |
| fn_80271AE0 | 0x80271AE0 | m2c |
| fn_80271CF4 | 0x80271CF4 | m2c |
| fn_80272094 | 0x80272094 | m2c |
| fn_8027291C | 0x8027291C | m2c |
| fn_80273AB8 | 0x80273AB8 | m2c |
| fn_80285050 | 0x80285050 | hand |
| fn_80289AE4 | 0x80289AE4 | m2c |
| fn_80289BD8 | 0x80289BD8 | m2c |
| fn_8028B408 | 0x8028B408 | m2c |
| fn_8028B47C | 0x8028B47C | m2c |
| fn_8028B4F0 | 0x8028B4F0 | m2c |
| fn_8028BA08 | 0x8028BA08 | m2c |
| fn_8028BC24 | 0x8028BC24 | m2c |
| fn_8028DF98 | 0x8028DF98 | raw-lit sweep 2026-09-06: 19.0% (DIFF) |
| fn_8025E9AC | 0x8025E9AC | m2c |
| fn_80285050 | 0x80285050 | hand |
| fn_8028BA08 | 0x8028BA08 | m2c |
| fn_8028BC24 | 0x8028BC24 | m2c |
| fn_8025D010 | 0x8025D010 | stub |

## 2026-09-01

- **PROMOTED fn_8014E440** (3516B, scale+rotation matrix builder) — was an
  INERT hand-cracked EXACT draft; promotion initially failed because
  `bdnz $` inside a non-terminating inline-asm string emits a relocation
  (`undefined: '$'` at link). Fix: `.long 0x42000000` (see doc-30 new
  "Promotion trap" section). Suggested rename: `build_mgr_scale_rot_matrices`.
- **PARKED fn_8025A248, fn_8025A5FC, fn_8025A1D0** — NS-family ctx-pointer
  functions whose cracks rely on file-scope global register `__asm__` vars
  (r31/r6/r3 pins); project avoids asm, promotion perturbs the unit.
  UPDATE 2026-09-02: fn_8025A248's promotion failure was NOT the register
  vars — it is an unreferenced ORPHAN that mwld deadstrips as a standalone
  object (doc-13 second instance; detail in the draft header).
- ~~Confirmed parked: fn_8000BEEC~~ **SOLVED 2026-09-06** (see top); fn_800FE42C
  (crossjump suppression wall), fn_8025A258 (prologue-shape wall, 28.3%).

## 2026-09-02

- **PROMOTED fn_8002AE34** (56B, m2c) — gate wrapper: calls fn_80029A30
  (2480B skater-setup helper, itself unmatched) only when flag 0x800000 is
  set on `[arg0+4]`, else returns 0. The `if/return` + `var_r3` accumulator
  form stalls at 50%; the **ternary form** is EXACT (result coalesced into
  r3, arg0 spilled to r9 — same accumulator shape as doc-25). Suggested
  rename: `check_flag_and_setup`.
- **REPAIRED fn_8015E868** (scriptcmd, PS body) — COMPILE FAIL had a trivial
  cause: the draft referenced QB_VEL_Y/QB_VEL_Z before they existed. Hashes
  brute-forced via tools/qb_hash.py (0x1680A0FB=vel_y, 0x8F89F141=vel_z) and
  added to include/qb_constants.h → now NEAR 83.6% with -mps-float.
- **BREAKTHROUGH fn_8025A248 promotion mystery SOLVED** — the "DOL differs on
  promote" park note was wrong about the cause. It is an unreferenced orphan
  function: mwld deadstrips its standalone object (no .comment export bit,
  nothing in the DOL references it), .text loses 0x10 bytes and ~39886 DOL
  bytes shift. Second confirmed instance of doc-13 (now updated). Currently
  covered by auto-asm fallback; permanent fix = config.yml force_active.
  Caveat applies to its twins fn_8025A5FC / fn_8025A1D0.
- **BASELINE RESTORED**: HEAD's build did NOT produce a byte-identical DOL
  before this session's fix (the parked fn_8025A248.c sat in src/ as a
  registered Matching object). DOL now byte-identical at
  ff6faeb0f2b524ecbe1aeaff78ff154a284c27c9.
- **IMPROVED fn_8015F308** 89.9% → 93.8% (doc-15 twin-call: shared call's
  result only consumed by arm-1 → call belongs inside arm-1).
- Classified/parked: fn_800A08C0, fn_800A0564, fn_800A07F0 (paired-single
  bodies; capstone PS decode blind spot, docs/parkings/06); fn_801E72F0
  (0x1B14, doc-28 CR-save + doc-15 residue); fn_800C0240 (mr r9,r12 coin).

## 2026-09-02

- **PROMOTED fn_8015A5C8** (448B, ScriptKillSkaterCamAnim) — cracked the last
  2-word load-target coin: the *pointer load itself* must be pinned to r3
  (`register s32 pff8 __asm__("r3") = *(s32 *)&lbl_80305FF8;` then deref
  `pff8+0x44`). Earlier probes pinned the xor operand or used barriers — the
  load-target web must BE r3 for the sda21 load to land there.
- Probed the 98.5-99.5% ceiling fns; all are genuine 1-4-word scheduling /
  regalloc coins whose next lever is not obvious:
  fn_80173D30 (li r4,0 vs mr r4,r30 arg window), fn_8019E770 (add r28,r11,r28
  commutative canonicalization — 8 operand/web forms swept), fn_801A71DC
  (li/mr window at 2 chain heads; semantic-dependence trick fixed one site,
  cascade-broke the other), fn_80167E04 (guard cmplw r30-vs-r29; pin flips
  cascade), fn_801575E0 (X/Z li-mr inversion; fences/shared-zero resist),
  fn_8017DD54 (prologue mr save-order coin), fn_801BE820 (switch compare-tree
  shape; if/else-chain + u32 cast regress), fn_801410E0 (param-save order;
  stmt reorder + barriers regress).

## 2026-09-02

**The ".sdata2 +0x40 promotion blocker" is DEAD.** Empirical proof: this
session promoted **~29 new compiled objects** into the link with zero sdata2
shifts, via 3 fixes:

1. **Orphan protection via `force_active` (doc-13 generalized).** Reference
   scan of all EXACT candidates vs the retail DOL found 6 orphans (referenced
   by nothing: 0x8013A744, 0x8013A8D0, 0x8013A9FC, 0x802245A4, 0x8025A248,
   0x8025A5FC). All 6 now in `config.yml force_active:` → dtk emits them into
   the ldscript FORCEACTIVE block → mwld keeps them. NOTE: configure.py alone
   does NOT regenerate `build/G2TE52/ldscript.lcf` — promote_wip's
   add_gen_leaves + reconfigure step does; after hand-editing config.yml run
   `python3 configure.py --dtk tools/dtk --ninja tools/ninja` AND promote (or
   touch the build) so dtk rewrites the .lcf. Inline `#` comments inside the
   YAML list items confused dtk's parser — put comments on their own lines
   above the block.
2. **fn_8025A248 restored as a C unit** (fix, now durable
   config.yml) — this was the actual fragility behind every earlier +0x40
   flip: the tail region was silently losing 0x10 bytes whenever mwld's GC
   decisions wobbled.
3. **Draft hygiene fixes** found during promote re-verify:
   - fn_8000C938 referenced undefined label `fn_80269394`; retail symbol is
     `PADControlMotor` (see src/fn_800C5D8.c) — relabelled, re-verified EXACT.
   - fn_8015BA18's stale `// FLAG: -fno-schedule-insns` line (from its 92.2%
     parked era) broke the promote re-verify; plain compile is EXACT 204B.
     promote_wip reads `// FLAG:` but the sweep does NOT — keep FLAG lines in
     sync with the parked status or drop them.
   - Hand-cracked drafts lacked the `range=0x…-0x… size=…B` marker
     promote_wip requires; markers added from symbols.txt sizes.

**Promoted this session (all verified DOL byte-identical `ff6faeb0f2b5…`):**
doc-47/49 family: fn_8000C938, fn_8000F95C, fn_8000F9C4, fn_8000FA70,
fn_80032610, fn_800394CC; singles: fn_80076F8C, fn_800A638C, fn_80122450,
fn_80130E88, fn_80136BE4, fn_80159E20 (ScriptSelectCurrentSkater),
fn_800B62EC, fn_800B68A0, fn_800DCEF4, fn_800DF4E0, fn_8011405C
(ScriptStartPreLoadedStream), fn_801177BC (ScriptResetEventHandlersFromTable),
fn_80118CF4 (ScriptLoadCollision), fn_80130F40, fn_80131474, fn_80136CAC,
fn_8015BA18; orphans: fn_8013A744, fn_8013A8D0, fn_8013A9FC, fn_802245A4,
fn_8025A5FC (twin of fn_8025A248).

**Two doc-24 walls CRACKED via relocation-addend analysis** (the beq/bne is
reloc-filled; raw .o bytes identical, only the R_PPC_REL14 addend differs —
disassemble BOTH DOLs, match addends, then infer block layout):
- **fn_80136CAC** (132B, DVD-path helper): the `if (*(base+0xA8) != 0)`
  branch — retail addend 0x64 = load into temp_r3, call AND the
  `*(base+0xA8)=0` store both INSIDE the if, `return 1` SHARED after it
  (beq skips the store but NOT `li r3,1`). Store-after-if → 0x60;
  call+store+return-1 all inside → 0x6C. Draft + registry row updated.
- **fn_8013A9FC** (188B, script message handler): the bit-test branch —
  retail addend 0x74 = **`return 4` early-exit inside the bit branch** (beq
  → `li r3,4; b epilogue`, skipping the fn_8013F74C test); the F74C if is
  the ELSE path of the outer bit-test if. m2c had flattened the nesting
  into sibling ifs (addend 0x60). Registry row updated.

**Park updated:** fn_8020ACB0 (308B, message-dispatch): addend walk proves
retail is a 2-entry state-machine dispatch (hash-match beq's ENTER the
fn_800CC038 send handler mid-block at 0xDC/0x80; the m2c `&&` guard is a
semantic inversion). Needs the handler emitted once with both beq's landing
inside it — parked with full map in the draft header.

**Remaining EXACT-in-wip after this session: 5** — 0x80003464 (init section,
below TEXT_START), doc-24 trio (fn_80134E1C, fn_80169070, fn_80172C44),
fn_8020ACB0 (state-machine layout). Registry rows for the promoted fns were
removed by promote_wip automatically.

## Session — doc-24 trio SOLVED (2026-09-02)

All three masked-EXACT park members promoted; **remaining EXACT-in-wip: 2**
(0x80003464 init-section, fn_8020ACB0 state-machine). Each member had a
different root cause behind the identical reloc-masked symptom — full write-up
in docs/parkings/solved/24-continue-postdec-loop-branch-targets.md:

- **fn_80172C44** (232B): m2c inverted `||` into `&&` — retail's beq@0xEC
  addend lands INSIDE the fn_8011CF0C call. Or-form → EXACT.
- **fn_80169070** (1124B, ScriptLoadFromMemoryCard): switch **default arm
  missing** — both orig default-arm branches converge on .text+0x3C8 (the
  cleanup block). `default: goto cleanup;` → EXACT.
- **fn_80134E1C** (852B parser): cross-jump tail barrier must precede the
  empty loop so bge@0x2AC threads directly to the shared add-tail (0x338).

The reloc-addend method is now the general tool for masked-EXACT walls:
decode differing branch words as displacements against both address maps;
the orig target block names the required source shape.

## Session — fn_8020ACB0 SOLVED (2026-09-02)

The "state-machine dispatch" park was the last solvable EXACT-in-wip and it
fell to the same lesson as the doc-24 trio: **the parked flow reading was
inverted; the true retail shape is the plain one.** Steps:

1. Re-disassembled the retail ELF (the draft was INERT, so build/G2TE52
   main.elf IS retail): one CC038 tail-merge block at .text+0xDC
   (`mr r3,r31; bl fn_8020ADE4; mr r3,r30; li r4,1; li r5/r6,0;
   bl fn_800CC038; b epilogue`) with THREE entries — beq@0x44/beq@0x5C
   (hash match 0xA4B7A992/0xDA3A5A4D) -> 0xDC, beq@0xCC + the 0x1C0C!=0
   fall-through -> 0xDC, and the lfs fast path b@0xA4 -> 0xE8 (into the
   MIDDLE of the merged tail, skipping the ADE4 call).
2. The m2c draft's `!= A && != DA` guard skips the send on hash match — a
   semantic inversion. Retail: hash match SENDS.
3. Plain 3-site if/else with the natural `fn_800CC038(temp_r30,1,0,0,var_f1)`
   at each site lets MWCC regenerate the merge: 308B, 100% masked, all 10
   branch addends match retail (8x REL14 + 2x internal REL24).
   The old goto-rewrite failed because it wasn't the natural form.

**Promoted — DOL byte-identical. Remaining EXACT-in-wip: 1**
(0x80003464, below TEXT_START / init section).

## Session — doc-13 CLOSED (2026-09-02)

Doc-13 (mwldeppc orphan deadstrip) moved to solved/: mechanism was already
proven (reachability GC, FORCEACTIVE mitigation); the missing piece was
executing the mitigation for the ORIGINAL orphan fn_8025254C, still parked
in gen_leaves `PARKED` under the disproven boundary theory. Executed:
config.yml force_active += fn_8025254C, `PARKED = set()`, leaf regenerated
+ registered via register_build.sh, `nm` confirms `8025254c T fn_8025254C`,
**DOL byte-identical**. 7 orphans total now retained via force_active.
Caveat recorded: twin fn_8025A1D0 stays parked for CODEGEN reasons (~80%,
caller-r31 ctx pointer), not linker reasons.

## 2026-09-03 — NEAR sweep #2 (36 drafts 97.6-99.5%), no promotions

Regenerated /tmp/near_list.txt: 36 NEAR drafts. Re-attacked the top coin
candidates plus first-time probes of the mid tier. All walls this round are
doc-15-class scheduler/allocator coins — no flow inversions remained (the
reloc-addend method found none).

Swept deep (no EXACT, all variants cataloged in draft headers):
- **fn_80173D30 (99.5%, 1 word)**: want `li r4,0` arg vs our `mr r4,r30`.
  Retail forwards the pinned r30 into the STORE only; ngccc asm-pin
  copy-prop forwards into the call arg too. store-through-tmp / reorder /
  0*tmp / plain-local (84% — pin IS the allocation) all resist.
- **fn_80221C00 (97.8%, 1 word)**: want `addi r4,r1,8` at 0x7c (call2
  rematerializes &sp8) vs our `mr r4,r30` CSE. Barrier is load-bearing
  (delete → frame flips 0x28→0x20, stmw r14, 84%); mem-clobber 84%,
  r-input 93%, C89 ptr-locals/+0/pc-epilogue inert.
- **fn_800A80D8 (98.1%, 2 words)**: mr r3/mr r5 copy-order around ori r4.
  Full flag set: -O0 3%, -fno-schedule-insns 96%, others inert; val/obj/
  both-locals inert; boolize 57%; asm-input nudge inert.
- **fn_801903B8 (98.6%, 2 words)**: retail materializes hash `lis r4`
  BETWEEN lis r9 and the two loads. 5 const-hoist shapes all emit
  identically — scheduler ignores source-level const placement.

First-diff artifacts recorded on never-probed drafts (unprobed before this
batch): fn_80195668 (mr/ori coin, sibling of 800A80D8), fn_801D1210 (lis/lfs
coin, sibling of 801903B8), fn_8015AACC (cmpw/stw pair), fn_802241F0 (3-word
arg order), fn_800C9808 (cmpwi/stfs pair), fn_80181DA0 (prologue save/copy
order, 5 words), fn_801FBF90 (prologue mr swap).

Verdict: the NEAR tier is now uniformly doc-15-class walls; next
leverage is the doc-15 scheduling model itself, not per-function source
sweeps. No build-affecting changes this batch (all probes in /tmp).

## 2026-09-03 — full-body reconstruction of tiny low-score drafts: 6 promoted

Random-sampled 60 unprobed (<50%) wip drafts, picked the smallest, and
reconstructed bodies from retail disassembly. **6 promoted, DOL
byte-identical after each batch:**

| Function | Size | Crack |
|---|---|---|

Diagnosed and parked (headers updated):
  prologue emits `mflr r0; stw r0,4(r1); stwu r1,-N(r1)` (mflr BEFORE stwu;
  also r29-r31 saved after stwu). Game ngccc always emits stwu first — 9
  debug/PI family and DBGRead helpers.
- **Mis-split fragments (not C-reconstructable as-is)**: fn_80125384
  (mid-function `b` back to head 0x80125374), fn_80125488 (real head is
  fn_80125480, size 0x64), fn_8025A6FC (dispatch island using caller r30/r31).
  Splitter needs head-drafts / fold-ins, not fragment drafts.
- **fn_800DE3D0**: real size 0x410 (1KB+ paired-single PSq math + script
  calls), not 92B — the filler draft's compile length was misleading.
  Dedicated project, not a quick reconstruction.

General lessons: (1) tiny "wrong" drafts often hide INVERTED conditions and
wrong arg lists — read the full DOL flow before trusting m2c; (2) MWCC
bitfields are MSB-first; (3) constructor convention = return self, which
changes register webs; (4) sample-score sweeps waste effort on fragments —
check symbols.txt size/type and first-insn prologue first.

## 2026-09-03 — splitter-boundary audit (all 2983 wip drafts vs symbols.txt)

New `tools/audit_wip_ranges.py` (report) + `tools/fix_wip_ranges.py` (repair). Key correction to
the earlier mid-session finding: the "fixed-0x28 island" family were mostly drafts at *named*
symbols (ScriptNgc_Message, ScriptPlayStream, …) — the old fn_-only scans were blind to them, and
the real defects were **marker-shaped, not symbol-shaped** (all 11488 symbol sizes held up).

- **64 at-start markers fixed**: 49 missing canonical markers added (values always from
  symbols.txt; prose `// range A-B` lines upgraded in place), 15 wrong end/size rewritten —
  incl. 9 zero-length (`end=start`), truncated hex `0x8024E04` (fn_80249B70), 256B-short
  fn_801FEF08, and 10 entries that disagreed with the true symbol extents.
- **38 fragments neutralized**: drafts at addresses inside another function (7 crossed the
  parent end, 31 claimed arbitrary 0x28 sub-spans of the 80123xxx family). Markers replaced with
  `// FRAGMENT:` notes — never promotable, no longer mislead promote/test tooling.
- **4 unlabeled regions annotated** (no function symbol claims them): 802572C4 (float data
  80261C1C). Markers kept for bookkeeping only.
- `tools/check_markers.py` upgraded: recognizes all symbol names (was fn_-only, silently passed
  ~330 named-symbol drafts) and skips fragments/unlabeled; still the pre-promote size gate.
- `audit_wip_ranges.py` exit 1 = dangerous class (at-start missing/mismatched marker); wire into
  CI/batch flow before promoting.

DOL byte-identical after the sweep (md5 c35167355175a039ccd25b8283a204ff); 105 draft headers
changed, no code touched.

## 2026-09-03 — : random mid/low-score reconstruction round (2 promoted)

Random sample of 120 unprobed ≤400B drafts scored with test_wip_drafts: 1 EXACT (0x80003464,
init-section — promote_wip.py refuses non-.text addresses BY DESIGN, permanently unpromotable),
20 NEAR. Deep-dived the top 8; **2 promoted, DOL byte-identical**:

- **fn_80169D64 (89.7% → EXACT, ScriptCardIsDamaged)** — the m2c draft's `volatile` stack
  pointers over-constrained scheduling: retail SINKS the label-guard stores into the call-arg
  windows. Plain (non-volatile) stack pointers reproduce it exactly. Lesson: don't pin stores
  the compiler is allowed to move unless the DOL proves they're fixed.
- **fn_8011C03C (85.2% → EXACT)** — result-channel pin: `register s32 r __asm__("r3")` keeps
  fn_8011BD7C's return in r3 through the `or. r3,r3,r3` test and into the fn_801210B4 arg slot.
  Plain local → compiler hoists `li r3,0` above the test → or. r0 form. The r3-pin is the
  general fix for the "or. rX copy coin".

**Six doc-15 walls cataloged in draft headers** (8013B5C4 96.4% extract-order, 802413C0 94.3%
mr-store order, 80136D30 88.9% magic/addr web, 80158B7C 88.6% call-window store order,
801C0E7C 85.1% pin-vs-late, 80114C20 82.8% alloc swap, 8023869C 72.4% load order + web shift,
8021CDA0 73.6% web shift). Every source-level variant tried regressed or tied — these need
scheduler modeling, not more sweeps.

Also this session: full splitter-boundary audit of all 2983 wip drafts (64 markers fixed, 38
fragments neutralized, 4 unlabeled annotated) — see the audit entry above.

### — r3-pin rollout + FAIL triage (same day)

- **-mps-float recovers 0x80213E48** (FAIL → NEAR 62.5%, paired-single float math — add the
  flag to its future sweeps); the two gx-chan drafts (80289AE4/80289BD8) still need real GX
  SDK headers.
- **Residual-classified all 10 remaining NEARs.** Four had semantic gaps:
  - **fn_8008C2C0 (57.1% → 88.6%)**: signature is **6 params** (prologue saves r6/r7/r8),
    fn_80081794's result stores as a **byte** at +0x178, and the lbl_80366478 handle load must
    be hoisted into a named local (retail loads before the label stores; ngccc sinks it
    otherwise). Residual 4 words = label-pair register swap, doc-15 web coin.
  - **fn_80184558 (62.5%, parked)**: retail's `b 8` back-edge skips the redundant `mr r3,r31`
    — but chained-r3 source forms crater (retail r3 is a callee-saved copy, not live r3) and
    the r4 pin breaks arg allocation. phi-shuffle is the only reachable back-edge form.
- Pure coins parked: 80025D0C (arg spill mr), 801A11D0 (fmr/load web), 80114520 (store-bank
  rotation), 80250E24 (shift-arg web), 8022053C (r27-r30 alloc + K hoist), 800BD674
  (subf-of-1 + lfs pair order), 8007F7F8 (byte-extract forms + cmp shape).
- DOL byte-identical throughout; best-match bodies written back per the parking rule.

## : -mps-float sweep of all 315 remaining PS drafts + link-integrity cleanup

Rescored every remaining paired-single draft under `-mps-float` (the flag that
proved decisive): **15 EXACT surfaced**, 2 of them carrying multi-instruction control-flow
asm that cannot ship. Also untangled the two crashed batches this round inherited.

**16 promotions landed (DOL byte-identical, link-verified):**
fn_800A952C, fn_801A362C, fn_801C39EC (2108B!), fn_801CB074, fn_801D16C0, fn_801DB240,
fn_801EE948 (712B), fn_801F46D8, fn_801F8170, fn_801F81E0, fn_801F98B4, fn_801FD03C,
fn_8022F5B0 — all EXACT only under `-mps-float`; the whole class was mis-scored for
its entire life because sweeps ran flag-less. Plus the crashed-batch survivors
fn_801CCF08, fn_801D478C, fn_801F2D48 (promoted earlier, registered+link-verified now)
and fn_8011C03C as well.

**Demoted (2 + 2) with park notes:**
- **fn_801B4404, fn_801B5A54**: EXACT bodies embed SN asm `bdnz $` self-targeting
  windows — the inline `$` links as undefined symbol '$'. Multi-instruction
  control-flow asm is out of bounds; plain-C constant-count loops emit mtctr/bdnz
  natively (fn_8014E440/fn_801FA1C8 precedents).
- **fn_801D2C58**: the crashed promotion never saw a link; its linked bytes
  differ from retail at 0x801D2D36-4F (4 bytes, reloc-field mismatch) despite a 100%
  masked compare. Demoted; re-verify link bytes before re-promotion.
- **fn_801B27F8** (parked, not demoted): same `bdnz $` defect, caught pre-promotion.

**Tooling: `promote_wip.py` now refuses any draft whose asm strings contain `$`**
(offline screen — the two failed batches would both have been prevented).

## : PS NEAR tier residual-classified; bdnz-$ idiom SOLVED (doc-30 closed)

**Residual-classified the 8 highest PS NEARs under -mps-float** (all parked with header
notes): 801CE65C 99.0% (store-run base CSE — breaking the run craters to 50%), 800D521C
98.3% (fadds operand order — allocator pick, `sum+f`/`sum+=f`/`f+sum` all emit the same),
80109AE4 97.7% + 80245410 96.7% + 801FB550 96.6% (call-arg materialization orders),
801B26D8 95.8% (K-hoist web), 801FC678 93.2% (arg order).

**fn_801D2C58 fully diagnosed** — the draft is genuinely EXACT (masked 100%). The linked
4-byte divergence is mwldeppc branch relaxation: our object's two conditional branches
carry REL14 relocs pointing at the forward out-of-line tail (retail's post-link shape);
the linker instead relaxes them backward to the identical in-function tail at fn+0x70.
Both tails return 1 via the same epilogue. Not source-reachable; needs a link-level
REL14-target check in promote_wip.py before it can ever ship.

**doc-30 bdnz-$ idiom SOLVED and both convertible drafts promoted:**
- **fn_801B4404** (608B) and **fn_801B27F8** (264B): the SN-asm `li/mtctr/bdnz $`
  empty-countdown windows convert to PLAIN C — pointer-init statements + a
  `for (i = 4; i != 0; i--) __asm__ volatile("");` constant-count loop, which ngccc
  lowers to li/mtctr/bdnz itself. The multiproduct prologue window in 801B4404 also
  split into six single-instruction asm statements (lis/lfs/addi). DOL byte-identical.
- **fn_801B5A54 stays parked**: its window interleaves real loads/mults with the
  countdown and a 16-insn PS chain follows; the C form needs full re-derivation
  (first attempt 14.4%).
- promote_wip.py's `$` screen stays: any remaining `bdnz $` draft fails fast with a
  pointer to this recipe.

## : fn_8004A800 full reconstruction (11.7% → 95.95%)

The m2c draft was structurally wrong everywhere. Retail decoded and rebuilt:

- **Function identified**: frontend UI-element factory (suggested rename
  `FE_CreateUIElement`). Switches qb arg4's class hash → menu-group enable,
  switches arg2 → one of 12 element creators, installs, vtable-setup,
  priority, returns via arg0.
- **m2c hallucinations fixed**: all 11 creator calls are ZERO-arg;
  fn_8000F2F8 takes 2 args; fn_8009DFC0 takes 2 args (elem, handle);
  fn_800098F4 1-arg; fn_801286D0 4-arg; vtable offsets are `lha` (s16);
  case hash is 0x03C84A59 (m2c ate a leading 0); the empty QB_DEFAULT case
  (flag stays 0, no call) was missing entirely.

**New reusable lever — unsigned switch trees**: retail's comparison trees
are UNSIGNED balanced BSTs (`cmplw` for subtree tests). ngccc emits a
signed tree for `switch (s32)`. Source form that reproduces retail:

```c
u32 sw1v;
switch (sw1v = sp18) { ... }
```

This is general: any hash-keyed switch in the codebase probably needs the
u32-temp form. (Tree shape is value-canonical — source case order is free.)

**Second lever — p-scratch prologue**: retail's `addi r9,r1,8; stw 0,4(r9);
stw 0,8(r9); ... mr r30,r9` (store scratch + CSE copy for the long-lived
handle pointer) reproduces when the init stores go through a *separate
scratch pointer local* `p` whose live range ends at `hp = p` — the compiler
materializes `addi r9,&w` for the stores, then coalesces the copy into the
pinned `hp` (r30). Direct `&w` stores sink the stores into the call window
instead (5% form); `hp = &w` first reorders the init (60%-killing).

**Third lever**: empty `asm volatile("")` after the WINDOW creator call
blocks the old-elem load hoist into the call shadow (retail loads it after
`mr r31,r3`).

Parked at 95.95% (355/370): residual = 2 allocation coins in the two
`fn_80128228`-index arms (mr-hoist + global-anchor r11/r9 web). Register
pins, m2c-exact web, `"+r"` barriers, flag placement — all tie or regress.
doc-15 class; needs allocator modeling.

## : u32-switch lever rollout (24 drafts improved, 5 promoted)

Applied the `switch (swvN = expr)` + u32-temp transform to all 81
hash-switch wip drafts (74 transformable):

- **5 EXACT promoted (DOL byte-identical)**: fn_80081794 (18.18% crater!),
  fn_800B0844, fn_800B14C0, fn_800B1550, fn_80119498 — every one was a
  5-18% DIFF whose ONLY problem was the signed comparison tree.
- **19 improved/writeback**: 8023357C 64.4→97.7 (parked: 2-word
  load-vs-lis/ori scheduler coin), 80115A28 15.4→75.2 (frame-shape differs,
  separate analysis), 80012C28/80033CFC/80034368/80035B24/8003ABD8/
  8003AFC8/80081920/800DCD30/800E426C/800EDB3C/80205574/80206554/
  802038C8/801EFE18/80065220/801106B0/800D3C44 all improved.
- 2 regressed, not written back (8020B280, 801E97CC); rest tied.

The u32-switch form is now the **default first try** for any hash-keyed
switch draft. Note: retail's trees are value-canonical UNSIGNED BSTs —
source case order is free, so any draft whose residual is a *different
tree shape* (different root key, different subtree dispatch order) should
be re-derived with this form before being called a scheduler coin.

## : doc-15 tree-shape parks re-derived with the u32 form

Revisited the parked drafts whose residuals were classified as switch-tree diffs:

- **fn_801F3D30 (1016B): 48.2% -> 55.5%.** The stale "switch tree off by 3 insns" note was wrong — the tree matches (value-canonical). Real fixes, all verified: (1) single-counter loop schedule — m2c's duplicated counters pinned an extra callee-saved (stmw r25 -> r26, now = retail); (2) u8 (`lbz`) field reads at +0x336; (3) `lbl_802AE2D4` string symbol for the sprintf fmt — HA/LO reloc pair with lis@ha hoisted to r26 + addi@l per iteration, exactly retail's shape. Residual = arg1 in r26 vs retail r27 + per-site mr/addi CSE coins. Notable: retail emits `crclr cr1eq` before both fn_80269F4C calls. Explicit prototypes still score best here; see the falsification note below — crclr does not generalize as a prototype signal.
- **fn_801A2584 (96B): re-confirmed parked.** u32-temp switch form also hoists the `mr r4,r5` arg setup above the dispatch; note amended.
- **fn_8016D930:** not tree-shaped (walker-birth timing residual) — untouched.
- The "7 untransformed hash-switch drafts" were diagnosed: 6 were transformed-and-reverted by the sweep itself; the 7th (fn_80112048) already uses the u32 cast (96.1% leaf-layout coin).

New durable levers recorded: (a) m2c loop counter duplication = +1 callee-saved — rewrite as single-counter loops when the prologue saves one extra register; (b) string args should be `lbl_*[]` symbols, not hex constants, so the HA half hoists like retail; (c) retail-side `crclr cr1eq` correlates with call declaration style (precise rule corrected in).

## 2026-09-03: known-lever rescan — fn_8004C858 diagnosis, crclr signal falsified

Rescanned NEAR drafts for the residual classes; fn_8004C858 (168B, `ComputeMaxWrappedFlag`: max of +0 over 10 stride-0x18 entries at arg0+0x5D8, skipping +4==0, XOR with fn_800421CC(sp8), cleanup, return equality) absorbed the batch.

- **Arity confirmed but kept out of the parked form.** fn_8009DFC0 takes `(obj, &sp8)` — retail site does `lwz r3,8(r1); addi r4,r1,8; bl`, matching its promoted callers. But the correct 2-arg call scores **20.9% under every declaration form** (no decl, `()`, `(s32,s32)`, `(void*,void*)`): ProDG hoists the &sp8 arg CSE into the loop window (`mr r4,r29`) and the tail shifts. The semantically-wrong m2c 1-arg call is structurally luckier (50.0%), so the draft keeps it per best-match convention; the fix must land together with the CSE lever, never alone.
- **crclr is NOT a prototype signal (hypothesis falsified).** Direct A/B on this call: `crclr cr1eq` appears before the `bl fn_8009DFC0` in EVERY declaration form tried — no decl, implicit ``, explicit `(s32,s32)`, explicit `(void*,void*)` — while retail has NONE. The fn_80269F4C correlation (explicit proto matched retail's crclr) does not generalize; treat retail-side crclr as context-dependent, not a declaration-style tell.
- **Parked at 50.0%** (draft note documents the arity truth): (a) the &sp8 CSE home — ProDG hoists `addi r29,r1,8` function-wide and shifts `stmw` to r29/0x14; retail rematerializes `addi r3,r1,8` at BOTH call sites and saves r30/0x18 (same open anti-CSE lever as fn_80124110; volatile sp8, dying-pointer local, walk-arg0 all crater 20-33%); (b) register-web: retail homes fn_800421CC's result in a fresh r9 kept live across the loop (tail xor reads r9), ProDG reuses r3 — cascading into sp8 loading as r0 at the cleanup and the bool sinking after the branch; (c) retail computes the bool in var_r31's own home (xor;subfic;adde into r31) BEFORE the cleanup branch; every source form tried craters 9-24%.

## : extra-stmw sweep (duplicated-loop-counter artifact)

Sweep method (one-off script, not committed): compile every wip draft, compare its `stmw` start register against the retail DOL, flag drafts that save MORE callee-saved registers than retail, then rewrite m2c duplicated-counter do-while loops (`temp_rN = var_rM + 1; ... var_rM = temp_rN;` snapshot chains) as single-counter loops — the fn_801F3D30 lever, automated. Keep-if-better on rescore; rejects reverted.

**88 candidates found; 9 improved:**
| Function | Score | Note |
|---|---|---|
| **fn_800F1B5C** | 11.7 → **20.4%** | stmw r24 → r26 — now EXACTLY retail's r26 |
| **fn_800CC698** | 28.8 → **36.4%** | biggest single jump |
| fn_801B6A60 | 15.0 → 15.4% | 2 loops |
| fn_800639E8, fn_80086D90, fn_8019AA88, fn_8022E5B4, fn_802548F8, fn_80104668 | +0.1–0.5% | marginal |

79 rejects/SKIPs reverted, no regressions, no EXACT (nothing to promote; DOL untouched — drafts are inert).

**Key diagnosis (fn_80124110, 54.1%):** its extra callee-saved is NOT loop counters — it's **call-arg address CSE**: mine hoists `addi r30,r1,8` (=&sp8) into a callee-saved across the GX call sequence, retail rematerializes `addi r3,r1,8` per site and puts a zero variable in r30 instead. Call-arg twin of p-scratch store case (doc-15/38 class). Recorded in the draft header; an anti-CSE source form for `&local` call args remains an open lever.

**Lever confirmed as a class:** m2c loop-counter duplication = +1 callee-saved in the prologue. When a draft's only prologue delta is one extra `stmw` register and it contains do-while loops, try the single-counter rewrite first.

## : extra-stmw sweep, second idiom + combined re-run

Pass 2 added a **pointer-walk loop** rewriter (m2c `tempX = var; … var = next(…); …tempX…` snapshot chains → move post-advance tempX uses before the advance). Result: no wins on the walk class (fn_8006DEE0/8006C780 rejected — the moved sequence perturbs their schedule), but a **combined re-run** of both passes over already-rewritten files found a **second counter loop in fn_800CC698: 36.4 → 55.6%** (now NEAR).

Also surfaced: fn_80124110's and fn_8026FD2C's residuals are NOT loop counters (call-arg address CSE / heavy asm pins respectively); fn_801B6A60 has a ProDG **ICE when compiled without -mps-float** — a diagnostic hazard worth knowing (bare test_one calls on __ps_t drafts crash the compiler; draft_flags picks the flag up automatically).

Final state of the 9 pass-1 keeps (all verified on disk): fn_800CC698 28.8→55.6%, fn_800F1B5C 11.7→20.4% (stmw r24→r26 = retail), fn_800CC698's sibling keeps unchanged, and the marginal +0.1–0.5% set. 79 candidates re-confirmed parked.

## : qb node-search trio matched (80128228 / 801289E4 / 801286D0)

All three EXACT and promoted — DOL byte-identical.

- **fn_80128228 (108B):** signature fix only — m2c hallucinated fn_80127F60 as 3-arg; retail passes **4** (`arg0, arg1, 1, &sp8`), arg1 flowing through untouched. Lookup keyed entry, optional reload-on-miss.
- **fn_801289E4 (172B):** m2c's goto-maze (result var + explicit advance chain) hid that retail **returns directly from inside the loop**; natural-return while-loop form is EXACT. u8 tag read at +2 (lbz). Recursive list search for a 0xD0000-tag node with id match (FindKeyedNodeRecursive).
- **fn_801286D0 (308B):** full reconstruction. Three non-obvious retails facts: (1) the else arm DOES test key==0 (m2c dropped it); (2) the validation gate tests **arg1** (search mode), not arg3 — the compiler hoists it into callee-saved **cr4** (`mfcr`/`mtcrf 8` ABI save/restore, cr2-4 are callee-saved); (3) the truth value must be written `((x ^ 0xA) == 0)` so ngccc emits the subfic/adde carry form — `(... != 0)` gives branchy code and a 2-word mismatch. Decl order val-then-ne pins val→r30 / ne→r29.

Two process notes: rewritten drafts must keep `#include` **after** the leading comment block (promote strips everything before the body — a line-1 include gets dropped, which is what the first promote attempt tripped on), and the `range=` marker must stay in the header for promote_wip.

## : fn_80127F60 caller arity sweep — 3 more EXACT

Prompted by the fn_80128228 discovery (m2c called fn_80127F60 with 3 args; retail takes 4). Audited all 7 wip + 2 promoted callers against the callee's own disassembly (r3=arg0, r4=key, r5=type filter vs node's 8-bit type field, r6=&out; recursive at 0x80128098).

**3 defective drafts fixed, all EXACT and promoted — DOL byte-identical:**
| Function | Defect | Fix |
|---|---|---|

All three are the fn_80128228 wrapper pattern (lookup + store + reload-on-miss); fn_801282E0's out-param is `f32 *` (lfs/stfs). Remaining callers (801280E0, 80128398, 80128470, 8012865C) already correct. fn_80127F60 itself is still unpromoted wip (0x180B) — its own draft is next in line for the same treatment.

## : fn_80127F60 — EXACT, promoted (DOL byte-identical)
384B recursive keyed-entry lookup with type filter + f32 out (FindEntryValueF32;
calls all the fn_80128228-family wrappers). Full retail reconstruction; the m2c
draft's goto-maze was replaced. Residual from the first attempt was 2 words:
the recursion out-slot address. Three frame findings (all reusable):
- **Volatile-double locals pack before non-volatile ones** regardless of
  declaration order (ProDG frame packer). To pin a slot at frame+8, declare a
  *volatile double* there — a plain `volatile double _dummy` forced every
  named f32 local down a slot.
- **Recursion out-slot = volatile double sp8d, declared first**, used via
  `(f32*)&sp8d` at the call and `*(s32*)&sp8d` at the copy. A named f32 out
  local gets stack-shared with the disjointly-live arg-temp (r3 slot) and the
  call target moves to 0x10; the double can't share, so the address stays put.
- The int->double cvt temp is **source-transparent**: plain `(f32)(s32)val`
  makes ngccc emit the xoris + .rodata2 magic (lbl_8029E5F8 = 0x4330000080000000)
  via lis+disp — no constant needed, and fix_fp_pool binds the pool site.
Also: the arg2==2 gate is loop-invariant + call-crossed -> hoisted into
callee-saved cr4 (mfcr/mtcrf 8), matching finding. The raw-stw vs
conversion split of the two write arms and inline tag expressions (no named
tag local -> lwz r0/mr r11 CSE home) complete the body.

## : slot-residual sweep — fn_80006350 EXACT, promoted (DOL byte-identical)
Sweep method (one-off script, not committed): compile every NEAR wip draft,
classify each scored-word miss; a *slot miss* = want/got differ only in a
r1 displacement (addi rX,r1,imm or op rD,disp(r1) with same op+regs). A
draft qualifies when it has slot misses and zero structural misses.
Result: exactly one draft in the codebase is pure slot-class — fn_80006350
(2D rotation matrix, Math_BuildRotation2D). Its diff was a uniform +0x10
frame shift: retail frame 0x30 vs the 0x20 the live set needs, body 100%.
Two volatile doubles declared first (never a double[2] — arrays pack after
non-volatile locals and do NOT lift the frame) restored the layout exactly.
Confirms the packer rules from the other side: volatile locals are
never dead-eliminated, so they are the tool for recreating unreferenced
retail frame space. All other NEAR drafts have structural residuals — the
pure slot class is closed.
Pipeline footgun re-confirmed: drafts must keep `#include` AFTER the leading
// comment block (promote strips everything before the body), and /* */
block comments must be converted to // lines (promote only strips //).

## 2026-09-03: fn_80119094 ScriptSetConfig — EXACT, promoted, DOL byte-identical

524B script opcode handler applying the config QB block: language hash (fn_801286D0) -> 5-case u32 switch storing the language id to lbl_802FFE48, six fn_801289E4 flag checks (subtitles enable/disable in lbl_802FFE58 via fn_8001473C/fn_80014770, two toggles each in lbl_802FFE54/lbl_802FFE68), and a frame-rate lookup (fn_80128228, default 60) into lbl_802FFE6C. Returns 1. m2c draft was 26.5%; final reconstruction EXACT.

- **u32-switch-temp lever generalized to hash-dispatch trees.** The case set spans the signed boundary (QB_ENGLISH 0xD37CFDFF is negative), and retail's BST balances over the UNSIGNED order — root = unsigned median 0xA8469630, and the first split compare is cmplw. An `s32 sp8` switch roots at the signed median with cmpw (80-82% NEAR ceiling); assigning `u32 langKey = (u32)sp8;` and switching on that reproduces retail's tree exactly. lever confirmed on a third function shape.
- **Case ORDER in source = emitted tree shape (values don't matter).** Retail's order is ENGLISH, FRENCH, 0xCBE70ACB, 0xA8469630+GERMAN (shared body) — exactly m2c's order. Five orderings swept; only this one is EXACT. **Grouping matters too:** merging the two value-3 cases into a FRENCH/0xCBE70ACB fallthrough pair (like the GERMAN pair) craters 100% -> 32.8% — ProDG's emitted BST is sensitive to case grouping, not just order. Since retail matches the duplicated-body form, the original source had FRENCH and 0xCBE70ACB as separate case labels with duplicated bodies; only the GERMAN pair was a true fallthrough.
- **lis+addi literal args are data symbols.** `fn_8001473C(0x8029D400)` as a literal emits lis/ori; retail has lis/addi — the HA/LO form of an unrelocated data ref. Pass `(s32)&lbl_8029D400`.

## 2026-09-03: four Script* opcode handlers — all EXACT, promoted, DOL byte-identical

Neighbors of ScriptSetConfig, reconstructed and promoted together (440B total): fn_80119368 ScriptIsPS2 (48B), fn_801193E0 ScriptGetPlatform (144B), fn_80119018 ScriptGetElapsedTime (108B), fn_80118F40 ScriptTimeGreaterThan (140B). All four m2c drafts had real semantic defects, not just schedule noise.

- **fn_801282E0 arg order:** the f32 threshold lookup is `fn_801282E0(arg0, 0, &sp8, 0)` — m2c scrambled it to `(0, &sp8, 0, 0x802A0000)`, hallucinating a fourth arg.
- **fn_801277E4 lookup-arg semantics:** its second arg is the hash of the KEY being stored, not a passthrough. m2c's `QB_PLATFORM` hash 0xC6C72F34 was a hallucination; retail's r4 = **0xC6AD2F34** = QB_PLATFORM in qb_constants.h. ScriptGetPlatform takes TWO params (arg0 unused, arg1 read at +0x18).
- **ScriptGetPlatform's switch:** cases {1,2,3} -> 0x988A3508 (the PS2-family platform hash — 1/2/3 map to the same value as ScriptIsPS2's predicate), 4/5/7 distinct, default -> var_r5=0 via the pre-init (NO default clause — m2c invented one and put the PS2 hash in it).
- **ScriptIsPS2 EXACT source form:** three `if (x == N) goto block_5;` tests sharing a `return 1;` block, with a trailing `goto block_8;` + `block_8: return 0;` — the trailing goto blocks ProDG's epilogue factoring (`li r3,0; bnelr`). Plain if-chains, ||-expressions, switches (with/without default), bool-value and ternary forms all fold into an arithmetic range check (addi/subfic/adde) or factored epilogues that retail doesn't have. The goto-shared-block shape is m2c's block_N output verbatim — more evidence those goto mazes are often FAITHFUL, not artifacts.
- **ScriptTimeGreaterThan:** returns `(f32)(u32)spC > sp8 * lbl_8029D3A0` where spC = fn_800145AC() - *(s32*)&lbl_80302C30 (elapsed since load, NEGATED in m2c), sp8 = threshold from fn_801282E0. lbl_8029D3A0 (rodata2) = **1000.0f** — threshold is seconds, comparison in ms. Unsigned cast `(f32)(u32)` is required: retail uses the `lis 0x4330` unsigned int->f32 idiom, not the signed xoris form. Named `temp_r30` local forces the fn_800145AC() load before the call into callee-saved r30 exactly as retail.
- **ScriptGetElapsedTime:** both values must be homed into named locals BEFORE the tail call (`temp_r29 = sp8; temp_r28 = *(s32*)(arg1+0x18);` then fn_80127684(temp_r28, 0x3EB3566B, lbl_80303150 + fn_80124F44() - temp_r29)) — retail keeps r29/r28 loads before the fn_80124F44() call; inlining either into the expression reorders them.

## 2026-09-04: three more Script-pool handlers — EXACT, promoted, DOL byte-identical

Three of the four unnamed Script-region drafts cracked; the fourth parked at its shape ceiling.

| Function | Was → Now | Notes |
|---|---|---|
| `fn_80119794` (104B) | 37.0% → 100% | pool-reset init; m2c's raw literal pointer → HA/LO `lbl_80387E44` symbol refs |
| `fn_801198C8` (108B) | 29.6% → 100% | id-in-use predicate; **early-return form** (`!=0 → return 0`) gives retail's inverted `beq→walk` polarity with the shared `li r3,0` fallthrough |
| `fn_80119A08` (76B) | 63.2% → 100% | next-free-id loop; plain `while (fn(arg0,arg1)==0) arg1++;` — m2c's `var_r31` copy is unnecessary (v2 and v3 both EXACT) |
| `fn_80119A90` (104B) | 46.2% → 92.3% parked | one-time init gate; see park note in draft |

### findings

- **Branch polarity is a source-order signal.** Retail C8 emits `cmpwi; beq→walk` with the `return 0` epilogue as *fallthrough*, and m2c's goto-maze (inverted test) produced the wrong polarity every time. The early-return rewrite (`if (fn(...)!=0) return 0;` before the walk) reproduces it exactly — third confirmation that m2c goto-mazes invert branch polarity relative to source.
- **Two-statement pointer init (`p = SYM; p += K;`) vs one folded statement is schedulable, not semantic.** A90's retail body wants the folded `lis r9,-0x7fc7; addi r9,-0x73e8` (bare `lbl_80388C18` HA/LO), followed by the separate `+0xBF0` statement — but the binding order also pins register allocation: whichever temp is created last is forced into r9 for the `-0x18` stride. All 6 statement orders × 2 declaration orders swept; the only orders matching allocation put C4C's `lis` *after* C40's, while retail emits it *before* — a 2-word scheduler coin no known lever reaches.
- **Arithmetic check on HA/LO pairs before believing a decode:** `lis 0x8039; addi -0x73e8` = 0x80388C18, not 0x80398C18 — v9 (bare symbol) and v16 (base+0x1418 into the adjacent pool) are mask-identical; parked the cleaner bare-symbol form.
- **m2c literal-pointer hallucinations keep resolving to real symbols:** `0x80389808` in this draft's m2c was wrong; the retail pointer walks `lbl_80388C18` (the 0xC00 4-byte pool) from +0xBF0 down, 0x80 slots × −0x18.
- **Cross-draft validation:** fn_80119A08 (next-free-id) consumes fn_801198C8 (id-in-use) with the exact 2-arg arity predicted by retail's `mr r30/r31` spill — the wrapper chain is now fully promoted end-to-end.

Working tree: 3 promoted files + registrations + A90 park update; sweep scripts removed.

## 2026-09-04: parked-NEAR lever rescan — no promotions, three walls re-confirmed

Rescanned the 36 parked NEAR drafts (97.2–99.5%) for the polarity lever plus the CSE-rematerialization class. One polarity hit (fn_801BE820) turned out to be a switch-tree shape diff, not a polarity flip; the six-draft address-CSE cluster (fn_80221C00 + fn_8021D2C4/D5DC/D7F0/D888/D990, each 1 word from EXACT) and two single-word walls were re-probed. All confirmed immovable this round.

- **fn_801BE820 (98.5%): the polarity scan hit is a red herring.** The 4 missed words (ble↔bgt, bgt↔blt + both cmpwis) are the right-subtree boundary tests: want tests 0xA (`ble→default`) then 0xC (`bgt→default`) where the draft tests 0xC then 0xB. All switch-layout/order/default-position variants tie at 98.5% — the tree-builder choice is not case-order driven here (contra). Parked as-is; header already documents the nested-if/u32/arm-order attempts.
- **Address-CSE cluster (6 drafts, 1 word each): array-decay rematerialization decoded but unhelpful.** All share the same miss — retail rematerializes `addi r4,r1,8` at a call while the draft's `mr r4,r30` reuses the store CSE home. Key experiment: **bare array-decay call args DO rematerialize** (proving retail called with a decayed array), but then the direct stores also fold to sp-relative, and a pointer local for the stores re-pins the call arg at one site. The two-expression-web source (pointer for stores + bare decay at calls) is not expressible: casts/spellings canonicalize and ProDG merges identical-value webs. fn_80124110-class open lever; parked.
- **fn_80173D30 (99.5%, 215/216): tmp-zero reorder is a byte-for-byte no-op.** d2 (extra `tmp = 0;` between the else-if's call and store, intending to kill r30's zero liveness so the call arg materializes `li r4,0`) compiles IDENTICAL to baseline — ProDG's branch-proven r30==0 still forwards into both the call arg (`mr r4,r30`) and the following store. Wall re-confirmed at word 59.
- **fn_8018BC9C (97.4%, 37/38): truthiness spellings all tie.** The sole diff is the rotated-loop preheader null test: want `or. r9,r9,r9` vs got `cmpwi r9,0`. Bare-truthiness (`while (var_r9 && *var_r9 != 0)`), uncast-value, and plain-`*var_r9` forms all compile to the same cmpwi; the loop body (words 15-22) is already opcode-identical to retail, so only the preheader test encoding differs — a MW(`or.`)-vs-GCC(`cmpwi`) codegen choice not reachable from source spelling. e1-e3 tie at the parked 97.4%; draft unchanged.

Net: zero promotions; three park notes confirmed current (fn_801BE820, the 80221C00 cluster, fn_8018BC9C/80173D30 single-word walls). No draft edits this batch — every candidate already held its best form on disk. Temp scan/sweep scripts removed.

## 2026-09-04: four Script-pool list functions — all EXACT, promoted, DOL byte-identical

Picked the four small DIFF drafts flanking the promoted pool functions (fn_80119794/fn_801198C8/fn_80119FB4) — same lbl_80302C40 doubly-linked list and lbl_80387E44 slot pool. All four were semantically close but carried class-defect m2c bodies.

| Function | Was → Now | Key defects fixed |
|---|---|---|
| `fn_80119668` (80B) float-run scaler | 0.0% → 100% | m2c deref'd the f32 run as s32 (lwzx/stwx vs lfsx/stfsx); symbols/HA-forms fine once typed f32 |
| `fn_8011970C` (96B) default-state predicate | 3.3% → 100% | layout-only — see lever below |
| `fn_80119E48` (200B) pool-list refresh walk | 14.3% → 100% | m2c hallucinated `fn_800145AC(0x80300000)` arg (real: no-arg); raw `0x80387E44` literal → `lbl_80387E44` symbol |
| `fn_80119F10` (164B) doubly-linked unlink | 26.7% → 100% | raw `0x80302C40/0x80302C4C` literals → the `lbl_*` globals; matches promoted caller fn_80119FB4's `extern s32 *lbl_80302C40` decl |

### Findings

- **The goto-anchored shared-return lever (new).** fn_8011970C's retail shares ONE mid-function `return 0` block: the f2/f3/f4 failures branch BACKWARD to it, and `return 1` is the final fallthrough. Sequential-return sources stall at 46% (ngccc scatters epilogue copies); `return 1` last + duplicate `return 0`s at 92.3% (one extra trailing ret0 copy). EXACT only came from anchoring the shared block with a label inside the FIRST if body and `goto ret0;` from the later tests — ngccc honors label placement, emitting the ret0 block mid-function with the backward branches retail has. This is the return-block counterpart to early-return lever and worth scanning other NEAR drafts for (want-side shared retN in the middle + got trailing copies).
- **f32-vs-s32 deref still the #1 m2c type defect** (fn_80119668: 0.0% purely from lwzx/stwx on floats). Float-typed structures generate obvious lfsx/stfsx wants.
- **m2c hallucinated call args** (fn_80119E48's `fn_800145AC(0x80300000)`) resolve against promoted callers — fn_800145AC is `s32 fn_800145AC(void)` (confirmed by 6 promoted externs).
- **Cluster validated end-to-end:** fn_80119FB4 (removal-by-slot-id, promoted) → fn_80119F10 (unlink) → fn_80119E48 (refresh walk) → fn_8011A95C/fn_80119C38/fn_8011A6A8 all cross-check arities against the retail r3-r6 assignments.

Working tree: 4 promoted files (annotated with behavior + suggested renames) + splits.txt/configure.py registrations + WIP.md; temp sweep scripts removed.

## 2026-09-04: voice-pool callee cluster — 2 new EXACT + 2 source cleanups, DOL byte-identical

Continued the cluster inward: fn_8011A6A8 and fn_8011A95C are the pool-lookup functions promotions call, and fn_8011ED40/fn_8011F210 their leaf helpers — together the AX voice-pool manager (lbl_8038EBBX = 8-byte voice entries, lbl_80387E44 = 59-slot x 0x3C pool, AXSetVoiceState at the leaf).

| Function | Was → Now | Notes |
|---|---|---|
| `fn_8011A6A8` (96B) | DIFF → 100% NEW | find-and-kill wrapper; **direct-return form EXACT**, m2c's var-result form 33%; m2c passed arg0 to the 1-arg fn_8011F210 |
| `fn_8011A95C` (160B) | DIFF → 100% NEW | 59-slot pool search for id with fn_8011ED40(i) active check, *out=i; m2c dropped arg0 + mangled the ED40 branch |
| `fn_8011ED40` (36B) | was EXACT (asm-pinned) | **rewritten plain-C, still EXACT — doc-02 claim FALSIFIED** |
| `fn_8011F210` (76B) | was EXACT | decl cleanup: `fn_8011ED40(void)` → `(s32)` with arg0 (same bytes, now true arity) |

### Findings

- **cr4 usage reproduced by plain C.** Retail fn_8011A95C hoists the loop-invariant `out != NULL` test into cr4 (`cmpwi cr4,...` + beq cr4 inside the loop), forcing the mfcr/stw/mtcrf CR-save prologue — and ngccc reproduced it byte-for-byte from a natural do-while with `if (out != NULL) *out = i;` inside the match. First evidence ngccc's allocator will use non-volatile CR fields like MW when the structure demands it; no source trick needed.
- **doc-02 FALSIFIED (asm pins removable).** The promoted fn_8011ED40 header claimed the lwzx base/index operand order requires `register ... __asm__("r9"/"r11")` pins. The real lever is the TABLE's C TYPE: `extern s32 lbl_8038EBB8[]` + `lbl_8038EBB8[idx*2]` emits `lwzx rD, base, scaled-idx` (retail's order), while `(char*)lbl + idx*8` emits the scaled index as rA (88.9% ceiling). Replaced the asm-pinned body with plain C — DOL re-verified byte-identical. Worth re-checking other asm-pinned drafts for this same typing lever.
- **Leaf reads its arg directly:** fn_8011ED40 (no prologue) uses r3 for `idx*8` before any call; declaring `s32 idx` suffices.
- **Call-chain validation:** fn_8011A6A8 → fn_80119934(arg0,arg1) (2-arg, r29=r4 confirmed in retail) → returns slot idx; fn_8011F210(idx) → fn_8011ED40(idx) → AXSetVoiceState. Arities now consistent across six promoted files.

Working tree: 2 new promoted files (A6A8/A95C) + 2 rewritten already-promoted sources (ED40/F210) + splits.txt/configure.py + WIP.md; temp sweep scripts removed.

## 2026-09-04: fn_80119934 — EXACT, promoted, DOL byte-identical

Last unpromoted link of the voice-pool chain (callee of fn_8011A6A8, sibling of fn_8011A95C): 212B dual-field search over the 59-slot lbl_80387E44 pool, promoted EXACT.

- **What it is:** two passes over the pool — pass A returns the first i in 0..0x3A whose slot->id1 (word at +0) equals id with fn_8011ED40(i) active; pass B (i reset to 0) re-scans for slot->id2 (word at +4), running QB side effects fn_801257B8(0x6D2E270E, 0), and only if that returns 0 then fn_801257B8(0xD7BB618D, 0), before returning i; nothing found -> -1. arg0 is unused (2-arg ABI matches fn_8011A6A8's call).
- **KEY: struct-typed access is the whole match.** The pool entries are really 0x3C-byte structs; writing `lbl_80387E44[i].id1` / `.id2` reproduces retail byte-for-byte. Pointer-walk reconstructions (char*/s32* stepping +0x3C) stalled at 24.5%→43.4%→69.8%: GCC folds `lbl + 4` into a single symbol-addi for pass B while retail materializes the base (`addi r9,0x7e44`) then adds 4 (`addi r30,r9,4`) — the two-addi chain only falls out of struct-field strength reduction. Third confirmation that *typed* source (float arrays, s32[] tables, struct arrays here) beats cast/pointer spellings.
- **Loop shape:** retail pre-advances the walk pointer right after the load (`lwz; addi r30,+0x3c; cmpw`) — the advance must be written BEFORE the compare in the loop body or GCC sinks it to the bottom (position shift cascades every word).
- **m2c defects:** dropped arg0, hallucinated pass-B base as independent address 0x80387E48 (it's pool+4), and its `block_3` goto maze was fine semantically but wrong shape.

Cluster status: fn_80119934 → fn_8011A6A8 → fn_8011F210 → fn_8011ED40 plus fn_8011A95C are ALL promoted now; the pool-manager chain is fully EXACT end-to-end.

Working tree: 1 promoted file + splits.txt/configure.py + WIP.md; temp sweep scripts removed.

## 2026-09-04: registry cluster round 1 — 1 EXACT + 2 parked

Next three drafts in the 0x8011A-0x8011B voice-registry region (helpers/neighbors of the pool-chain functions, sharing lbl_80302C40/lbl_80387E44/lbl_80387E50 and fn_80119470/fn_8011A95C/fn_80119B24).

| Function | Outcome |
|---|---|
| `fn_8011AC40` (84B) | 9.1% → **EXACT, promoted** — pitch wrapper: `fn_8011AC94(arg0, arg2, fn_80270A84(arg1->0, -(arg1->8)) * lbl_8029D528)`; m2c deref'd f32s as s32. Also proved fn_8011AC94 is 3-arg (r3/r4/f1) contra its 2-param wip draft |
| `fn_8011AA4C` (128B) | 22.4% → **53.1% parked** — f32 accessor with dual-default returns |
| `fn_8011B958` (156B) | 5.1% → **20.5% parked** — list walk + pool-handle return |

### Findings

- **GCC 2.95 return-block merge vs MW inline returns is a NEW wall class.** Both parked functions need retail's *inline* return blocks (A-load right after the gate test and after the fcmpu, B-load mid-function, `bne`→epilogue for the value return) — MW never hoists returns. ngccc tail-merges the two identical `return lbl_80302C3C` blocks and jump-threads the rest, producing a 4-8B shorter function where every post-divergence word misaligns. The goto-anchor fixes ONE block (AA4C: 28.1% → 53.1% by pinning the A-return inline) but the merge of the *second* identical A-return + the B/v thread remain. Compiler flag probing: ngccc rejects -fno-reorder-blocks-and-partition/-fno-reorder-blocks/-fno-tree-tail-merge (GCC 2.95-era driver) but accepts -fno-cse-follow-jumps — tried, no layout change. Open lever: express the control flow so GCC has nothing to merge (e.g. make the two A-returns differ at the C level), or a per-file flag that defeats the tail-merge.
- **The cr4/cr7 natural-C trick does NOT transfer to a cr7-dependent field SELECT inside a loop.** fn_8011B958's retail hoists `arg3!=0` into cr7 once and selects between two branch-loaded fields per iteration; GCC walks in r9 (retail r11), shrinks the frame (-0x10 vs -0x18, no r31 base save), and uses address-offset selection. Ternary / if-else / do-while / for(;;) all land 15-20%.
- **ABI finds keep compounding:** fn_8011B958 is 4-arg (r6 → cr7), fn_8011AC94 is 3-arg — both contradict their m2c drafts; fn_8011AA4C confirmed fn_80119B24 as 2-arg.

Working tree: 1 promoted file + 2 parked drafts (best forms + wall notes) + splits.txt/configure.py + WIP.md; temp sweep scripts removed.

## 2026-09-04: restored-draft bulk sweep (b581991b set) — 1 promoted + 3 stale cleaned

Swept all **1,121** restored-but-still-unmatched drafts from commit b581991b
("restore deleted wip", 2026-09-03; 1,126 restored, 5 already promoted since).
`test_wip_drafts.py --addr-file` over the exact set, 8 parallel slices:
**2 EXACT / 114 NEAR / ~999 DIFF / 3 FAIL** (FAILs are paired-single drafts that
need `-mps-float`, parked by design).

- **fn_801503F4 (412B, m2c) → PROMOTED, DOL byte-identical.** Masked-EXACT but
  the object emitted an allocatable .bss (dead `static s32 M2C_CARRY = 0;` left
  by the m2c post-process — declared, never used) so `promote_wip` skipped it
  with "object emits allocatable data outside .text". Removing the dead static
  kept 100% masked and promoted clean.
- **fn_80109F18 (244B, m2c, -fno-gcse) → confirmed masked-EXACT link trap.**
  Header note ("PARKED (link-level), do not auto-re-promote") is still accurate:
  promote registered + linked, DOL DIFFERS, auto-revert safe (draft kept in
  wip/). Reloc-addend diagnosis (doc-24 method) still open.
- **Cleaned 3 stale drafts** (fn_8000C938 / fn_8000F95C / fn_8000F9C4): their
  functions were already promoted 09-02 (b1506814, registered in
  splits/configure, WIP.md rows gone) — the restore re-created older draft
  copies that the sweep was skipping as "promoted". Deleted; inert drafts,
  DOL unaffected.

DOL re-verified byte-identical after the failed-then-reverted 80109F18 attempt
left a stale differing DOL on disk (auto-revert restores splits/configure but
does not rebuild).

## 2026-09-07: random-sample round — 2 promoted + 2 improved parks

Three random samples (24 + 20 + 12 drafts). **2 EXACT promoted, DOL
byte-identical after each:**

- **fn_801134FC (76B, m2c) → PROMOTED** — ScriptStopAllSounds: `fn_80119A90`
  walk with `fn_80112F90`-call gate + `fn_80119160` per-node; the missing
  `mr r3,r30` arg-restore between the two calls was the whole diff.
- **fn_8009A4D8 (76B) → PROMOTED** — small QB property setter.

**Improved parks:**

- **fn_8003A80C 50.0% → 95.9% parked (196B, c).** Two real fixes, not flags:
  (1) recipe-89 applies — byte-countdown 0x44A0/0x18 copy loop needs
  `// FLAG: -fno-strength-reduce -fno-schedule-insns2` (want keeps
  `li r10,0x44A0; addic.; bne`, plain compile emits mtctr/bdnz);
  (2) the detach call passes the HANDLER, not the object:
  `fn_80009AAC(arg0->unk0x60)` — want's `r3` already holds the +0x60 load at
  the call, the arg0-form injected an extra `mr` and shifted everything.
  Identified: script-object node-list assign (name copy via fn_80126F40,
  handler re-register via fn_8003AE28, 294×6-word array copy, +0x64 copy,
  returns arg0). Residual: `+1c/+34/+4c` branch displacements only
  (reloc-masked at link; masked pct 95.9 because the 3 target words sit in
  masked insns — verify at promote time).
- **fn_801430FC permutation matrix closed (94.3% stays).** Swept all 6
  source-load orders of the tail's f_a/f_b/f_c × 3 flag sets = 18 compiles:
  abc/bac 94.3, bca/cba 93.1, acb/cab 90.8. GCC's scratch-reg coloring
  (want F808→r11/F80C→r10/F810→r9 vs got r9/r11/r10) is reg-allocator, not
  source-reachable; parking note updated with the full matrix.

**Confirmed parked (no movement):** fn_8014E1DC 96.6% (scheduler 2-word swap,
13-shape re-probe stands), fn_8007BDC8 71.4%→kept best (preheader hoist flip),
fn_80057EF4 71.4% (was 50.0% — struct-field typing redraft). fn_8009A5B4
re-probed at 95.1% NEAR, still parked (known wall).

Sample-3 residual DIFFs (all m2c stubs <27%, no action): 8009A898 26.7,
8028DF98 19.0 (matches 09-06 raw-lit sweep), 801F3910 18.4, 8000FAB4 9.7,
8009A524 5.9, 800E46FC 4.8, 80146560 1.0, 8009A658/800079D8 0.0.

Working tree: 2 promoted files + 3 parked drafts (best forms) + WIP.md;
probe script removed.

## 2026-09-07: random-sample round 2 — parks re-verified, no promotion

Sample 4: 20 drafts (seed 4). Top: 80161420 94.9 / 80143B7C 94.3 /
801414F0 93.8 (all three are known doc-15 coin-flip parks, notes stand) /
**fn_8014DDFC 77.3% (792B)** — the only draft with real headroom.

- **fn_8014DDFC re-probed 78.9→77.3 parked.** Full diff census: 104 words =
  21× merge-test `lbz r0` (all one root: the shared merge-test var sits in
  callee-saved r27 instead of want's r0 scratch) + branch-displacement
  shifts + prologue frame (stmw r27 vs want stmw r28). Re-tested the old
  claim "pinning var_r0 to r0 moves ~45 switch lis/ori": today it costs
  77.3 → 48.5 (r0-pin) / 37.4 (r0-pin + ternary) — worse than the park.
  New shapes probed: table-addr fold `-0x48` pre-computed (76.8), named
  tbl temp (FAIL), byte-7/8 conditional cases as ternary selects (66.2),
  QB_Z direct ternary return (77.3, no change). All regressions; want's
  r0-scratch merge var + r28 save-set stays GCC-unreachable from this
  source shape. Park note updated with today's numbers.
- Sample-4 residual DIFFs (no action): 800CC2D4 38.9, 8001A7AC 35.3,
  800888B0 33.3, 8000FE2C 26.3, 800E43E8 22.2, 8003AEEC 15.0, 800E48E0 13.9,
  8009A788 13.2, 801FFEE8 2.8, 8005D20C 2.0, 80026140 1.4, 80003984 1.1,
  8028D930/80004518/80008E50/800079D8 0.0.

Working tree: 1 parked draft updated (fn_8014DDFC note); probe script
removed; DOL untouched (md5 c3516735…).

## 2026-09-07: random-sample round 3 — 1 promoted (DOL byte-identical)

Sample 5: 20 drafts (seed 5). **fn_80024D00 47.6% → EXACT, PROMOTED (168B,
DOL byte-identical, md5 c3516735… unchanged):** script-object stream/label
reload. Three real fixes:
- arg0 +0xC is a pointer-sized stream HANDLE, not the shared struct's s32
  (sibling fn_80024CA4 EXACT passes the same field to fn_800551D4(ptr)) —
  the handle type loads into r3 for the NULL gate (want `lwz r3,0xc(r31)`)
  and kills the r0-temp;
- the format string is the registered rodata2 symbol `lbl_802913E8`
  ("models\\%s\\%s"), not the raw literal — fixes the lis/addi vs lis/ori;
- **fn_80060490 consumes a NINTH stack arg** (AGENTS §6af already knew);
  widening the proto and passing `sp8 = 0` explicitly restored the 0x220
  frame (want stw r0,8(r1) = the stack-arg home).
- The m2c `fn_80054388(arg1, 0x802913E8, &sp10)` was also arg-swapped
  (want r3=arg1 label, r4=string) — the symbol swap fixed the arg order.

**fn_80054388 (its corrupted callee) redrafted 23.3% → 42.5% parked (152B).**
Real structure recovered: 2-arg `strstr(arg0, "/")`-gate pair (want's own
`bl strstr` words match unmasked) + varargs `fn_80269F4C(arg2, lbl, arg0,`
`arg0, arg1)` print. ngccc does NOT crossjump the two strstr bl sites for
this body (160B vs want's single shared bl at +24 — the doc-31 merge) so the
whole tail sits one word off. 3/4/5-arg and goto/ifelse/twin-gate shapes
swept: 5-arg best (42.5), 4-arg 28.9, 3-arg 2.6. doc-31 note: sister
fn_8005529C kept both bls — retail's merge condition is narrower than
recorded; new member added to doc-31.

**Doc-15 members re-confirmed parked (no movement):** fn_8009A5B4 95.1
(caller fn_80024D00 promotion didn't shift its li-grouping coin),
fn_80143B7C 94.3, fn_8014DDFC 77.3 (re-probe stands).

Sample-5 residual DIFFs (no action): 800E43E8 22.2, 8009B3B4 19.1,
80057FBC 18.8, 8005896C 18.7, 8003AEEC 15.0, 8009A788 13.2, 80007A4C 6.9,
80006FA8 6.1, 8020D1F4 5.0, 80026140 1.4, 800E5FE4 0.6, 800086B0 0.2,
8008EDC0 0.1, 8028D930 0.0, 8002CDE4 stub.

Working tree: 1 promoted file (fn_80024D00) + 1 redrafted park
(fn_80054388) + splits/configure + WIP.md; probe scripts removed.

## 2026-09-07: unparked sweep + SDA-route promotions — 4 promoted (DOL byte-identical)

Full sweep of all 2,437 drafts without a PARKED marker (6 foreground slices).
Results: 2 EXACT + ~88 NEAR + ~2,240 DIFF, plus 3 compile-error drafts.

**Promoted (5 total, DOL byte-identical after full rebuilds):**
- **fn_8027052C** (224B) — `sin()` (fdlibm). Was 98.2% standalone with one
  R_PPC_EMB_SDA21 false diff; LINK-SIM EXACT via sda_verify; registered in
  configure.py with `-msdata=eabi -G8 -fno-schedule-insns2` (AGENTS.md 5q).
- **fn_80270290** (348B) — `floor()` (fdlibm). Header already said
  "EXACT via sda_verify" but was never registered — same 5q route,
  `-msdata=eabi -G8`.
- **fn_8028E008** (48B) — dispatcher thunk (.sdata handler slot
  lbl_803CA324), VERIFIED EXACT note from 2026-08-26, never registered;
  same 5q route, `-msdata=eabi -G4`.
- **fn_80072230** (120B) — record-array init with 0x600 delay loop.
  86.7% → EXACT: the inner delay counter must REUSE `var_r7` (the outer
  counter's variable — `li r7,0x600` overwrites it after the hoisted
  `var_r7-1` lands in r0 for the `!= -1` test); the outer counter is a
  separate `var_ctr`. Distinct names for the two counters were the
  register-coloring blocker.
- (earlier in session) the 160B store-swap family x6, fn_8002B920, etc.

**Improved parks:**
- **fn_8003ED20** 68% → **81.8%** (36/44): the m2c goto-form loop was the
  blocker — a plain `while` spelling gives want's rotated shape (b over body
  to bottom test) at exactly 176B. fn_801285A4 prototyped (kills its crclr),
  fn_801294BC must stay unprototyped (prototyping restructures the loop,
  18/44). Residual: ProDG per-use sp8 reloads (body-top r3 + post-call r9)
  vs GCC's stack-slot CSE — 8 words.
- **fn_8003A80C** parked at **95.9%** (47/49, FLAG: -fno-strength-reduce
  -fno-schedule-insns2): residual = GCC doloop CTR conversion (mtctr/bdnz vs
  want's addic./bne, 6 words) + tail return-value order (2 words). No
  -fno-doloop in this GCC; bottom-decrement/break forms and 8 flag combos tie.

**Re-confirmed walls (no breakthrough, notes unchanged/current):**
- fn_80173D30 (99.5%, 1 word): r30-pin copy-prop forwards the branch-proven
  value into the fn_80131008 arg where want rematerializes `li r4,0`;
  single-assignment tmp form tested → 97.2% regression.
- fn_8025A894 (96.7%): TRK naked draft; andis. dest + cmplwi/cmpwi
  eq-canonicalization, both GCC-canonicalization walls.
- fn_8008076C (94.8%): one color left (sub reload r6/r9 vs want r11);
  4 spelling nudges tie.
- fn_80031EC8 parked at 79.6%: single r29/r31 role swap cascade (doc-06).

Tooling note: run_terminal_command background jobs get killed — sweep must
run in foreground slices; /tmp/leaf scratch is slice-safe because slices
compile disjoint addresses.

## 2026-09-07: db-module wired as mwcc lib objects - 5 promoted (DOL byte-identical)

The 5 "VERIFIED EXACT (mwcc)" g6 drafts (fn_8028D340, fn_8028D6FC=DBRead,
fn_8028D824=DBInitInterrupts, fn_8028D878=DBInitComm, fn_8028D930=MWCallback)
are now wired into the build as **lib objects in the OdemuExi2 module**
(mwcc GC/1.2.5n, cflags_odemuexi2) - src/OdemuExi2/*.c - and the full build
is byte-identical. First mwcc-lib promotions from wip drafts.

Key learnings (trap documented):
- The g6 drafts were verified under mwcc, but the game lib ("game" module)
  compiles via ngccc - which CANNOT emit the SDK prologue order
  (`mflr r0; stw r0,4(r1); stwu` before anything else) nor small-data SDA
  forms. Under ngccc, fn_8028D340 compiled 48B vs want 44B and the +4 shift
  broke every downstream bl (1348-byte DOL diff). Never register a
  mwcc-verified draft into the ngccc game module.
- Correct route: put them in the matching lib module (OdemuExi2, mwcc
  GC/1.2.5n). The wip drafts' stale body names (Vtable0x803089D0_m7/m8/m10,
  fn_8028DAF4, fn_8028D930) must be renamed to the real SDK symbols
  (DBInitComm/DBInitInterrupts/DBRead/DBGRead/MWCallback) so data-table
  references (lbl_803089EC -> DBRead) resolve.
- Shrink OdemuExi2/DebuggerDriver.c's split to its first contiguous range
  (0x8028D494-0x8028D6FC); a unit with discontiguous ranges around interior
  units makes dtk's link-order resolver report a cyclic dependency. The gap
  regions (DBQueryData/DBGHandler/DBG*) get auto stubs - unlinked/unstubbed
  regions keep original DOL bytes via patch_dol.
- DBInitComm writes MMIO 0xCC006828; added `lbl_CC006828` absolute symbol to
  config/G2TE52/ldscript.tpl (pattern: lbl_CC008000).
- mwcc objects must be pure ASCII (sjiswrap warns on UTF-8 dashes).
- Tooling trap: `for`-loop + heredoc + relative paths in one shell command
  cross-wired file contents once (files rewritten from the wrong wip draft);
  restored drafts from git (83487ead6) and rewrote in a single script.

## 2026-09-07: odemuexi2 moved into libs/ (structure parity with other libs)

The OdemuExi2 module now lives in the standard lib tree like dolphin/libgcc:
- include/odemuexi2/DebuggerDriver.h -> libs/odemuexi2/include/odemuexi2/
- src/OdemuExi2/*.c -> libs/odemuexi2/src/ (all 6 files, git mv)
- configure.py module: "lib": "odemuexi2", src_dir "libs/odemuexi2/src",
  object paths de-prefixed (DebuggerDriver.c, DBGFlushBuffer.c, ...);
  cflags_odemuexi2 gains -ir libs/odemuexi2/src -i libs/odemuexi2/include
  BEFORE the dolphin paths (its own types.h-style headers win).
- splits.txt unit headers renamed to odemuexi2/<file>.c (dtk derives unit
  names from the split headers, so they must match the new source paths).
- Verified: full rebuild, all 6 objects under build/G2TE52/obj/odemuexi2/,
  DOL byte-identical; nm shows DBGFlushBuffer@D340, DBRead@D6FC,
  DBQueryData@D788 (stub), DBWrite@D49C (stub), DBInitComm@D878,
  MWCallback@D930 - all at their retail addresses.
- libs/README.md documents the module.

## 2026-09-08: odemuexi2 completion sweep - 12 new EXACT drafts, wiring deferred

Rewrote the remaining OdemuExi2 functions as standalone TUs under
libs/odemuexi2/src/ and verified each with tools/mwcc_verify.py (single-word
whole-.text compare against the DOL slice, same cflags as the lib module):
- DBClose/DBOpen (4B no-ops): EXACT
- Vtable0x803089D0.c (m0-m6 thunks, one TU): EXACT (m4 returns 0, m5/m6 void)
- fn_8028D464: EXACT
- _DBGReadStatus (D96C, 0xAC): EXACT (Select/Sync/Deselect inline static,
  DBGEXIImm extern)
- DBGWrite (DA18, 0xDC): EXACT (same shape; SDA refs via lbl_-prefixed externs)
- DBGRead (DAF4, 0xDC): EXACT
- DBGReadMailbox (DBD0, 0xAC): EXACT
- DBWrite (D49C, 0x260): EXACT (SendCount extern named lbl_803CAA58 so
  mwcc_verify patches the SDA offset; frame 0xFFD0)
- DBQueryData (D788, 0x9C): EXACT - old park note's "1-insn scheduling slot"
  was a harness artifact; extern helpers fixed it
- DBGHandler (D8F0, 0x40): EXACT - same; the "mwcc floats cmplwi" wall was
  also an artifact of the wip harness context
- DBGEXIImm (DC7C, 0x298): drafted, NOT yet verified
- fn_8028D36C: re-attacked in the standalone-mwcc context; tail (x8 CTR
  unroll + andi. remainder) now understood and matched, but the 7-word head
  block (cmplwi/subfic-r3/li-r6/bgelr) still walls ~25 spellings; park note
  updated. Parked wip draft kept as best (93.7%).
- fn_8028DF3C / fn_8028DF98: untouched.

NOT yet wired: the 12 verified sources are not registered in configure.py's
odemuexi2 module or splits.txt. Wiring plan (resume from here):
1. Add each file to the odemuexi2 module Object list (Matching) and to
   splits.txt as odemuexi2/<name>.c units with their ranges:
   fn_8028D464 D464-494, DBClose D494-498, DBOpen D498-49C, DBWrite D49C-6FC,
   DBQueryData D788-824, DBGHandler D8F0-930, _DBGReadStatus D96C-A18,
   DBGWrite DA18-AF4, DBGRead AF4-BD0, DBGReadMailbox BD0-C7C,
   DBGEXIImm C7C-F14 (needs verify first), Vtable0x803089D0.c F14-F3C.
   Shrink the DebuggerDriver.c NonMatching split accordingly (keep it
   contiguous; gaps get auto stubs).
2. The shared statics (SendCount/lbl_803CAA58, DBGCallback, SendMailData,
   RecvDataLeng, pEXIInputFlag, EXIInputFlag, lbl_803CAF18 buffer ptr) must
   live in exactly one linked TU - put them in DebuggerDriver.c (it is
   NonMatching but its .data/.sdata DO link; verify no duplicate-symbol).
3. Rebuild, cmp orig/G2TE52/sys/main.dol build/G2TE52/main.dol, update
   libs/odemuexi2/README.md checkboxes.

## 2026-09-08: 16 odemuexi2 functions wired as Matching, DOL byte-identical

Registered the 12 drafts + the 4 previously-wired functions as
Matching lib objects; the whole module D340-DF14 is now matched except
fn_8028D36C (parked head-block), fn_8028DF3C/fn_8028DF98 (no drafts), and the
fn_8028DF14-DF38 thunks (already matched in the game module):
- splits.txt: old odemuexi2/DebuggerDriver.c unit (D494-D6FC) replaced by
  fn_8028D464/DBClose/DBOpen/DBWrite/DBRead/DBQueryData/DBInitInterrupts/
  DBInitComm/DBGHandler/MWCallback/_DBGReadStatus/DBGWrite/DBGRead/
  DBGReadMailbox/DBGEXIImm units at exact symbol ranges.
- configure.py: same 15 files added to the odemuexi2 module (Matching).
- DBGEXIImm verified EXACT (664B) after un-static-ing the definition.
- Fixed DBGReadMailbox.c: body was misnamed `_DBGReadStatus` (tww confirms
  DBGReadMailbox = cmd 0x60000000; _DBGReadStatus = cmd 0x40000000).
- Link resolves all externs: DBGEXIImm cross-TU; data symbols lbl_803CAF1C/
  20/24/28/2C/30/34/803CAA58 via auto-stub objects; OS* from dolphin.
- Vtable0x803089D0.c NOT wired - those 7 thunks are already matched in the
  ngccc module as fn_8028DF14-DF38 (wiring both would duplicate symbols).
- Full rebuild: LINK OK, DOL BYTE-IDENTICAL; nm shows all 16 symbols at
  retail addresses (DBGFlushBuffer D340 ... DBGEXIImm DC7C).

## 2026-09-08: vtable thunks moved into odemuexi2 lib; promoted wip twins deleted

- The 7 dispatch thunks fn_8028DF14-DF38 were already matched as gen-leaf
  files in the GAME module under their attested names Vtable0x803089D0_mN.
  Moved (git mv) them to libs/odemuexi2/src/Vtable0x803089D0_m{0..6}.c and
  swapped the registrations from the game module to the odemuexi2 module
  (configure.py + splits.txt). The single-TU Vtable0x803089D0.c draft is
  redundant and was deleted. DOL byte-identical.
- fn_8028DF3C was already matched/promoted in the game module (configure.py
  line ~7360); only fn_8028DF98 remains draftless in the module.
- wip cleanup: deleted src/wip twins of promoted functions where the wip copy
  is fully superseded - fn_8009A758, fn_8028D464 (unparked twins), plus
  fn_80285050 (-> gx/GXInit.c), fn_8028D788 (-> DBQueryData.c), fn_8028D8F0
  (-> DBGHandler.c) whose park notes predate the lib-route EXACT matches.
  All other wip drafts kept (unpromoted or still the best available form).
- Verified: full rebuild, DOL byte-identical, all 23 module symbols at retail
  addresses.

## 2026-09-08: fn_8028DF98 attacked and parked (best 10/20 off)

The last unwired OdemuExi2-range function (0x8028DF98, 80B) — MSL-style I/O
dispatch: fd 1..2 -> fn_8028DF3C (WriteUARTN wrapper), fd 0 -> -1, else ->
lbl_8025C558 (attested label, direct bl). No callers in the DOL (data/fn-ptr
only); no tww reference.

Breakthroughs this session:
- Identified want's exact structure: ble to a *trailing* block containing the
  two arg shuffles + bl fn_8028DF3C, default case inline, `li r3,-1` hoisted
  between `cmpwi r9,0` and `beq` (pre-materialized ternary arm).
- ProDG 3.9.3 `register s32 fd` trick forces want's head exactly (mr r9,r3 +
  addi r0,r9,-1 + cmplwi r0,1): `g9` variant.
- ProDG goto-form forces want's block order but loses the head; mwcc 1.2.5n
  `p1` matches want's tail block-for-block.
- mwcc_verify want-slice caveat: harness reads len(got) bytes, so 76B bodies
  compare against a truncated want — always sanity-check body size vs
  symbols.txt (fn_8028DF98 is 0x50).

Park reason: every shape with the right head has blocks swapped, every shape
with the right block order loses the head; the ngccc arg-shuffle hoist is not
killable via accepted cc1 flags. ~40 shapes across both compilers documented
in the park note in src/wip/fn_8028DF98.c. OdemuExi2 module stays 26/28
(fn_8028D36C and fn_8028DF98 unmatched; everything else wired and
DOL-byte-identical as of).

## 2026-09-09: random no-park sweep — 4 promoted, 3 parked with breakthroughs

Random no-park drafts from `src/wip/`, matched before parking.

**Promoted (DOL byte-identical):**
- `fn_8011850C` (ScriptUnloadAnim, 232B) — key: `fn_800F28E4` takes **2 args**
  (its `mr r4, r3; cmpwi r4, 0` was the return value being passed on as arg2);
  the two trailing zero-stores emit in **reverse source order** (0x48 before 0x4C
  in C to get 0x4C-first in asm).
- `fn_801848C8` (104B) — key: the function is **void** (callers discard the
  result). The "return arg0+4" was coincidental — the latch's `addi r3, r31, 4`
  is the body call's arg; a real `return arg0+4` breaks the merged-latch shape
  (34.6%) while `void` hits 100%.
- `fn_8009C838` (112B) — allocator `fn_800098F4` takes **1 arg** (m2c passed a
  spurious 2nd); the unk0x14 store + call arg share the hoisted pool load.
- `fn_801A3A30` (104B) — both `fn_801812B8`/`fn_801812DC` take **3 args**
  (s32, s32, f32); trailing stores again emit reverse-source-order.

**Parked with big improvements:**
- `fn_8007E5EC` (232B, 82.8% with `-fno-schedule-insns`, 79.3% plain): fixed
  m2c's s32*-scaled `stwx` (dest is byte-addressed), counter must init **after**
  the alloc call to stay in r6, guard as `if (var_r6 < (u32)count)` do-while,
  loop loads/stores in reversed C order, callback as symbol `fn_8007E4B0`
  (literal materializes lis+ori; symbol gives want's lis+addi). Residual: first
  word color r0 vs r8 + a load-order swap GCC won't change.
- `fn_8007111C` (624B, 82.7%): local `Vtbl7111C` struct with **s16** offsets
  (want uses `lha`), `fn_801293FC` returns s32 (not s8), frame struct local
  forces slot layout (GCC 2.95 allocates plain locals in first-use order, which
  put sp8 at 0x24), color packing via `u8 *col` base reproduces the
  `addi r9, r1, 0x24` word. Residual: arg0 in r29 vs want's r31 (cascades into
  every vtable section) + byte-store schedule.
- `fn_800F2EDC` (172B, 30.2%, 160B got): semantics proven (7-arg F2BA8 call,
  r10 = arg0->unk0x18). Residual: GCC cross-jumps the two `return 0` tails the
  want keeps separate (preset-0 setcc), arg colors, frame 0x28 vs 0x30.

All three parked drafts carry full notes in the file headers.

## 2026-09-09: fresh random no-park sweep — 11 promoted, 4 parked

Second random sweep of no-park drafts; all worked to 100% before promoting.

**Promoted (DOL byte-identical):**
- `fn_8005D0F8` (84B) — nested linked-list walk; m2c's guarded do-while was
  wrong, want is a plain `while` (`cmplw; blt`); walker must be `void *`
  (an `Unk_2EF06E12 *` scales `var_r31 += 0xC` by the 0x7B0 struct size).
- `fn_801288C4` (128B) — recursive search; the giant one-expression boolean
  rematerialized `0xD0000` inside the loop; rewriting as an if-chain lets
  LICM hoist `lis r29, 0xD0000` into the preheader. 100% on first try.
- `fn_8009E1F0` (72B) — `unk0x20` read as **s16** (`lha`), and drop the
  spurious 4th call arg (`mr r6, r9`).
- `fn_801A7048` (92B) — m2c's `*((s32 *)base + idx)` scaled by 4; want is
  byte offsets (`lwzx`); the mask is `-2 rol (arg1 & 0x1F)` = `~(1 << n)`.
- `fn_80060934` (112B) — keeps a dead `stw` to 8(r1): the local must be
  `void **volatile` (plain volatile cast gets DCE'd); the `mr r3, r0` +
  conditional-reset shape came from `return temp_r9->unk0x14` inside the if.
- `fn_800130AC` (112B) — the two-addi address materialization
  (`0x349C + 0x18C`) comes from separate pointer-increment statements in
  source, not an index `[0x63]` (which GCC folds into one addi).
- `fn_80025224` — same recipe as `fn_8009E1F0` (s16 `lha` read + extra arg).
- `fn_800A6C3C` (132B) — loop counter must be **u32** post-decrement
  (`do { } while (var_r31-- != 0)`); trailing stores emit reverse source
  order (C order 0x4, 0x8, 0x14 → asm 0x14, 0x8, 0x4... verified exact).
- `fn_8001F91C` (312B) — dispatch table at 0x80300278/0x8030028C must be
  referenced as **symbols** (`extern char lbl_80300278[]`), not hardcoded
  constants: the want materializes two separate base registers (r9 for the
  first call's load, r30 hoisted for the loop) which only symbol refs with
  @ha/@l pairs reproduce; hardcoded addrs give lis+ori and 23%.
- `fn_8005EBA4` (64B) — f32 store needs `*((f32 *)&unk0xC)` cast (struct
  field is s32); vtable offset is an **explicit s16 deref** at +0x38
  (`*(s16 *)((char *)p + 0x38)` — a plain `(s16)` field cast makes GCC load
  from +0x3A on big-endian); the vtable fn takes **1 arg**.
- `fn_80033F10` (144B) — six f32 stores need casts; GCC rotates the last
  written store to the front (source order 0x2C,0x18,0x1C,0x20,0x24,0x28
  emits want's 0x28,0x2C,0x18,0x1C,0x20,0x24); `fn_8006FB50` takes
  **2 args** (the sibling `fn_80033AF4` pattern: pass `unk0x30` back in);
  `fn_800335E0` **returns** the inner call's result, and that return value
  is passed **directly** into `fn_8009FDD8` (want skips the re-`mr r3,r30`
  because fn_800335E0 leaves r3 = its return).

**Parked with best-match bodies:**
- `fn_8009E004` (172B, 83.7%) — all 5 list-init store groups match after
  source-order rotation; residual is a 7-word register-allocation cascade in
  the tail (F18/F1C load order vs `mr r3, r30` placement).
- `fn_800134AC` (244B want, 252B got) — deep scheduling hole around an
  8-arg vtable call; symbol-reference fix landed but store orders still shift.
- `fn_8002DD70` (60B, 46.7%) — float-field init (s32 struct fields, want
  stores floats): GCC's scheduler reorders the stfs regardless of source
  order; variant A (source order) is best.
- `fn_80124F44` (152B, 63.2%) — float→int conversion guard. Full source
  proven: `fn_800145AC()` takes NO args; conversion is `(f64)(u32)diff`
  (plain stw + magic 0x4330000000000000, no xoris); `^ 0x80000000` belongs
  to the `>= 2^31` path (lbl_8029E438 as f64). Every want word matches
  except one dead `mr r3, r9` GCC 2.95's first scheduling pass inserts into
  the fall-through fix_truncdfsi2 chain — all ~20 alternative source shapes
  (ternary, result-var, `<` vs `>=`, explicit else, f64/u32 temps) either
  keep the mr, invert the branch layout, or shift FPR/GPR colors.

## 2026-09-11

Picked random drafts with no parking/probe comments. First swept all 2,182
unparked drafts with the standard compile+masked-compare harness (8-way
parallel): 5 already-EXACT, 83 NEAR. **14 promoted, DOL byte-identical
(`main.dol: OK`, `cmp` clean) after each batch:**

`fn_8000E324`, `fn_8001B56C`, `fn_80062584`, `fn_800966D8`,
`fn_80058EE4`, `fn_80024724`, `fn_8003B6D4`, `fn_8005B9B4`,
`fn_8005D7D4`, `fn_801BE7F4`, `fn_8001D424`, `fn_8009C508`,
`fn_801A57D4`, `fn_800EC330`.

**Missing-prototype / crclr class (doc-52) is still the cheapest bulk win**
(`fn_8003B6D4`, `fn_8005B9B4`, `fn_8005D7D4`, `fn_801BE7F4`): m2c strips
callee protos, so ngccc inserts `crclr cr1eq` / `crset cr1eq` before the
`bl`; adding the real prototype drops it. m2c also frequently mis-counts args
(`fn_8005D7D4` phantom 3rd, `fn_800EC330` phantom 3rd, `fn_801A57D4` phantom
5th) and drops the leading arg0 (`fn_801BE7F4`).

New generalizable recipes found this session (all pure C, no asm):

1. **"Return-value" explains the phantom `mr r11,r3`** — three tiny
   functions m2c typed `void` actually RETURN their object; the return-home
   copy is want's `mr` and it also fixes the store scheduler's merge order
   (`fn_80024724`, `fn_80058EE4`, `fn_8001D424`). The loaded value landing in
   **r3** in want is the tell. Re-check the "pure regalloc coin" parks for
   this before blaming allocation.
2. **Ascending source stores emit descending order** — `fn_8001D424`: writing
   the three `stfs` in ascending source order (`unk0, unk4, unk8`) makes ngccc
   emit want's out-of-order `8,0,4`; every other source order is 4-5/7.
3. **Named index local controls mulli-vs-shift-add** — `fn_8009C508`: a
   `s32 i = arg1 * 3;` local then `p[i]` gives want's `slwi/add/slwi` and the
   r9/r11 coloring; `p[arg1 * 3]` or a `Vec3*[arg1].x` folds to
   `mulli r4,r4,0xc` (0%). Also reproduces want's exact register homes.
4. **s16 self-offset in vtable blobs** — `fn_800EC330`: want `lha r3,8(r9)`
   means the vtable's +0x8 offset byte-pair is a SIGNED HALFWORD; typing the
   local Vtbl struct `unk0x8` as `s16` fixes it (s32 gives `lwz`).
5. **f32* params instead of struct-field casts** — `fn_800966D8`: retyping
   `Unk_2EF06E12*` -> `f32*` (fields at +4) removes an s32->f64->f32
   conversion and exposes the pure `fcmpu/mfcr/rlwinm` setcc. Loop shape:
   `s32 r = a > b; if (!(a < b)) return r; return -1;` is what materializes
   the setcc BEFORE the `bgelr` (the natural `if (a<b)...` hoists li/blt).
6. **Bitfield insert** — `fn_80062584`: mask/shift/or emits rlwinm/rlwinm/or;
   typing the slot as a bitfield struct with a 1-bit field at bit 3 emits the
   single `rlwimi`.

**Link-level trap (new):** `fn_8001DFF4` re-promoted in a batch and DOL-diffed
at 32 bytes, ALL inside its own range — masked-EXACT is NOT link-exact for its
doc-51 raw-lit->symbol rewrites (the 16 dispatch-table stores resolve
`lis+addi` vs retail and the lbl_803CAF18 anchor ordering differs). It poisons
a whole promote batch; park/verify it alone. The batch revert correctly rolled
back `fn_8000E324`/`fn_8001B56C`, which then promoted clean. (The old
".sdata2 +0x40" blame is wrong for this member.)

**Parked with best-match bodies (this session):**
- `fn_80125548` (32B, 12.5%) — semantics fixed (m2c scaled the loaded base
  instead of indexing it); residual is pure regalloc (want idx->r9/lis->r11/
  base->r10 vs ngccc lis->r9/idx->r0/base->r11); ~6 shapes identical.
- `fn_8000DDB0` (76B, 89.5%) — real source is a plain `while (test==0) call();`
  (m2c's top-test goto gave 57.9%); residual is ONE loop-exit scheduling coin
  (want `li r3,0` before the loop-back `beq`, ngccc after).
- `fn_801744B8` (80B, 90.0%) — byte-index fixed; residual is the dead index
  temp's register (want r0, ngccc reuses arg1's r4 for stwx).
- `fn_801A871C` (120B, 86.7%) — duplicate extern + phantom args + fn_80019D08
  arg fixed; residual is one arg-setup order swap on the 2nd of two identical
  calls (scheduling, not source order).

## 2026-09-11b

Same random-unparked-draft brief, but this round was driven by four new
purpose-built search tools instead of hand-probing, which is what made the
yield 13 instead of ~2. All four live in `tools/` and are re-runnable:

- `tools/proto_audit.py` — for every draft, diff each *declared* callee
  prototype against the promoted `.c` (arity, per-arg type, return type).
- `tools/fix_call_arity.py` — for each arity mismatch, restore the real
  declaration and search (insert position x candidate expression drawn from
  params/locals/constants) for the alignment that best matches the DOL.
- `tools/store_order_search.py` — greedy search over the source order of every
  run of `base->unkNN = ...;` stores (ascending/descending field order).
- `tools/score_body.py` — score one candidate body against the DOL.

`tools/gen_leaves.py` also gained `LEAF_TMPDIR` so parallel callers no longer
race on one `/tmp/leaf/*.o` pair (this is what was silently hanging the
eight-way sweep).

**13 promoted, DOL byte-identical (`cmp` clean) after every batch:**
`fn_80123A98`, `fn_8004F210`, `fn_8005D380`, `fn_801FB15C`, `fn_800AAB54`,
`fn_8006F4AC`, `fn_8006F54C`, `fn_8006F828`, `fn_8008743C`, `fn_800A681C`,
`fn_800A6E5C`, `fn_800B0DB0`, `fn_80128FFC`.

New generalizable recipes (all pure C — no asm added):

1. **Write the store block in ASCENDING field order.** The DOL order is the
   *compiler's* schedule, not the source order. `fn_8004F210` missed by 9
   stores that source-order == DOL-order could not fix; ascending source order
   (`+0xA8..+0x1D4`) emits want's interleaved `1C0,1C8,1CC,1D0,1D4,1AC,...`.
   Same fix promoted `fn_8005D380` (85->100: `0x4,0x0,0x8` -> `0x0,0x4,0x8`).
   Found by search, not by reading disasm: ~60 permutations/second is cheaper
   than reasoning about the scheduler.
2. **A wrong-arity callee prototype hides a dropped argument — but the
   auto-guess can pick the WRONG value.** `fn_801FB15C` wanted
   `fn_801F9594(var_r3, 3)`, not `(3)`. `fn_801AF164` wanted
   `fn_801AF004(arg0, spC, 0)` — the inserted value was the pointer already
   live in r4 (want emits `mr r3,r31 / li r5,0` and never reloads r4).
   Conversely `fn_80128FFC`: the arity tool's own guess (`arg0`) was wrong and
   the correct argument was the *loaded* field (`arg0->unk0x8`), which also
   knew want's `lwz r3,8(r31) / cmpwi r3,0 / bl`. Always read the call's
   argument registers in want before trusting an auto-alignment.
3. **m2c types a byte-offset base as `s32`, then indexes it as `s32*`** — the
   offset gets scaled a second time, and the extra `slwi rX,rX,2` shifts every
   following instruction (looks like an unfixable cascade). Declaring the base
   `char *` and using `*(s32 *)(base + off)` fixes it. **One typed fix cracked
   seven functions at once**: `fn_800B0DB0` and its six twins
   (`8006F4AC/F54C/F828/8743C/A681C/A6E5C`), all 58.5% -> 100% in one edit —
   the same shape as `fn_8005D380` in the previous batch. Grep the family
   before parking any `*((s32 *)base + off)` draft.
4. **A walker typed as a struct advances by that struct's SIZE.**
   `fn_80123A98`'s sample cursor was `Unk_5B449B03 *` (0x114B) so each `+= 1`
   advanced 0x114 bytes; it is a halfword walker — `u16 *` with two separate
   `+= 1` steps also lets GCC fold the first into want's `lhzu`.
5. **Raw address literal vs symbol** — `0x802ABC84` materialises as `lis+ori`
   (plus a stray `lis r0`), the `.rodata2` symbol `lbl_802ABC84` as want's
   `lis r9,ha / addi r9,r9,lo` pair. Check `config/G2TE52/symbols.txt` before
   spelling an absolute address as a constant (`fn_801AF164`, 67.4 -> 79.1).
6. **Pointer-table index written with pointer arithmetic on the INTEGER.**
   m2c's `*(s32 *)(idx * 4) + 0x8039BE6C` scales the table address by 4; the
   fix is the table as a real array (`lbl_8039BE6C[idx]`). Same file also had
   recipe 4 (`fn_80123A98`, 84.1 -> 100).

**Improved but not matched (best bodies kept, reasons in-file):**
- `fn_801AF164` 79.1% — both real fixes applied (symbol + dropped arg);
  residual 9 words is arg-setup scheduling (`li r6,0` early in want) plus the
  r6-vs-r0 colour of the sp8 reload. `-fno-schedule-*` and ~20 shapes: no move.
- `fn_80128FFC` — promoted from 70.4% to 100% once the call argument was
  corrected; kept as the worked example for recipe 2.
- The 70.7% `Unk_2EF06E12` hash-table family is fully retired (see recipe 3);
  the remaining NEAR list is now dominated by documented walls
  (`fn_80173D30` 99.5% one-word scheduler pin, `fn_8007E5EC` 79.3% allocator,
  `fn_80166640` 94.2% store-sink).


## 2026-09-11c

Same random-unparked-draft brief.  2163 no-park drafts swept (38 s, 8-way);
`tools/fix_call_arity.py` run over the whole set; `tools/fix_void_calls.py`
(new) and `tools/stmt_perm_search.py` (new) added.

**Promoted (DOL byte-identical after every batch):**
- `fn_801AF164` (172B, 43 words) — `fn_801AF004` really takes 4 args and the
  4th is the already-live `sp8`; plus drop the stray file-scope
  `static s32 spC;` (see recipe 10).
- `fn_80054F08` (144B) — `*(void **)0x80364C28` must be the symbol
  `lbl_80364C28`, and the cursor's `unk0x4` test must be hoisted into its own
  local BEFORE the `var_r30 = temp_r9` copy (see recipe 8).  No pins.
- `fn_80225E70` (504B, paired-single) — the entire 40% gap was ONE phantom
  argument (see recipe 7): `fn_800F100C` is `void f(void)`, but
  `fix_call_arity.real_proto()` counted a `(void)` parameter list as one `s32`
  and so "restored" a bogus arg on every attempt.  Removing it frees r26 and
  the r26/r27/r28 role set (found/idx/zz) falls out exactly as want has it.
- `fn_80016810` (76B) — `fn_800158D8` is `void f(void)`; the
  `(s32)lbl_80290B50` argument was pure m2c invention (the store to `unk0xC`
  is real, the call arg is not).
- `fn_80009738` (84B) — same `(void)` class, found and fixed by
  `tools/fix_void_calls.py`.
- `fn_800103C4` (60B) — `var_r9 = arg0 + 0x20C; var_ctr = 7;` must be written
  in the OPPOSITE order; the pair is an independent assignment run and the
  scheduler emits it back-to-front (recipe 12).  Found by the widened
  `store_order_search.py`.
- `fn_80018570` (268B) — four independent fixes: the loop's store still used
  a raw literal (`+ (s32)0x80302EE4`) so it compiled to
  `addis r11,r31,-0x7fd0 / stw r0,0x2ee4(r11)` instead of want's
  `lwzx r9,r31,r30 / stwx r0,r31,r30` — the symbol there is `DefaultTexData`,
  NOT the `lbl_80302EE4` the draft invented (that name is absent from
  symbols.txt and fails the final link); `OSResumeThread`'s argument is
  `lbl_8031FB28` (0x8031FB28), not `lbl_8032B28`; the setup order must be
  `var_r31 = NULL; OSResumeThread(...); var_r29 = 8;`; and the two byte
  resets must be written in the REVERSE of want's order (recipe 9).

**Tooling bug fixed (this was poisoning every prior arity sweep):**
`fix_call_arity.real_proto()` treated `f(void)` as one `s32` parameter.  A
new `tools/fix_void_calls.py` targets the class directly (drafts that pass
arguments to a promoted zero-argument callee): 104 candidates, 12 improved
(0 -> 2.6, 2.2 -> 10.3, 3.7 -> 46.6, ...), and it is what surfaced
`fn_80009738`.  `tools/proto_audit.py` now reports ARITY / **VOIDARG** / TYPES
separately (VOIDARG = 132 declarations across 90 drafts).

**Parked with best-match bodies:**
- `fn_80173D30` (864B) — re-confirmed 215/216 (the one word is `li r4,0` vs
  `mr r4,r30`; ~20 more spellings incl. u8/s8/u32 temp types, `(void*)0`,
  volatile — no move).  Unchanged.

**Tooling widened: `store_order_search.py` now sees every independent store.**
The original detector only matched runs of `base->unkNN = ...`.  It now also
matches ANY run of >=2 consecutive single-line assignments at the same indent
(so `*(u8 *)((char *)p + 0x7) = 0xFF;`, `arr[i] = 0;`, plain locals), and it
emits a `rev` candidate for every run plus `asc`/`desc` when the lines carry
comparable numeric offsets.  Full run over the 505 drafts scoring >= 30%:
**one new match** (`fn_800103C4`) and **42 drafts improved** in place, greatest
first: `80060DEC` -> 91.7%, `8006C780` -> 82.9%, `8007F7F8` -> 52.0%,
`801A6E64`/`801A6ECC` -> 76.9/76.7%, `80055CB0` -> 71.7%, `8005B420`/`8005B4F0`
-> 73.1%, `801A7178` -> 68.0%.  Every improvement was re-verified in-process
before being written.

**New reusable tools** (all re-runnable, all `LEAF_TMPDIR`-safe, all now listed
in `tools/cleanup_oneoffs.sh`'s keep-list so the hygiene pass can't lose them):
- `tools/fix_void_calls.py` — rewrite declarations + calls of promoted
  `(void)` callees that the draft passes arguments to.
- `tools/stmt_perm_search.py 0xADDR --from RE --to RE` — hill-climb the source
  order of an arbitrary contiguous statement block (swaps, moves, reversals,
  3-cycles; for blocks too long to enumerate, see `store_order_search.py`).
- `tools/which_words.py 0xADDR [body.c]` — print ONLY the relocation-masked
  mismatching words (the full `my_diff.py` listing is unreadable once
  relocations dominate); `my_diff.py` now honours the `// FLAG:` line and
  takes `--body FILE`.

## 2026-09-12

Same random-unparked-draft brief. 40 no-park drafts sampled at random, scored
8-way in parallel, then worked top-down. **11 promoted EXACT, DOL byte-identical
`ff6faeb0…` after each promotion batch** (8 + 2 + 1), one parked with a
best-match body. Reusable parallel scorer: `/tmp/pscore.py`-style `Pool` over
`test_wip_drafts.test_one` (note: set `LEAF_TMPDIR` per worker or the workers
race on `/tmp/leaf`).

**Promoted (all no-flags, flagdiff-verified via `test_wip_drafts`):**
- `fn_80056AE0` (60B) — `if (x == 0) return 0; call; return 1;` (early-return)
  plus a callee prototype.  The `li r3,0` BEFORE the `cmpwi` falls out of the
  early-return spelling once the proto removes the `crclr cr1eq`.
- `fn_8012F4DC` (104B) — dropped-second-arg class: first call really takes
  `(arg0->unk0xE0, arg0)`; loading into r3 for the null test (instead of r0)
  comes for free from the 2-arg call shape. Prototypes for all three callees.
- `fn_801A63E8` (124B) — two levers: the dead `do { n--; } while (n)` loop is
  really an EMPTY COUNTING `for (i = 0; i < n; i++) ;` (the do/while spelling
  hoists `mtctr` above the `cmpwi`; the for-loop spelling emits want's
  `cmpwi; ble; mtctr; bdnz` order), and both array bases must be NAMED pointer
  locals so ngccc emits `addi`+`stwx` instead of folding +0x3C into the index
  add. Also m2c's `*((s32 *)arg0 + 0x3C + idx)` stride was 4 bytes/unit wrong.
- `fn_8007E4B0` (84B) — lexicographic (hi16, lo16) u32 compare; the tail is
  the plain two-branch form, and the halves are plain u32 locals (`a >> 16`,
  `a & 0xFFFF`) — no `(u16)` casts.
- `fn_800F3690` (56B) — 1-arg virtual thunk (m2c passed the fnptr as a bogus
  2nd arg); the +0x88 dispatch offset is an s16 (`lha`) so the record needs a
  local typedef with s16 there.
- `fn_8012E65C` (180B) — two plain `if (e != 0 && lookup(...) != 0) { h();
  return; }` blocks (m2c's single `||` with comma-expression reload was
  noise); `extern s32 lbl_803032A4;` + `extern Unk *lbl_80303294[];` makes the
  global loads direct (`lis+lwz` / `lwzx`) instead of an address-in-register.
- `fn_801F0DC8` (188B) — event-record dispatcher. Three levers: the m2c param
  ORDER was permuted (guard tests r7 ⇒ plain `(arg0..arg4)`); arg1/arg2 stay
  s32 and narrow at the use sites (`(u16)` / `(u8)` casts); and the local
  record at sp8 is a 0x28-byte struct whose pointer field holds `&sp30` —
  that is what keeps the sp30/&sp30 stores alive (a separate dead `s16 *spC`
  local is DCE'd, collapsing the frame 0x50 → 0x28) with `pad[0x20]` putting
  sp30 at frame+0x30.
- `fn_80131234` (144B) — list walker: the flags load must come AFTER the
  `fn_8012ED7C(cur)` call (`next = walk(cur); flags = cur->unk0xCC;`), so it
  can live in r0; loading it first forces it into r30 across the call and
  grows the frame/stmw span. Also `if`/`else` with one shared epilogue, not
  an early return.
- `fn_80137C10` (44B) — **see recipe 13**.
- `fn_801318C8` (152B) — sibling of `fn_80131234`: drop m2c's three phantom
  args to `fn_8012ED7C`, type the skip node as a POINTER (want `cmpw`), same
  call-then-load ordering rule.
- `fn_8012FAFC` (208B) — virtual-method trampoline. BOTH the QB_OBJECT and
  QB_COMPOSITEOBJECT calls take FOUR args (m2c dropped arg3 from the first):
  arg3 is still live in r6 on the first path (it is only saved to r29 for the
  `fn_8009FDD8` path), so no `mr r6` is needed there and jump optimization
  merges the two identical call tails (`b 0x8012fb60`); a 3-arg first call
  makes the tails non-identical and ngccc duplicates them (228B vs 208B).
  Also TWO record layouts: arg2+8 → s16@0x20 / fn@0x24, obj+0x18 → s16@0x68
  / fn@0x6C.

**Parked with a best-match body:**
- `fn_80054720` (252B) — 24.7 → 25.4% but now byte-for-byte aligned from the
  first `bl` on. The m2c raw literals were replaced with their registered
  symbols (doc-51): `lbl_80293074/84/98/AC/C8/DC` strings, `lbl_802930F0/F4`
  f32s, `lbl_8030044C/48` .data objects — that alone fixes the
  `lis+ori`→`lis+addi` materialization and turns m2c's
  `fn_8005E1B8(*(f32 *)0x802930F0)` int→float `fctiwz` round-trip into a
  direct `lfs f1`. Residual = want HOISTS both `lis rN,lbl_803004C@ha` to the
  function top and holds them in callee-saved r29/r28 across ~30 calls
  (frame 0x18, `stmw r28`), while ngccc emits them at the store sites in r9
  (frame 0x10, `stmw r30`) — that one scheduling choice shifts every
  following word (hence the 25%). `extern void*` vs `extern s32`, local
  result temps, nesting the calls, and `-fno-schedule-insns{,2}` / `-O3` /
  `-fno-delayed-branch` all leave it identical. doc-15 family.

**New recipes:**
7. **`(void)` callees.** Before blaming regalloc, check the callee's promoted
   source: `grep "^[a-zA-Z].*fn_X(" src/fn_X.c`.  m2c invents an argument
   where the real function takes none; a phantom arg forces the value into a
   callee-saved register and shifts the whole register role set
   (`fn_80225E70` 61 -> 100% from this alone).
8. **Copy propagation can eat the intermediate cursor.**  In
   `temp_r9 = p->next; var_r30 = temp_r9; if (temp_r9->unk4 == -1) ...`,
   GCC substitutes `var_r30` into the test, sees `temp_r9` die at the copy,
   coalesces both into one register — dropping want's `mr` AND freeing the
   temp's register for a different variable.  Hoisting the field test into its
   own local (`temp_r0 = temp_r9->unk4;` before the copy) keeps `temp_r9` live
   past the copy and the whole allocation falls out with no pins.
9. **A two-store reset is emitted back-to-front.**  ngccc prints the pair in
   reverse of the source, so `A = 0; B = 0;` is what produces want's
   `stb ...B` then `stb ...A` AND the matching base-register assignment
   (`fn_80018570`: writing `D9 = 0; DA = 0;` is what lands r30 = D9 base /
   r31 = DA base instead of the swapped pair).
10. **`promote_wip.py` rejects "allocatable data outside .text".**  Almost
   always a stray file-scope `static` m2c left behind for a name that is also
   a local (`static s32 spC;` next to `u8 *spC;`).  Deleting it never changes
   the codegen, so re-score and re-promote.
11. **Check the real symbol NAME, not just that a symbol exists.**  A draft can
   invent `lbl_80302EE4`; the address is real but the name is not in
   `symbols.txt`, so the draft scores 100% and then fails at the final link
   with `undefined`.  `grep -nE "0x8030...." config/G2TE52/symbols.txt` —
   here the object is `DefaultTexData`.
12. **Independent consecutive assignments can need REVERSING.**  Not just store
   blocks: `var_r9 = arg0 + 0x20C; var_ctr = 7;` must be written in the
   opposite order to get want's `li r3,7` first (`fn_800103C4`).  Run
   `tools/store_order_search.py` over any draft scoring >= 30% before parking
   it — it found 42 latent improvements plus one match in one pass.
13. **The entry `mr r11,r3` prologue is a RETURNED ARGUMENT.**  `fn_80137C10`
   (doubly-linked-list node init) stores into its argument six times and
   blr's with r3 intact; m2c typed it `void`, and ngccc then uses r3 as the
   store base, losing want's `mr r11,r3` (40B vs 44B).  The callers prove the
   truth: `fn_8013DA08` calls it as `(char *)fn_80137C10(fn_800098F4(0x1C),
   node)`.  With `return arg0;` the whole body falls out — store order
   included — with NO asm.  So before parking an "r11 is pinned as the dest
   base" function, check whether the function RETURNS its pointer argument
   (the return value keeps r3 live, which forces the copy).

---

## 2026-09-12 (random no-park sample, 2 passes)

Sampled 60 then 48 fresh `src/wip` drafts with no parking comment and scored
all 8-way in parallel. Yields: 8 promotions, 3 new parks.

**Promoted EXACT (all byte-identical, DOL unchanged):**

| fn | size | key fix |
|---|---|---|
| `fn_80137A84` | 80B | both `fn_80137AD4` calls take arg0 (m2c dropped arg1 of the first); callee prototype kills a stray `crclr cr1eq` |
| `fn_8007BC08` | 92B | plain counting `for` (m2c's `if + do/while` was 88B); `lbl_80300474` is a pointer global, +0x4C is that pointer |
| `fn_8002D084` | 132B | **recipe 14** + spurious `temp_r9` removed (the mask is only tested, `fn_8002CA8C` gets the array element) + `fn_8002CA64` takes TWO args |
| `fn_8022C83C` | 92B | plain `while` walk (pre-test + back-edge `or.`); +0x10/+0x20 are pointers, +0x18 is s16 (`sth`); the three clears are written 0x10, 0x14, 0x18 |
| `fn_801302F0` | 84B | **recipe 15** (`crclr cr1eq` needs a variadic callee); +0x10 is a `u8 *` cursor |
| `fn_801FCF84` | 96B | `-fno-schedule-insns` (scheduler hoists the `lis/addi` for the string arg); +0xA0 a pointer, +0x10 an f32 |
| `fn_801F348C` | 104B | `lbzx`/`stbx` — the +0x32C array is BYTES (m2c's `(s32*)base + i` double-scaled); +0x336 is a u8; signed `cmpw` loop |
| `fn_8002D03C` | 72B | **recipe 14** (`hi++`); m2c read `temp_r0` before assigning it |

**Parked with a best-match body:**
- `fn_8000CCF4` (232B, 63.8%) — **recipe 16**: the `if (result == 0) return 0;`
  diamond. want is `or. r29,r3,r3 / bne body / li r3,0 / b end`; ngccc always
  emits the hoisted `li r3,0 / beq end` form at this address, for every
  spelling tried. The tail is independently off (want's `fn_8000F10C` call has
  FOUR args with the global as arg0).
- `fn_80023988` (252B, 42.2%) — byte-stream writer: `stb` not `stw`, u8 cursor
  +0x8 / end +0xC re-loaded per access, `u16 v = arg1 - 1`. A clean rewrite
  gets 38.1%; everything matches to +0x34 then ngccc hoists the `li 0x10`.
- `fn_80055334` (184B, 47.8%) — FOUR args (r3..r6); frame 0x428 with the small
  buffer first (r1+8, 0x200) and the sprintf buffer second (r1+0x208, 0x204);
  variadic `sprintf` (recipe 15). Residual = want keeps TWO copies of the
  output-buffer address (`addi r31,r1,0x208` then `mr r25,r31`) and thus saves
  r25; ngccc uses one register.

**New recipes:**
14. **A packed counter is a bitfield, not a mask expression.**  When want shows
    `srwi r9,r0,SH / addi r9,r9,±1 / rlwimi r0,r9,SH,MB,ME` on a field of the
    same word, writing `(t & LO) | (((t >> SH) ± 1) << SH)` makes ngccc pick a
    `rlwinm/clrlwi/addis/or` strength-reduced form instead — 50%.
    Modelling the field as a real bitfield (`struct { u32 hi : 13; u32 lo :
    19; }`, big-endian so `hi` is the *top* 13 bits) and writing `p->hi++` /
    `p->hi--` reproduces want exactly (`fn_8002D03C` 50 -> 100%,
    `fn_8002D084` 90.9 -> 100%).  If the SAME word is also tested with
    `andis.` (masked, in place), put a union next to the bitfield and test
    `u.w` — a bitfield test would use `rlwinm.` (extract) instead.  This is the
    sibling of recipe 9 (back-to-front stores) for `stfs`-free fields.
15. **`crclr cr1eq` before a `bl` means the callee is VARIADIC at that call
    site.**  A fixed prototype produces a body that matches word-for-word
    *except* the missing `crclr` (`fn_801302F0` 47.6% -> 100% by declaring
    `void fn_8012CB60(void *, ...);`).  18 matched files in `src/` already use
    `, ...);`; for libc, `extern void sprintf(s32, ...);` (see
    `src/fn_8005D4A8.c`) and `extern s32 fn_8005570C(void);` for a thunk whose
    `void` promoted source is really used as a value.
16. **The early-return diamond can be a block-layout wall (negative result).**
    want `or. rX,r3,r3 / bne body / li r3,0 / b end` (the canonical layout of
    `if (result == 0) return 0;`) is NOT produced by ngccc here: it hoists
    `li r3,0` above the branch and inverts the sense.  Braced/unbraced,
    `if (!t)`, `if (0 == t)`, assign-in-condition, `if (t) ; else return 0;`,
    init-zero, declaration reordered, pointer-typed result, and
    `-O1/-O3/-Os/-fno-schedule-insns{,2}/-fno-delayed-branch/-fno-tracer` ALL
    give the identical hoisted form.  If the first divergence is exactly this
    diamond, stop early — it is not a source lever (`fn_8000CCF4`).

## 2026-09-12 (tool-driven sweep over ALL 2012 no-park drafts — 5 promoted, 4 parked)

Method: scored **every** untouched `src/wip` draft (comment block = exactly the
4 standard header lines) 8-way in parallel (`/tmp/pscore_inc.py`, ~35 s for
2012 drafts) instead of sampling. 2012 drafts scored; 3 came back EXACT and 54
NEAR. All `main.dol` rebuilds stayed byte-identical (`ff6faeb0…`).

**Promoted EXACT (5):**

| fn | size | key fix |
|---|---|---|
| `fn_8002DF68` | 232B | six independent `= 0/1` stores re-ordered to want's exact order (`0x60,0x68,0x30,0x34,0x54,0x58`); `arg0+0x18` sub-record via a typed local; the `arg3` float block written ascending and left to the scheduler; `fn_8002E0F8` prototype. |
| `fn_8009D020` | 100B | swept-in (no change needed) |
| `fn_8000C79C` | 204B | swept-in (no change needed) |
| `fn_8009E4B0` | 196B | walker loop must be a **`for`**, not m2c's `if (count>0) do/while`; both `fn_8012701C` calls take the pointer + `3` (m2c dropped arg0), and the `else` path passes `arg0->unk0x24`, not `arg1`. |
| `fn_801213FC` | 76B | `fn_80120664` takes **no** args (m2c invented `0x80300000`) and needs a real prototype — without one ngccc emits `crclr cr1eq` (recipe 15) and the tail shifts. |

**Parked (4) with notes in-file:** `fn_80073880` (75.6% → **87.4%**),
`fn_801B00E0` (64%), `fn_8009C9D4` (64%), `fn_8001B8D0` (56.5%).

**New recipes:**

17. **The walker-loop *guard form* is load-bearing.** m2c renders `while`/`for`
    loops as `if (n > 0) { do { … } while (i < n); }`. That guard folds to
    `cmpwi r0,0` because GCC knows `i == 0` at the entry test, while want keeps
    the general `cmplw rX,r0 / bge` there. Writing the loop as a real **`for`
    (i = 0; i < n; i++)** reproduces want's duplicated top test exactly
    (`fn_8009E4B0` 75.5% → 100%; also seen in `fn_8007E5EC`'s residual note).
18. **Independent constant stores: brute-force the source order.** When the
    only divergence is the *order* of a run of `stw r0,off(rN)` / `stw r8,…`
    with different immediates and no data dependencies, the scheduler preserves
    enough of the source order that sweeping all N! orders finds the exact one.
    A `// FLAG:`-aware parallel variant scorer over the whole body runs ~40
    permutations/second/core, so 6! = 720 is a few seconds
    (`fn_8002DF68`: only `0x60,0x68,0x30,0x34,0x54,0x58` gives 100%).
19. **A 16-argument call can be the real signature.** `fn_80073880`'s tail is
    `fn_8001EA14(s32×8, f32×3, s32×5)`: m2c saw only the outgoing stack stores,
    reconstructed them as locals `sp8..sp18` and invented an 11-arg call whose
    float args were typed `s32` — producing an `fctiwz` round trip and a
    callee-saved `f31` (frame 0x58 vs want 0x48). The f32 trio (EABI: 8 ints →
    r3-r10, 3 floats → f1-f3, 5 more ints → stack) fixes the whole frame.
20. **Negative — argument-setup order is an allocator wall.** When want sets
    `li r3,c` first for a call and ngccc always defers it to last (because the
    other args' constants are already in registers), no source spelling moves
    it: `fn_8001B8D0`'s five- and seven-arg calls, 9 words, identical under
    named index locals, `-fno-schedule-insns{,2}`, `-fno-gcse`, `-O3`,
    `-fno-delayed-branch`, fixed vs variadic prototypes. Beware a higher
    *masked* score that comes only from an extra word shifting the args into
    the right slots.

## 2026-09-12 (top-of-worklist NEAR sweep + repo integrity repair)

Method: re-scored the ranked NEAR worklist produced by full sweep
and worked the best entries (99.5% → 98.9%) instead of sampling. Every
`main.dol` rebuild ends byte-identical (`ff6faeb0f2b524ecbe1aeaff78ff154a284c27c9`).

**Promoted EXACT (2) — both previously *parked* drafts, both off by 1–2 words:**

| fn | size | key fix |
|---|---|---|
| `fn_80169F04` | 324B | **97.5% → 100%**. The residual was the *second* `fn_80127684` call: want emits `ori r4,hash-lo` and only then `mr r5,r26`, ngccc emitted the copy first (it matched want at every sibling call site). An empty `__asm__ volatile("")` immediately after that call ends the scheduler region where the retail source must have ended it, and the constant then completes before arg3 is copied. |
| `fn_8019E770` | 544B | **99.3% → 100%**. The residue was filed as "commutative canonicalization" of `add r28,r11,r28` (want) vs `add r28,r28,r11` (ngccc). No source spelling of `temp_r11 + temp_r28` moves it (5 forms tried) and unpinning r11 regresses to 94.1%; declaring the *destination* temp `register s32 temp_r28 __asm__("r28")` pins the operand roles and gives 100%. |
| `fn_801689C8` | 1476B | **99.5% → 100%** in two independent steps: (a) the `+0x2C54` sum was an *operand-role* problem, not association — writing `(temp_r25 + 0x2C54) + temp_r22` (same value) puts the constant on r22 as want does; (b) the switch's **implicit default** fell through to `common:` while retail jumps to `exit_free` — adding `default: goto exit_free;` fixes it. (b) is invisible to the masked scorer; see recipe 26. |

**Re-probed and left parked (3), all the *same* one-word class:**

- `fn_80173D30` 99.5% (1 word): want `li r4,0`, ngccc `mr r4,r30`, where r30
  holds the branch-proven 0. ~25 more spellings this round (all-zero arg
  spellings `0U`/`0L`/`'\0'`/`(u8)0`/`(s32)NULL`/`(char*)0`/`!1`/`0&0`/`~0+1`/
  `0.0`-cast; arg1 typed `u8..u32`/`char`/`void*`/`Unk*`/`f32`) — the f32 run
  proved the rewrite lands, and every one still yields `mr`.
- `fn_80167E04` 98.9% (1 word): entry guard `cmplw r30, r0` (want) vs
  `cmplw r29, r0` (got) on the rotated `for`; r30 also holds 0 here. The
  guarded-`do/while` rewrite (recipe 17's shape) compiles back to the same
  `cmplw r29`.
- `fn_801A71DC` 99.0% (4 words = 2 sites × 2): `hpre3 = fn_8003E7CC(0xC),
  walker = (s32 *)r25v;` — want schedules `li r3,0xC` before `mr r30,r25`,
  ngccc the other way, at both comma-expression sites. Two statements, a
  swapped comma order, asm barriers around the assignment, mid-function
  `__asm__("" : "+r"(walker))`, top-of-function `register ... __asm__("r30")`
  pins and 9 flag sets (`-fschedule-insns{,2}`, `-fno-delayed-branch`, `-O3`,
  `-fno-gcse`, `-fno-strength-reduce`, `-fno-rerun-cse-after-loop`) all stay
  at 99.0% or regress.

**New recipes:**

21. **An empty `__asm__ volatile("")` is a *scheduling-region* tool, not just an
    ordering hack.** When want and got differ only by which of two independent
    instructions (a half-constant `ori` vs a register copy) is scheduled first
    *inside one call's argument setup*, and the sibling call sites already
    match, the difference is the extent of the scheduler's region. Dropping an
    empty volatile asm at the exact point the region must end reproduces
    want's ordering with no other change (`fn_80169F04` 97.5% → 100%, and it is
    the same class as the barriers already carried around `t30 += 0x2C54`).
    Distinguish it from recipe 20: if the *whole* argument block is in the
    wrong order, it is the allocator (unfixable); if only one pair inside a
    single call swaps, try the barrier.
23. **When a commutative `add`/`or`/`xor` disagrees in *operand roles*, pin the
    destination temp — not the source order.** `add rD,rA,rB` and
    `add rD,rB,rA` are the same value, but the *register roles* are also what
    the allocator chose for the two source temps. Rewriting the C expression
    (`a + b` ↔ `b + a`, cast forms, `+=`) leaves ngccc's form untouched, while
    `register T dst __asm__("rD")` on the unpinned temp reproduces want exactly
    (`fn_8019E770`, another "ceiling" that was really a 1-word
    allocation tie).
25. **Reassociating a sum changes which operand gets the constant.** `(a + K) +
    b` and `(b + K) + a` are the same value, and GCC picks the constant's
    register role from the *source order of the operands*: `fn_801689C8` wanted
    `addi r0,r22,0x2C54; add r29,r25,r0` and only produces it when the C is
    written `(temp_r25 + 0x2C54) + temp_r22`. Also tried for the same spot:
    flat `a + b + K`, `b + (a + K)`, temp staging, `s32`/`u32` flips, casts —
    all leave the ngccc form. So: when a `addi`+`add` pair disagrees about the
    base, **swap the two addends in the source**, don't retype anything.
26. **The masked scorer cannot see control flow — a wrong `if`/`switch`
    structure still scores 100%.** Every branch is emitted as a REL14/REL24
    relocation and the masks deliberately ignore its displacement, so a draft
    that jumps to the *wrong* local label (e.g. an implicit `switch` default
    falling through to the next label instead of the retail target) shows
    369/369 while the linked DOL differs by 2 words. `fn_801689C8` was exactly
    that (`b 0x80168CB8` vs retail `b 0x80168E98`); the fix was reproducing the
    retail default target. Use the new **`tools/br_targets.py 0xADDR`** — it
    resolves branch relocations the way the linker does (`base + sym + addend`)
    and compares every branch whose target lands inside the function, so this
    class is caught in ~1 s instead of after a 4-minute promote + DOL diff.
    Beware of streaming disassemblers here: capstone stops at the first word it
    cannot decode, which silently hides every later branch (decode word by
    word, as the tool does). `tools/promote_wip.py` now runs the same check
    (`br_targets.internal_branch_diffs`) *before* its reconfigure+link step, so
    a control-flow-wrong draft is refused in under a second with the offending
    branch addresses instead of failing the DOL diff four minutes later.
    Verified by round-tripping `fn_80169F04` (fixture draft → promote → DOL
    identical) and by re-introducing the `fn_801689C8` default bug, which the
    gate reports as `0x80168C34 want ('b',0x80168E98) got ('b',0x80168D78)`.
27. **Negative — constant rematerialisation is a wall.** When a live register
    already holds the constant (usually 0) that a call argument or a loop-entry
    guard needs, ngccc copies/uses that register (`mr r4,r30`, `cmplw r30,r0`)
    where the retail compiler materialised a fresh one (`li r4,0`,
    `cmplw r29,r0`). No source shape separates them: 3 functions, ~40 spellings
    of the zero, type flips on the callee parameter, restructured branches, and
    register-pin permutations all produce identical code. Park on sight.

**New tool:** `tools/br_targets.py` (see recipe 26) — link-accurate internal
branch-target check for a WIP draft. Scanned the 99%+ NEAR set with it: the two
remaining control-flow-wrong drafts are `fn_801575E0` (1 branch, 1444B) and
`fn_80173910` (2 branches, 408B, the `lis` page-anchor hoist); both stay parked.

**Repo integrity repair (important):** `src/fn_8017E170.c` had been rewritten
into a "prettier" body (`if (score > 1000000) return 1000000; …`) that no
longer matched the DOL — the build emitted `li r3,0x3E8` where the retail DOL
has `li r3,0x64` at `0x8017E1C0`, i.e. the tree had silently stopped being
byte-identical. Restored the verified body from `f8862928c~1`
(`if (arg0 > 0x3E8) return 0x64;`, plus the duplicated `0x64` guard) and the    DOL is byte-identical again. Lesson: a pretty-print/"cleanup" pass over a
promoted `src/fn_*.c` is *not* verified by the objdiff report (the unit still
scores as present) — only `cmp orig/G2TE52/sys/main.dol build/G2TE52/main.dol`
catches it.

## 2026-09-12 (random no-park sample, 6 promoted, 2 parked)

Method: random samples from the 141 drafts with no parking comment, restricted
this round to functions <= 360B (the large ones in the sample all scored <15%
and were left alone).  Each candidate was rewritten from the want disassembly
before any park decision; every promotion below rebuilt the DOL byte-identical
(`tools/promote_wip.py`, which now also runs the `br_targets.py` gate).

**Promoted EXACT (6):**

| fn | size | key fix |
|---|---|---|
| `fn_80131714` | 116B | **recipe 29** — `fn_8000A778()`'s RESULT is `fn_8013157C`'s arg1, so the call must be written NESTED.  Also TEN params: args 9/10 come from the caller's own stack (`lwz r30,0x40(r1)` / `lwz r29,0x44(r1)`) and are forwarded as `fn_8013157C` args 9/10 (`stw r30,8(r1)` / `stw r29,0xc(r1)`), matching doc 15 §fn_8013157C. |
| `fn_80059488` | 148B | **recipes 30 + 33** — `lbl_80364C38 = lbl_80364C54[idx]` is a plain 0x1C struct copy (one typed struct decl, not m2c's seven hand-rolled stores); `fn_8007C144` takes NO args (bare `bl`); and the guard must be `if (idx >= 0) { …; return 1; } return 0;` (early-exit-first inverts want's `bge` and scores 27%). |
| `fn_80121518` | 84B | **recipe 32** — typed 3-field struct at `lbl_8039BA58` (the `lis r30,@ha` page anchor must survive the `memset` call) and ASCENDING field-store order (0,4,8).  m2c's 0,8,4 order rotates the arg homes to r29/r28/r27 and drops to 71.4%. |
| `fn_80121218` | 56B | **recipe 28** — m2c's `0x8038F2D8` / `0x8038F0E4` are really `lbl_8038F0C0 + 0x218` / `+ 0x24` with a 0x21C element stride; viewing them as struct fields reproduces want's `lis r9,lbl_8038F0C0@ha ; addi r9,r9,-0xf40 ; addi r11,r9,0x218`.  The `A != 0 && B != 0 -> 1` shape is worth 100%; the short-circuit `if (A == 0) return 0; return B != 0;` is 68B at 28.6%. |
| `fn_80120580` | 80B | **recipe 34'** — same `lbl_80302F10` guard family; `fn_80015310` is 2-arg `(arg0, global)`.  Needs the guard kept POSITIVE (`if (arg1 == 1) return 1;`) plus `if (call == 0) return 0; return 1;`: only that pair merges the two `li r3,1` sites into want's single shared return-1 block.  Ternary / `!= 0` / result-local spellings all tie at 80% (16/20). |
| `fn_80120CBC` | 88B | **recipe 34** — sibling of the above; the winning tail is the POSITIVE `if (r != 0) return r->unk8; return 0;` (`or.`/`bne`, load in the fall-through).  The `== 0` form is 88B at 86.4% with the two tail blocks swapped; `&&` / ternary / result-local collapse to 84B. |

**Parked with a best-match body:**
- `fn_8006A1DC` (116B, 86.2% = 25/29) — constructor with a self-referential
  node list and four f32 stores.  Two real m2c bugs fixed first: the call
  `fn_80009A44(0xC, 0x80294A10)` is **1-arg** (an explicit prototype also
  removes a spurious `crclr cr1eq`), and 0x8/0xC/0x10/0x14 are **f32** (with
  the shared `Unk_DB0E2BAB`'s s32 slots the draft grew to 140B with `fctiwz` +
  `stfd`).  Fixed by viewing the object through local typed structs.  All
  registers and store orders then match; the residual 4 words are the
  scheduler hoisting the `lis`+`lfs` pair above `stw r9,0(r30)`.  720 statement
  orders x {load-early, load-late, direct-global, initialiser} x
  `#pragma scheduling off` all cap at 25/29.
- `fn_801312C4` (80B want / 84B got, 8/20 = 40%) — one extra `mr r9,r0` in a
  bitfield RMW.  see the draft header + recipes 14/28b below.

**New recipes:**
28. **m2c "absolute addresses" that are 0xNNNN apart are one symbol plus
    offsets.**  When want shows `lis rX,SYM@ha ; addi rX,rX,off1 ; …
    addi rY,rX,off2`, grep `config/*/symbols.txt` for the *lower* of m2c's two
    addresses (they differ by a struct/array field offset): `fn_80121218`'s
    0x8038F2D8/0x8038F0E4 are `lbl_8038F0C0` + 0x218/0x24 with a 0x21C stride,
    and only the symbol-relative spelling reproduces the shared page anchor.
    A raw-constant draft cannot produce that `lis`, so it can never exceed
    ~28%.
29. **A callee return that feeds the next call's first argument must be written
    NESTED.**  `fn_8013157C(fn_8000A778(), a1, …)` reproduces want's bare-r3
    handoff; splitting it into `t = fn_8000A778(); fn_8013157C(t, …)` is also
    100%, but the "statement call, then re-pass arg0" form loses the r3 chain
    and scores 3.4% (`fn_80131714`).  If want has no `li r3,` before the second
    `bl` and no `mr r3,` restore, the first arg IS the previous call's result.
30. **A callee that want calls with NO argument setup is a 0-arg prototype.**
    `void fn_8007C144(void);` emits a bare `bl` with whatever r3 already holds;
    m2c's eight invented arguments forced 228B (`fn_80059488`).  Same lever as
    recipe 15's prototype rule, for the no-arg case.
31. **`#pragma scheduling off` is not a general ordering fix.**  It emits
    multi-store blocks in *reverse* source order and keeps the same allocator
    coin, so it can only help when every disagreement is a store order
    (`fn_8006A1DC` 86.2% -> 69% with the pragma on the already-best body).
32. **Field-store ORDER selects the parameter home registers.**  Writing a
    struct's fields ascending (0,4,8) reproduced want's r28(arg0)/r27(arg1)/
    r29(arg2); m2c's scrambled 0,8,4 order gave r29/r28/r27 and cost 28%
    (`fn_80121518`).  When the saved-reg homes look "rotated" but every
    instruction is otherwise present, permute the field-store statements first
    — it is cheaper than pinning.
33. **Early-exit-first inverts want's block layout.**  When want shows
    `cmpw…; bge main; li r3,0; b end`, the source is the guard-positive
    `if (idx >= 0) { body; return 1; } return 0;`, NOT `if (idx < 0) return 0;`
    (the latter lays the return-0 block out at the end; `fn_80059488` 27% vs
    100%).  Mirror of the `fn_80120580` / `fn_80120CBC` guard-family results.
34. **Tail-diamond polarity decides which of the two tail blocks is the
    fall-through.**  `if (r != 0) return r->field; return 0;` puts the load in
    the fall-through (`or.`/`bne`) exactly as want does; the `if (r == 0)
    return 0; return r->field;` spelling swaps the blocks and caps at 86.4%
    (`fn_80120CBC`).  The sibling rule (recipe 34') is that the *shared*
    return-1 block in `fn_80120580` only appears when the guard is positive
    AND the last check is `if (call == 0) return 0;` followed by `return 1;`.
28b. **Bitfield insert (`rlwimi`) vs explicit mask: the mask form gets hoisted.**
    want's `rlwimi r0,r31,0x1d,2,2` with `mr r31,r3` (arg0 kept raw) is only
    reachable through a real C bitfield member: the explicit
    `(v & ~0x20000000) | ((arg0 << 0x1D) & 0x20000000)` lets mwcc hoist the
    invariant `rlwinm r31,r3,0x1d,2,2` out of the loop (35%).  A union of
    `{ s32 word; struct { u32 a:2; u32 flag:1; u32 rest:29; } bf; }` gets the
    in-loop `rlwimi`, but ngccc then needs a separate RMW destination register
    (`mr r9,r0`) where want reuses r0 — 84B vs 80B, 4 union layouts and 3 cast
    layouts all tie.  Park on sight if the only diff is that extra `mr`.
    NOTE: this is *not* the same as recipe 14 — there the bitfield was needed to
    fix `srwi`/`rlwimi` strength reduction; here the field insert itself lands,
    and the leftover is a regalloc temp.

## 2026-09-12 (random no-park sample, 1 promoted, 3 parked)

Same method as described above: random drafts with no parking comment, rewritten from
the want disassembly before any park decision.  Promotions were rebuilt and the
full DOL re-verified byte-identical.

**Promoted EXACT (1):**

| fn | size | key fix |
|---|---|---|
| `fn_8011F308` | 156B | Global-counter init loop over `lbl_8038ED90[]` with a `lbl_80302CF8` bound.  The loop counter must be declared `s32` + the calls need real prototypes so `fn_8011F3A4(0, 0, lbl_8029D6C0)`'s f32 third arg lands in f1 with no `crclr` tag.  Straight rewrite of the m2c draft. |

**Parked with a best-match body:**
- `fn_8000CDDC` (176B, 95.5% = 42/44, size-exact) — lookup/memcpy dispatch.
  Real m2c/Ghidra bugs fixed first: the NULL path is `return 0;` (not
  `arg3 = NULL; return arg3;`), and both copies need the **conflicting**
  `void memcpy(s32, s32, s32);` prototype (the standard
  `void *memcpy(void *, const void *, u32)` matches the GCC builtin, so ngccc
  tags the call variadic and prepends `crclr cr1eq` — 2 x 4B = the whole 184B
  overshoot; see recipe 35).  Block order needs the `== 0` / `!= 0` inverse of
  the natural reading (recipe 36).  Residual is 2 words, ONE scratch register:
  want `lwz r5,0(r31)` vs got `lwz r0,0(r31)` on the p[0] guard.  ~10 spellings
  tried; classic AGENTS.md constant/scratch-reg class — park on sight.
- `fn_8011A56C` (316B, 91.1% = 72/79, size-exact) — slot-table walker.
  Rebuilt from m2c's 25.9% goto tree.  Levers: every callee needs a prototype
  (else each call is tagged variadic + `crclr cr1eq`), and the pool is the
  0x3C-stride `lbl_80387E44` (same as promoted `src/fn_80119934.c`) — an
  index-based `Slot3C *e = &lbl_80387E44[idx]` reproduces want's
  `lis r9,0x8038 ; addi r26,r9,0x7e44` base register plus `mulli r31,idx,0x3c`;
  the raw-constant spelling loses the base register and 20%.  Two residual
  sites: (1) the f32 param home — want spills f1 *between* the arg3/arg4 GPR
  homes, ngccc always groups the FPR home last regardless of declaration
  position; (2) the 4-arg `fn_8011A450` call — want emits `mr r3,r27` first,
  ngccc sinks it below the arg materialisation (the doc-15 fn_8015F670 wall).
- `fn_80120924` (168B, 71.4% = 30/42, size-exact) — OSGetTick spin + tail
  calls.  Same lever as recipes 28/32: view the raw `.bss` byte arithmetic as
  a TYPED struct (`extern S20924 lbl_8039D940;` with `.unk0xB0/.unk0xB4/
  .unk0xC0/.unk0x190`).  A raw `*(s32 *)(lbl_8039D940 + 0xC0)` makes mwcc pick
  0xC0 as the addressing anchor (`addi r11,r9,0xc0 ; lwz -0x10(r11)`), losing
  want's `addi r31,r9,-0x26c0` base register entirely (42.9%).  Residual is a
  3-register role rotation (want r30 = base / r29 = tick / r31 = tick-copy;
  ngccc r30 = base / r29 = tick / r31 = 0x80000000): symbol-typed struct,
  local pointer, extra dummy locals, tick type, declaration order all tie.
- `fn_801312C4` (80B want / 84B got, 8/20) — covered previously.

**New recipes:**
35. **A conflicting (non-builtin-signature) prototype suppresses the call
    tag.**  ngccc matches `void *memcpy(void *, const void *, u32)` to the GCC
    builtin and treats even an explicitly declared call as variadic, emitting
    a `crclr cr1eq` before the `bl` (4B each).  Declaring the *conflicting*
    `void memcpy(s32, s32, s32);` (same as promoted `src/fn_8006BC90.c`) makes
    it an ordinary call with a bare `bl`.  Use this for any libc-ish name where
    want has no `crclr` — it is also why plain missing prototypes cost a
    `crclr` (recipe 30's inverse).
36. **Write the branch inverse when want's fall-through is the "unexpected"
    path.**  `fn_8000CDDC`'s dispatch wants `if (p[2] == 0) { if (p[0] != 0)
    fn_8000C9CC(...); else memcpy(...); } else memcpy(...);`, i.e. the source
    tests the NATURAL positive condition inverted.  Writing `p[2] != 0` first
    (or `p[0] == 0` inner) inverts want's fall-through and costs ~22%.
    Sibling of recipes 33/34: read the `beq`/`bne` destinations, then pick the
    spelling whose fall-through is want's next block.

## 2026-09-12 (random no-park sample, 4 promoted, 0 parked)

Same method as Batches 104/105.  All four rebuilt the DOL byte-identical
(`tools/promote_wip.py`, final md5 still `c35167355175a039ccd25b8283a204ff`).

**Promoted EXACT (4):**

| fn | size | key fix |
|---|---|---|
| `fn_8005B65C` | 48B | **recipe 38** — 0x4/0x8 are f32 (a local struct, not the shared `Unk_2EF06E12`'s s32 slots, which forced int<->float conversions), and the two `stfs` must be written **0x8 then 0x4** in source; want emits them 4,8.  The natural order scores 83.3%. |
| `fn_80026BF8` | 76B | **recipe 28b** — the whole body is `arg0->f = arg0->f + 1` on a SIGNED 8-bit bitfield at bit offset 17 (`u32 a:17; s32 f:8; u32 b:7;`), then `fn_8002D548(fn_8002D2A0(), arg0)` NESTED (recipe 29).  The explicit-mask spelling hoists the read (40.9%, 88B); the unsigned field is 89.5%. |
| `fn_80130D24` | 80B | **recipe 37** — cache the loop-bound field in a local and mwcc puts it straight in r11 and drops the `mr r11,r0` copy (40%, 76B); the back-edge must RELOAD `arg0->unk38`.  Also `v = *p; p += 0x2C; if (v == arg1)` puts the bump before the compare (natural order 80%), and the entry guard is `if (i < arg0->unk38)`. |
| `fn_801255B8` | 72B | **recipe 30's inverse** — the ONLY m2c bug was the missing `void fn_80125548(S1255B8 *)` prototype (variadic tag + `crclr cr1eq`, 38.1%, 84B).  The temp-local form (`temp = fn_8012543C(arg0->unk4); if (temp) fn_8012DE30(temp);`) is exact; loading unk4 first or re-calling for the arg regress. |

**New recipes:**
37. **Loop bounds re-read from a field are what force the `mr rN,rM` copy.**
    When want shows a single `lwz r0,field` + `cmpw i,r0` at loop entry and then
    `mr r11,r0` just before the loop body, the source's back-edge test reads the
    FIELD again (`} while (i < obj->count);`) rather than a cached local.  A
    cached local gives ngccc the bound directly in r11 and loses the whole
    4-instruction prologue (76B/40% vs 80B/100%, `fn_80130D24`).  The entry
    guard must still be written `if (i < obj->count)` (not `count != 0`) so the
    entry test is `cmpw r9,r0`.
38. **Two same-value stores to adjacent fields come out SWAPPED.**  want's
    `stfs f1,4(r9) ; stfs f1,8(r9)` is produced by SOURCE order 8-then-4, not
    4-then-8 (`fn_8005B65C`, 83.3% -> 100%).  Writes to two different offsets
    are independent for mwcc and the emitter reverses the pair; if the values
    are identical, try both orders before touching types.  (Same family as
    recipe 32, but 32 is about *parameter homes*, this is about the store
    *order* itself.)

**2026-09-13 — random-batch sweep (no-park-note drafts): 18 EXACT promotions
(DOL byte-identical `ff6faeb0…`).** Picked 64/320/400-address random samples
of the ~2,050 un-parked wip drafts, scored them in parallel, then worked the
NEAR/most-fixable ones. Both promotions rounds landed byte-identical; the
second batch of 8 FAILED at link as a batch (patch_dol `Init r2 setup
computes None` — the known `.sdata2 +0x40` tail-region GC flip) but each of
the 8 promoted fine ONE AT A TIME, so the blocker is a multi-object-at-once
link-state effect, not any individual draft. Prefer single-fn promotions
when a batch trips it.

**Tooling fix (same day):** `tools/test_wip_drafts.py`'s issue-01 auto-dummy
heuristic was wrong for 8-aligned want frames — `want_fpr_frame()` required
`stfd == frame-8` and returned `None` otherwise, so multi-double prologues
whose first `stfd` sits lower were never dummy-tested (~206 drafts). It now
classes every 8-aligned FPR-saving want `ambig8` and dual-tests as-is vs
dummy (whole 64-byte prologue window scanned). Non-promoted population:
137 `pad8` + 318 `ambig8`. Validation: `fn_8011A7FC` with its dummy stripped
scores 82.9% → 100% via auto-injection. An all-318 `ambig8` sweep then found
**0 EXACT** (292 DIFF / 24 NEAR / 2 FAIL — body quality, not the frame); ties
now keep as-is instead of falsely tagging `[dummy]`, and `fn_8021546C` gains
91.5% → 93.9% from the dummy. Details: doc-01.

**Promoted EXACT (18):**

| fn | size | key fix |
|---|---|---|
| `fn_800A9E0C` | 116B | `static s32 sp8` global → LOCAL `s32 sp8[256]` (want frame 0x410); callee call is 3-arg `fn_800A9CE8(arg0, sp8, arg2)` (m2c passed 1); params scrambled; the `or./beq/ble` pair is TWO ifs (`count == 0` then `count > 0`), one compound `!=0 && >0` folds to a single `ble` (112B). |
| `fn_8007B4EC` | 108B | m2c indirect call had a phantom 3rd arg — it is 2-arg `(obj+off, 3)`; disp->0x8 is s16 (`lha`). |
| `fn_8004F2C4` | 92B | 2-arg `fn_800A3C50(arg0+0x190, 0)` (m2c phantom raw-literal 3rd arg) + callee protos (crclr, 108B→92B). |
| `fn_80203034` | 104B | protos for both callees; self-link stores must be SOURCE `0x8` then `0x4` (emitter reverses to want's `4,8`). |
| `fn_80243B14` | 92B | `fn_80243A48(arg0, i, 0)` (m2c dropped args 1+2); predicate `if (*p != 0)` + do-while with the inc after the if. |
| `fn_80056A6C` | 92B | m2c running-offset do-while → `for (i...; i < arg0->0x158; i++) fn(arg0->0x15C + i*0x10)` (element-indexed affine). |
| `fn_8005BE6C` | 128B | m2c used 4-byte `*(s32*)` char reads → signed `char`; backwards scan `while (--len > 0) c = arg0[len-1]`; fn_8000A778 proto. |
| `fn_800A807C` | 92B | same element-indexed affine loop as fn_80056A6C (8-byte stride). |
| `fn_80012AD8` | 160B | key/value table walk: 2-arg `strcasecmp((char*)v, arg0)`; the walker uses SIGNED s32 addresses so the loop test is `cmpw` (pointer compare emits `cmplw`). |
| `fn_8004B0E8` | 116B | fn_8004B03C proto (crclr, 120B→116B); failing-path store order must be SOURCE 4,8,0 → emits 0,4,8. |
| `fn_8009E1A0` | 80B | 2-arg indirect call (m2c phantom fn-ptr arg); arg0+8 is a POINTER (`lwz`), disp->0x8 is s16 (`lha`). |
| `fn_800ADCD4` | 144B | m2c goto-CFG had both `fn_80013E2C()` calls argless and no protos; factored `return 1` tail + early `return 0` reproduces the shared li r3,1. |
| `fn_8011A7FC` | 140B | FP param-reuse (reassign `farg0` in place, not a fresh var) + explicit `volatile double _dummy` — see doc-01 note: want frame 0x18/stfd 0x10 IS the +8 quirk; `want_fpr_frame()` now classes all 8-aligned wants `ambig8` and dual-tests them (heuristic fixed 2026-09-13). |
| `fn_8007BCCC` | 80B | protos for all three callees (crclr). |
| `fn_8005B9E0` | 44B | m2c passed raw literal `0x80360000`; want forwards arg0 (still in r3) + proto. |
| `fn_8005E988` | 64B | m2c phantom 2nd arg on the dispatch call (single-arg); disp->0x28 s16. |
| `fn_8005CF80` | 64B | m2c DROPPED the first call arg (`fn_8005D420(arg0->0x8, &sp8, 1)`); early-return-then-call block order (`if (x==0) return 0; return call;`). |
| `fn_80077A40` | 80B | m2c had the two obj loads reversed, used 4-byte stores for a byte token (want `stb`), phantom 3rd arg; token `s8 sp8[4]` must store 0,1,2,3 ascending. |

**Parked with notes (4):** `fn_80057E2C` (1-word GPR-color: want `mr r9,r3` + load into r3; ~14 spellings all 76B), `fn_80062B28` (5-word addressing web: `lwz r0,LO(r9)`/`lhz r10,4(r11)` vs ngccc's `lwz r11,LO(r9)`/`addi r9`), `fn_801982D4` (store-scheduler: `mr r3` placement + self-link order), `fn_80173D30` (pre-existing doc-15 1-word wall, uses `__asm__` pin — skipped).

**New recipes:**
39. **Element-indexed affine loop beats m2c's running-offset do-while.**
    For `for (i = 0; i < count; i++) fn(base + i * STRIDE);` write the argument
    as `base + i * STRIDE` (element-index) — ngccc strength-reduces it into
    want's pointer walker. The m2c `off += STRIDE` running-offset variable
    regresses to 41-47% (fn_80056A6C, fn_800A807C; also the promoted
    fn_80032610 lesson).
40. **`cmplw` vs `cmpw` is a pointer-vs-integer source tell.**
    A loop bound on a `s32` local (`s32 p, end; ... while (p <= end);`)
    emits signed `cmpw`; the same loop written with pointer types emits
    unsigned `cmplw`. When want has `cmpw` on an address-like value, the
    original used integer addresses (fn_80012AD8).
41. **Same-value adjacent stores emit in REVERSE source order.**
    `n->0x8 = x; n->0x4 = x;` emits `stw ...4` then `stw ...8` (fn_80203034);
    an ascending-address source order emits descending. Independent of value —
    try the reversed source order before touching types.
42. **Byte-token stores must be ascending-indexed.**
    `s8 sp8[4]; sp8[0]=..; sp8[1]=..; sp8[2]=..; sp8[3]=..;` emits
    `stb 8/9/10/11`; any permutation makes ngccc reorder to 0,2,3,1
    (fn_80077A40).
43. **`if (x == 0) return 0; return call;` vs the if/else block order.**
    For a guarded tail call, the early-return-then-call form keeps the call
    INLINE (`beq ret0`); `if (x != 0) { return call; } return 0;` moves the
    call out of line and inverts the branch (fn_8005CF80).

**2026-09-13 (b) — harness correctness pass + 2 more EXACT promotions +
br_targets made the fast gate for doc-24.** Started from "why are whole
draft populations scored against the wrong codegen?". Four harness bugs
fixed; 2 functions promoted (both single, DOL byte-identical `ff6faeb0…`).

**Harness fixes (all four were scoring/gating a DIFFERENT program than
`promote_wip.py` builds):**

1. **`gen_leaves.compile_fn` had no subprocess timeout.** `wibo`
   occasionally deadlocks with many concurrent instances; with no timeout
   that wedged the worker forever and every bulk sweep hung (a 6-worker
   all-draft scan stalled >5 min on one `ngcas`). Added
   `COMPILE_TIMEOUT = float(os.environ.get("NGCCC_TIMEOUT", "120"))` around
   the `subprocess.run` → a hang becomes one FAIL row. Full-pool scans now
   complete (3,589 drafts) instead of hanging.
2. **`tools/br_targets.py` ignored the `__ps_t` → `-mps-float` auto-rule**,
   so it compiled paired-single drafts as SCALAR code and diffed them against
   PS retail — producing bogus internal-branch diffs. This was **falsely
   refusing promotions at the gate**: see `fn_8010284C` below. `body_of()`
   now mirrors `promote_wip.draft_flags()`.
3. **`__builtin_ps_*` without `__ps_t` did not get `-mps-float`** in
   `test_wip_drafts.py` / `promote_wip.py`. 16 drafts call the PS builtins
   without naming the type; 3 of them were FAILing to compile (now compile:
   `fn_800FFB58`, `fn_801F8250`, `fn_80254CEC`); none are near-matching, so
   this is a correctness fix, not a match win.
4. **Whole-draft rescore with the fixed harness** → 6 masked-EXACT (up from
   5): the 4 below plus `fn_80003464` (4B empty fn below `TEXT_START`, not
   promotable) and `fn_8001DFF4` (reloc-target divergence, doc-51).

**Promoted EXACT (2):**

| fn | size | key fix |
|---|---|---|
| `fn_80109F18` | 244B | doc-24 member: draft was `if (sp8.unk00 != 0) { body }` (m2c wrapper) → `beq` past the body; retail's early `if (sp8.unk00 == 0) return;` → `beq` to the epilogue. Same linear instruction stream, wrong target. `br_targets` 0 diffs after the swap; `-fno-gcse`. |
| `fn_8010284C` | 152B | NOT a layout bug — the blocking `br_targets` diff was a false positive from fix #2. PS pair-copy draft; `-mps-float` (auto). |

**Best-body improvements (parked, not promoted):**

- `fn_801C0BA0` (244B PS): **91.8% → 96.7%** (59/61). The `else`-branch scalar
  loads were declared `cx, sx, sz, cy, sy, cz`; the scheduler emitted
  `sx, sy, sz, cy`. Brute-forcing all 120 declaration orders tops out at
  `cx, sx, cy, sy, sz, cz`, which emits retail's `sx, sz, cy, sy, cz` exactly.
  Residual = 2 words (the `lfs c610` scheduled one slot before the `fsubs`),
  a pure scheduler wall: late assignment, inlined literal, c610-first, and 5
  store orders all tie or regress. Also gained the `// FLAG: -mps-float` line
  it never had.
- `fn_800F16C8` (200B): **82% → 84%** just by materialising the `// FLAG:
  -fno-schedule-insns2` line its own notes referenced. It had carried NO FLAG
  line, so every sweep scored it without the flag. (Its remaining wall is the
  documented doc-06 register-role rotation.)

**Recipe 44 — permutation-sweep the declaration order when the residual is a
load/store GROUP inside one basic block.** If the diff is k consecutive loads
(or stores) emitted in a different order, the fix is the C declaration /
statement order, not types. Brute-force the permutation (`itertools`,
`test_one` per candidate) — 5! = 120 compiles is ~a few seconds and
`fn_801C0BA0` was found that way after the two obvious orders both failed.

**Recipe 45 — "flag-in-prose" drafts.** 356 drafts mention a real cflag in
prose while carrying NO `// FLAG:` line; **348 of them are already parked**, so
this class is nearly exhausted — the flags were tried before parking. Of the 8
un-parked ones only `fn_800F16C8` improved (recipe above). Prefer adding the
FLAG line so the recorded best is reproducible.

**Recipe 46 — a masked-EXACT draft with an inverted `x != 0` wrapper is a
doc-24 member; check it with `br_targets` FIRST.** `tools/br_targets.py`
resolves REL14/REL24 the way the linker does and names the exact word without a
rebuild — it caught `fn_80109F18` in one command. Only fall back to the manual
rebuild + `cmp_dols.py` recipe when `br_targets` reports 0 diffs and the DOL
still differs (then it is a reloc-target problem like `fn_8001DFF4`, not a
layout one). Full write-up: doc-24's 2026-09-13 section.

**2026-09-13 (c) — THE MISSING-FLAG SWEEP: 2 EXACT promotions, 643 drafts
mis-scored.** This is the biggest single lever found this session. A *blind*
per-draft compiler-flag matrix — every un-parked draft x 22 candidate flags,
keeping the best — reshuffled the whole pool:

| flag | drafts improved |
|---|---|
| `-fno-schedule-insns` | 260 |
| `-O1` | 220 |
| `-fno-schedule-insns2` | 115 |
| `-fno-gcse` | 48 |

**643 of the 2,041 un-parked drafts (31%)** score higher under a flag their own
FLAG line does not mention, and the jumps are enormous (e.g. `fn_8007B558`
20.0% → 79.4%, `fn_8023590C` 42.9% → 82.1%, `fn_8007BAA8` 24.1% → 78.6%).

Why it works: an m2c/draft body is essentially a *transcription of the retail
disassembly order*. ngccc's `-O2` runs instruction scheduling, which reorders
the body away from that order; `-fno-schedule-insns` emits it in source order
and lands on retail's words. This is an established per-function tool, not a
hack — `configure.py` already carries `-fno-schedule-insns` (24 fns),
`-fno-schedule-insns2` (19), `-fno-gcse` (10) etc.

**Both flags were verified at the link, not just masked:** `fn_8000DB60`
(100B) promoted from 40% → EXACT under `-fno-schedule-insns` — its old park
reason ("global base-register duplication, ngccc CSEs both `.data` globals onto
one base") was simply a scheduling artifact, the dual-base form falls out
automatically. `fn_8009C8A8` (112B) needed the flag *and* recipe 47.

**The 61 drafts reaching >=50% had the measured flag written into their FLAG
line** (with a dated note), so the recorded best is reproducible instead of
being a number no tool can regenerate. 643 drafts improved overall but most are
still far from matching; only the >=50% band was written back.

**Recipe 47 — the 8-byte dispatch-entry table (`s16 self-offset + s32 handler`).**
Retail repeatedly emits, for a table found at some base `B`: a word load of the entry base at offset OFF through the base register into r9, a signed-halfword load of the self-offset at entry offset 0 into r3, and a word load of the handler at entry offset 4 into r0 for an indirect call with base plus offset.

The entries are 8 bytes: `{ s16 offset; s16 pad; s32 handler; }`, and the same
shape recurs at 0x8, 0x10, 0x18, 0x20, 0x28, 0x30, 0x38, 0x90, 0x158 in the
pool: `fn_80057BEC`, `fn_8007B558`, `fn_8007BAA8`, `fn_8009533C`,
`fn_80079FB4`, `fn_800A2688`, `fn_800A4EE0`, `fn_800F39DC`, `fn_80058684`,
`fn_80070BA8` — all typed by m2c as `Unk_2EF06E12 *` / `Unk_C7387A53 *`
(s32 fields), which emits `lwz` for the offset and mis-colours the pointer
(`lwz r4,…` where retail has `lwz r9,…`).

Fix template (index = OFFSET/8), keeping m2c's one-local-per-call shape:

```c
typedef struct DispEntry {
    s16 unk0x0;          /* self-offset added to the object base */
    char pad0x2[0x2];
    s32 unk0x4;          /* handler */
} DispEntry;

temp_r9 = (DispEntry *)arg0->unk0x4C;
((s32 (*)(void *, void *))temp_r9[4].unk0x4)(
    (char *)arg0 + temp_r9[4].unk0x0, temp_r9);   /* entry at 0x20 */
```

Do **not** retype the shared bases (`Unk_2EF06E12` has 2,041 users,
`Unk_C8FEE62D` 1,314) — the dispatch table is its own type. Status: `fn_8009C8A8`
PROMOTED with this; `fn_80057BEC` 71.4% → 90.2% and `fn_8007B558` (baseline
79.4%) reached 88.2% with the array form — the residual on both is register
colour, so the shape is right even where it is not yet exact.

**Recipe 48 — sweep flags *blind*, never trust the draft's FLAG line.** 356
drafts mention a flag in prose without recording it (recipe 45), but this round
shows the problem is far wider: the FLAG line is often simply silent. Re-scoring
the pool under a flag matrix is cheap (~20 compiles/s) and found 2 EXACTs plus
61 frontier drafts in one pass. Re-run it after any harness change.


### 2026-09-13 (d) — extended flag matrix: the flag vocabulary was the frontier

**Recipe 49 — sweep the *whole* flag vocabulary, not the four schedule flags.**
`configure.py` carries more per-function flags than the earlier matrices ever
tested: `-fno-sched-spec`, `-fno-sched-interblock`, `-fno-strength-reduce`,
`-fno-expensive-optimizations`, `-funroll-loops`, `-fno-delayed-branch`,
`-fno-function-cse`, `-fomit-frame-pointer`, `-ffixed-r9`, `-ffixed-r11`,
`-O1`/`-O3`. Re-running the blind matrix (`/tmp/flagmatrix3.py`, 2,031 un-parked
drafts x 16 flags) on top of the flags already recorded found:

| flag | drafts it is the single best choice for |
|---|---|
| `-fno-schedule-insns` | 201 |
| `-O1` | 179 |
| `-fno-schedule-insns2` | 110 |
| `-ffixed-r9` | 80 |
| `-fno-expensive-optimizations` | 50 |
| `-fno-gcse` | 41 |
| `-ffixed-r11` | 20 |
| `-fno-strength-reduce` | 13 |
| `-funroll-loops` | 4 |

**479 drafts improved** across the two passes (137 written back at >=30%, then a
second pass that first re-scored each draft under its *own* FLAG line so the
baseline was honest, +7 more). Measured flag written into each draft's FLAG line
with a dated note (`/tmp/apply_flags3.py`).

**Why `-fno-strength-reduce` matters (new):** it is what stops ngccc turning a
`do { n -= K; ... } while (n != 0)` countdown into a doloop
(`li r0,<count> / mtctr / bdnz`). Retail almost always keeps the
`addic. r11,r11,-0x18 / bne` form. `fn_8023590C` went 82.14% -> **92.86%** on
this flag alone (26/28; the residual is 2 words of initialiser order). See
`docs/parkings/30-empty-doloop-bdnz-window.md` for the shape.

**Why `-ffixed-r9`/`-ffixed-r11` matter:** when want's colouring is forced to
avoid a register that ngccc insistently uses for the wrong value, banning it
sometimes lets the allocator land on retail's assignment. 100 drafts are best
under one of them (they can also *regress* a draft that was fine — always A/B).

**Promotions this round:** `fn_80077718` (64B, m2c self-arg + recipe-47 s16
dispatch offset, plain flags — see `docs/parkings/solved/52-...`).

**Best-body improvements recorded on parked drafts:**
- `fn_8023590C` 82.14% -> 92.86% (`-fno-strength-reduce`); residual = 2 words of
  `li r11,0x3a98` vs `addi r9,r9,0x3c94` emission order (all 4 source
  permutations identical).
- `fn_8004C7B0` 18.92% -> 86.11% (`-fno-expensive-optimizations` + a manual
  `volatile double _dummy`); residual = 5 stack-offset words (`sp8` lands at
  r1+0x10 where retail has r1+8).
- `fn_80079FB4` 77.78% -> 91.67% (`-fno-sched-spec` **or** `-fno-schedule-insns`
  — same body, recipe-47 entry at 0x158); residual = the `lwzx/stwx rA,rB`
  operand order, a gcc constant.
- `fn_801C0BA0` still 96.72% (recipe 44's load-order permutation), `fn_8008076C`
  94.79%, `fn_8007E5EC` 86.21% — all documented colouring walls.

**Negative result worth keeping:** the matrix was re-run a second time on top of
the first pass's flags to catch *combinations*; it produced 342 raw hits but only
8 with gain >= 3%, so **single- and double-flag space is saturated**. The
un-parked frontier is now emission-order and register-colour walls, not
mis-flagged compiles.

### 2026-09-13 (e) — sweep the flags on the PARKED drafts too (recipe 49b)

The earlier flag matrices only ever looked at **un-parked** drafts, but the
flags they discover are exactly the ones the parking notes claim "were tried"
— and (recipe 49) those notes are often wrong about which variant was actually
run. Re-running the extended vocabulary over all **1,548 parked drafts**:

| outcome | count |
|---|---|
| new masked-EXACT found | 9 |
| newly promoted | **5** |
| parked drafts whose best body improved | **497** (144 by >= 5 pts) |

**5 promotions, DOL byte-identical** (all were parked, two of them at ~30-40%):

| fn | size | flag | was -> now |
|---|---|---|---|
| `fn_80013238` | 28B | `-fno-schedule-insns` | 2/6 -> EXACT |
| `fn_801312C4` | 80B | `-fno-schedule-insns` | 38% -> EXACT (frame also fixed) |
| `fn_80136D30` | 288B | `-fno-expensive-optimizations` | 88.9% -> EXACT |
| `fn_801A1150` | 128B | `-fno-expensive-optimizations` | 87.5% -> EXACT |
| `fn_80239CF4` | 144B | `-fno-sched-interblock` | 36.1% -> EXACT |

Plus four more SOLVED drafts worked by hand in the same pass:
`fn_80077718` (52), `fn_8021D5AC`, `fn_801982D4`, `fn_801F9EB8` — see below.

**`80207430` is the cautionary tale:** the flag matrix reports it at a masked
**100.00%**, but `br_targets` refuses it (one latch displacement). Recorded in
`docs/parkings/solved/24-...`; the parking note's claim that `-fno-schedule-insns2`
had been tried was false — but the 100% it produces is a *false* positive, which
is precisely why the control-flow gate exists.

**Recipe 50 — pin BOTH argument registers to fix a `mr` birth-order swap.**
`fn_801F9EB8` (116B) sat at 89.66% on two words (`mr r4,r30 ; mr r3,r31` vs the
reverse). Naming temporaries, reordering the source expression and casts all
emit identically. Declaring `register s32 a4 __asm__("r4"); register void *a3
__asm__("r3");` and assigning them in that order is 100%: a pin makes the
argument pseudo's birth order the source order, so the allocator can no longer
pick either `mr` first. Full write-up in `docs/parkings/15-...`.

**Recipe 51 — structural one-word fixes worth checking before anything else.**
Three of this round's promotions were *not* allocator walls at all:
- `fn_801982D4`: two ring-initialiser stores emitted in reverse source order —
  write `unk0x10` before `unk0xC` in the source.
- `fn_8021D5AC`: the outer pointer load must stay in `r9`; ngccc coalesces it
  with the inner load because the outer dies at the second load. An r9 pin on
  the outer pointer (`-ffixed-r9` lets it hold) splits them.
- `fn_80077718`: m2c's phantom self-argument (doc 52) **plus** the recipe-47
  `s16` self-offset — the arg fix alone is 93.8%.

**Also recorded (no promotion):** manual `volatile double _dummy;` took
`fn_8004C7B0` 83.33% -> 86.11% (it supplies retail's 8 wasted frame bytes);
residual = 5 stack-offset words with `sp8` at r1+0x10 vs retail's r1+8.
`fn_8023590C` reached 92.86%; `fn_80079FB4` 91.67%.

**109 parked drafts had their measured best flag written into the FLAG line**
(`/tmp/apply_flags3.py`, `/tmp/fm5_apply.tsv`), so the numbers above are
reproducible from the files rather than being folklore.

### 2026-09-13 (f) — iterating the flag sweep saturates; `-ffixed-rN` beyond 9/11 is dead

Two follow-ups to (e), both cheap and both negative in the useful sense:

**Iterated pass (recipe 49c).** Re-ran the extended vocabulary over the parked
drafts a *second* time, this time computing each draft's baseline under its own
(now updated) FLAG line first. Result: **0 new EXACT**, 402 raw hits, only 115
with gain >= 3 and 65 with gain >= 5 — i.e. the first parked pass already
captured the real wins and single/double-flag space is now exhausted on both
halves of the pool. 28 more drafts had their measured flag written back (with
lower thresholds for the very-low-score band, so future sessions start from the
right configuration instead of the parked number).

**`-ffixed-rN` sweep (recipe 52, negative).** The vocabulary only shipped
`-ffixed-r9`/`-ffixed-r11`; I swept `-ffixed-r3..r12` over every un-parked draft
>= 60% (28 of them). **Zero EXACT, zero improvements above 2.4 points.**
Banning a register only helps when the banned register is one ngccc uses for a
value retail puts elsewhere *and* no other allocation degrades — for the
callee-saved/volatile range that is essentially only r9 and r11 (already in the
vocabulary). Do not spend another sweep on this axis.

**Where the remaining frontier actually is** (all verified by hand this round):
- stack-slot *ordering* between two locals (`fn_80239924`, `fn_8004C7B0`) —
  declaration order, alignment attributes and padding locals all reproduce the
  same swapped layout;
- one-word scratch-register choice for a dead comparison result
  (`fn_8025A1D0`: `andi. r6` vs `andi. r0`, repeated 3x; pinning the result
  variable, a temporary, and six flag sets all agree);
- global-base register routing (`fn_8011D788`, `fn_801B6EB8`) — the `lis` pair
  is at the right offset but the base register differs, and no `-ffixed-rN`
  moves it;
- the loop-preheader invariant placement (`fn_80207430`, doc 24).

### 2026-09-13 (g) — the store-order search was scoring drafts under the WRONG flags

**3 promotions, all from one corrected tool.** `fn_80098B7C` (160B),
`fn_800F1448` (160B) and `fn_801AEE7C` (152B) are now in `src/`; the DOL stayed
byte-identical (`ff6faeb0...`) after each individual promote.

**The bug (recipe 53 — check the tool, not the function).**
`tools/store_order_search.py` and `tools/stmt_perm_search.py` both built the
compile input with

```python
strip(text)   # drops EVERY line starting with `//`
...
test_one(addr, body)          # no extra_flags at all
```

so the draft's own `// FLAG:` line was deleted *and* never passed as
`extra_flags`. Any draft whose header carries `-mps-float`,
`-fno-schedule-insns`, `-fno-gcse`, ... was therefore scored against a
**different program** than the one the harness scores. Worse, `--write`
persisted that body: running it on `fn_8020CAA4` reported
`22.2% -> 22.2%` and copied the reverted body back into `src/wip` (its true
score is 98.7%). Both tools now mirror `promote_wip.draft_flags()` —
the `// FLAG:` / `// extra_cflags:` tokens filtered through
`gl.FLAG_TOKEN_RE`, plus the `__ps_t` / `__builtin_ps_*` -> `-mps-float` rule —
and pass them to `test_one(addr, body, flags)`.

**Sweep after the fix: 585 drafts >= 50%.** 3 EXACT (the promotions above,
each a plain *reverse* or *ascending* reorder of one contiguous assignment run)
and 48 score improvements, the best being `fn_800BD96C` 97.8%,
`fn_80153D54` 95.3%, `fn_800E4EB8` 92.9%, `fn_80200B40` 91.7%.

**Full-permutation follow-up** (`/tmp/perm_run.py`: every permutation of runs
of <= 5 statements, not just reverse/asc/desc): 390 targets, **0 EXACT**, 20
improvements — `fn_80221930` 97.6%, `fn_8018CC18` 97.3%, `fn_80227D64` 96.5%,
`fn_80114ADC` 96.2%, `fn_8017B390` 93.3%, `fn_80182C8C` 90.7%,
`fn_801F8DA8` 90.3%. Non-monotonic permutations do help (they are what
`store_order_search` cannot see), they just do not close the last 2-6 words.

**Recipe 54 — pairwise flag combinations are a DEAD AXIS.** Doc 09's
"crashwoc update" left `--combos 2` as the untried lever. It is now tried,
twice, exhaustively enough to close it:

| sweep | space | EXACT | best combination find |
|---|---|---|---|
| all 1- and 2-subsets of a 13-flag vocabulary, drafts >= 70% | 91 combos x 353 | 0 | **none** — every one of the 8 improvements is a *single* flag |
| all 15 non-empty subsets of the 4 scheduling flags, drafts >= 85% | 15 combos x 234 | 0 | 1 improvement, single flag |

8 further drafts had their measured single-flag best written into the FLAG
line (`fn_80135170` 88.46->91.03 `-fno-schedule-insns2`; `fn_8011CF0C`
81.73->83.65 `-fno-strength-reduce`; `fn_80197DB8` 77.42->78.23 `-fno-sched-spec`;
and `8009EF74`, `8003ED20`, `8016AB1C`, `8020773C`, `80115A28`). If two flags
together ever beat one flag alone, it did not happen in 2,400 draft-combination
evaluations. Stop sweeping flag pairs.

**Recipe 55 — classify the residue before grinding (`/tmp/classify.py`).**
Every non-promoted draft compiled under its own FLAG line and bucketed by what
the diffing words *are*:

| class | drafts | meaning |
|---|---|---|
| MIXED | 2340 | permutation words *plus* a real colour/width/other word |
| OTHER | 1114 | anything else |
| PERM | 49 | pure permutation of one instruction multiset (scheduling) |
| SWAP | 39 | exactly one adjacent pair exchanged |
| FAIL | 12 | compile error (invisible to score ranking) |
| COLOR | 6 | differs only in a register field |
| EXACT | 5 | masked false positives (all blocked by the promote gates) |
| WIDTH | 1 | `lwz` vs `lha/lbz/lhz`, same regs+offset (recipe 47 retype) |

Only **39+49+1 = 89** drafts are in the "source-order/field-retype" classes the
tools can reach; the 3,454 MIXED/OTHER drafts are genuine codegen walls. That
ratio is the honest picture of what is left.

**Un-parked frontier after this round:** 2033 drafts, of which 2 are >= 90%,
5 are >= 80%, 8 are >= 70% and **1941 are < 50%**. There is no cheap pool left;
work has to be one function at a time.

**2026-09-13 (g) addendum — the FAIL class is 12 drafts, and 5 of them were
one-line tooling/loss errors.** Fixing the compile error is worth doing even
when the body is bad, because a `FAIL` is invisible to every score ranking:

| fn | error | after fix |
|---|---|---|
| `fn_80235D1C` | m2c **dropped the 2nd `strcpy` argument** (retail keeps the incoming `r4` = arg1 live for the first call instead of reloading it) + `s32`/`lwz` where retail loads `u16`/`lhz` | **EXACT -> promoted** (84B) |
| `fn_8013A7D4` | `temp_r11_3` typed `Unk_A99C4F7E *` but the field used is `Unk_BDBFA817::unk0x17FC` — a wrong *type*, not a cast | 63.1% |
| `fn_801168CC` | call passes 4 args to a 2-arg prototype | 7.6% |
| `fn_8002E3A8` | one call site passes a 5th (string) arg to a 4-arg prototype | 5.0% |
| `fn_8009A8CC` | one call site passes 4 args to `sinf` | 1.7% |

For the four arity errors the fix is a *second prototype name with the right
arity* for the odd call site: `REL24`/`REL14` branch targets are relocation
masked (`0xFC000003`), so the symbol name is free and the emitted instruction
stream is unchanged. Only the type error (`fn_8013A7D4`) is a real code change.

**The other 7 FAILs are not thug2 drafts at all.** `fn_80289AE4`, `fn_80289BD8`,
`fn_8028B408`, `fn_8028B47C`, `fn_8028B4F0`, `fn_8028BA08`, `fn_8028BC24` are
`family=gxtev` bodies that `#include <dolphin/gx.h>`, `<dolphin/os.h>`,
`<dolphin/gx/GX.h>`, `<dolphin/gx/GXInit.h>` — none of which exist in this
repo's include tree (thug2 only has `types.h`, `structs.h`,
`qb_constants.h`, `SN_PS.h`) — and two of them re-`typedef` `u8`/`u16`, which
`dolphin/types.h` already declares. Their own headers say the real work needs
**mwcc plus the GX SDK headers** and lives in the separate `gxtev-permuter/`
project. Do not try to make them compile in the ngccc harness; they will never
be scored here.

### 2026-09-13 (h) — the field-width census: 193 drafts, 2 more promotions

**More promotions** (DOL byte-identical `ff6faeb0...`, one at a time):
`fn_8001CF80` (144B) and `fn_801980C4` (204B). Both are the new recipe 56.

**Recipe 56 — count the WIDTH diffs, then retype the variable (doc 53).**
`classify.py` only calls a draft `WIDTH` when *every* diff is a width diff, so
the lever looked like 1 draft. Counting drafts with **at least one** diff whose
mnemonic differs but whose registers+displacement are identical gives **193 of
3,567**. Dominant kind: `lha`(want) vs `lwz`(got) — 61 drafts — i.e. retail
reads an **s16** field where the draft reads s32.

- `fn_8001CF80` was the one width-*only* draft (19/19): a 4x zero-fill of a
  0x1E-byte PAD block where every store was `*(s32 *)`. Making them
  `u16`/`u8` to match retail's `sth`/`stb` took it 47.2% -> **100%**; nothing
  else changed.
- `fn_801980C4` had 2 of 8 diffs of this kind (`Unk_2EF06E12::unk0x8` is `s32`,
  retail `lha`s it). A local `Unk_801980C4_vt { s16 @0x8; s32 @0xC }` retyping
  `temp_r9_2/temp_r9_3` took it 84.3% -> 88.2%; two colour levers then finished
  it (pin the scratch to r11, and hoist the condition load above the copy with
  a **named** temporary — see doc 53; the naive line swap alone collapses the
  function to 7.8%).

**Recipe 57 — the store-order lever is now exhausted pool-wide.** Re-ran
`store_order_search.py` (post FLAG-fix) over the *whole* remaining pool: 2,964
drafts < 50% scanned, **657 improved, 0 EXACT** (best `fn_801980C4` 84.3%,
then 73.5%, 69.9%). Combined with the >= 50% pass (585 drafts, 3 EXACT, 48
improved), the lever has now been applied to every draft that has a movable
statement run. It produced 3 matches, all in the >= 50% band. Do not re-run it.

**Three more diagnostic tools carried the same FLAG-line blind spot.** The
static-flags bug fixed for `store_order_search`/`stmt_perm_search` also affected
`which_words.py`, `want_vs_got.py`, `score_addrs.py` and `triage_near.py`:
- `which_words.py` parsed `// FLAG:` with the naive `startswith("-")` rule and
  **ignored `__ps_t` -> `-mps-float` entirely**, so every paired-single draft was
  disassembled as *scalar* code and the printed "diffs" were fiction (e.g.
  `fn_801C0BA0` showed a wall of `lwz`vs`psq_l` that does not exist; the real
  residue is 2 words);
- `want_vs_got.py` took flags **only** from argv, so `want_vs_got.py 0x801C0BA0`
  was scalar too;
- `score_addrs.py` and `triage_near.py` read the draft but compiled it with no
  flags at all.

All four now call the new shared `gen_leaves.draft_flags(text)`, which is the
single source of truth (validated `FLAG_TOKEN_RE` tokens + the PS rule).
Any tool that compiles a draft and does NOT go through it will disagree with the
harness — that class of bug has now cost three separate sessions.

**Width census tool:** `/tmp/width_scan.py` (reuses `classify.py`'s helpers) —
re-run it after any bulk edit; it prints the per-draft width/total diff counts
and the exact mnemonic pairs with byte offsets.

### 2026-09-13 (i) — four promotions; the *named float temporary* and a new flag axis

Full-pool rescan at the start of this session: **600 NEAR / 6 masked-EXACT (5 of
them genuinely blocked) / 2908 DIFF**. Four functions promoted (all DOL
byte-identical), two parked drafts moved close to the ceiling.

| fn | size | was | fix |
|---|---|---|---|
| `fn_8006FD50` | 216B | 66.7% | `*(char *)` where retail `lwz` + s16 dispatch offset + 2 pins |
| `fn_8007EAE8` | 300B | 64.0% | 2-arg `fn_80009A78` + `stwx` operand order + s16 offset + 2 pins |
| `fn_8017DD54` | 716B | 98.9% | **`-fno-rerun-cse-after-loop`** (new flag axis) |
| `fn_800D521C` | 232B | 98.3% | **named float temporary** preserves `fadds` operand order |

Parked-draft improvements (best body written back, notes dated):

| fn | was | now | residual |
|---|---|---|---|
| `fn_800CB4D8` | 75.9% | **96.3%** | 1 scheduler swap in a call's arg setup |
| `fn_800DF004` | 55.7% | **95.5%** | 1 scheduler swap (`lwz` vs `or.`) at both call sites |

**Recipe 58 — a NAMED local temporary can be the only thing that preserves an
FP operand order.** `fn_800D521C`'s residual was `fadds f13,f0,f13` (want
`f13,f13,f0`) and its park note called it "a register-allocation coin" that
`sum += f`, `sum = sum + f` and `sum = f + sum` all canonicalise away. They do —
but `{ f32 s2 = f + sum; dst = s2; }` emits the want order. A named temporary is
the classic C idiom for *forcing* materialisation (recipe 51), and here it also
pins the RTL operand order that the combine step would otherwise normalise.
Check this before parking any "commutative-operand-order coin" in floating
point. Same session, `fn_800A1B5C`/`80206F7C`/`801A6FB4` remain genuine
indexed-`stwx` rA/rB coins (doc 49) — the named-temp trick does NOT apply to
integer EA operands.

**Recipe 59 — `-fno-rerun-cse-after-loop` is a real axis.** `fn_8017DD54`
(716B, 98.9% for months) is a two-parameter copy in the prologue that ngccc
re-CSEs and re-orders; the flag emits retail's order. A pool-wide sweep of the
flag alone over all 3,234 un-promoted drafts found **0 further EXACTs but 66
improvements**, 26 of them by >=3 points (`/tmp/nf_improved.tsv`), concentrated
on the low-score structural population (`80077CFC` 8.1->44.4, `8001E248`
31.1->66.7, `801C2B04` 49.3->72.9). It is now part of the vocabulary — see
recipe 49/49b for how to run the sweep (`/tmp/newflag.py`, `CAND=` selects the
flag).

**Recipe 60 — m2c's call transcription is wrong in three mechanical ways, and
each one is a whole-frame mistake.** All three showed up this session and are
cheap to check with `want_vs_got.py`: the want line is right and the got line is
one instruction out.

1. **Merged / dropped arguments.** `fn_8007EAE8` and `fn_800DF004` both call
   `fn_80009A78` / `fn_8009FDD8`, which are **2-arg** functions; m2c emitted
   `f(arg2); g(QB_X)` — a call whose first argument is the *previous call's
   result* has become a discarded call plus a 1-arg call. Symptom: want `bl X`
   then `lis r4,const`, got `lis r3,const` (the constant lands in r3).
2. **A missing prototype makes the call varargs.** Any callee with no
   prototype at all gets `crclr cr1eq` before the `bl` (mwcc's varargs
   sequence) and the whole frame is 4 bytes too large. Symptom: one extra word
   plus every later offset shifted. Adding the real prototype removes it —
   `fn_800DF004` was 4 diffs, of which 2 were this.
3. **A pointer-typed field mistyped as `char`.** `fn_8006FD50` loaded the first
   list node with `*(char *)(...)` (retail `lwz`); the `lbz` + `extsb` pair then
   cascaded through the whole function. Fix the *cast's pointee type*
   (`*(Unk_2EF06E12 **)`), never the use site.

**Recipe 61 — the FLAG line can go STALE and actively regress.** `fn_800CB4D8`
carried `-fno-expensive-optimizations`, measured on an *older* body, and it was
load-bearing then (50.9% -> 75.9%). After this session's five structural fixes
the same flag scored **29/54** while the flag-free build scored **52/54**. The
draft now records "NO FLAG LINE" and why. Any time you rewrite a body, re-run
the flag sweep on the new body; never inherit the old line.

**Recipe 62 — the `-ffixed-rN` / pairwise-combo negative results now have a
sibling: 56 flags x 62 drafts found nothing.** A broad vocabulary (CSE, ifcvt,
floop, web, RTL alignment, `-fno-ipa-*`, `-mcpu`, plus 21 two-flag combos)
applied to every NEAR draft >=96% produced **exactly zero** flips. The
1-2 word residuals at 97-99% are allocator/scheduler tie-breaks: the remaining
1-diff drafts (`80091C88`, `801A6FB4`, `80206F7C`, `8018BC9C`, `80167E04`,
`801025D0`, `801CE65C`, `80221C00`, `80173D30`) all have park notes that already
list the exhaustive source/flag sweeps, so treat them as closed unless a *new*
source-shape lever appears (this session's two — the named float temp and
`-fno-rerun-cse-after-loop` — each fixed one such draft).

**Where the frontier is, updated.** Diff-count census of the top 60 NEAR drafts
(`/tmp/diffcount.py`): 9 are 1 word off, 31 are 2 words off, 20 are 3-10 words
off. Every one of the 1-word drafts is a documented coin. The 2-word class is
almost entirely *pairs of adjacent-instruction transpositions*, which the
adjacent-line-swap search (`/tmp/adjswap.py`) cannot reach — the two
instructions do not come from two adjacent source lines.

### 2026-09-13 (i) — addendum: the adjacent-line-swap search found two more

**Promotion #5: `fn_800C9808` (360B), 97.8% -> 100%.** Swapping the two lines

```c
p = sp8;                        __asm__("" : "+r"(p));     /* MUST come first */
__asm__("" : "+r"(p));     ->   p = sp8;
```

The `"+r"` pin is the *birth* of the pinned pseudo; putting the assignment after
it is what lets the scheduler place the move. Corollary of recipe 51: a pin does
not just name a register, it also fixes where the value becomes live.

**Refused: `fn_80221930` (332B), 97.6% -> masked 100% (0/83).** Moving
`return 1;` out of the if-body makes the body byte-identical under the reloc
masks, but `br_targets` refuses it: `0x80221A24` has want `ble` to
2149718628 and got 2149718632 (+4B) — `li r3,1` lands in the wrong arm. This is
the doc-24 class again: **a masked-100% body is not a match, and the branch
target check is the only thing that catches it.** The draft records the refusal
and stays parked at the masked-100% body.

**Tool worth keeping: `/tmp/adjswap.py 0xADDR [--write]`.** It brute-forces every
adjacent pair of source lines in a draft, scoring each through `test_one` with
the draft's own `// FLAG:` line (the first version forgot that and reported
`fn_8020CAA4` as 18.8% instead of 98.7%). It found both of the above in ~30s
each after six other 2-word drafts refused every flag in the vocabulary. Run it
on every 2-3 word NEAR draft before assuming a scheduler coin — 2 of 8 hits this
round.

**False-positive warning.** `--write` persists the winning body even when the
masked score is 100% but `br_targets` disagrees, so always run
`tools/promote_wip.py` (which refuses) rather than trusting the score.

### 2026-09-13 (j) — the copy the allocator ate: m2c's `var = temp; if (…) var = NULL;`

**Three promotions + several multi-point jumps, all from one source-shape
observation.**

m2c transcribes the classic "walk a linked list and NULL-clamp the cursor" idiom
as two statements:

```c
var_r11 = temp_r9;
if ((s32) temp_r9->unk0x4 == -1) {
    var_r11 = NULL;
}
```

mwcc **coalesces `var_r11` with `temp_r9`** into one register, so the copy
(`mr r11, r9`) disappears and the function is 8 bytes shorter than retail. Write
it as an if/else instead and the two pseudos can no longer share a register:

```c
if ((s32) temp_r9->unk0x4 == -1) {
    var_r11 = NULL;
} else {
    var_r11 = temp_r9;
}
```

| fn | size | was | fix |
|---|---|---|---|
| `fn_80031FC4` | 136B | 73.5% | the if/else form (both arms of the loop) **+** an `s16 unk0x8` local vt |
| `fn_80015A58` | 80B | 60.0% | the if/else form alone |
| `fn_801C26D8` | 240B | 11.7% | the if/else form (4 instances) **+** s16 vt **+** an explicit `(char*)arg0 + 0x34` base local (want `addi r30, r3, 0x34`, not `mr r30, r3`) |

Swept pool-wide (`/tmp/ifelse_sweep.py`, all 211 drafts carrying the pattern):
1 EXACT, 18 improved ≥1 point, 20 body rewrites written back. A finer sweep that
tries *subsets* of a draft's instances (`/tmp/ifelse_subset.py`) found no further
EXACT — all-or-nothing is the right granularity, so **recipe 63 is closed**.

Note this is the *opposite* of recipe 50: pinning the argument registers kills a
coalesce that *should* happen, the if/else form forces a copy that *must*
happen. The lever is the source shape, not a flag.

**Recipe 64: m2c's pointer arithmetic double-cast is a bug, not a type.**
`*(s32 *)((s32 *)PTR + 0x388)` scales by 4 — it reads byte offset `0xE20`, not
`0x388`. When the want shows `lwz r9, 0x388(r11)`, the correct C is
`*(s32 *)((char *)PTR + 0x388)`. `fn_801A27CC` was 62.5% -> 87.2% once the
`0x388` field and two more things below were fixed. 321 drafts still contain
`*(T *)((T *)` — worth a look, but the offset is only wrong when the m2c cast is
the *inner* one, so a blanket rewrite is unsafe.

**Recipe 65: check the callee's vra return width.** m2c guesses every prototype
as 32-bit. `fn_801A27CC` computes `(u32) fn_8001448C() + 1` and retail emits the call to fn_8001448C followed by adding one to register r4, which holds the low word of the 64-bit return.

With `u32 fn_8001448C(void)` we got `addi r3, r3, 1`; with the true
`u64 fn_8001448C(void)` (its promoted body returns `u64`) the `+1` lands on r4
and 76.6% -> 82.98%. Same lever was needed for `fn_8011C164`'s `extern s64`
declaration.

**`fn_801A27CC` also wanted three independent fixes** — s16 local vt for
`unk0x58`, a real `void fn_801A362C(void *, s32);` prototype (without it mwcc
emits the varargs `crclr cr1eq` and the whole tail shifts), and the statement
order `fn_801A362C(...); temp_r4 = fn_8001448C() + 1; arg0->unk0x144 = 1;
arg0->unk0x140 = temp_r4;`. It now sits at **87.2%** with the sole residue being
six register colours (`temp_r9` on r4-not-r9; the call target at `0x388` on
r10-not-r9). Pinning `temp_r9` to r9 *regresses* to 20.8% (frame grows to 192B),
so the colour is not reachable through a pin.

**Caveat on the if/else form.** For a *loop-carried return* value it can go the
other way: `fn_8001517C` (63.3%) emits `var_r3 = temp_r0; temp_r0 = load(...);`
with the copy first, and both the "fix the order" and "if/else" rewrites drop it
to 26-29% (116B/124B against a 120B want). Always re-score; the mis-ordered form
is sometimes the one that reproduces retail's `lwzx r0; mr r3, r0`.

**Also closed this round:** `-ffixed-rN`-style per-address flag sweeps on the
2-diff NEAR drafts (`/tmp/fsweep1.py`, 40 flags × `fn_800BD96C`/`8015AACC`/
`80195668`/`801D1210`/`802241F0`) — **no flag moves any of them**, which
re-confirms that a two-adjacent-instruction transposition in a *heavy*
function is a scheduler tie-break, not a flag axis.

### 2026-09-13 (k) — the FLAG line is a cache; `-Os` + two new flags; call-arity by register shift

Four more promotions this round, all verified `build/main.dol == orig/main.dol`
(`ff6faeb0…`). The unifying discovery is that a draft's `// FLAG:` line is a
*decision cached against a body that no longer exists*.

| fn | size | how |
|---|---|---|
| `fn_8005D4F4` | 108B | 57.1% -> 85.2% (prototype) -> **EXACT** by deleting `-O1` |
| `fn_80044F60` | 244B | 54.7% -> 83.6% (two prototypes) -> **EXACT** (a dropped 2nd call arg) |
| `fn_80079FB4` | 144B | parked "GPR colour wall" -> **EXACT** by deleting the flag line |
| `fn_80117FC0` | 156B | 60.0% -> 92.3% (`-fno-expensive-optimizations`) -> **EXACT** (4-arg callee) |

**Recipe 66 — a `// FLAG:` line is a cached decision; re-sweep it after every
body fix.** `tools/flagrefresh.py` re-tests 16 candidate flag sets against every
draft that carries a FLAG line (451 of 3556). 34 improved, one of them to EXACT.
`fn_80079FB4`'s park note describes "a pure GPR colouring tie ... do not re-grind
without a new allocator lever" — *all* of it measured with
`-fno-schedule-insns -fno-sched-spec`, which cost 8.3 points; plain `-O2` is 100%.
`fn_8005D4F4`'s `-O1` had been chosen (48% -> 51.7%) against a body that still
emitted a varargs `crclr`. Corollary: never trust a park note's score without
re-measuring, and never trust the flag next to it either.

**Verification rule:** re-measure candidates through `gen_leaves.draft_flags()`
before writing. That function auto-adds `-mps-float` for `__ps_t` drafts, so a
sweep that passes `extra_flags` straight through scores such a draft with
`-mps-float` *missing* and reports a phantom gain (5 of 34 rows reverted this way
in `tools/apply_na.py`).

**Recipe 67 — two flag axes that were simply absent from the vocabulary.**
`tools/newaxis.py <flag>` runs one baseline + one compile per candidate over the
whole `src/wip` tree.
* `-Os` — **265** drafts improved, five by >= 10 points (`800CCD34` 92.8 -> 97.2,
  `8003EB5C` 5.6 -> 27.8, `800EC448` 1.1 -> 23.3). `-Os` is not "just -O2
  smaller": it flips block-ordering defaults, so it behaves like a scheduling flag.
* `-fno-rerun-cse-after-loop` / `-fno-expensive-optimizations` — **208** more,
  `80175690` +51.9 (14.9 -> 66.8), `80077CFC` +36.3, `8001E248` +35.6,
  `8021D990` +27.8, `801C2B04` +23.7.
The earlier "pairs of flags never beat their best single flag" verdict (doc 09)
still holds; these are all *single* flags, and the pool simply never had them.

**Recipe 68 — call-arity mismatch detected by register *shift*** (mirror of
doc 52). When want's argument-setup registers are each one slot **higher** than
ours and r3 has no setup before the `bl`, the callee has one more *leading*
parameter than the prototype declares — and that first argument is usually the
enclosing function's own arg0, already live in r3:

Retail keeps the enclosing function's own arg0 untouched in r3 with no setup before the call, staging zero into r4, the frame address at offset 8 into r5 and zero into r6, while a 3-argument prototype instead stages zero into r3, the frame address into r4 and zero into r5, shifting every setup register one slot lower.

Same word count, so neither the length check nor the score betrays it — only the
shift. `fn_80117FC0` (10th promotion of the session) and `fn_80044F60` were both
this, in opposite directions.

**Length-mismatch census** (`tools/lenmis.py`): 116 non-promoted drafts compile
to a different instruction count than retail. Equal-length residues are always
register/schedule ties; a length mismatch is a *whole-frame* bug — a dropped call
argument, a varargs `crclr`/`crset` word, or an extra epilogue copy. That census
is what located `fn_80044F60` (240B vs 244B: a callee was declared 1-arg and
takes two).

**Spurious-crclr census** (`tools/crclr_proto.py` / `tools/lenmis.py`): half the
pool (1797 of 3556) emits a `crclr cr1eq` retail does not have. On the >= 50%
subset this lever gave 2 of 4 promotions, so it was run pool-wide with the two
obvious prototypes per callee (arity from the call site x {s32, void} return):
**992 of 1797 drafts improved, seven of them to EXACT, zero regressions.**

| fn | size | prototype inserted |
|---|---|---|
| `fn_80018DEC` | | `s32 OSIsThreadSuspended(s32);` |
| `fn_800913C4` | | `s32 fn_800098F4(s32);` |
| `fn_800F2CB0` | | `s32 fn_800F34F0(s32, s32, s32);` |
| `fn_801770FC` | | `s32 fn_8009CF2C(s32);` |
| `fn_801A3910` | | `s32 fn_8009FDD8(s32, s32);` |
| `fn_8021F89C` | | `s32 fn_8019880C(s32);` |
| `fn_80234C64` | | `s32 fn_8023C598(s32);` |

The lesson is the size of the class, not the individual fixes: **half of all
remaining drafts are compiling a different program from retail because a callee
had no prototype in scope.** Any tool that scores drafts must therefore apply the
same prototype rule, and any hand-written draft should declare every callee.

### 2026-09-13 (k.2) — the masked-100 refused case is a *dead epilogue copy*, and the check is right

`fn_80221930`'s masked-100 body branches `ble → 0x80221B5C`, which is **past the
function's last byte** (0x80221A7C) — it lands inside the *next* function
(`xori r3, r3, 1` at 0x80221B5C, from fn_80219638's inline body). GCC emitted a
fallthrough into an out-of-line tail it placed after the neighbouring function's
epilogue. The masked score cannot see this; `tools/br_targets.py` refusing the
promotion is correct, and the `return 1`-inside-the-if shape that produced it is
a dead end, not one reword away. Plain `return 1` at function end gives 97.6%
(the scheduler merges the arms differently). Recorded so the next masked-100
hunt treats an out-of-range branch as *proven wrong*, not "probably a mask
artefact".

### 2026-09-13 (k.3) — length-mismatch census round 2; two case-map truths; the preheader-placement wall

Post-prototype-refresh census (`tools/lenmis.py 50`): 152 drafts compile to a
different length than retail, 120 without `__asm__`. Worked the top of the list:

* `fn_80207430` (98.5% masked): the last diff is the loop back-edge target —
  want's `blt` re-enters at the *load* (+0xB0) with the walker init in the
  preheader; ours re-enters at the *addi* (+0xAC).  Measured the full constraint
  pair (see the draft's park note): init-inside-loop gets the back edge wrong;
  init-hoisted gets the back edge right but GCC then schedules the addi before
  the `bge` guard, sliding 2 branch sites (92.4%); do-while destroys the tail
  diamond (10 diffs); `-fno-cse-follow-jumps`/`-fno-sched-*` move nothing.
  **ngccc cannot keep the walker init in the preheader AND after the guard.**
  Parked with the measured table.
* `fn_80115A28` (85.7%): retail's semantic case map decoded from the compare
  tree — CHECKSUM→0xD (not 0xA!), QB_STRUCT(0x456D28D1) is the second 0xA case,
  and 0x3200752A is not a case at all.  Applying the correct map scores *worse*
  (83.8%) because it changes GCC's tree shape; 260 case-order permutations of
  both maps top out at 86.7%.  Truth recorded in the park note, old map kept
  (score rules until a preheader-placement lever exists).
* `fn_80068760`: goto-walker → plain `for(;;)` walker: 70.0% → 76.7% and length
  now exact (120B).  Residual is want's `beqlr` conditional return + a ternary
  targeted *at the return register* (doc-25 family).  Parked.
* `fn_801F0610` (+20B): the dispatch is not on QB_* mode constants — want's
  compare list contains the four *PARAMS* hashes (0xB8CC8633…), i.e. retail
  switches on a different field/state machine.  Needs a semantic rebuild, not a
  mechanical fix; note updated.

Lesson of the round: **a masked score cannot distinguish "byte-exact program"
from "byte-exact except control flow", and neither can a correct-looking C
shape.**  `tools/br_targets.py` is the only referee; when it refuses, dump the
relocation addends (they are the *targets*, not the stale in-word
displacements) before theorising.

### 2026-09-13 (l) — missing-prototype calls: 7 promotions

The length-mismatch census (151 drafts) + a new undeclared-callee scan
(`tools/undecl_scan.py`) found drafts where m2c called functions it never
declared. Implicit-int calls insert `crclr cr1eq` (4B) and drop the real
return ABI — the +4 signature. Chasing the *word* (crclr lands before an
unrelated call) is the tell.

**7 EXACT (DOL byte-identical `ff6faeb0…`):**
`fn_8019BB98` (strcpy + fn_800092B0 protos), `fn_8017E340` (undeclared
mid-chain call), `fn_80174A58`/`fn_80175450`/`fn_801754AC` (batch-inferred
s32 protos), `fn_80185D10`/`fn_80185E9C` (protos + `(char *)` base for a
`+0x18` load — m2c's `(s32 *)p + 0x18` scales by 4 and emits `0x60(r3)`).

**Big gains kept:** `fn_80113C5C` 55.6→84.6, `fn_8023499C` 50→81.0,
`fn_801B07D4` 52.4→92.5 (also: reference the 0x802ABD98 table as an **extern
symbol**, not a numeric literal — literals emit `lis/ori`, symbols emit
retail's signed `lis/addi` %hi/%lo pair), `fn_80174D1C` 50→66.7,
`fn_80190840` 50→60.5, `fn_80129E28` 65.6→67.7, `fn_80118184` 53.8→55.3.

**Negatives:** prototypes on already-correct implicit calls regress
(`fn_80112A94` 81.1→68.3); wrong types collapse frames hard (8 drafts to
DIFF; 8003CF18 98→73.8 — all auto-reverted by the batch A/B). Top-22 NEAR
pool: no win (their "missing" decls are self-recursion noise).

Recipe 63 (doc 56). Batch tool: infer arity from call sites → insert
`s32 fn_X(...)` protos → A/B → revert on regress/no-score; EXACT banner has
no `%`, parse the banner first.

## 2026-09-14 — unparked NEAR pool: 2 promoted, 4 improved parks

Swept the `src/wip/` drafts that carry **no** park note (standard 4-line
header only) and worked the top of the score list. DOL byte-identical
`ff6faeb0…`; PROGRESS 8033 → **8035 / 11493 (69.912%)**.

**2 EXACT (promoted):**

- `fn_800A42F8` — 61.9 → 88.1 → **100.0**. Three independent truths:
  1. the slot-array base is **re-read at every use** (`4 × lwz r9,0(r31)`):
     the stores go through the pointer derived from `arg0->unk0x0`, so GCC
     cannot prove they don't alias `arg0+0`, and m2c's single `temp_r9`
     hoist is wrong;
  2. the three slot accesses are **full 32-bit** (`lwz r3,0xc(r11)`,
     `stw r27,4(r9)` with r27 = `0xC377C572` = `QB_NULL_SCRIPT`) and the
     `+0xC` guard is `*(s32 *)x != 0` with `fn_8012701C(*(s32 *)x, 3)`
     (two args) — m2c's `char` fields gave `lbz`/`stb` at the wrong offsets;
  3. **the address must be built as an integer sum with the loop offset
     FIRST**: `*(s32 *)(var_r30 + arg0->unk0x0)` emits `add r9,r30,r9`
     and the lwzx/stwx operand order follows it; `(char *)arg0->unk0x0 +
     var_r30` emits `add r9,r9,r30` (5 words).  Plus the entry test is
     `var_r28 < (s32)arg0->unk0x4` (`cmpw r28,r0`), not `count > 0`.
- `fn_801A5C70` — 57.1 → 85.7 → **100.0**. Two recipes:
  1. **an indexed load needs a variable offset.**  Want reads the
     arg0+0x20 slot as `lwzx r3,r29,r28` with r28 = 4, so the byte offset
     must be a *variable* (`off = 4;`), not a literal: a literal always
     folds to `lwz r3,4(r29)` (10.7%).
  2. **the assignment order of two locals selects the register order.**
     `off = 4;` written *before* `var_r29 = arg0 + 0x1C;` makes ngccc put
     the offset in r28 and the base in r29 → `lwzx r3,r29,r28`.  Swapping
     the two assignments swaps r28/r29 (85.7%).  (Also needed the missing
     `fn_8000F2F8(Unk_9F352E7C *, s32)` proto: implicit-int cost the
     `crclr cr1eq` *and* one callee-saved register — `stmw r26` vs `r27`.)

**Big gains kept (parked, exact size):**

- `fn_8012EE64` — 56.9 → **95.4** (62/65, exact 260B).  All three calls
  take **two** arguments and m2c dropped one each:
  `fn_8012701C(arg0->unk0xDC, 3)` (the loaded value is *reused* as r3, so
  want shows `lwz r3,0xdc(r31); cmpwi r3,0; li r4,3`),
  `fn_800A3D8C(arg0->unk0xE0, 3)`, and
  `fn_8009DFC0(arg0->unk0xBC, &arg0->unk0xBC)` — `fn_8009DFC0` is
  `(Unk_2EF06E12 *, Unk_2EF06E12 *)`, the second arg is the node address
  (`addi r4,r31,0xbc`), cf. `fn_8004CC88`'s `fn_8009DFC0(sp8.a, h)`.  The
  one-arg forms were a whole instruction short (256B) and lost 12 words.
  Residual = 3 scheduling words (want hoists `addi r4` above the `cmpwi`).
- `fn_80097478` — 61.8 → **85.3** (29/34, exact 136B).
  (a) the header table is read as **bytes** but written as a **word**;
  (b) the 4th comparison reads **byte 3 of the stack copy** — the source
  took `&spC`, so write `((u8 *)&spC)[3]` (a plain `(u8)spC` keeps spC in a
  register and collapses the tail to 13.9%); (c) prefer the real
  `extern u8 lbl_803018C8[]` symbol over a `(u8 *)0x80300000 + 0x18C8`
  literal — the symbol makes GCC CSE the `lis` and emit `addi r10,r9,0x18c8`
  (the two `lis` words still mask as reloc matches).  Residual = the two
  address-taken locals' **stack-slot numbering** (want sp8@r1+8 / spC@r1+0xC,
  ngccc the reverse); all 6 declaration permutations, type mixes and store
  orders leave it unchanged — it is usage-driven, not declaration-driven.
- `fn_80174D1C` — 66.7 → **79.5** (31/39, exact 156B).  The walk loop is
  **body-first**: `for (;;) { if (o4 == -1) p = NULL; if (!p) break;
  p = p->oC; n++; }` reproduces the `b` over the body to the bottom test and
  the `bne` back-edge.  The `(a || (x = f()))` form must keep the call's
  result in the same variable the function returns.  Residual = one
  register-color coin (want address temp r11 / walk ptr r9; ngccc the
  exact opposite) — unaffected by assignment order, a named address local,
  or every declaration order.

**Probed, not improved (note left in the file):**

- `fn_8001517C` (63.3%) — two semantic facts confirmed, no shape beat the
  coincidental m2c body: (1) the vtable adjuster is a **signed halfword**
  (`lha r0,0x30(r9)`) — reuse the local-struct idiom from
  `src/fn_80057E7C.c` (`VT_7A53` with `s16 unk0x30;`); with it the whole
  dispatch body compiles 1:1.  (2) `var_r3` must coalesce into **r3**;
  ngccc instead allocates it to a callee-saved reg (13 words more) or fuses
  the inner test into `or. r3,r3,r3`.  10 flag combos, assign-in-condition
  and separate-temp forms all sit at 26.7%.

Tooling: `tools/wdiff.py <hexaddr>` prints a masked want-vs-got instruction
diff with capstone mnemonics — reads the draft straight from
`src/wip/fn_<addr>.c`.

**2026-09-15 (b) — random-batch sweep of no-park drafts: 3 EXACT promotions
(DOL byte-identical `ff6faeb0…`) + 4 parks with notes.** Sampling only
`src/wip` drafts with **no** `// …PARK` line (1,826 files) and scoring 256 of
them found no free matches (best 73.3%), so each pick needed real work:
- **fn_801205D0 (108B) EXACT, promoted** — three m2c artifacts: the object
  field was spelled `*(s32 *)((s32 *)p + 0x11C)` (= byte 0x470, not 0x11C);
  `fn_80009A78` takes **one** arg (m2c passed `arg0` twice, adding a stray
  `mr r4,r3`); and all four callees need prototypes (unprototyped calls each
  emit `crclr cr1eq`).
- **ScriptGetEditedParkGapName / fn_80234B80 (76B) EXACT, promoted** — the
  string arg was a raw `0x802B0928` literal; referencing `lbl_802B0928`
  (doc-51) plus the two missing callee protos is the whole diff. The draft's
  blind `-O1` header flag was actively wrong (89.5% with it, 100% at -O2).
- **fn_8006EF98 (124B) EXACT, promoted** — the fn_8005D9F0 twin. Applying
  that recipe verbatim (u32 `n`/`i`, `} while (i-- != 0);` post-decrement
  latch, tail stores 4/8/0x14, real protos) took 47.1% → 100%. Confirms the
  u32-counter rule: with s32 ngccc synthesizes an extra `mr r0,r31` before
  the post-decrement test.
- **fn_8022F184 parked at 96.3%** (26/27, size-exact) — protos + QB reads
  fixed the rest. NEW empirical rule for the residual word: ngccc emits
  `or. rX,rX,rX` iff the tested value's register is **live** after the branch
  and `cmpwi` iff it is **dead** (verified with a 13-case probe matrix).
  want's outer `cmpwi r3,0` sits on a value whose `beq` edge returns that
  same register, so every li-free source shape is live → `or.`; the shapes
  that produce `cmpwi` (direct `if (fn() != 0)`, explicit `return r` in both
  arms) materialize the 0 on the false edge and run 2 words long. ~40
  shapes/flags, all 108B or 116B/112B as tabulated in the draft header.
- **fn_8005EF7C parked at 80.0%** (size-exact) — the indirect call is 1-arg
  (m2c passed the vtable pointer as a bogus 2nd arg, shifting everything);
  residual is a pure home coin (want object in r3 + field load in r0; ngccc
  object in r9 via `or. r9,r3,r3` + load in r3). 9 spellings incl.
  pointer-typed local structs — all 80.0%.
- **fn_80016304 parked at 71.8%** (`-fno-schedule-insns`) — the CARDGetStatus
  output is a full CARDStat **local** (frame 0x88, `sp8.length` at +0x20),
  not m2c's `static s32 sp28`. Residual = arg0/arg2 callee-saved home swap +
  the two return blocks in the other order (152B vs want 156B); 7 return
  structures all converge.
- **fn_80012C28 parked at 75.0%** (`-O1`, size-exact) — QB-helper arity bug
  again (`fn_801280E0(arg0, 0, &sp8, 1)` is 4-arg, ctx first); residual is the
  doc-15 call-setup interleave plus the QB case-body temp home.

**2026-09-15 (c) — residual-ranked sweep of ALL 1,787 no-park drafts: 13 EXACT
promotions (DOL byte-identical) + 36 improved + 1 park, and two new recipes.**

Instead of sampling, everything was scored and then **ranked by the residual**
(`tools/diff_census.py`: non-branch mismatching words, since branch targets are
masked and the percentage alone hides 4-diff-in-11-word drafts). That ranked
list is what the whole session ran on.

- **fn_801FBE60 (124B) EXACT, promoted — new recipe 57 (lis sharing).** The
  `lis r28` / `addi r4,r28` split (callee-saved, `T != D`) means MWCC
  *materialised the symbol's address once and shared the `lis`*; that needs a
  register alive across the call, so the frame grows. Three levers: the format
  string had to be the real `lbl_802AE5B4` symbol + `s32 sprintf();` (a raw
  literal makes ngccc emit `lis+ori`, a value, not `lis+addi`, an address);
  the buffer is `char sp8[0x38]` — **the frame size picks the buffer** (want
  0x50 ⇒ locals run to the `stmw` slot at 0x40); and the loop must be the plain
  `while`, because m2c's `if (p) { loop: … goto loop; }` keeps the `lis` inside
  the loop so it coalesces with the argument register. 71.0 → 100.
- **8-member vtable-setter family EXACT, promoted** (`fn_80050140`,
  `fn_80066E68`, `fn_80067554`, `fn_800677A8`, `fn_80067BA4`, `fn_80067DB4`,
  `fn_80067FC4`, `fn_800681D4`, all 56B). doc-52 again: `fn_X(0, 0xADDR)` is a
  phantom 2-arg call, the real one is `fn_X(arg0)`. Their headers said
  `-fno-schedule-insns`; that flag was **hiding** the defect — with the arg
  dropped they are exact at default flags.
- **fn_8022CFF8 (44B) EXACT, promoted.** Its header carried
  `-ffixed-r11` (45.45%); the real defect was the **two indexed stores being in
  the opposite order** (retail writes the non-zero slot first), which also
  lands retail's r11 index colour. Without the flag: 100%.
- **fn_80069130 (72B), fn_8006E9AC (72B), fn_8009F60C (56B) EXACT, promoted.**
  Phantom args again (2-arg vs m2c's 3-arg; the `lis` half of a label read as an
  argument). `fn_8009F60C` also needed the doc-53 `s16` retype of the dispatch
  offset (`lha r3, 8(r9)`), via a local view type.
- **fn_80055CB0 (452B) 71.7 → 82.3, parked with note.** doc-53 width retype
  (two local types: `s16 @0x38` on the dispatch object, `s16 @0x8` on the
  `Unk_2EF06E12` frames) = 75.2; then the doc-53 "load the condition's sentinel
  into a named local *before* the `var = temp` copy" lever on the two `0x280`
  walkers = 82.3. Residual is the pair of `crclr cr1eq` words and the `0x27C`
  list's colour chain — every prototype spelling re-colours the whole function
  (34–44%) so the two effects cannot be separated; no `__asm__` pins used.
- **36 drafts improved** by `tools/drop_phantom_arg.py` (the best:
  `fn_8004567C` 40.9→76.2, `fn_800A3C50` 19.4→75.9, `fn_800A33E4` 19.4→74.3,
  `fn_800685A4` 36.7→72.4); all kept the better body in place.

**Two generalisable lessons.**
1. **A `// FLAG:` line is a cache, and it can mask the fix** — the 2026-09-13
   flag matrix only ever rescored *bodies* with a flag applied, so a wrong flag
   hides the real defect. Re-score flagged drafts with **no flags** and compare
   (`tools/noflag_score.py`). 356 no-park drafts carry a flag; here it exposed
   `fn_8022CFF8` (and would have exposed the whole setter family had the arg fix
   not been tried first).
2. **Rank by residual, not by percentage.** `tools/diff_census.py` +
   `tools/real_diffs.py` (prints only the non-branch mismatches) turn a 1,787
   draft pool into a worklist, and a 4-diff/11-word draft is far cheaper than a
   30-diff/200-word one at the same percentage.

**2026-09-15 (d) — widened phantom sweep + two more promotions + one 96.1% park.**

- Widened `tools/drop_phantom_arg.py` to bare `0x80xxxxxx` literals in **any**
  argument position (233 candidates beyond the 124 trailing-only ones): 37 more
  drafts improved (best `fn_8009F054` 41.2→75.0, then promoted;
  `fn_80041FDC` 69.6→71.8). No further complete matches came out of the widened
  set on its own.
- **`fn_8009F054` (64B) EXACT, promoted** — m2c transposed the call's argument
  order: retail leaves r4 untouched (the callee's 2nd arg is this function's own
  2nd parameter) and shifts everything one slot; 7 args, not 6. The signature is
  an **off-by-one across the whole argument register set** (4 of 16 words).
- **`fn_80041FDC` (308B) 71.8 → 96.1%, parked.** The `fn_800A54AC` call had no
  prototype, so ngccc passed the trailing `f32 lbl_80292398` as an *integer*
  (`lwz r4,0(r29)`) and emitted `crset cr1eq`; the real 7-param prototype ending
  in `f32` gives retail's `lfs f1,0x2398(r9)`. Residual = 3 words of scheduler
  slot-fill before the `fn_80127684` call; 5 spellings tried (named `&sp8`
  locals at use-site/function scope collapse to 51.3%, casts and a reordered
  `fn_800A3BDC`/`fn_80126EAC` pair are neutral or worse).
- `tools/real_diffs.py` now takes `--flags "<cflags>"` so a body file (which has
  no `// FLAG:` header) can be diffed under the draft's real flags — without it
  a flagged draft's residual is measured against the wrong program.

**2026-09-15 (e) — frame/shift detection + two new automated sweeps: 6 EXACT
promotions (DOL byte-identical) and 246 drafts improved in place.** This round
was about *detectors* rather than hand work: three of the six matches came from
tools that found a draft whose body was already correct apart from one
systematic spelling error.

- **fn_80125020 (104B) EXACT, promoted.** Found by `tools/frame_only_scan.py`
  (drafts whose only diffs are the prologue/epilogue — 1 hit in 1,787) and
  confirmed by the wider `tools/shift_scan.py` (slide `got` against `want` by
  ±N words over the body): 14.8% with an 0x18 frame + `stmw r29` where retail has
  0x10 + `stmw r30`. The cause was m2c's `fs_t` local: keeping the malloc result
  in a C local makes a pointer live across both calls (one extra callee-saved
  register, +8 bytes frame, whole body slides one word). Retail stores the result
  into the u32 global and reads it back. Doc-57 addendum.
- **fn_800249A4 (156B) EXACT, promoted.** 94.9% → 100% on one word: the
  `arg0->unk0x10` read must be hoisted into a local *before* the
  `arg0->unk0x8 = (s32)lbl_802913F8;` store, or MWCC schedules `mr r30, r4` above
  `lwz r3, 0x10(r31)`. The other two fixes were the doc-52 label argument and
  the doc-53 `s16` vtable offset (`lha r3,8(r9)`). Doc-52 addendum.
- **fn_8006A8C0 (92B) EXACT, promoted.** 41.7 → 91.3 from the new
  `tools/label_arg_scan.py`, then 100 by passing the *symbol*
  (`fn_8006A960((s32)lbl_80366590, &sp8)`) instead of the literal `0x80366590`:
  MWCC emits `lis+ori` for a literal constant but `lis+addi` for an address.
  Doc-51 addendum.
- **fn_800DF3F0 (48B), fn_800872FC (92B), fn_800144EC (72B) EXACT, promoted.**
  All three from the doc-51 extended sweep (`tools/raw_sym_scan.py`), including
  fn_800DF3F0 which had been *parked with the correct diagnosis*
  ("lis+ori vs lis+addi addressing differs from original compiler") — the
  observation was right, the lever simply had not been applied. fn_800872FC went
  7.4 → 100 and fn_800144EC 31.6 → 100. The two FP ones need the
  `fix_fp_pool.py` step to retarget their int→float magic pool at an existing
  DOL label (the promote tool refuses a body whose pool cannot resolve).
- **Two new automated sweeps + a splice helper.** `tools/raw_sym_scan.py`
  (raw address literal → registered `lbl_*`, every position including the
  mid-argument `,` case that `fix_raw_lit.py` never matched; 240→82, 722→151,
  re-scan→13 improvements), `tools/label_arg_scan.py` (m2c's invented *symbol*
  call argument; 179→33) and `tools/apply_better.py`, which writes a winning
  variant body back into its draft with an `UPDATED <date>: old% -> new%` note.
  Net: ~246 drafts improved, all improvements kept.
- **fn_80054388 (152B) 50.0 → 89.5%, parked.** Three real fixes: drop m2c's
  bogus label argument, correct the vararg counts (the `lbl_80293024` call
  passes arg0 twice), and write the guard as `do { … break; } while (0)` so MWCC
  emits the shared tail block first (the plain nested `if` puts the two sprintf
  blocks in the opposite order: 63.2%). Residual is 3 words of prologue — retail
  saves arg1 (`r29←r4`) before arg0 (`r31←r3`), ngccc the other way; 12 flag
  combos do not change it. The stale `// FLAG: -fno-gcse
  -fno-expensive-optimizations` was **removed**: with the new body it costs 13
  points (76.3% with, 89.5% without) — another instance of doc 55, a `FLAG:` line
  is a cache that can hide the defect.
- **Process fix:** `tools/apply_better.py` initially dropped the
  `#include "types.h"` line when splicing (the sweep helpers strip it
  because `compile_fn` re-adds it). Scoring is unaffected — `score_body.py`
  strips and re-adds the include too — so it only surfaced at promotion time as
  `f64 undeclared`. The tool now restores the include, and the 254 affected
  drafts were repaired; the two promotions that failed because of it were
  re-run and are byte-identical.

**2026-09-15 (f) — stale-FLAG sweep: 1 EXACT promotion (DOL byte-identical) from
a draft that was parked as a register-colouring wall.** `tools/flagdrop_scan.py`
A/Bs each flagged draft's header flags against *no* flags (809 drafts → 14
winners) and `tools/flagtok_scan.py` peels one token out of a multi-token FLAG
line (809 → 7, all ≤ 2pt).

- **fn_80079DA8 EXACT, promoted.** Parked with *"doc-15 scratch-color coin flip,
  3 words: want homes the shift …"* — 94.7% with its recorded flags and **100%
  with none**. The 3 residual words were the stale flag, not the allocator. Worth
  re-reading as a general rule: when a park note blames register colouring for a
  2–4 word residual, re-test the flag axis before accepting the regalloc story.
  (fn_80054388 earlier in this session was the same failure mode, found by hand.)
- The other 13 flag-drop drafts and 7 token drops were kept at their better
  scores, with the A/B recorded in each header so the next sweep does not
  re-add the flag. Doc-55 addendum covers the mechanism and the two scanners.

A quick audit of the *existing* parks for the levers automated earlier today
(`grep` the park notes for "lis+ori"/"lis+addi"/"phantom"/"literal") returned
almost nothing: 185 literal-named parks → 0 further improvements, 59
phantom-named parks → 2 small ones. The notes were accurate; the wins this round
came from new *detectors*, not from re-running the old levers.

**2026-09-15 (g) — the "label as a call argument" family: 5 EXACT promotions
(DOL byte-identical) + 16 drafts improved + doc 58.**

Started from the ≤4-residual, size-exact worklist (only six drafts in the whole
1,785-draft pool) and widened to ≤8 residuals, which surfaced a family: ten
drafts whose *only* defect was `bl>crclr`/`bl>mr` plus a one-word size excess.

- **Root cause (new doc 58):** for `arg->unkNNN = (s32)lbl_X;` m2c reads the
  `lis/addi` pair a *second* time and appends `(s32)lbl_X` to the **next** call's
  argument list. Retail's `bl` has no argument setup at all, so the draft spends
  an extra `lis/addi` + `mr r3, rX` before the `bl`, and — collateral damage —
  the two struct-field stores get the opposite register assignment. Cheapest
  tell: m2c emits the `extern char lbl_X[];` declaration **twice**, once per role
  it thinks the symbol plays. 71 no-park drafts carry a duplicated label extern.
- **Promoted:** `fn_80062988` / `fn_8009DEF8` / `fn_801A38A0` (40 → 100, the
  zero-arg-call + `andi. r0,r30,1` / `mr r3,r30` tail family) and
  `fn_8002DCCC` (42.9 → 100, object-header variant). One more promotion in the
  same pass: **`fn_8019D388`** (84.6 → 100) — not this recipe but the sibling
  observation that hoisting a **global deref into a local above an unrelated
  store** makes MWCC issue the `lwz` early and reuse the register for the `+8`
  (`addi r3,r11,8`); its stale `-fno-schedule-insns2` header flag was *masking*
  the fix (84.6 with the flag, 100 without — doc 55 again).
- **Improved:** `fn_800500B8` 33.3→85.7, `fn_80066998` 33.3→85.7,
  `fn_8002E050` 20.5→83.3, `fn_80032328` 30.8→72.0, `fn_80203810` 40.0→68.4,
  `fn_8007ABB8` 40.0→63.2, `fn_800F1F74` 39.0→61.5 (its phantom argument is the
  `sprintf` **format** string), `fn_8004238C` 32.1→46.2, `fn_80045FA8` 25.0→40.0,
  `fn_8022E16C` 35.3→36.9, `fn_8016A480` 23.7→25.0, `fn_80018098` 14.3→19.4,
  `fn_801B2B10` 12.1→12.8, `fn_80234444` 3.9→4.8, `fn_8023D8E4` 21.3→22.2,
  `fn_80145C14` 9.6→10.1. Every one A/B-verified against its pre-edit body
  (git HEAD) — no regressions.
- **`fn_800EC5A4` 89.5 → 94.7** and **`fn_800685A4` 89.7 → 93.1**, both still
  parked at a 2-word residual: the first is a pure store-order question
  (`tools/stmt_perm_search.py` over all 120 orders of the 5-statement tail tops
  out at 94.7 — MWCC preserves store order here, so the DOL's order *is* a source
  order, and the remaining word is `unk0x4 = QB_PARTICLECHAIN` sinking one slot);
  the second needed the doc-53 `s16` view type (`lha r3,8(r9)`) and is left with
  the `arg0->unk0xC != 0` test homing in r0 instead of the DOL's r4 — 8
  alternative condition spellings and 6 flag combos all stay at 93.1.
- **`fn_80173D30` (1 word, 99.5%) stays parked, but the diagnosis is now
  sharper:** the residual `li r4,0` vs `mr r4,r30` in the `tmp == 0` else-if is
  caused by the draft's own `register s32 tmp __asm__("r30")` pin — the
  allocator *knows* tmp is 0 on that edge and reuses r30 instead of
  materialising the constant. Removing the pin fixes that word but re-colours
  the whole 216-word function (84.3%), so the pin is load-bearing. `fn_8004567C`
  4-word residual is also unchanged: giving `fn_8005EBE4` its real prototype
  removes the `crclr cr1eq` but drops the size by one word (33.3%), so the
  `mr r0,r4` + sunk store there is a scheduler artefact, not a proto artefact.
- **New tool: `tools/label_call_arg_scan.py`** — walks every call in a draft,
  finds arguments that are *entirely* `(s32)lbl_XXXXXXXX` (any position,
  optional `&`), rebuilds the argument list, and A/B-scores the plain and the
  prototype-adjusted variant, keeping the best per address. Also new:
  `tools/residue_census.py` (what *kind* of word is wrong, not just how many —
  this is what exposed the `bl>crclr`/`bl>mr` family) and
  `tools/diff_census.py`'s size column read as a worklist.

**2026-09-15 (h) — doc-56 missing-prototype sweep: 8 more EXACT promotions
(DOL byte-identical) and 275 drafts improved.**

Picked up the drafts the doc-58 round had taken to 83–86% and closed them, then
automated the lever that kept showing up.

- **Closed from the 85.7% / 83.3% tail (each a *second*, unrelated edit after
  the phantom-argument fix — all EXACT):**
  `fn_800500B8` (85.7→100) and `fn_80066998` (85.7→100): the two struct-field
  stores are in the opposite *source* order — retail materialises the 0x1A8
  store's address first.
  `fn_8002E050` (83.3→100): `arg0->unk0x14 = lbl_80291AA8;` must come *after*
  the two self-link stores.
  `fn_80032328` (72.0→100) / `fn_80203810` (68.4→100) / `fn_800B2B3C`
  (68.4→100): one extra `crclr cr1eq` word from an undeclared trailing callee
  (`fn_800320D8`, `fn_8009F558`).
  `fn_80185D70` (33.3→100): the literal goes in **r5**, not r3 — retail keeps the
  incoming r3/r4, so the wrapper must be declared `(s32 a, s32 b)` and forward
  them; and m2c's `(s32 *)X + 0x18` had **scaled** the offset to 0x60 where the
  DOL loads the byte offset 0x18.
- **New sweep `tools/proto_undeclared_scan.py` (doc-56 addendum).** For every
  draft, declare each callee that has no prototype in scope; use the callee's
  own `src/fn_XXXXXXXX.c` signature when it exists, else infer the parameter
  count **from the call site** (`void *` and `s32` pass identically on PPC, so
  only the count matters). Two traps that cost real time:
  1. the "already declared" regex must **require a return type**, otherwise it
     also matches the call statement `    fn_X(a, b);` and skips the callee;
  2. **prefilter on the object code** — compile once and skip drafts whose got
     contains no `crclr`/`crset`, else the sweep is ~5 prototypes × ~10 callees
     per draft and runs for hours (1785 drafts: hours → 5 min).
  Result: **275 drafts improved, 3 promoted EXACT** — `fn_801A0D50` (45.8→100),
  `fn_8012E018` (47.4→100, the *return type* mattered: `void *fn_800105CC(u32 size);`
  inside `fn_X(fn_800105CC(0x1C))`), `fn_8007ABB8` (63.2→100). Best partials:
  `fn_8004CDAC` 50.0→97.0, `fn_80010C1C` 32.4→94.4, `fn_8004238C` 46.2→92.0,
  `fn_8005C944` 42.3→84.0, `fn_800A1AE8` 33.3→82.8, `fn_80234FC0` 41.2→81.2,
  `fn_80062934` 40.9→81.0.
- **Verification trap worth recording:** for a draft with a `// FLAG:` header,
  before/after must be compared *with those flags applied*. Nine of the 275
  edits looked like regressions when both sides were scored at default flags
  (`fn_800F45A4` 23.3 vs 21.4); under its real `-O1` the pair is 57.1 → 73.2,
  i.e. exactly the improvement the sweep measured. `score_body.py` does **not**
  read the header FLAG — pass it explicitly, or use `score_addrs.py`.

Session total: **15 promotions** (`fn_8019D388`, `fn_80062988`, `fn_8009DEF8`,
`fn_801A38A0`, `fn_8002DCCC`, `fn_800500B8`, `fn_80066998`, `fn_80032328`,
`fn_80203810`, `fn_800B2B3C`, `fn_80185D70`, `fn_8002E050`, `fn_801A0D50`,
`fn_8012E018`, `fn_8007ABB8`), ~310 drafts improved, 3 new tools
(`residue_census.py`, `label_call_arg_scan.py`, `proto_undeclared_scan.py`),
doc 58 + addenda to docs 56 and 58.

**2026-09-15 (i) — iterative prototype sweep + the `fn_801839F0` r5 family:
4 more EXACT promotions (DOL byte-identical), 118 drafts improved.**

- **Made `tools/proto_undeclared_scan.py` iterative.** A draft usually carries
  more than one undeclared callee and the first prototype only removes the first
  `crclr`; the sweep now loops up to 4 rounds, re-deriving the declaration set
  from the current best body each round. Restricting to the 1,026 no-park drafts
  whose object code still has a `crclr`/`crset` keeps it cheap: **114 drafts
  improved, 2 promoted EXACT** — `fn_8018B90C` (26.4→100, four-arg
  `fn_80128228`) and `fn_801992A8` (62.5→100). Best partials `fn_800AAEA4`
  64.9→97.1, `fn_8018403C` 55.6→96.2, `fn_80185474` 61.9→95.0, `fn_80171868`
  66.7→89.7, `fn_8021B3E0` 70.7→89.3. All 114 re-verified with flag-aware
  scoring: **0 regressions**.
- **The literal can live in a *later* argument slot — a different defect.**
  `fn_801839F0` is called by 26 wip drafts and retail puts the literal in **r5**,
  with r3/r4 carrying the caller's *incoming* args (`bl; li r5,1; bl`). m2c
  dropped those two pass-through arguments. Fix: declare the enclosing wrapper
  with (at least) two leading params and forward them —
  `fn_801839F0((s32)a, (s32)b, 1)`. Of the 8 family members whose argument is a
  literal this closed **`fn_8018403C`** (96.2→100) and **`fn_80185474`**
  (95.0→100), plus `fn_8018694C` 85.7→89.3, `fn_80184BB0` 37.5→43.8,
  `fn_80184EB4` 40.7→44.4, `fn_80183F08` 13.6→15.3, `fn_80183FDC` 8.3→12.5. The
  other 18 pass a computed value and the same edit makes them *worse* — A/B.
- **Stop-loss recorded:** `fn_80184558` (66.7%) looks like the same family but
  its residual is a redundant loop-carried copy (`var_r4 = arg1;`) that emits two
  `mr`s; removing it drops to 62.5%. `fn_8018BC14` (67.6%) is unchanged by
  reordering its `fn_80188190` call against the field load. Both are written into
  doc 56 so the next pass does not re-try them.

Session total: **19 promotions** — `fn_8019D388`, `fn_80062988`, `fn_8009DEF8`,
`fn_801A38A0`, `fn_8002DCCC`, `fn_800500B8`, `fn_80066998`, `fn_80032328`,
`fn_80203810`, `fn_800B2B3C`, `fn_80185D70`, `fn_8002E050`, `fn_801A0D50`,
`fn_8012E018`, `fn_8007ABB8`, `fn_8018B90C`, `fn_801992A8`, `fn_8018403C`,
`fn_80185474` — with ~430 drafts improved in place, 3 new tools, and doc 58 plus
addenda to docs 56 and 58.

**2026-09-15 (j) — closing the top of the residual-ranked worklist: 4 more EXACT
promotions (DOL byte-identical) and a new look-alike defect documented.**

Working down the re-ranked no-park list (`score_addrs.py` over all 1,765 drafts)
and fixing the best partials one at a time:

- **`fn_800AAEA4` (97.1 → 100).** Its 1-arg call `fn_8009FCD8(arg0)` is really
  2-arg: retail leaves the *previous call's result* sitting in r3 and only emits
  `mr r4,r31` for arg0, so the source is `fn_8009FCD8(temp_r30, arg0);`. m2c
  drops a leading argument whenever the value is already in r3 — a second
  variant of the doc-52 "arguments restored from the live register file" family.
- **`fn_80171868` (89.7 → 100).** Two fixes: the **scaled-offset look-alike**
  (`(s32 *)X + 0xC` had become `+0x30`) and the loop's `var_r31 += 0x190;` must
  come **after** the call — with it before, MWCC schedules the `addi` ahead of
  `mr r4,r28` and one word lands wrong; after the call it drops into the last
  free slot exactly as retail.
- **`fn_8004CDAC` (97.0 → 100).** doc-53 member 3: `temp_r9->unk0x10` is an
  **s16** added to a pointer (`lha r3,0x10(r9)`), fixed with a local view type
  `{ char pad[0x10]; s16 unk0x10; s32 unk0x14; }` so the shared
  `Unk_C8FEE62D` header is untouched (`unk0x14` stays `lwz`).
- **`fn_8018694C` (89.3 → 100).** Two fixes: the scaled-offset look-alike
  (`+0x18` → `+0x60`), and the function really takes **four** params — m2c named
  them `arg2`/`arg3` (it knew the *indices*) but placed them in r3/r4, while
  retail saves **r5/r6** and forwards the untouched r3/r4 to `fn_801839F0`, so
  the signature needs two leading pass-through params.

**New look-alike defect written up in doc 53:** m2c emits `(T *)(fn_X(...)) + N`
where `fn_X` returns an *integer*, which makes `+N` pointer arithmetic scaled by
`sizeof(T)`. Three members now (`fn_80185D70` 0x18→0x60, `fn_80171868` 0xC→0x30,
`fn_8018694C` 0x18→0x60). **Detection shortcut:** a diff with the *same base
register* and a displacement that is a clean multiple of 4 (0xC vs 0x30) is this
bug, not a width problem — grep the draft for `(s32 *)`/`(T *)` casts applied to
a call result before `+`.

**Also built `tools/late_literal_slot_scan.py`** (doc-56 addendum 2's detector):
it finds, straight from the object code, calls where want materialises a literal
in r5/r6/r7 immediately before a `bl` while the draft puts the same literal in
r3. Tightening it to require adjacency on both sides plus a source-level
`callee(LIT)` confirmation collapsed the 1,620 raw hits to **1**, and that one
was coincidental — the `fn_801839F0` family from addendum 2 is exhausted in the
current pool. The tool is kept for future drafts.

Session total: **23 promotions** — `fn_8019D388`, `fn_80062988`, `fn_8009DEF8`,
`fn_801A38A0`, `fn_8002DCCC`, `fn_800500B8`, `fn_80066998`, `fn_80032328`,
`fn_80203810`, `fn_800B2B3C`, `fn_80185D70`, `fn_8002E050`, `fn_801A0D50`,
`fn_8012E018`, `fn_8007ABB8`, `fn_8018B90C`, `fn_801992A8`, `fn_8018403C`,
`fn_80185474`, `fn_800AAEA4`, `fn_80171868`, `fn_8004CDAC`, `fn_8018694C` — with
~440 drafts improved in place, 4 new tools, and doc 58 plus addenda to docs 53,
56 and 58.

**2026-09-15 (k) — m2c's *dropped* argument: 12 EXACT promotions (DOL byte-identical)**

The last few rounds all attacked m2c's *phantom* (extra) arguments. This round
went after the mirror image — m2c **dropping** an argument — and it turned out
to be the single biggest lever left in the pool.

Re-ranked all 1,763 no-park drafts (`score_addrs.py`) and worked the residual
census (`residue_census.py` over the whole pool, 3,203 mismatch words) down from
the top:

| fn | size | score | lever |
|---|---|---|---|
| `fn_80010C1C` | 144B | 94.4 → 100 | the final two `temp->unkX = temp;` self-store pairs are in the *opposite source order* (write `unk0xC` before `unk0x10`) |
| `fn_800A33E4` | 140B | 74.3 → 100 | same self-store-pair order fix |
| `fn_8004238C` | 100B | 46.2 → 100 | **doc 59** — `fn_80009AAC(arg0->unk0x190)` |
| `fn_8005C944` | 100B | 42.3 → 100 | doc 59 + **doc 60** — `fn_8005C9A8(arg0,1)`, `fn_8005D194(arg0->unk0x8,3)` |
| `fn_800685A4` | 116B | 89.7 → 100 | doc 59, *second* slot — `fn_8000F9C4(g, arg0->unk0xC)` |
| `fn_80242528` | 104B | 80.8 → 100 | doc 59 nested form + plain `while` instead of m2c's `if(n>0){do..while}` |
| `fn_80234FC0` | 64B | 81.0 → 100 | **doc 60** — the function is not `(void)`: it forwards incoming r3 |
| `fn_800A3C50` | 116B | 75.9 → 100 | **doc 61** — `extern s32 lbl_80301A78;` instead of `extern char lbl_80301A78[]` + deref |
| `fn_800F21E8` | 136B | 85.3 → 100 | doc 60 + doc-53 `s16` view type |
| `fn_8018BED8` | 212B | 73.6 → 100 | doc 59, both `fn_8012701C(3)` calls |
| `fn_80126E28` | 116B | 79.3 → 100 | doc 59 nested form (4 args, first = the preceding call's result) + the `arg1+2` byte is a plain `u8` load |
| `fn_800A1AE8` | 116B | 74.3 → 100 | **doc 60 second form** — m2c emitted the params as `(arg1,arg2,arg3,arg0)`, every home one slot low; real signature `(s32 arg0, T *arg1, U *arg2, s32 arg3)` |

**Three new recipes** (docs 59/60/61) with prefilters, because each lever needed
one to be affordable:

- `tools/cmp0_home_scan.py` → `tools/forwarded_test_scan.py` (**doc 59**): the
  guarded load becomes *compare-only*, so ngccc homes it in `r0`
  (`lwz r0,d(rB)` + `cmpwi r0,0`, 501 drafts). The retail source forwards the
  tested value into the guarded call. **Scope it to a call that is the first
  statement of the `if` body** — widening it to any call in the block gave
  hundreds of large regressions (`memcpy`, `memset`, the destructor call).
  ~20 drafts improved, 6 promoted.
- `tools/slot_low_scan.py` → `tools/lead_arg_scan.py` (**doc 60**): the whole
  argument block sits one register low because m2c never forwards the enclosing
  function's own parameter (`li r4,LIT` in want vs `li r3,LIT` in got, 401
  drafts). 23 drafts improved, 3 promoted. Two traps fixed: the "own function"
  regex needs a `{` (else it matches the first prototype), and prototype lines
  must be excluded from the call regex.
- `tools/label_scalar_scan.py` (**doc 61**): m2c declares every address-only
  symbol `extern char lbl_X[]`, so a scalar read goes through a full `lis`+`addi`
  address materialisation that cannot be hoisted above an unrelated store.
  Declaring the real object type folds the address into the load displacement.
  **Reported honestly: 410 qualifying drafts → 35 same, 2 worse, 0 better.** It
  is a *diagnosis* for a scheduling-shaped residual, not a sweep.

**Self-inflicted bug found and repaired.** The body-splicing helpers in this
round's scripts copy a variant written by `split_body()`, which strips the
`#include "types.h"` line. The leaf scorer does not care (it injects its
own prelude) but the full build does — `fn_8018BED8` failed promotion with
`parameter names (without types) in function declaration`. 46 touched drafts
were repaired by re-inserting the include, and every promotion was re-run one at
a time to find the culprit (the batch wrapper reverts *all* registrations when
any single build fails). Same class of mistake as the earlier `apply_better.py`
regression: **anything that rewrites a draft body must preserve the include
block.**

Session total so far: **12 promotions** — `fn_80010C1C`, `fn_800A33E4`,
`fn_8004238C`, `fn_8005C944`, `fn_800685A4`, `fn_80242528`, `fn_80234FC0`,
`fn_800A3C50`, `fn_800F21E8`, `fn_8018BED8`, `fn_80126E28`, `fn_800A1AE8` — plus
**~110 drafts improved in place**, 5 new tools, and docs 59/60/61 with README
rows. The no-park pool is down from 1,763 to 1,751.

**One caveat worth carrying forward:** `tools/forwarded_test_scan.py` and
`tools/lead_arg_scan.py` score with a bare `tw.test_one`, while
`tools/score_addrs.py` also A/Bs an **FPR dummy-injection** body for functions
whose want prologue has an FPR frame. The two disagree for those addresses, and
one applied winner (`fn_80089368`) turned out to be 1.4 → 1.1 on the real
scorer instead of 1.4 → 1.6; it was reverted. Re-verify every applied winner
with `score_addrs.py` (`tools/psc4.sh`) before trusting the in-scan delta.

**2026-09-15 (l) — same levers, wider sweeps: 3 more EXACT + shared scorer fix**

Continued the doc-59/60 levers over the *whole* prefilter sets rather than the
narrow intersection.

**Fixed the scanners' scorer first.** `forwarded_test_scan.py`,
`lead_arg_scan.py` and `label_scalar_scan.py` all called `tw.test_one`
directly, which is *not* what `tools/score_addrs.py` reports: for functions
whose want prologue has an FPR frame, `score_addrs` also tries a
`volatile double` dummy-injected body and keeps the better of the two. New
`tools/scan_score.py` centralises the exact `score_addrs` logic and all three
scanners now use it — the in-scan deltas now reproduce on the real scorer
(the wide-sweep winners all verified, zero regressions). This is what produced
the earlier false `fn_80089368` "1.4 → 1.6" (real: 1.4 → 1.1, reverted).

Also extended `forwarded_test_scan.py` with the **preceding-call-result**
candidate class: when the statement immediately above a call is itself a call,
its expression (what retail leaves in r3) is offered as a leading argument.
That is the `fn_80126E28` / `fn_80242528` / `fn_800AAEA4` shape, which the
"call is the first statement of the `if` body" scoping could not see.

**3 more EXACT promotions:**

| fn | size | score | lever |
|---|---|---|---|
| `fn_800EDEB4` | — | 41.7 → 100 | doc 59; insertion slot 1 (not 0) |
| `fn_800A8288` | — | 47.6 → 100 | doc 59; the tested field is the **first** argument |
| `fn_801F93F8` | 80B | 85.0 → 100 | doc 59, second slot — both `fn_80057D90` calls take **two** arguments, the tested field first and the enclosing `arg1` second |

**18 more drafts improved** across the wider sweeps, best `fn_800A2A60`
46.5 → 59.1, `fn_8007E984` 42.3 → 51.9, `fn_800EF9C0` 40.0 → 47.5,
`fn_8004631C` 38.4 → 42.5, `fn_801A2CF8`/`fn_801A2D90` 37.5 → 41.0. All
re-verified against the pre-round baseline with `score_addrs.py`: **0
regressions**.

**Exhaustion reported.** The doc-59 sweep over all 501 `cmp0` prefilter hits
(329 beyond the first intersection) produced its two EXACTs in the first 60
addresses and **nothing** in the remaining 269 — the lever is done in this
pool. The doc-60 remainder is all hits-1 / score<60 drafts and yields only
single-digit-point gains.

**One stop-loss recorded** rather than left as a trap: `fn_800F45A4` (78.0%,
9 residual words) looks like the doc-60 `li r4,0` pattern at two sites, but the
prefilter's only candidate (`fn_80054C6C(arg0, 0)`) is **worse** (→ 40.5), and
retail's `li r4,0` in fact follows two *virtual calls* whose results stay in
r3. Nesting the vcall as the first argument instead collapses the whole
function (→ 16.7%). Its residual is a register-home/scheduling question, not an
argument defect — do not re-try the argument lever here.

Session total: **15 promotions** — the 12 above plus `fn_800EDEB4`,
`fn_800A8288`, `fn_801F93F8` — with ~130 drafts improved in place, 6 new tools
(5 scanners + the shared scorer), and docs 59/60/61 plus README rows.

**2026-09-15 (m) — pool hygiene: five classes of draft that no body edit can
move, and a corrected audit of the 47 "unmatchable" parks.**

A residual-ranked sweep keeps re-picking drafts that score 0.0 forever. The
cause is that the candidate pool is built with

    grep -L -iE '^//.*park' src/wip/*.c

i.e. a draft counts as "not parked" unless a leading `//` comment happens to
contain the literal substring `park`. Four other classes can never be moved by
editing a body and carry no such word:

| class | tell | drafts | why a body edit is useless |
|---|---|---|---|
| promoted | `src/fn_<addr>.c` exists | 0 | already matched |
| parked | `// ...park...` | 260 | human/agent decision |
| **stub** | `family=stub` | 14 | only the raw disassembly as comments, **no C statements** → compiles empty, 0.0 by construction |
| **untestable** | `Status: UNTESTABLE` | 38 | not a `report.json` boundary |
| **unlabeled** | `UNLABELED:` | 2 | no function symbol claims the region; `check_markers` blocks promotion |

3,348 wip drafts → **3,034 sweepable**.  New `tools/sweepable_pool.py`
(`--stats`, `--0x`) builds the pool with all five exclusions so the filter no
longer depends on the human having typed the right keyword.

**Corrected audit of the 47 files parked as "UNMATCHABLE ADDRESS".**  The first
pass asserted, for all 47, that the address is not a function boundary and that
the scorer therefore falls back to raw DOL bytes.  Re-checking each against
`report.json` splits it into five genuinely different reasons — the blanket
claim was wrong for nine of them and, for the five `.init` stubs, wrong in both
directions:

1. **38 are `Status: UNTESTABLE`** and the claim holds: e.g. `0x801238A8` is
   strictly inside `fn_80123864` (212B); `0x80124480`–`0x80124B6C` are all
   inside `fn_80124478` (1820B).  `_want_sizes().get(addr, len(got))` therefore
   scores them against a **slice of the neighbour** — they can even reach 100 %
   as a prefix of somebody else's function, while a promotion has no symbol to
   attach to.  Already labelled correctly before this round; the only bug was
   that "UNTESTABLE" contains no `park`, so they were still being swept.
2. **7 are `.init` stubs**, and they *are* `report.json` boundaries — the whole
   region below `TEXT_START` (`0x800034A0`) is one unit,
   `main/auto_00_80003100_init`.  The harness's offset math nonetheless reads
   the **right** bytes, because the DOL places `.init` immediately before
   `.text` and `t_off + (addr - t_addr)` resolves through it (verified:
   `gl.d[0x460:0x470] == 4e800020 4e800020 7c0000a6 60002000`, which *is* the
   `.init` code at `0x80003460`).  They are parked because they are
   `family=stub` — no C body — and because the spans are raw-asm blobs:
   `0x80003254` (108B) contains an interior `blr` and therefore merges two
   functions, `0x80003100`/`0x80003334` are early-init `lis r1`/`mfmsr`/`mtspr`
   sequences.  "these can never reach 100 %" is false for them; "no C function
   reproduces them" is the real reason.
3. **`0x80003464`** is genuinely **EXACT** (4B empty `blr` leaf) and is parked
   only because it has no registration path — the pre-existing
   *"4B empty fn below TEXT_START, not promotable"* note.
4. **`0x80003300`** is `family=m2c` with a real body, but the body is eight
   `mtspr 0x390..0x397,r3` writes; no SPR write is reachable from C in this
   toolchain, so the guessed `mtspr(...)` compiles to eight *calls*.  Only
   `__asm__` could close it, which is banned.
5. **`0x802572C4` / `0x8025D010`** are `UNLABELED` — no function symbol.  The
   first is **data**: its first word `0x3F3504F3` is the IEEE754 bit pattern of
   a float, not an instruction.  The second is an unclaimed 3940B runtime-lib
   region with 24 interior `blr`.

All 47 headers were rewritten with their own accurate reason (they now differ,
rather than sharing one wrong paragraph), and `fn_80173D30`'s real park note was
restored after a `family=m2c` mis-classification clobbered it.  Every one of the
68 touched files is **comment-only** — verified with
`git diff --unified=0 | grep -vE '^[+-]\s*(//|\*|/\*|$)'`, empty; the build is
unchanged and the DOL byte-identical.

**Cosmetic follow-on.**  A batch writer earlier in the session had emitted `%%`
for `%` in comment prose (a `%`-formatting artefact).  `grep -l '%%'` matched 23
drafts: **20** had it in comment lines (fixed) and **3** only inside `__asm__`
strings, where `%%r1` is the correct escape for a literal `%r1` — left alone so
the fix could never touch emitted code.

New doc: `docs/parkings/62-unsweepable-draft-classes.md` + README row 62.

**2026-09-15 (m) part 2 — the pool was 44 % too small: 3 promotions from
never-scored drafts.**

Finishing the pool audit led to a much bigger finding than the parking classes.
Every sweep up to today ran on a candidate pool of **1,748** addresses.  Rebuilt
from scratch (`tools/sweepable_pool.py`, 3,348 wip drafts -> **3,034 sweepable**),
minus the 1,748 already known, there are **1,338 sweepable drafts that had never
been scored at all** — not FAILs, not oversized, simply never in any pool.  The
old pool was not a filtered superset; it was missing 44 % of the corpus.

Scoring all 1,338 with `tools/score_addrs.py` (16-way parallel, ~10 min):

| status | count |
|---|---|
| EXACT | 3 |
| NEAR | 479 |
| DIFF | 853 |
| FAIL | 3 |

The NEAR tail is *better* than the old pool's best: `0x801CE65C` 99.0,
`0x801A71DC` 99.0, `0x80167E04` 98.9, `0x801575E0` 98.9, `0x8020CAA4` 98.7,
`0x801903B8` 98.6, `0x801025D0` 98.6, `0x801BE820` 98.5, `0x801410E0` 98.2,
`0x800F6610` 98.1, `0x80254764` 98.0, `0x80173910` 98.0, `0x802241F0` 97.9.

**That invalidates this session's earlier "exhausted" verdicts.**  Docs 56, 59
and 60 were each closed as done-in-this-pool; those verdicts were measured
against the incomplete pool, so they were never about the corpus.  The first
re-run proves it: see below.

**3 promotions (DOL `cmp`-verified byte-identical), all from the doc-56
prototype lever over just the 1,338 new addresses** (136 drafts improved):

| fn | size | score | prototype |
|---|---|---|---|
| `fn_80118104` | 128B | 63.6 -> **100** | `void fn_801286D0(void *, void *, void *, void *)` |
| `fn_800E448C` | 204B | 56.6 -> **100** | `void fn_80064494(void *, void *, void *, void *)` |
| `fn_800DF5B4` | 180B | 43.8 -> **100** | `void fn_801286D0(void *, void *, void *, void *)` |

All three had been sitting there with a stale `// PARKED (/20)` note —
*"instruction scheduling, register allocation, or lis+ori vs lis+addi addressing
differs"* — that describes m2c's generic boilerplate and had nothing to do with
the actual one-word defect (an undeclared callee's `crclr cr1eq`).  Best
partials from the new set: `fn_800DC804` 61.5->76.0, `fn_800F0EF0` 57.9->78.4,
`fn_8011348C` 55.2->89.3, `fn_80103280` 51.2->95.0, `fn_800DFB64` 43.8->84.8,
`fn_8020630C` 40.4->91.8.

The other two EXACTs in the new set are known blockers, not wins:
`0x8001DFF4` (doc-51 reloc-target divergence) and `0x801D2C58` (doc-50 linker
REL14 relaxation); `0x801B5A54` is the parked SN-asm `bdnz $` case.

**Hand-attacked near-misses (all resisted, parked/documented, no `__asm__` added):**

- `fn_801CE65C` (99.0 %, 1 word, `-mps-float`) — want keeps the pinned `r11`
  base for the 6th of 8 PS pair stores (`psq_st f0, 0x28(r11)` = `arg0+0x48`)
  while ngccc rematerialises the `arg0` anchor (`0x48(r31)`).  Four more variants
  this round — swap the two `b20[4]`/`b20[5]` stores, advance `b20` by 0x8 before
  the 6th store, `volatile b20`, sink the 6th store to the end of the run — all
  land on 99.0476 or 96.1905.  The prior note's ~10 failed spellings plus these
  14 exhaust the source-level space; the park note ("allocator CSE coin",
  next idea: one walked pointer for both addresses) stands.
- `fn_80042DE8` (93.75 %, 2 words) — the `arg0->unk0x1A8 = obj` / `obj->unk0x4B8
  = arg0->unk0xC8` pair is emitted in the opposite order.  All 6 statement orders
  of the `g`-load/A/B/call block plus 8 flag combos: best is 93.75 (the current
  order) — **the swap that matches the object order is *worse* (54.5) because the
  allocator hoists the `g` load out from between them**.  Genuine store-order
  wall (doc-15 adjacent-instruction class).
- `fn_802209C4` (94.8 %) and `fn_80161420` (94.9 %) are the same class: three and
  one swapped pairs of independent address-materialisations.
- `fn_801A71DC` (99.0 %) — two `li r3,12` / `mr r30,r22` order swaps.

**Rule recorded for future rounds:** build the pool with `tools/sweepable_pool.py`,
print `--stats`, and write the pool size into the sweep note.  An incomplete pool
is indistinguishable from an exhausted lever.

Docs: doc-56 addendum (lever not exhausted; the 3 promotions), doc-62 addendum
(the pool was 44 % too small + the second worklist), README row 62 updated.

**2026-09-15 (n) — sweeping the 1,338 never-scored drafts: 40 more improved, and
the doc-58 lever is genuinely done.**

Re-ran this session's three argument-lever sweeps over the 1,338 addresses that
the old pool never contained (docs 56/59/60; doc 58 was already re-run for the
prototype one).  Every winner was re-verified with `tools/score_addrs.py` — an
independent scorer in a fresh process — before being kept.

| lever | candidates | drafts improved | EXACT |
|---|---|---|---|
| doc-59 forwarded-test (`cmp0_home_scan` -> `forwarded_test_scan`) | 407 of 1,335 | **29** | 0 |
| doc-60 leading passthrough (`slot_low_scan` -> `lead_arg_scan`) | 105 of 1,335 | **12** | 0 |
| doc-58 label-as-call-arg (`label_call_arg_scan`) | 13 dup-extern drafts | 0 | 0 |

Best doc-59 gains: `fn_802394F8` 83.3 -> 87.5, `fn_80131E50` 70.0 -> 75.0,
`fn_800E2A18`/`fn_800E2A70`/`fn_800E2AC8` 34.8 -> **72.7** (a three-member
`fn_80069C58` family), `fn_8022BD5C` 38.3 -> 66.0, `fn_800E28F8`/`2958`/`29B8`
40.0 -> 56.0.  Best doc-60 gains: `fn_80116840` 43.2 -> 51.4, `fn_80206554`
31.2 -> 50.0, `fn_800D68B8` 14.5 -> 34.4, `fn_801147F8` 7.6 -> 18.1.

**doc-58 is finished in the current corpus**, and this time against the *whole*
pool.  The 13 drafts that still carry the duplicate-`extern` tell use the label
as a *value* or as an integer *offset* (`(char *)var_r6 + (s32)lbl_803C9BF8`,
`(void *)lbl_80364CC8`) rather than as a call argument, so the scanner correctly
finds nothing.  The offset form is a genuinely different (and new) shape, left
as a lead, not a wall: 58 no-park drafts match `+ (s32)lbl_X`, but the best of
them (`fn_80073880` 87.4 %) diverges structurally for unrelated reasons and the
rest are all < 80 %.

**The 97–99 % NEAR tail of the new pool is the doc-15 adjacent-instruction
family, and it is already walled.**  Hand-checked the top of the new list:

- `fn_80167E04` 98.9 % — the last word is `cmplw r30,r0` vs `cmplw r29,r0`, i.e.
  retail's loop guard compares in r30 where ngccc folds to r29.  Four *new*
  variants: swap the `i`/`best` pins (89.5), move `best = 0;` past the
  `fn_801286D0` call (96.8), drop the `+r` barrier on `best` (96.8, the barrier is
  load-bearing), add a barrier on `i` (98.9, no change).  Current form is best —
  recorded as a stop-loss.
- `fn_801903B8` 98.6 % — `[lis r4 hash-hi]` vs `[lwz r3 field]` swap; its note
  already records cond-first reordering, named-temp staging, `+r` on t29 and
  both `-fno-schedule-insns*` as worse.
- `fn_801575E0` 98.9 % (wall), `fn_8020CAA4` 98.7 % (ps_diff park),
  `fn_801025D0` 98.6 % (the `fn_801CE65C` PS store-base class), `fn_801BE820`
  98.5 % (`{B..C}`-range-vs-default switch compare tree, wall).

**Process bug found and fixed: a sweep winner can lose its `// FLAG:` line on
re-apply.**  `gen_leaves.draft_flags` scans the first 120 lines, and m2c-shaped
drafts carry the flag *inside* the body — after the includes, immediately above
the function.  The first apply pass kept "everything before the first
`#include`" and silently dropped it, so `fn_800E2A70` measured 34.8 -> 72.7 in
the sweep but 34.8 -> 17.4 after re-apply; three wins were wrongly reverted
before the cause was found.  All 12 are now applied with the flag intact.
New tool **`tools/apply_scan_winner.py`** splices a scanner's winner with
(a) *all* original comment lines kept and (b) an A/B gate that refuses anything
not strictly better — plus a `WARN` if the flag set changes across the splice.

Build unchanged and the DOL byte-identical; the new pool is 3,031 sweepable.

**2026-09-16 (o) — two more EXACT promotions (672B) + two reusable source-shape
levers: the shared-`else` control-flow tell, and the "one reload = one colour"
rule.**

1. **fn_8008076C (384B) — the doc-15 `sub` colouring was NOT regalloc: the tell
   is a PEELED first iteration.** Was parked at 94.79 % (masked-EXACT) with want
   colouring ALL FOUR reloads of `node->unk0x14` as r11 while the draft got
   r6 / r11 / r11 / r9.  Two independent fixes were needed:
   * **shared-`else` tell:** the draft used nested ifs; retail has BOTH `beq`s
     (outer +2c and inner +40) targeting the SAME 0x80080830 (the else body), so
     the source is ONE `if (a != 0 && (b & 0x10)) { ... } else { ... }` with
     short-circuit `&&` — the inner test's false path IS the outer else.  The
     masked word score hides this; `tools/promote_wip.py`'s internal-branch-
     target check catches it (`REFUSE ... internal branch target(s) differ`).
     Generalise: **two conditional branches in want pointing at the same block
     mean short-circuit `&&`/`||`, not nested ifs.**
   * **one reload = one colour:** the draft respelled `*((void **)&node->unk0x14)`
     inline inside each expression -> four independent pseudos -> four colours.
     Retail RE-ASSIGNS one variable before each use (`sub = *((void **)&node->
     unk0x14);` as plain statements, and as the do-block's LAST statement so the
     trailing `while` test reads the same variable) -> one pseudo -> one colour
     = want's r11.  The tell is the peeled first iteration: want +68 reuses the
     header's r11 with NO reload, which only happens when the header check and
     the body reads are the same variable.  Bonus: with this shape the old
     `__asm__("" : "+r"(n))` barrier became unnecessary and was removed (still
     EXACT); only the pre-existing `register ... __asm__("rN")` pins remain.
2. **fn_80174DB8 (288B) — four more doc-56 missing prototypes.** Was parked at
   74.3 %; `tools/proto_undeclared_scan.py` had stopped after fn_8012701C, but
   fn_80126EAC, fn_8012705C, ScriptCleanup (a REGISTERED symbol at 0x801517BC,
   already matched in src/fn_801517BC.c) and fn_80199490 were still undeclared —
   four `crclr cr1eq` words.  Arg counts read straight off want: fn_80126EAC and
   fn_8012705C are both called with NO args (`bl` with no preceding `li r3`/`mr
   r3` — for fn_8012705C the previous call's result is still in r3), so declare
   them `(void)`.  Lesson: that scanner stops at the first class its heuristic
   ranks, so re-scan the pool after each promotion wave, not once.

3. **fn_800A3528 (172B) — the `mr` that regalloc cannot give you, and the
duplicated-guard tell.** Was parked at 67.4 % (168B, one word short) on a
doubly-linked-list unlink walker.  Two coupled fixes:
   * **loop form:** the m2c `loop_6: if (v != NULL) { ...; goto loop_6; }` shape
     makes ngccc DUPLICATE the guard — an inline `cmpwi r31,0` right after the
     preheader *and* the rotated one at the bottom.  A plain
     `while (v != NULL) { ... }` makes both preheader paths jump straight to the
     single rotated guard at the bottom, which is want's layout.  (Tell: two
     `cmpwi` guards on the same variable in want.)
   * **keep the copy:** want is `lwz r9,0x3c(r3) / lwz r0,4(r9) / mr r31,r9 /
     cmpwi r0,-1`.  With `p = arg0->unk0x3C; v = p;` ngccc coalesces the copy
     away (loads straight into r31).  Hoisting the FIELD READ into its own local
     BEFORE the copy — `p = arg0->unk0x3C; t = p->unk0x4; v = p; if (t == -1)
     v = NULL;` — keeps r9 live across the copy, so want's `mr r31,r9` survives.
     **A live-range extension, not a register pin.**  Both levers are needed:
     the `if/else` preheader scores 90.7 % and while(1)+goto only 9.3 %.

Flag families re-confirmed inert (39 sets over 7 families; no change for
fn_80112A94).  Also re-confirmed: **fn_80112A94 (96.8 %) stays parked** — its
3-word residual is a pure call-arg GPR/FPR interleave (`lwz r7,0x18(r1)` hoisted
above `lfs f1/f2` in want); four fresh source shapes (copied-int local, copied
f32 locals, comma assignment, ternary read) all score identically, so the
re-assignment lever above does not reach it.  **fn_8007A9F8** was re-attempted
and stays parked at 70.3 %, but all four of its defects are now pinned in its
header (u8 config bytes at 0x6/0x7 vs the u16 struct field, the fn_80009A78 +
memset missing prototypes, the `->unk0x118` struct-padding read that must be the
RAW 0x118, and the three-distinct-locals register shape for the four
`arg0->unk0xC` reloads).

DOL byte-identical (`ff6faeb0…`) after both promotions; both promoted files were
then cleaned to warning-free builds by retyping the *prototypes* (s32), not by
casting at the call sites.

**2026-09-16 (p) — doc-56 is NOT exhausted: an all-at-once prototype rescan finds
64 wins and 1 more promotion (fn_8018D684, 312B).**

fn_80174DB8's promotion showed `tools/proto_undeclared_scan.py` stops early, and
the reason is structural: it adds ONE prototype per round, requires a strict
improvement each round, and gives up when a round finds none.  When a draft
carries SEVERAL undeclared callees the first prototype alone still leaves the
other `crclr cr1eq` words shifting the tail, so no single addition helps and the
scan reports nothing — the fix only exists for the whole SET at once.

New tool **`tools/protoscale.py`** (parallel, 16 workers): prefilter the pool by
compiling each draft and looking for a real `crclr`/`crset` in the object; then
for every draft that has one, splice prototypes for ALL undeclared callees at
once (signature from the callee's own `src/<name>.c` definition when it exists,
otherwise arity from the call site) immediately ABOVE the function DEFINITION —
splicing at the top of the file fails, because the structs.h types are not in
scope yet — and keep only strict improvements.  Also note: a "declaration" must be
matched as a line-anchored statement (`^[ \t]*(extern )?ret name(args);`), NOT as
`\bname\s*\(...\)\s*;`, which also matches `x = fn_FOO();` and marks every
callee as already declared (that bug made the first run report 0 wins of 330).

Result over the 1,697 unparked drafts: **963 compile with a `crclr`** — the class
is far bigger than the ~70 previously touched — and **64 improve**:

| address | before | after |
|---|---|---|

Applied with `tools/apply_scan_winner.py --note "doc-56 rescan..."` and every
applied address re-scored in a fresh process.  DOL byte-identical.

**The second promotion came from the same rescan but a different lever.**
`fn_8007671C` (92B) sat at 91.3 % with exactly two wrong words — `mr r30,r5` vs
`mr r30,r3` and `li r4,0xa` vs `li r3,0xa` — and both are SEMANTIC, read straight
off the register traffic:

* `li r4, 0xa` immediately after `bl fn_80009A44` means the allocator's RETURN
  VALUE is the first argument of the very next call: the two statements are ONE
  nested expression `fn_8007DE80(fn_80009A44(0x290), 0xA)`.  (`fn_80009A44`'s own
  promoted body is declared `void` because its callers ignore r3, but its value is
  just `fn_8000F10C`'s return passed through — so it really returns a pointer; the
  draft must declare `void *fn_80009A44(s32);`.)  Written as two statements the
  arg lands in r3 and the callee's second parameter is lost, which is exactly the
  two-word diff.
* `mr r30, r5` at entry => the value stored into the new object is the THIRD
  parameter, not the second (`s32 a0, s32 a1, s32 a2`), a mistake m2c makes
  whenever a prologue `mr` names a high argument register.


**Consequence for the remaining ~899 crclr drafts:** their `crclr` is what retail
itself has (an unprototyped varargs call at that site), so no prototype may be
added — that residue is a *true* negative, not a tool gap.  Do not re-run this
class again without a new lever.
| fn_80285050 | 0x80285050 | stub |

## 2026-09-16 — 4 promoted, 2 improved, 3 tool bugs

Random no-park sweep continued into a toolchain audit. **DOL byte-identical
`ff6faeb0…`** after every promotion.

**Promoted:**
- `fn_801A34EC` (76B) — the `if (p != NULL) { … return …; } return 1;` spelling;
  the draft's early-return form emitted the `li r3,1` block last instead of
  first, which shifts every following word.
- `fn_8021F990` (184B) — `switch`: `case 0: case 1:` must SHARE one body and
  `default:` must be empty/omitted (`default: break;` is wrong), and the case
  bodies are emitted in **source declaration order**, `{0,1}, 9, 5, 2`;
  ascending order caps at 69.6%. New doc `parkings/solved/63`.
- `fn_8002AEF4` (188B) — the vtable method at `unk0x14` really takes
  `(void *, f32, f32, s32)`: **integer last**. ~15 previously-failed source
  shapes were chasing a scheduling coin that did not exist. Addendum to
  `parkings/15`.
- `fn_800E3520` (124B) — **stale park, already solved**: it only matches WITH
  its own `// FLAG: -fno-schedule-insns2`. Found by a flags-aware re-score of
  the whole wip corpus (3,328 drafts → 14 EXACT, of which this was the only
  promotable one; the rest are the doc-50/doc-51 blockers and the `0x8028D4xx`
  empty-`blr` false positives).
- `fn_801BE820` (1084B) — switch **compare-tree pivots**: retail listed
  `case 9:`/`case 10:` falling through into the `default:` body, so the
  expanded key set was 8 keys `{5..12}` instead of 6. Documented as the second
  form of doc 63.

**Improved parks:** `fn_8010B7EC` 94.8 → **97.4%** (same arg-class-order defect
at `fn_8010B920`: pointer must be LAST); `fn_8005BD04` 81.0 → **83.3%**
(`clr` declared `u8[4]` made GCC fold the alpha literal `-0x80` to `+0x80` —
same stored byte, different encoding; `s8 clr[4]` restores `li r0,-0x80`).

**Tool bugs fixed (each had produced a confident wrong conclusion):**
1. `tools/score_body.py` + any `gen_leaves.compile_fn` caller compile to
   `$LEAF_TMPDIR/<addr>.o`, keyed by ADDRESS only — parallel workers on the
   SAME address report each other's scores. A six-variant sweep showed 97.4%
   for a body that really scores 62.3%. `score_body.py` now defaults
   `LEAF_TMPDIR` per-PID. **Parallel over many addresses = safe; parallel over
   many variants of one address = not.**
2. `score_body.py` / `diff_near.py` ignored the draft's `// FLAG:` line
   (`pool_score.py`, `stmt_perm_search.py`, `ps_diff.py` already honoured it).
   `fn_800E3520` reads 87.1% vs its real 100%; `fn_80124110` does not compile
   at all under default flags. Both now read the header and take an override.
3. `diff_near.py` fed each region to `md.disasm` in ONE call, and capstone's
   generator STOPS at the first undecodable word — paired-single code is
   exactly that. `fn_801DA420` (172 words) printed `25/25 match (100.0%)`; it
   is 163/172. It now decodes word-by-word with a `.word` fallback, uses the
   registered want size from `report.json`, and prints `# flags:` / `# size:`.

**New tool:** `tools/reorder_scan.py` — flags drafts whose residual is a pure
reorder of the same words (relocation-masked, branch targets folded). 126
corpus-wide; it is what surfaced both arg-class-order cases. A companion sweep
over switch drafts that adds missing `case N:` arms before `default:`
(`casegap`, 30 drafts ≥ 75%) found only `fn_801BE820`.

## 2026-09-16 — 3 promoted, 2 parked, 1 tool bug, 6 drafts improved

**Both promotions DOL-verified byte-identical**, and neither came from the
sweep's EXACT set: a full 12-way masked sweep of all 3,325 wip drafts returned
13 EXACT, and that set is *entirely* the known non-promotable population (see
item 3). The two promotions were a masked-EXACT draft whose control flow was
wrong (caught by `br_targets`) and a scanner find.

1. `fn_801136AC` (128B, ScriptAddSoundBanks) — **the masked-EXACT trap again.**
   The draft scored 100% under the reloc masks but its forward `b` at
   `0x801136E4` targeted `0x80113704` instead of retail's `0x80113708`:
   `promote_wip.py`'s `br_targets` gate caught it (this is exactly why that gate
   exists). Root cause: the escaped-slot reload must be the **last statement of
   the loop body** and the `bottom:` guard must read it back through the
   register local. Written inline (`var_r31 < ((Unk *)sp8)->unk4`) the reload
   lands AT `bottom:`, so both entries into the guard run it and GCC rotates
   the loop by one word.
2. `fn_80173B98` (120B) — **SOLVED via the same new recipe** (two nested-call
   sites; both callees promoted, so arities came from `src/fn_<addr>.c`).
   Detail in the follow-up section below.
3. `fn_800EFDC0` (76B) — **SOLVED via a new recipe**, see doc 60 addendum (o):
   the two calls are NESTED (`fn_800F10F0(fn_80009A44(0x18), 8)`); reading them
   as separate statements leaves the 8 one register low (`li r3,8` vs want's
   `li r4,8`) *and* injects a `crclr cr1eq` for the undeclared callee. Found by
   `tools/reorder_scan.py`. Store order (`0x8` before `0xC`) was the second
   half. `src/fn_80009A44.c` was retyped to return the struct it allocates
   (byte-identical, re-scored EXACT) so the passthrough is legal C.
4. The sweep's 13 EXACT drafts are all *deliberately* not promotable — recorded
   here so the next session does not re-chase them:
   `0x80003464` below `TEXT_START`; `0x8001DFF4` link-level blocker;
   `0x8028D494`/`0x8028D498` (OdemuExi2 DBClose/DBOpen) and
   `0x8028DF14/18/1C/24/2C/34/38` (the OdemuExi2 debug vtable) are already
   covered by registered lib units, so promoting them as `src/fn_*.c`
   overlaps an existing split — the promotion tool refuses and reverts.

**Tool bug: `tools/sweepable_pool.py` missed block-comment park notes.**
Its park test was `^//.*park`, but a large share of the corpus writes the park
note as a `/* … */` block at the END of the file (`fn_8000A0A8`). Those drafts
were classified *sweepable* and re-entered every residual-ranked sweep, where
they were re-picked and re-analysed from scratch. `PARK_RE` now also matches
`/*` and ` *` continuation lines; 8 drafts moved sweepable -> parked
(1,633 -> 1,625).

**`fn_80112A94` (376B, ScriptLoadSound) PARKED 96.8%** — three words, all one
`lwz r7`/`lfs f1`/`lfs f2` interleave in the final call's arg setup. 20 further
shapes (staged s32/u32/cast/pointer temps, all-eight-args staged in want's
emission order, f32 temps in both orders, decl-order moves, volatile sp18 —
note a MID-BLOCK declaration is a C90 error and scores FAIL, so staging temps
must live in the declaration block) plus a 10-flag matrix: no lever moves it.
Genuine doc-15 `expand_call` arg-class coin (same wall as `fn_80156CB0`).

**Follow-up (same session): the nested-call recipe generalised — 1 more promotion.**
`fn_80173B98` (120B) was **SOLVED 56.7 -> 100 and promoted** with TWO
instances of the same defect (`fn_8009FDD8(fn_8017471C(...), QB_TRICK)` and
`fn_801EF978(fn_8009FDD8(temp_r30, QB_SKATERENDRUN), 0)`): the draft read each
call as an independent statement, so each argument block sat one register slot
low. Both callees were already promoted, so the real arities came straight out
of `src/fn_<addr>.c`. `fn_802359A4` yielded two more instances of the same
recipe (`fn_80129068(fn_80128F94(), 0xEA6, 1)`,
`fn_801F50B0(fn_801F672C(), QB_LOAD_SK5ED, temp_r30)`) plus a pointer-scaling
defect (`var_r30 += 4` on an `s32 *` is `+0x10`, retail is `var_r30++`) and a
loop-rotation defect; it stays parked at its honest 45.2% for a register-home
residual. See doc 60 addendum (o).

**NEW HAZARD: compensating errors inflate scores.** `fn_802359A4`'s recorded
56.45% was a spurious `crclr cr1eq` (+1 word, missing prototype) cancelling a
missing `mr r0,r3` (-1 word), so every later word aligned by accident. Fixing
only the prototype drops it to 27.4%. **Rule: when a draft has a known missing
prototype, fix that first and re-measure before trusting its score.**

**Scanner re-runs over the corrected 1,625-draft no-park pool** (8-way):
`proto_undeclared_scan.py` 7 hits -> 3 drafts improved (`fn_8022B214`
30.0 -> 65.8, `fn_8018C080` 10.1 -> 10.3, `fn_800427AC` 12.8 -> 13.8);
`frame_only_scan.py` 0 hits; `reorder_scan.py` 19 hits, of which exactly one
(`fn_800EFDC0`) carried the `crclr` tell and it is now promoted. A dedicated
crclr census over the whole pool (`got` has a `crclr cr1eq` want does not)
returns **0 drafts** — the doc-56 class is drained for this pool.

**2026-09-17 — random no-park sweep: 10 EXACT promotions (DOL byte-identical
`ff6faeb0…`; all verified through promote_wip.py) + 0 new parks.**
Pool: the 1,587-draft sweepable set (`tools/sweepable_pool.py`, no park note);
scored whole-pool in 16 parallel slices, then worked near-misses plus a
`shuf` random draw. Promoted: **fn_8007B9DC** (96B), **fn_8001B7F4** (68B),
**fn_8005BD04** (168B), **fn_8021FA48** (108B), **fn_800163A0** (168B),
**fn_800F1F74** (156B), **fn_8007E984** (100B), **fn_80057298** (156B),
**fn_801372B8** (132B), **fn_8022B524** (172B).
New reusable recipes:
- **missing-prototype → `crset cr1eq`** (fn_8007B9DC): an undeclared callee
  that takes an f32 makes ngccc mark the call varargs and emit an extra
  `crset cr1eq` (size +4). Declaring `s32 fn_80094858(f32)` removes it. The
  mirror of the doc-56 `crclr` tell — scan for the SET variant too.
- **m2c arg-inversion + phantom fnptr self-arg** (fn_8001B7F4): m2c emitted
  `temp(0xA, arg1, arg2, arg3, temp)` for want's `temp(arg1, 0xA, arg2,
  arg3, arg4)`, so the callee also has a 4th param. The `crclr cr1eq` in
  want means the fn-ptr cast must be OLD-STYLE `s32 (*p)();`.
- **struct-forced stack-slot order** (fn_8005BD04): when want's frame packs
  `[sp8][outs[3]][clr]` but ngccc assigns the slots out of declaration order
  (6 declaration permutations all 83.3%), put the order-sensitive pair in ONE
  local struct (`struct { s32 sp8; s32 outs[3]; } S;`) and keep the third
  object a separate array. The struct fixes the aggregate order; the array
  staying an array keeps want's `addi r9,r1,off` + indexed `stb k(r9)`
  addressing. Trap: `S.sp8 = *(clr)` derefs to s8 (one byte) — keep the
  `*(s32 *)clr` spelling.
- **global deref hoist before unrelated stores** (fn_8021FA48): both
  data-symbol derefs must be assigned to locals BEFORE the field stores; the
  inline-at-call form lets ngccc sink the load and reuse the base register
  (same idiom as the promoted caller src/fn_80013CAC.c).
- **two phantom call args** (fn_8007E984): `fn_80093F48(v, arg0, 3)` is really
  `(v, 3)` and `fn_8005EF24(arg0, arg1, arg1)` is `(arg0, arg1)` — dropping
  both is byte-exact. The doc-59/60 "forwarded/missing arg" notes had chased
  the opposite direction.
- **per-record s16 dispatch offset + clean while** (fn_80057298): the vtable
  record's offset at +0x8 is `s16` (want `lha`, shared struct says s32 →
  `lwz`); a plain `while ((item = fn(...)) != 0)` reproduces want's rotated
  layout that the m2c goto form did not.
- **`sprintf` misnamed as a helper** (fn_800F1F74): 0x80269F4C is SDK
  `sprintf` (symbols.txt scope:global); a `fn_80269F4C` prototype links as an
  undefined symbol. Full redraft (m2c had read a byte index as a word index)
  + `-fno-schedule-insns2` for the `addi r4` / `mr r3` call-site order.
- **doc-34 lever A (bound as a named local)** cracked TWO parks in this sweep
  before they were written up as new walls: fn_801372B8 (`s32 lim = 0x3E8` —
  SIGNED `cmpwi K; bge` also folds) and fn_8022B524 (`u32 lim = 0x1388U`).
  Both promoted; doc 34 updated with the signed + zero-trip-guard flavors.
  **Sweep cue:** a draft whose only residue is `cmpwi/cmplwi K-1` + inverted
  branch, or `cmpwi 0,0` where WANT has `cmpw rX,r0`, is a doc-34 member.

**2026-09-17 (b) — stale `// FLAG:` headers can *cause* the miss; 2 twins promoted**

- `fn_800F12F4` + `fn_801A9B1C` (156B each) — exact twins: identical body, only
  the per-iteration callee differs (`fn_800F10AC` / `fn_801A9A5C`), both doing
  the same `1 << arg0->unk0x0` outer loop over 0xC-byte chunk slots, each slot
  draining a singly-linked list (`fn_80012224`) then releasing the slot.
  Both EXACT now — **no FLAG line at all**.
- **Reusable finding (worth checking before any redraft):** the draft carried
  `// FLAG: -fno-schedule-insns` from an earlier automated sweep. That flag is
  *worse than useless here* — the identical body scores **33%** with it and
  **100%** without. A stale `FLAG:`/`extra_cflags:` header silently downgrades
  every score `test_wip_drafts.py` and `promote_wip.py` compute for that draft,
  so a draft parked "NEAR at 51%" may actually be an exact match. When a draft
  is close, **try it with the FLAG line deleted before rewriting the body.**
- The two body fixes that mattered once the flag was gone:
  1. the callees were undeclared, so every `bl` got a spurious `crclr cr1eq`
     (`fn_80012224(0, var_r30)` needs a prototype: the 2nd arg is a pointer,
     not an int);
  2. the draft's explicit `if (temp_r27 > 0U)` guard around the outer loop made
     ngccc fold the shift into a record form — `slw. rX, r0, r9` + `beq`
     instead of want's plain `slw` + `cmplw r11, r27` + `bge`. Dropping the
     guard and writing a plain `while (i < lim)` restores want's guard exactly.
  (Note this is the *opposite* of doc 34: there the fix is to make the bound a
  named local to *block* a fold; here the fold had to be removed by deleting an
  explicit `> 0` test that the original source never had.)
- `promote_wip.py` takes addresses as **argv**, not stdin
  (`tools/venv/bin/python tools/promote_wip.py 800F12F4 801A9B1C`). Piping them
  in silently falls back to the full EXACT list and dies on stale entries.

**2026-09-17 (c) — 9 PROMOTED. Two new reusable levers: store-run rotation, empty-arg-block calls**

Started from the 27 no-park NEAR drafts (of 617 NEAR, 590 already carry park notes).
`--slice` x8 in parallel on `test_wip_drafts.py` is the cheap way to rebuild that
list; filter with `grep -qiE park` + `grep -q __asm__` to drop the parked/asm ones.

**A whole 156B family (8 members) promoted** — `fn_800F12F4`, `fn_801A9B1C`,
`fn_801727BC`, `fn_8000E508`, `fn_80057870`, `fn_8006FF0C`, `fn_800A6670`,
`fn_800A6CB8`. Identical body: `1 << arg0->unk0x0` outer loop over 0xC-byte chunk
slots, each slot draining a singly-linked list (`fn_80012224`) then releasing it;
per-member callee differs (`fn_800F10AC`, `fn_801A9A5C`, `fn_801726FC`, ...).
Find them with `grep -l 'fn_80012224' src/wip/*.c` + `size=156B`. All eight were
held back by the **same two defects**:
  1. a **stale `// FLAG: -fno-schedule-insns`** (see doc 55) — body unchanged,
     27.5% with the flag, **100% without**;
  2. the callees were undeclared (spurious `crclr cr1eq` before every `bl`) and
     the draft carried an explicit `if (temp_r27 > 0U)` guard that ngccc folded
     into a record-form `slw.`+`beq` instead of want's plain `slw`+`cmplw`+`bge`.
  ⇒ **NEW LEVER (store-run rotation)** `fn_800F3598` 50→**100**: see the doc-09
  addendum. When the residual is only a permutation inside a run of stores to one
  base, ngccc emits the run **rotated right by one**; write it **rotated left by
  one**. No flag reproduces it (12-flag sweep on that draft), and `volatile` is
  the *wrong* tool (it pins source order = the wrong order).  Two independent runs
  in one function, both obeyed it (73.33 → 80/83 single-run → **100**).
  ⇒ **NEW LEVER (empty arg block)** `fn_800F3598` same draft: a `bl` whose whole
  argument block is *absent* means the wrapper takes the caller's own parameters
  and forwards them — `fn_800F3598(arg0, arg1)` calling `fn_800F3684(arg0, arg1)`.
  m2c had 1 arg and the wrong one. See the doc-60 addendum. 50% → 73.33% from the
  arity fix alone; neither the 120B length check nor the score can see this.

**Other sessions' levers re-used (all cheap, all worth trying first):**
  * doc 56 (`missing prototype`) — the `crclr cr1eq` tell, 8 of the 8 family.
  * doc 34 (`bound as a named local`) — closed `fn_801372B8` + `fn_8022B524`
    earlier in this sweep (see entry (a) above).
  * doc 53 (`field width retype`) — `fn_8001517C`: `unk0x30` is `s16` not `s32`
    (want `lha`), and `unk0x3C` is a **same-shape self-referential vtable
    pointer**. Local view typedef `VT_1517C`, 63.3 → 66.67%, still parked on a
    one-word `mr r3, r0` copy ngccc always coalesces (6 shapes tried; its
    fully-typed form scores *lower*, 26.67%, only because the missing word shifts
    the offsets — trust the diff, not the %).

**Traps hit this session, worth avoiding:**
  * `promote_wip.py` takes addresses as **argv**. Piping them to stdin silently
    runs the *whole* `EXACT` list and dies on stale entries.
  * `test_wip_drafts.main()` **strips** any line mentioning `dolphin/types.h`
    before compiling, so hand-built bodies for `test_one()` must not carry that
    include or the score is meaningless (I measured 25.6% vs the real 51.3%).
  * the pool-wide "declared flags vs none" A/B (814 flagged drafts, parallel
    `/tmp/dual.py`) found only **2** marginal cases, neither EXACT ⇒ doc 55's
    stale-flag class is now essentially drained; the family above was the live
    instance. Do not re-run that sweep expecting wins.

**2026-09-17 (d) — 3 PROMOTED + 1 park rescued (92.4%); a dangerous orphan-file landmine**

Promoted byte-identical: `fn_8000B0BC` (140B), `fn_8000B148` (244B), `fn_8022E258`
(228B). `fn_8004F6B8` (420B) lifted **64.81% -> 92.38%** and parked with the wall
decoded (frame 8B short + one arg-setup swap).

* `fn_8000B0BC` had `stricmp` — **not a linkable symbol in this build**. The MSL
  name is `strcasecmp` (0x8026B04C). The masked scorer cannot see this (the call
  displacement is relocation-masked), so check every *external* callee against
  `config/G2TE52/symbols.txt` before a bulk promote; the failure only shows up as
  `undefined: '...'` from the linker.
* `fn_8022E258` = doc 56 (three undeclared callees -> two `crclr cr1eq`) plus a
  nested-ternary guard rewritten as the plain `v = 1; if (!(x)) v = 0; if (v)`
  flag idiom. 49.1% -> 100%. Also: two of its callees are promoted with
  *incomplete* prototypes (`fn_8022DD54` as 1-arg though want passes 3,
  `fn_80240C80` returning `void` though want reads r3) — the call sites are right,
  the neighbour definitions are short.
* `fn_8004F6B8` stacked **three** levers: doc 56 (`fn_8009DFC0` undeclared, and
  its block_20 call was missing its first argument) -> 90.48; doc 09's store-run
  rotation -> 92.38; doc 55 (delete the now-regressing
  `-fno-expensive-optimizations`) -> the flag alone was *38 points* worse.

### LANDMINE: `src/fn_8001DFF4.c` — a masked-EXACT that must never be promoted
This is the sharpest false-positive class found so far, and it is **self-inflicting**:
  * the draft is `PARKED` and scores **100.0%** under the masked compare;
  * `promote_wip`'s *per-function* check therefore PASSES and it **writes**
    `src/fn_8001DFF4.c`;
  * only the batch's final whole-DOL `cmp` catches it (32 bytes, first at vaddr
    `0x8001E150`) — its own header explains the cause: the neighbouring
    dispatch-table `lis/addi` targets come out **reordered**, and a function
    pointer is a **relocation**, so the mask hides it completely;
  * the revert path **unregisters the file but leaves it on disk**, and
    `add_gen_leaves.py` re-registers *every* `src/fn_*.c` with a range marker —
    so the next unrelated promote silently re-adds it and fails with a diff that
    looks like it belongs to the *new* draft. That is exactly how it was hit
    today (it looked like `fn_8022E258` was breaking 0x8001E153).
  Fix used: `rm src/fn_8001DFF4.c`, then re-promote; the draft's header now
  records the trap.
  **Rule: never build the promote list from a masked-EXACT scan alone.** Filter
  the candidates for a park keyword first (`grep -qiE park`), and if a batch
  fails the DOL check, `git status src/fn_*.c` for orphans left by the revert
  before blaming the newest draft.

**2026-09-17 — random-batch sweep (no-park-note drafts): 5 EXACT promotions
(all DOL byte-identical `ff6faeb0…`) + 4 parks with notes.**
Promoted: **fn_8004CE30** (116B), **fn_800EB4E0** (104B, PS), **fn_8006F3F4**
(184B), **fn_8000702C** (100B, PS), **fn_80084458→fn_80184458** (208B).
New reusable recipes (all verified by the promote path):
* **matched-sibling first.** Before decoding a draft, grep the whole `src/`
  for its callees/siblings — a promoted neighbour gives the exact callee
  ARITY and often the whole idiom. This solved four of the five above:
  `fn_80012224` is `(s32, void *)` (2 args, from fn_8000E508/fn_8000E9F4 —
  m2c had dropped the second, which also removed want's `li r3,0; bl` shape),
  `fn_801A275C` is `(Unk_31DE137E *, s32)` (from its own promoted body),
  `fn_8018B4C0`/`fn_80184168` and the `sp8`/`for(...; sp8++)` iterator idiom
  come from fn_80184C50, and the whole PS vector family
  (fn_800063B4 + `__ps_t` copies) from fn_8000702C/fn_80006350/fn_80006F6C.
* **m2c's bare `0;` statements are paired-single ops.** `fn_800EB4E0` and
  `fn_8000702C` both had two/four `0;` lines where want has psq_l/psq_st:
  spell them as `((__ps_t *)dst)[k] = ((__ps_t *)src)[k];`. And a plain
  `__ps_t + __ps_t` IS the game's `ps_add` under -mps-float (fn_800BDE4C
  style) — no builtins/asm needed (fn_80006FA8). Naming `__ps_t` anywhere in
  the body also auto-applies -mps-float.
* **jump-threading blocker (NEW tool-visible failure mode).** fn_8004CE30:
  `if (sp8.a != 0) A(); if (sp8.a != 0) B();` compiles BYTE-EXACT yet ngccc
  threads the first `beq` PAST the second test (its destination re-tests the
  same value) -> promote_wip refuses with "internal branch target(s) differ".
  Fix: read the first condition into a local (`v = sp8.a; if (v != 0) ...`)
  and keep reading `sp8.a` for the second test. Rule of thumb: a masked
  byte-exact draft can still hide a control-flow difference; always fix the
  branch diff before assuming the score is real.
* **two-load key spelling** (fn_8006F3F4): reading `*arg1` twice (once for the
  bucket index, once in the loop compare) instead of caching it in a `key`
  local is what makes ngccc split the live range and emit want's extra
  `mr r11,r0`. Caching it silently loses one word and shifts everything.
  Same draft: a source-level `next = node->unk0x8;` BEFORE the field test
  (not an inline use in the taken arm) reproduces want's early load, and the
  else-arm stores are again counter-intuitive order (`unk0x0` first emits
  want's `stw 4(r4)` then `stw 0(r4)`).
* **char* local vs struct-typed global** (fn_80121CD0): for a global state
  block, access the EARLY part through `char *p = lbl;` (a named local base —
  the raw `*(s32 *)(lbl + 0x2C0)` form makes ngccc CSE a bogus base), but
  spell the TAIL members as a struct-typed global so ngccc REMATERIALIZES the
  symbol into a fresh register (want's second `lis/addi`) instead of reusing
  the live base. 45.5% -> 86.4%.
Parks (best body + note in each file): **fn_80036328** 11.1% (0x20-stride
scan; residual is a pure {count,base} home swap — the count in want lives in
r0 for the guard and is copied to r8 for the loop compare, which no spelling
reached), **fn_80121CD0** 86.4% (two scheduling coins: the two `li rX,0`
order and one tail store rotation), **fn_801A33BC** 54.8% (callee arities
fixed from siblings; residual is the loop's MATERIALIZED `&&` — want sets
`p = NULL` on the field-test failure and re-tests, which ngccc only emits for
an explicit-assignment source shape whose block order then differs),
**fn_80006FA8** 36.4% (PS vector accumulate; prologue/frame/params/return
all exact, residual is the interleaving of the two copies with the two adds —
with the allocation coupling documented in the draft).

**2026-09-17 (later) — random no-park sweep: 5 more EXACT
promotions (all DOL byte-identical) + 2 parks.**
Promoted: **fn_8000728C** (124B, first try), **fn_8003E77C** (80B,
`ScriptCombineFaceTextureWithOverlay`), **fn_800A9C70** (80B, bool),
**fn_80011D7C** (100B), **fn_80012170** (104B).
New reusable recipes (each verified by the promote path):
* **`xor` + `subfic` + `adde` spells as `(x ^ M) == 0`** (fn_800A9C70,
  and already in src/fn_801F1428.c).  This is the one case where the C is the
  *opposite* of what the arithmetic looks like: the sequence computes
  `x != 0`, but the spelling that makes ngccc emit it instead of
  `cmpw`+branch+`li` is `== 0`.  Plain `!= 0` (or a bare `<var> != <const>`)
  drops the whole tail to a branch — check the `subfic/adde` family first.
* **a DEAD read of a global array forces the array base into a callee-saved
  register** (fn_80012170).  want had `stmw r28` + the table base hoisted into
  r30 ABOVE three `bl`s; the one-statement store form made ngccc rematerialise
  the base into a volatile r9 AFTER the calls and save only r29..r31 (34.6%).
  Reading the current entry into the `dst` variable the store then reuses
  (`dst = tbl[arg0]; ... dst = ctor(...); tbl[arg0] = dst;`) makes the
  base+index address live across the calls — ngccc keeps it in r30 and the
  dead read itself is DCE'd, so codegen is byte-identical either way.
  Same draft: the table is `s32 *lbl_802FFF08[]` (byte-scaled addressing keeps
  want's un-shifted `stwx`), and `fn_80011F94` takes FOUR args
  `(void *, s32, s32, s32)` per src/fn_80126064.c.
* **call-site arity is set by the callee's body, not by the register count**
  (fn_8003E77C, fn_800A9C70).  want leaving r3 untouched before a `bl` means
  the caller's own arg0 IS that argument (pass-through signature).  And when a
  callee only USES r3/r4, a caller that still has r5..r8 loaded is passing
  leftovers, not arguments: fn_800503C8's m2c 6-arg `fn_80050428(arg2, r6, r7,
  r8, arg1, r10)` was really the 2-arg `fn_80050428(arg0, arg2)` whose r6/r7/r8
  are just the block copy's live values.
* **`ScriptCombine*`/QB-script family signatures come from siblings**
  (fn_8003E77C): `s32 ScriptCombineFaceTextureWithOverlay(Unk_2EF06E12 *arg0)`
  is exactly src/fn_80162E54.c's `ScriptCombineTextures` shape — same include
  set, same `extern s32 lbl_80366474`, same 4-arg `fn_801286D0`,
  `fn_8005CF80(lbl_80366474, sp8)` with no cast.
Parks (best body + note in each file): **fn_800503C8** 33.3% (0x18-byte param
block copy + `fn_80050428(arg0, arg2)`; right size/anchor/store order and the
same instruction multiset, residual is two ngccc allocation decisions — the
arg0/arg1 r9/r11 naming swap and the load-batch-vs-interleave; explicit load
temps, `u32 *src`, mixed anchor and -fno-schedule-insns[2]/-O1/-O3 all tried),
**fn_80097478** 85.3% (sp8/spC stack-slot numbering: an 18-variant declaration
order × type sweep AND an array/struct-union body were added on top of the
note below — ngccc's slot order is usage-driven, confirmed not reachable).

**2026-09-17 — 7 more EXACT promotions (all DOL byte-identical) +
1 tool fix.**
Promoted: **fn_800F3708** (56B vcall thunk), **fn_8009FE78** (60B vcall thunk),
**fn_8009E3D0** (56B), **fn_800421D4** (76B recursive flag walk),
**fn_8001737C** (80B), **fn_8009E408** (56B), **fn_8009E440** (52B).
* **vcall thunk family (fn_800F3708 / fn_8009FE78).**  The canonical spelling is
  the one tools/gen_vcall_fns.py emits and src/fn_800575DC.c uses:
  `void **t = *(void ***)((char *)o + V); fp = (void (*)(...))t[W/4];
   fp((char *)o + (signed short)((s16 *)t)[H/2], ...);` — the entry is
  {s16 self-offset at H, fn pointer at W} and the offset MUST be loaded with
  `lha`, so spell the field access as `(signed short)((s16 *)t)[H/2]`, never as
  a struct member.  m2c's recurring error in this family is passing the loaded
  function POINTER as the call's last argument; want leaves every register it
  does not set untouched, which is how you read the real arity.
* **QB-reader wrapper family (0x8009E3D0 / 0x8009E408 / 0x8009E440).**  One
  shape, three callees: guard `arg0->unk0x24 != NULL`, load into r0, `li r3, 0`
  for the fall-through, `mr r3, r0` before the bl.  The callee's OWN prototype
  (src/) fixes the call: fn_80128228 and fn_801286D0 take
  `(Unk_2EF06E12 *, s32, s32 *, s32)` -> `(node, arg1, arg2, 0)`; fn_801289E4
  takes only `(Unk_2EF06E12 *, s32)` -> `(node, arg1)` and no r6 setup.
  Writing the guard as `var = 0; if (...) var = call(); return var;` costs the
  tail (26.7%) — the early-return form is what reproduces `li r3,0` before the
  `cmpwi`.
* **two `if (...) return 1;` statements are NOT equal to one `||`**
  (fn_800421D4): two separate ifs make ngccc merge the two `li r3,1` sites and
  invert the first branch (25.0%); the single
  `if ((f & M) || (p && fn(p)))` reproduces want's block order exactly.  Also:
  m2c recursed on the MASKED value instead of on `arg0->unk0x58`.
* **matrix local + wrapper prototypes** (fn_8001737C): a 0x30-byte stack local
  initialised by the `PSMTXIdentity` wrapper fn_8001D320 must be declared
  `f32 sp8[12]` — that sizes the 0x40 frame AND makes the `addi r3,r1,8`
  argument legal (src/fn_8001D320.c declares it `(void)`, which would emit NO
  argument at all).  Same draft: want had a single `lwz r4,0xa8(r31)`, so read
  the field once and reuse it for both the test and the first call.
* **TOOL FIX (tools/br_targets.py): the internal-branch check was asymmetric.**
  `want_targets()` skips `bl` ("skip calls and indirect branches; keep
  conditionals") but `got_targets()` kept every REL24/REL14 whose target lands
  in the function — so a SELF-RECURSIVE call resolves to the function's own
  base on the got side only, and promote_wip refused an otherwise perfect draft
  (`REFUSE 0x800421D4: 1 internal branch target(s) differ ... 0x800421f8 want
  None got ('bl', 2147754452)`).  Fixed by skipping the reloc when
  `tgt == base`; calls to addresses strictly inside the function are still
  compared.  Lesson for future batches: a refusal whose "want" side is `None`
  is usually the checker, not the draft — verify with
  `tools/br_targets.py 0xADDR` plus `tools/want_dis.py` before redrafting.
* **batch-hygiene note (hit again):** a promote batch that DIES mid-list
  (SystemExit from a refusal) leaves the already-written `src/fn_*.c` files on
  disk with their WIP drafts intact.  The next promote re-registers them via
  `add_gen_leaves.py` (that is why the DOL stayed identical), but the stale
  drafts + `WIP.md` rows must be removed by hand — `rm src/wip/fn_*.c` for every
  address that now has a `src/fn_*.c`, then drop its WIP.md row.

**2026-09-17 — 4 more EXACT promotions + 1 park.**
Promoted: **fn_8003E5AC** (76B `ScriptSetFaceMassageTextureOverlay`),
**fn_800EF690** (168B).  Parks: **fn_801907E0** (62.5%, corrected call, note).
* **m2c slides a literal argument out of the MIDDLE of a 4-arg call.**  This is
the single most productive fix in these batches — three separate drafts
(fn_800EF690, fn_8003E5AC, fn_800421D4) had a 3-arg `fn_801286D0(arg0, &slot,
N)` where the truth is `fn_801286D0(arg0, 0, &slot, N)`: the out-pointer sits in
r5 (not r4) and r4 is either the literal 0 or this function's own pass-through
arg1.  Read the *register numbers* in want (`addi r5,r1,8` = out-pointer 3rd,
`li r4,0` = literal 2nd, `li r6,N` = flag 4th) before trusting m2c's arg list;
the project's own `tools/late_literal_slot_scan.py` documents the same trap.
* **a 0/1 select tail needs BOTH constant arms spelled out.**  fn_800EF690:
`var_r3 = 0; if (c) var_r3 = 1; return var_r3;` makes the variable live across
the callee and forces `stmw r30` + `li r30,0` before the `bl` + `mr r3,r30`
(83.3%).  Writing `if (c) { var = 1; } else { var = 0; }` instead makes ngccc
if-convert it to want's `cmpwi r3,0; li r3,0; beq; li r3,1` with the variable
in r3 and only r31 saved.  (A 0/1 tail is the one shape where the *else* arm
matters more than the then arm.)
* **`Script*` function names come from symbols.txt.**  `ScriptSetFaceMassageTextureOverlay`
  is the literal symbol at 0x8003E5AC; grep `config/G2TE52/symbols.txt` for the
  address before naming a promoted file's function `fn_XXXXXXXX`.

**2026-09-17 — 6 EXACT promotions + 3 parks (deep-dive batch).**
Promoted: **fn_801994A0** (164B), **fn_8023D6FC** (132B), **fn_800EF9C0**
(156B), **fn_80123864** (212B).  Parks with corrected decodes: **fn_80078864**
(94.7%), **fn_80182B88** (note), **fn_800450B4** (note).
* **`(u16)` on a 32-bit field is NOT a 16-bit field — it compiles to `lhz` at
  field+2 in big-endian.**  fn_80123864's last two words came from this: want
  had `lhz r4, 4(r11)`, and the draft's `u16 t = arg0->unk0x4;` (field s32)
  emits `lhz r4, 6(r11)` — the *low half* of the word.  A one-line probe
  settles it instantly:
  `u16 f(T *a) { return a->unk0x4; }` -> `a0630006` for a s32 field,
  `a0630004` for a real `u16 unk0x4;` field.  When want's load displacement
  equals the *field's own* offset, the field is genuinely narrow and the fix is
  a local typedef with the narrow field (never a cast of the s32 field).
* **An untouched parameter register is not an argument.**  Corollary of the
  arity rule: fn_80123864's indirect call `lbl_8039BE8C(arg0->unk0x0)` passes
  ONE arg; r4 still holds arg1 simply because that path never overwrote it.
  Declaring the pointer `(s32, s32)` and passing arg1 costs an extra
  `mr r4, r5` (the whole 1-word residual).  Before adding an argument for a
  register want leaves alone, check whether the register is just the incoming
  parameter.
* **`sp8p = &sp8;` (a pointer local read after an indirect call) is what pins a
  stack address into r30.**  fn_80123864: passing `&sp8` directly makes ngccc
  rematerialise `addi r4, r1, 8` after the call and the frame collapses to
  -0x10; the pointer local keeps it in r30 and yields want's
  `stmw r30, 0x10(r1)` / -0x18 frame.  Same shape as fn_800450B4's missing
  `mr r0, r4` — both are allocator answers to "does this value survive a call".
* **One base + displacements beats two folded addresses.**  When want shows
  `lis r9` / `addi r9, lo(sym)` / `lwz rX, off1(r9)` / `lwz rY, off2(r9)`, the
  global must be typed as ONE object carrying both fields: `*(s32 *)(sym+off)`
  per field lets ngccc fold each address separately and the `addi` disappears.
  fn_80123864 uses a local `Mgr` typedef exactly like the promoted
  src/fn_80121518.c does (its own `S121518`).
* **fn_801994A0 (QB/stream close) — the tested value is the argument.**
  `fn_801309EC` is `(Unk_15EF4A35 *)`, not `void(void)`: the guard's load then
  lands in r3 (not the compare-only r0) and the whole function falls out.  The
  other half: `arg0->unk0x4` must be loaded into a temp BEFORE the
  `arg0->unk0x8 = 0` store (`lwz r3` / `li r0,0` / `stw r0,8(r31)`), i.e. keep
  the direct `if (arg0->unk0x4 != 0)` form and let the store sink; hoisting it
  into a local forces `mr r3, r9` and costs 65 points.
* **fn_800EF9C0 — the sprintf buffer sizes the frame.**  `char sp8[32]`, not a
  bare `s32`: want's frame is -0x40 with the save block at 0x2c (five regs) and
  the buffer at r1+8.  A 4-byte local gives -0x28 and shifts everything.  Also
  `fn_800F2EDC` is a SIX-arg call (`li r7,0` + `li r8,0`) and `fn_800F2F90`
  must run BEFORE it (m2c had read `temp_r31` before assigning it).
* **fn_800450B4 — unsigned conversions drop the xoris.**  want has no
  `xoris r3, r3, 0x8000` and its rodata constant at 0x80292640 is plain
  0x4330000000000000 (read straight out of the DOL), so `fn_8005C5BC` /
  `fn_8005C5F0` return u32 and the (f64) idiom is the unsigned one.  Keeping
  the s32 prototypes adds two words; with u32 the body is ONE word short and
  every other region matches.  That last word is want's `mr r0, r4` before the
  0x190 store: the store is scheduled after the global load and the value
  survives in a fresh scratch register.  Not reproducible from C yet.
* **fn_80078864** parks at 94.7%: the 5-arg `fn_80078274(unk0x18, 0, unk0x10,
  1<<unk0x6, 1<<unk0x7)`, the `stb` at 0x9, the `lha` vtable offset at 0x58
  (use `Unk_07FDFB02`, which already has `s16 unk0x58` + `s32 unk0x5C`) and the
  u16 `unk0xA` are all verified; only the order of the two head loads
  (`lwz r3, 0x18(r9)` then `lwz r5, 0x10(r9)`) will not come out.
* **DOL data reads**: `main.dol` sections are 1.0/1.1/1.2 at 0x00..0x1C and
  2.0..2.10 at 0x1C..0x48 (addresses 0x48..0x74, sizes 0x90..0xDC); reading a
  float/double constant straight out of the file is the fastest way to decide
  which conversion idiom a function uses.

**2026-09-17 — fn_800AB604 58.1% -> 91.5%: an undeclared callee DESYNCS the whole function**

`fn_800AB604` (520B, the flagship "stuck near-miss" of this family) is now at
91.5% with a body whose *semantics* are complete.  The single biggest fix was
not in the body at all:

* **A callee with no declaration compiles as an UNPROTOTYPED call, and the
  extra `crclr cr1eq` shifts every instruction after the call by one word.**
  Here `fn_80131008(...)` (5 constant args) was undeclared, so ngccc emitted
  `lis r3 / li r6 / li r7 / ori r3 / li r4 / li r5 / crclr cr1eq / bl` where
  want has `lis r3 / li r4 / li r6 / li r7 / ori r3 / li r5 / bl`.  Declaring
  the real prototype (`void fn_80131008(s32, s32, s32, s32, s32);` — lifted
  from src/fn_8002BB14.c) took **70.2 -> 88.5 in one editable line**.
  Diagnostic signature of this trap: the pvdis/want-vs-got diff stops being
  local — after some offset *every* line is DIFF even though the instructions
  look related ('OK' lines reappear by accident).  Look for a `crclr cr1eq` in
  the GOT side where want has none, and for the `bl` that follows it: the
  function called there is missing a prototype (or is declared old-style
  `s32 f();`, which is the same thing — a *`f()`* declaration is only correct
  when want itself shows the `crclr`).  This is the same root cause as the
  fn_800F12F4/fn_801A9B1C entry above, but here it cost ~20 words, so treat a
  desynced tail as "prototype bug" before touching any types.
* **Loop guards must keep the COUNTER on the left.**  For a rotated
  `do{}while` inside a guard, write
  `if (var_r30 < (s32) arg0->unk0x2C58) { do { ... var_r30 += 1; } while
  (var_r30 < (s32) arg0->unk0x2C58); }`.  want's guard is `cmpw r30, r0` +
  `bge`; the natural `if ((s32) arg0->unk0x2C58 > 0) { do ... }` lets ngccc
  fold the guard to `cmpwi r0, 0` + `ble` and the two words are unreachable.
  (A plain `while`/`for` spelling instead of if+do-while restructures the loop
  entirely and drops the function to ~37% — do not "clean up" this idiom.)
* **Size an unknown local buffer from the frame.**  want's `stwu r1,-0x128` +
  `stmw r25, 0x10c(r1)` says: 0x10C - 0x4 (area ends at 0x10C) and 7 saved GPRs
  = 0x1C at 0x10C..0x128.  So locals = 0x10C - 0x8 = 0x104 → the function's
  only local is a ~0x100-byte buffer at r1+8, i.e. `char sp8[0x100]`.  The
  draft's `s32 sp8` gave a -0x30 frame: wrong prologue, wrong epilogue, and the
  sprintf send was off by a whole frame.  Same lesson as the fn_800EF9C0 entry
  above; here the constant that proves it is the *sum* (0x100 + 0x1C + 8 = 0x128).
* **Recover call arguments from the DOL, not from m2c.**  `fn_8011BE68` is
  `void fn_8011BE68(void)` (src/fn_8011BE68.c) so m2c's `fn_8011BE68(arg0)`
  added a spurious `mr r3, r29`; `fn_8012701C` is 2-arg and want passes the
  *loaded* `0x34D4` field in r3 (`li r4, 3`), i.e.
  `fn_8012701C((Unk_2EF06E12 *) arg0->unk0x34D4, 3)`; and the `sprintf` here is
  `sprintf(sp8, (s32) lbl_8029854C, arg0->unk0x34BC)` with 0x8029854C = `"%08x.qb"`
  (DOL read), whose *return* feeds `fn_8012EC50(fn_8000A778(sp8))` — a call whose
  r3 is the previous call's result has no other reading.
* **Residual (11/130 words) is emission order only:** the two loop preheaders
  (`li r28,0` / `lis r26`+`li r27,0` come *before* the pointer `addi` in want,
  after it in ours), the `fn_80131008` constant-arg order (4/6/7/3/5 vs
  6/7/3/4/5) and the sprintf `addi r4` vs `addi r3,r1,8` order.  Exhausted:
  flag matrix (-fno-schedule-insns2, -fno-gcse, -fno-delayed-branch, -O1/-O3,
  -fno-sched-*, -fno-reorder-blocks), pointer init before the guard, the zero
  as a named variable, 3-arg block-1 call, variadic and prototyped `sprintf`
  declarations, and `void *`/`u32` parameter types for `fn_80131008`.

**Promoted in this batch:** `fn_8012EE64` (260B) — 95.4% -> EXACT.
The last 3 wrong words were a *sinking* mirror of the fn_8009DFC0 case: want
computes the node address ABOVE the NULL test
(`lwz r3,0xbc(r31)` / `addi r4,r31,0xbc` / `cmpwi r3,0` / `beq`), which only
comes out if BOTH the loaded value and the node address are materialised into
locals before the guard:
```c
temp_r3 = arg0->unk0xBC;
temp_r4 = (Unk_2EF06E12 *) &arg0->unk0xBC;
if ((s32) temp_r3 != 0) { fn_8009DFC0(temp_r3, temp_r4); arg0->unk0xBC = 0; }
```
Writing `&arg0->unk0xBC` inline in the if-body (or taking only the value into a
temp) makes ngccc sink the `addi` below the `beq` — invisible to the
masked-word scorer until the very end, since only the *order* of the two
address-materialisation insns around the branch changes.

**2026-09-17 (second session): the "undeclared callee" sweep — 5 promotions**

The single highest-yield move of this session was not a new codegen insight but
a *filter*. `crclr cr1eq` in the `got` column of a diff is the fingerprint of an
unprototyped call: ngccc emits one extra word, everything after it shifts by 4
bytes, and a draft that is otherwise complete reads 40-50%. Four of the five
matches below came straight off that list (`cluster_scan` over the unparked
pool, sorted by the word immediately after the first mismatch).

* **`crclr cr1eq` == "a callee has no prototype".**  An undeclared callee is
  assumed `int f()`; the record-clear is emitted when an argument or the result
  needs a conversion the compiler cannot prove is unnecessary.  Declare every
  callee with a real prototype and re-score *before* rewriting any body logic:
  `fn_8007DEBC` 41.7 -> 100%, `fn_8011A888` 44.8 -> 51.7 (then 100% on the
  frame fix), `fn_8006C610` 48.6 -> 54.5 (then 100% on the value temp),
  `fn_801A6C4C` 43.8 -> 46.9 (then 100% on byte-based indexing).
* **An indirect call through a function-pointer *variable* must DEREFERENCE the
  array**: `(*(void (**)(s32, s32))lbl_80300284)(0x40, temp_r30)` loads the word
  and emits `mtlr`/`blrl`.  Casting the bare array name to a function pointer
  (`(void (*)(s32,s32))lbl_80300284`) is a *direct* call and emits `bl`
  (21.9%).  Also: the call's arity comes from what want actually sets in
  r3/r4/... — the leftover r5/r6 here are the OR'd shift results, not arguments
  (4-arg reading: 17.6%; 2-arg: 100%).  (`fn_8001FB2C`)
* **`lwzx` operand order is source-shape, not noise.**  `s32 *base` + element
  index emits `lwzx rD, rIdx, rBase` (index in the RA field); want's
  `lwzx rD, rBase, rIdx` is what a `char *base` with an explicit **byte** offset
  produces (`char *pa = (char *)arg0 + 4; idx = var_r30 << 5;
  *(s32 *)(pa + idx)`).  Semantically identical, 12.5% of the words different —
  the last gap on `fn_801A6C4C` (87.5 -> 100%).  Related: the m2c draft's
  `*((s32 *)arg0 + 0x2A4 + temp)` scales the offset by 4; these four loads are
  byte-addressed with bases at +4/+8/+0x2A4/+0x2A8 and a shared `i<<5` index.
* **A value temp before a call, when want stages through r0.**  want loads the
  global into r0 and then `mr r3, r0`; passing the dereference inline puts the
  load straight in r3.  `temp = *(s32 *)lbl_80301434; f(temp, &sp8);`
  (54.5 -> 100%, `fn_8006C610`).
* **A float clamp written `<=` can be the exact match.**  want's
  `fcmpu cr0,f31,f0 / cror cr0un,cr0eq,cr0lt / bns skip / fmr f31,f0` is the
  codegen for `if (f31 <= lbl) f31 = lbl;` (a MIN).  The `<` mirror emits a
  single `bge` — one word shorter, which shifts the entire tail and reads as a
  mysterious 51.7% missing one word.  Whenever a diff shows `cror`+`bns` on the
  want side and a bare `bge`/`blt` on ours, test all four relational mirrors.
  (`fn_8011A888`)
* **`report.json` can be 4 bytes short of the real symbol.**  `promote_wip.py`
  failed with "`split ... .text (0x8007DEBC..0x8007DF10) ends within symbol
  'fn_8007DEBC' (0x8007DEBC..0x8007DF14)`" for an otherwise byte-exact body:
  the report size was 84B, the symbol is 88B.  Widen the draft header's
  `range=0x...-0x... size=...B` marker to the symbol end and re-promote.

**Promoted this batch (each verified `DOL BYTE-IDENTICAL`):**
`fn_8007DEBC` (88B), `fn_8011A888` (116B), `fn_8001FB2C` (128B),
`fn_8006C610` (132B), `fn_801A6C4C` (128B).

**Parked with a better body:** `fn_801A26E0` (120B) 41.9 -> 77.4%.  The loop
shape is settled (`while (1) { node-test; if (NULL) return NULL; ... }` so the
node test is shared at the loop bottom, `if (var_r4-- == 0) return var_r3;` for
the countdown).  Residual 6/32 words: want compares the OLD r4
(`cmpwi r4,0 / addi r4,r4,-1 / beq`) while `var_r4-- == 0` makes ngccc preserve
it in r0 (`mr r0,r4`), and want keeps the walker node in r9 rather than
coalescing it with the r3 result.  Exhausted: pre/post-decrement, decrement
after the load, decrement in the condition, a `temp_cr0_eq` boolean local,
m2c's goto form, the duplicated-node-test spelling.

**2026-09-18 — random-pick session (8 no-park drafts): 2 EXACT promotions
(DOL byte-identical `ff6faeb0…`) + 2 parks with real bodies + 4 assessed/parked.**
Promoted (via `tools/promote_wip.py`, both `DOL BYTE-IDENTICAL`):
`fn_80044088` (136B) and `fn_8009C778` (124B).

New reusable recipe — **switch-tree pivot shaping** (`fn_8009C778`, 19.4 → 100%):
a switch's decision-tree pivot is chosen from the *case value set*, so an m2c
draft that drops a case rewrites the whole dispatch. Two levers:
1. **Give the switch every case the tree needs, even when its body folds to
   `default`.** `switch (x) { case 1: …; case 2: break; }` collapses the empty
   case and pivots LOW (`cmpwi x,1; bne default`), but
   `switch (x) { case 1: …; case 2: v = 0; break; case 3: v = 0; break; }`
   keeps three live nodes and pivots on 2 — want's
   `cmpwi x,2; beq exit; bgt exit; cmpwi x,1; bne exit`.
2. **Match the argument's signedness to want's range test.** WANT's
   `cmplwi x,2; ble default` (the empty-left-subtree low-bound check) only
   appears for an **unsigned** switch expression; the signed form emits a bare
   `ble` and picks the middle case as pivot instead. `fn_8009C778` needs
   `(s32 arg0, u32 arg1)` — the two switches in one function differ in
   signedness, so read each range test's opcode (`cmpw…`/`cmplw…`) separately.

Also promoted from the same shape family: `fn_80044088` (7.0 → 100%) needed
three stacked decode fixes, all semantic: (a) a per-record local typedef with
**f32** members at 0x17C/0x1B4 (the shared `Unk_E80761A5` types them s32, so m2c's
`(s32)arg0->unk0x17C` became an *integer* conversion and ngccc synthesized the
integer→double bias path instead of want's `fctiwz`); (b) the m2c 3-arg call
`fn_800586CC(0x80292508, &sp8, &spC)` is really 4-arg and its FIRST argument is
the **return value of the preceding call** — want never writes r3 between the two
`bl`s (`fn_800586CC(fn_80053790(arg1), lbl_80292508, &sp8, &spC)`), confirmed by
the sibling callers `fn_80042924`/`fn_80042F44`/`fn_80044960`; (c) doc-51: the
string must be the registered `lbl_80292508`, not a raw literal (which emits
lis+ori and misses one word).

Parked with a genuinely better body:
- **`fn_8006A67C`** (116B) 17.2 → **65.5%**, size- and frame-exact. New walker
  flavor: want memory-homes both walkers in the 8(r1)/0x10(r1) slots instead of
  registers. Solved half = the frame/slot shape (`void *volatile` — the volatile
  must qualify the POINTER, or a 4-slot local array used at indices 0 and 2 to
  reserve the 16-byte local area); residual = one colour swap of the reloaded
  head (`p` in r9/r0 vs r11), identical in the sibling `fn_8006A5F0` (now 94.3% — its own park note in the draft has the full lever ladder).
  Full write-up in `docs/parkings/32-walker-role-rotation.md` §2026-09-18
  (Flavor C).
- **`fn_80024A40`** (132B) 9.1 → 27.3% via a from-disasm PS redraft (the m2c body
  was five bare `0;` lines — it could not decode the paired-single ops). All five
  op-4 words are now decoded (ps_mr/ps_muls0×2/ps_sub×2 → a `blk[4]` pose build
  + two calls). Gotcha recorded in the draft: `__builtin_ps_*` **ICEs at
  expr.c:2802** when the first operand is a struct MEMBER — copy `__ps_t` members
  into locals first. Residual = FPR schedule + one missing `ps_mr` copy.

Assessed + parked (no better body found; current m2c draft kept, notes added):
`fn_8004BB2C` (404B, m2c-corrupt: one bare `0;` + `if (0)` CFG bail → compiles to
32/101 words), `fn_8004C458` (532B, wholesale callee-saved divergence; want keeps
arg1 in volatile r12 and builds the `arg0+0x5dc` base before the counters),
`fn_8024402C` (480B, frame 8 bytes short + a spurious `crclr cr1eq` from the
speculative 5-arg `fn_80240B0C` call), `fn_8026FF40` (564B, fdlibm tanh(f64);
re-measured 20.6%, not the 25.5% its stale header claims — body drifted; still
carries three inherited `__asm__` blocks that should be dropped before any
retry; no MSL fdlibm source exists under `libs/`, so it cannot be wired as a
library TU).

**2026-09-18 (b) — continued random picks: 1 EXACT promotion (DOL byte-identical)
+ fn_80019B90 56.7 → 92.5%.**
Promoted via `tools/promote_wip.py` (`DOL BYTE-IDENTICAL`): **`fn_8018E8C8`**
(352B, 61.4 → 100%) — three stacked type defects in one m2c draft, all fixed by
*changing the view type instead of casting*:
1. the vcall object at `arg0->unk0x14` was viewed as `Unk_FFAD6788`, which types
   0x98 as `s32`, so ngccc emitted `lwz` where want has `lha`. `Unk_89391A04`
   already declares `s16 unk0x98` + `s32 (*unk0x9C)(void *)` — the exact vtable
   shape — and needs no cast on the member;
2. m2c had hoisted the indirect call above `temp_r9 = arg0->unk0x14;`, so the
   draft read `temp_r9` before assignment;
3. the float leg was `*(s32 *)((s32 *)ptr + 0x18C)` — 0x18C scaled by 4, i.e.
   byte offset 0x630 — where want is `lfs f0, 0x18c(r3)`. The *immediately
   preceding promoted function* `fn_8018E868` (0x8018E868-0x8018E8C8) already
   carries the right view (`typedef struct { char pad0x0[0x18C]; f32 unk0x18C; }
   Unk_Sk8;`) plus the `fn_8009FDD8`/`fn_801745B4`/`lbl_80305EAC` declarations;
   reusing a neighbour's declarations is the cheapest first move on any draft.
   The `(s32)` on that f32 is what produces want's `fctiwz` + `stfd` pair.

Parked 56.7 → 92.5% (5/67 words): **`fn_80019B90`** (`ScriptNgc_Set50hz`), body
kept, no flags. Three real defects fixed — the local at r1+8 is a 0x110-byte
object (`char sp8[0x110]`, frame 0x28 → 0x130), `var_r31 = 0;` must sit *after*
the two global stores (else the compiler reuses the known-zero r31 for
`lbl_8037B794 = 0` and the init run loses a word), and **`fn_80096588` is a
genuine 3-arg function** (0x800965CC reads r5; the draft's 2-arg prototype was
dropping `li r5,0`) — that arity alone is +35.8 points. Residual is the
allocator's argument-materialisation order at two call sites (`li r3,0`
first vs last, and one r4/r5 swap) — same doc-15 arg-setup gap; unaffected by
literal casts, a live zero local, K&R prototypes, or a full flag matrix.

**2026-09-18 (c) — 4 more EXACT promotions (all `DOL BYTE-IDENTICAL`) + 1 park
raised to 92.5%. Two new reusable levers.**
Promoted: `fn_800A64F0` (152B, 50.0 → 100%), `fn_801262A0` (112B, 48.3 → 100%),
`fn_80126230` (112B, 43.3 → 100%), plus `fn_8018E8C8` from the entry above.

**LEVER — the callee's RETURN TYPE decides the caller's argument-setup order.**
`fn_800A64F0` sat at 92.1% on a single misplaced word: want `… ori r4 / li r6,1 /
mr r3,r31 / bl` but the draft produced `… ori r4 / mr r3,r31 / li r6,1 / bl`.
The only change needed was `void fn_801286D0(...)` → `s32 fn_801286D0(...)`
(the promoted `src/fn_8002E1CC.c` already had the real `s32`). A call that may
return a value has different RTL from a void one, so the scheduler places the
arg copies differently. Same lever, +3.4 points on `fn_8009FB7C` (43.3 → 46.7).
`tools/protoscale.py` cannot see this: it only splices prototypes for callees
that have **no** declaration, so a callee declared with a *wrong* signature is
invisible to it. New tool **`tools/protomismatch.py`** (list-of-drafts [nproc])
rewrites every draft declaration that disagrees with the real signature in
`src/<name>.c` / `libs/<name>.c`, all-at-once and one-at-a-time. Yield is low but
it is real: 2/150 sampled drafts improved, one of them with a wrong *parameter*
type (`fn_8001D440`'s `f32` args declared `s32` in `fn_800774C0`, 6.9 → 9.4).

**LEVER — early-return shape selects the block layout.** m2c's
`if (c) { A; return 1; } return 0;` makes ngccc lay the *else* out first
(`bne` over it into the body, `li r3,0; b end` inline); want has the body as the
fall-through with `beq` to a `li r3,0` placed at the very end, which is what
`if (c == 0) { return 0; } A; return 1;` produces. Worth 92.1 vs 50.0 on
`fn_800A64F0` and it is the same shape as the promoted sibling
`src/fn_800A638C.c`.

**LEVER — scan the callee's `bl` sites for parked siblings.** `fn_801262A0` and
`fn_80126230` are members of a five-strong sibling family around
`fn_80012098(v, 3)` (the others — `fn_801261C0`, `fn_801FC44C`, `fn_80240810`,
`fn_8022AB24` — were already byte-identical). Listing every `bl 0x80012098` in
`.text` and mapping each site back to its containing symbol is what found the two
still-parked members, and copying the *promoted* member's exact expression shape
was a one-shot 100% each time. Both drafts had the same m2c defect: the index
expression hoisted into a temp (`temp_r0 = *(s32 *)lbl_… * 4;` + byte-offset
casts) instead of two `s32[]` arrays indexed by a plain global — which loses the
`lwzx`/`stwx` forms, loses want's index RELOAD after the call (the callee can
rewrite the global), and drops the arg0 the call actually uses (`li r4,3` only:
r3 still holds `A[i]` from the test).

`fn_80019B90` parked at 92.5% (was 56.7%) — see the entry above for the
frame/init/arity fixes; its residual is the allocator's argument-materialisation
order at two call sites.

**2026-09-18 (d) — `fn_800A7DBC` 44.8 → 100% (EXACT, `DOL BYTE-IDENTICAL`).
Three more reusable index-loop levers.**
The draft was an untouched m2c body whose single fatal defect was
`*((s32 *)var_r30 + (s32)temp_r31)` — pointer arithmetic on an `s32 *`, so a
0xC byte stride became 4*0xC — plus m2c's `if (count > 0) do…while` reading of
the duplicated exit test. Each of the three fixes below was measured separately:

1. **`while (i < count)`, not `if (count > 0) { do … } while`.** want's guard is
   `cmpw r29,r0 / bge end` — the *same register* comparison as the back edge,
   which is what a while loop produces when the exit test is duplicated; the
   `if (count > 0)` form emits `cmpwi r0,0 / ble`. 44.8 → 65.5.
2. **Write the scaled index (`i * 0xC`), never an accumulating `off += 0xC`
   variable.** want initialises the scaled index in a preheader *after* the entry
   test (`bge end; li r27,0; li r30,0; lwz r31,0(r28)`; the back edge jumps past
   both `li`s). An explicit `off = 0` lands in the entry block *before* the test
   (65.5); the `i * 0xC` form lets the loop optimizer strength-reduce it into an
   induction variable whose initialiser is emitted in exactly that preheader.
   65.5 → 86.2.
3. **Form the address as an INTEGER sum with the scaled index first**,
   `(s32 *)((i * 0xC) + (s32)base)`, not `(s32 *)((char *)base + i * 0xC)`.
   want's indexed ops list the induction variable first (`lwzx r3,r30,r31` /
   `add r4,r30,r31` / `stwx r27,r30,r31`); the pointer form makes GCC put the base
   first (`lwzx r3,r31,r30`) — 4 words, all one operand swap. 86.2 → 100. The int
   form also keeps `base` reloaded each iteration (`lwz r31,0(r28)`), which want
   needs because the callee can rewrite `arg0->unk0x0`.

**2026-09-18 (e) — the `fn_80126EAC` family: 3 more EXACT promotions
(`fn_80069C78` 44.2→100, `fn_800AB990` 48.7→100, `fn_801F4BB8` 20.0→100; all
`DOL BYTE-IDENTICAL`). Two more reusable levers.**
`fn_80126EAC` + `fn_8012701C` + `fn_80019D08` appear together in **20 still
untouched drafts**; the promoted `src/fn_8002BB14.c` carries the family idiom
`temp = fn_80126EAC(fn_80019D08(8)); … if (temp != 0) fn_8012701C(temp, 3);`.
Finding families this way (callees shared by promoted code and ≥3 untouched
drafts) is cheap and high-yield — these three were one-shot 100% each.

**LEVER — the “stale arity” of a call is visible as a register want never
writes.** Three separate cases in this batch, each worth a whole function:
- `fn_801277E4` is 3-arg `(obj, key, value)`. want sets r4/r5 and leaves r3 —
  because r3 still holds the previous call's result, and `mr r30,r3` made the
  pseudo and r3 interchangeable, so GCC needs no extra move. m2c's 2-arg
  prototype silently dropped the leading object. Cost: 4 sites across
  `fn_80069C78` and `fn_800AB990`.
- `fn_8013183C` is 1-arg: want's r3 is already loaded from `0x58(r31)`.
- `fn_8013157C` is **10**-arg, not 8: want writes r3..r10 *and* two stack slots
  (`stw r0,0xc(r1)` / `stw r0,8(r1)`). Promoted 10-arg declarations already
  exist (src/fn_80152A4C.c).
- `fn_8012543C` is 1-arg (`s32 fn_8012543C(s32)`, see src/fn_800F6430.c).
Rule of thumb: if want leaves one of r3..r10 untouched at a `bl`, the call is
shorter than the draft thinks; if want writes stack slots, it is longer.

**LEVER — the loop preheader after the entry test (again, now on a pointer
walker).** `fn_800AB990`'s walk (`addi r30,r27,0x68` once, then `lwz r31,0(r30)`
/ `addi r30,r30,0x20`) must be written as an indexed dereference
`*(s32 *)((char *)arg0 + 0x68 + var_r29 * 0x20)` so the loop optimizer
strength-reduces it into the combined biv; an explicit
`var_r30 = (char *)arg0 + 0x68;` before a do/while emits the `addi` in the entry
block *before* the test. Same mechanism as `fn_800A7DBC` (entry (d)).

Also: `arg0+0x2BD` in `fn_801F4BB8` is a **u8** (`stb`/`lbz`), and its vcall needs
`s16 unk0xD8` + a function pointer at 0xDC — `Unk_4AA2E777` already declares both,
so only the `+0x14` vtable load needs the `*((void **)&…)` form.

**2026-09-18 (f) — m2c SCALED POINTER ARITHMETIC is a draft defect class, and it
was costing points on 31 drafts at once.** m2c prints some pointer walks as
`(s32 *)((s32 *)(X) + 0x14)`, i.e. the displacement sits OUTSIDE the cast and is
therefore scaled by `sizeof(s32)` (0x50 bytes) while the binary uses byte 0x14.
`(T *)(X + 0x14)` (displacement inside the cast = integer arithmetic) is FINE and
appears in 406 matching files — only the cast-of-cast form is a defect. Repair is
mechanical: `(T *)((T *)` → `(T *)((char *)`. New scanner
`tools/fix_scaled_ptr.py` (scan|apply, same recipe class as raw_sym_scan) scored
303 candidate drafts, 31 strictly improve; biggest one-shot jumps
`fn_8022D074` 48.3 → **82.1**, `fn_801211B8` 44.0 → **75.0**, `fn_8005DDF4`
30.8 → 44.7, `fn_80013A3C` 28.3 → 40.0. See docs/parkings/63.

**2026-09-18 (g) — three promotions this batch.**
- `fn_800A5418` (148B) 45.9 → **100.0**. Two defects: `sprintf` without a
  variadic prototype (want HAS the `crclr cr1eq`), and the counter update is a
  POST-INCREMENT *inside* the sprintf argument (`sprintf(sp8, fmt,
  arg0->unk0x4++)`), not a temp + separate store. The post-increment is what
  keeps the loaded value in its own pseudo (r9) with `mr r5,r9` and puts
  `addi r9,r9,1; stw r9,4(r31)` after the argument setup; every temp-local
  spelling lets GCC coalesce into r5 and store first (13.5-32.4%).
- `fn_80118214` (72B) 66.7 → **100.0**. `fn_80010758`'s arms were INVERTED
  (want calls it with 0 in the `!= 0` arm), the callee had no prototype, and —
  the decisive find — the function **takes a forwarded argument**:
  `fn_801289E4(arg0, QB_OFF)` with `ScriptSetMemThreadSafe(s32 arg0)`. want
  materialises QB_OFF into r4 and never touches r3; a 0-arg call form caps at
  88.9%.
- `fn_8022B214` (148B) 65.8 → **100.0**. m2c's `var_r3` + labels replaced by the
  real early-return nest (`if (r29 == 0) return 0;` / final `return 1;`), plus
  `fn_80219668(arg0)` (r3 still holds arg0 — no setup move in want) and
  `temp_r28 = lbl_80303148` read BEFORE the first call.

**2026-09-18 (h) — two more unmatched-but-improved parks.**
- `fn_80035B24` (752B) 55.3 → **91.0**: missing `fn_800361EC` prototype (doc-56,
  missed by the earlier sweep) + case 0x27B2B1C shares ONE `x != 0` conversion
  between its arms (m2c's two-variable accumulator makes ngccc duplicate it).
  Residual is block order only.
- `fn_8007F7F8` (392B) 53.1 → 56.1: the scaled-pointer repair above, plus
  `unk0x4` of `Unk_BA2D8CF9` is a BYTE (`lbz`) and `unk0x4` of `Unk_A8B25094` is
  16-bit (`lhz`). Residual is the loop preheader (want hoists five invariants,
  ngccc four and keeps `1<<arg2` / `arg2+1` in the loop).

**2026-09-18 (k) — reloc-aware diff, one promotion + three park improvements.**
- New tool `tools/reloc_diff.py`: prints the **reloc symbol** behind every got
  instruction next to the raw want word and resolves want branch targets through
  symbols.txt. The masked compare blanks `fc000003` (branch) / `ffff0000`
  (lis+@l pair) fields, so a draft that stores the wrong global, passes the
  wrong callee/argument, or has its statements in the wrong order can still read
  100%. This makes those blind spots readable.
- `fn_8007A9F8` (296B) — **promoted, DOL byte-identical**. The draft had been
  generated with a 232B window (the hole scan guessed the next boundary), which
  scored EXACT while hiding the last 16 instructions: symbols.txt has
  `fn_8007A9F8 size:0x128` and the next function starts at 0x8007AB20. Widened
  the compare window, re-verified 74/74, promoted.
- `fn_8003AEEC` 78.2 → **81.8** (`-fno-schedule-insns2`). Two reloc-symbol
  findings: the two global stores are in the WRONG ORDER (want: `E8 = arg2`
  then `EC = arg3`, which also fixes the r27/r29 coin), and the 4th argument of
  `fn_800099AC` is **arg3** — want never emits `mr r6,r9`, r6 still holds arg3.
  Residual: 1 copy-placement coin (ngccc spends `mr r0,arg3` on the EC store
  where want spends `mr r0,r3` on the call return).
- `fn_8003A3D4` 76.2 → **90.5**. The old draft's `var_r3` + `goto` forced the
  loop phi into r3 (`mr r3,r4; cmplw r3,r31`). The rotated pre-tested form
  `do { if (arg1 <= arg2) return res; res = fn_8003A344(arg0);
  if (res == (s32) arg2) return 1; arg1 = (u32) res; } while (1);` reproduces
  want's phi-free compare, both `li` exit blocks and the 2-register frame.
  Residual: 1 word (`li r3,0` emitted before vs after `cmplw`).
- `fn_800A2A60` 74.4 → **95.3**. Three semantics bugs the masks hid: (1)
  `fn_800098F4` had no prototype → `crclr cr1eq` (doc-56); (2) the **alloc
  result was dropped** from the next call — want is
  `fn_8001094C(fn_800098F4(0x1C), arg0)`, r3 keeps the allocation while r4 takes
  arg0; (3) the phantom argument (doc-52) belongs in slot 4 = `&lbl_80297D7C`
  (.rodata2), the draft had it in slot 3. Plus doc-15 homing: writing the
  lbl_80301A5C slot through a local `s32 *slot` reproduces want's r30 homing and
  the `stmw r30`/`lmw r30` prologue in one step.

**2026-09-18 (l) — two more promotions; the volatile-pun narrowing recipe.**
- `fn_8022D074` (112B) 82.1 → **100.0, promoted (DOL byte-identical)**, flag no
  longer needed. Two fixes: the call is `fn_80012098(v, 3)` — want sets only r4
  and r3 still holds the value loaded at 0x8022D098, i.e. m2c had **dropped the
  first argument** (the doc-59/60 class; the promoted siblings fn_801261C0 /
  fn_80126230 / fn_801262A0 / fn_801FC44C / fn_801FC4BC all use exactly
  `s32 v = lbl_X[lbl_Y];` + `fn_80012098(v, 3)`), and the typed-array form
  `extern s32 lbl_80305FCC[]; lbl_80305FCC[lbl_80305FDC]` reproduces want's
  `lwzx`/`stwx` (with the index reloaded before the store) where the char-*
  scaled-pointer recast left the index live in r11.
- `fn_8007BD70` (88B) 77.3 → **100.0, promoted (DOL byte-identical)**. The
  record has `lwz` fields at 0x0/0x4/0x8/0xC/0x18 but the shared Unk_2BAD2BE8
  view declares them u16 (correct for fn_8005872C, which stores them with
  `sth`). Two independent traps:
    1. `unk0x18` is a **pointer** here (`fn_8009A788`'s first parameter is
       `s16 *`) — `*(s16 **)&arg0->unk0x18` took it 77.3 → 81.8 alone.
    2. A plain `*(s32 *)&arg0->unk0x0` pun is **narrowed back to `lhz`**, because
       the value's only use is `(u16)((a + b) - 1)` and the pun's address is
       known to have type u16 — ngccc may then compute the truncated sum from
       the low halfwords. `*(volatile s32 *)&arg0->unk0x0` suppresses the fold
       and is the exact fix (the header already uses `volatile s32` fields
       elsewhere). A 32-bit *view pointer* gives the right loads but changes the
       allocation (no `mr r9, r3`, different argument order → one-word shift,
       <= 68.2%), so keep the puns on the u16 members.

**2026-09-18 (m) — store-order and halfword-width wins; three parks.**
- `fn_800A2A60` (172B) 95.3 → **100.0, promoted (DOL byte-identical)**. The last
  two words were the store order at the two `Unk_C7387A53` field writes and the
  fix was the OPPOSITE of what the old note claimed: with all doc-56/doc-52
  fixes in place, retail's source order is `unk0x84 = 1;` **first** and
  `unk0x88 = <lbl_80301A44 - lbl_80290628>;` second. The old "swap is worse
  (69.8%)" datapoint was measured against the pre-fix body (extra `crclr` +
  wrong `fn_8000F95C` argument), where the whole tail sat in a different
  schedule. Lesson: a store-order "wall" measured on a body with a known
  unrelated defect must be re-measured after that defect is fixed — 8 other
  shapes (local temp, pointer form, char-cast, aliased struct pointer, separate
  `one` local, global-store reorder) all stay at 95.3%.
- `fn_8009A898` (52B) 69.2 → **100.0, promoted (DOL byte-identical)**. m2c read
  four call arguments as WORD loads at offsets 0/2/4/6; want is four `lhz` at
  exactly those offsets. The tell was m2c's `*(s32 *)((char *)X + (s32)0x2)`
  odd-offset hack (it knew the fields were narrower but kept the s32 view).
  Fix: point the temporary at the u16 struct (`Unk_5B449B03`, u16 at
  0x0/0x2/0x4/0x6) instead of the s32 `Unk_5D1D68CC` m2c picked — the argument
  order was already right. New scan `.scratch/widthscan.py` looks for EXACTLY
  this bug class across the whole wip tree: it decodes want and got and flags
  mismatches whose mnemonics differ only in access width (lwz/lhz/lbz, stw/sth/
  stb). On the 1471-draft non-parked pool it found 208 hits but only 11 above
  45% — the class is real but mostly already harvested; the remaining ones are
  incidental (their real defect is elsewhere, e.g. fn_800607A0's frame).
- `fn_8003A3D4` (84B) **parked at 90.5%**: one-word preheader coin
  (`cmplw r4,r31; li r3,0` vs `li r3,0; cmplw r4,r31`). 10 further loop shapes
  (while+break, unrotated while+`return 0`, top-tested `for`, goto-label test,
  split decl/assign, separate `u32` counter, swapped predicate) all either
  reproduce the same 21 words with the same coin or regress (22.7%/27.3%).
- `fn_80068760` (120B) **parked at 76.7%**: the ternary prologue
  `var_r3 = (var_r9 != NULL) ? var_r9 - 0xC : NULL;` reproduces want's
  `[cmpwi r9,0][li r3,0][beq][addi r3,r9,-0xc]` exactly, but then the return-NULL
  block is duplicated (+2 words, 40.6%); every form with a single shared
  return-NULL block loses want's tail (`li r0,0 / beq / addi r0,r9,-0xc /
  or. r3,r0,r0`, i.e. the ternary temp in r0 plus a phi move fused with the
  back-edge test). Prologue and tail are mutually exclusive under ngccc.
- `fn_8003AEEC` (220B) **parked at 81.8%** (`-fno-schedule-insns2`): got is want
  with ONE extra `mr r0,r6` (the second global store `lbl_803003EC = arg3` goes
  through a copy of the parameter instead of `stw r6`), everything after it
  shifted 4 bytes and then re-synced. 15 source shapes all land on exactly
  81.8%; it is an RA colouring coin on the parameter pseudo that is also the
  outgoing 4th argument.
- Tooling added this round: `.scratch/vsweep.py` (score N candidate bodies for
  one address in parallel, one LEAF_TMPDIR each), `.scratch/scorelist.py`
  (score an explicit address list), `.scratch/widthscan.py` (access-width
  classifier described above), `.scratch/gotonly.py` (got-only disassembly with
  reloc masks). Also: `promote_wip.py` needs the `// family=... range=0x...`
  line in the draft header — rewriting a wip file wholesale without it fails
  with "no range marker".

**2026-09-18 — random-batch sweep (24 no-park-note drafts): 8 EXACT promotions
(DOL byte-identical `ff6faeb0…`) + 3 parks with reasons.** All 8 were promoted
with NO flags; two of them had stale auto-harvested `// FLAG:` markers
(`-Os` on fn_800815C0, `-fno-expensive-optimizations` on fn_8002E34C) that are
simply not needed — drop such markers whenever the flagless body is verified.
Promoted (**all DOL-verified byte-identical**):
- **fn_80058D80** (64B) — setter + vtable dispatch. m2c appended the loaded
  METHOD POINTER as a phantom 2nd argument; want writes only r3 and `blrl`s.
  Also: the adjust offset at 0x28 is `s16` (want `lha`) while the object field
  at the same offset is `f32` (`stfs`) — shared Unk_C7387A53 types both s32, so
  a local per-record typedef is required.
- **CScreenElement_SetAlpha** (68B) — two-field float setter with an `|= 0x400` dirty flag.
  Shared Unk_6A70655D types 0x88/0xD0 as s32; the draft's `!= farg0` then
  compiled an int<->float conversion instead of `lfs; fcmpu`. f32 fields in a
  local typedef => byte-exact.
- **fn_80014AE8** (76B) — singleton `lbl_803CAF54` trampoline into a
  FIVE-argument virtual call `(g + (s16)v->0x10, g->0x14, 0, arg0, g->0x2C)`.
  m2c emitted a phantom SIXTH arg and read temp_r9 before assigning it.
- **fn_8022BC98** (116B) — two-case state setter; case 1 re-enters itself with
  the real sibling getter fn_8022BD1C's value. Phantom 3rd arg on fn_8000A578
  (raw `0x80300000` rodata literal) dropped; `0x80303148` → registered
  `lbl_80303148` (doc-51).
- **fn_800815C0** (112B) — stamps `fn_800145AC() & 0x7FFFFFFF` into the
  top-bit-preserving header of every element. The old draft had doc-63 SCALED
  POINTER ARITHMETIC (`*((s32 *)var_r8 + arg0->unk0x20)` scales the byte
  walker); want is a plain element walk with the array base RELOADED per
  iteration. Header word must be `u32`.
- **fn_8002E34C** (92B) — fn_8021B55C is a TWO-argument call (want sets
  `li r4,0` before the bl) and the flipped flag is bit 29, not 28 —
  `((x >> 29) & 1) ^ 1` is what emits `rlwinm r5,r5,3,31,31`.
- **fn_801855E0** (172B) — container enumerator. The counter must be
  ADDRESS-TAKEN (`&i` is passed to fn_8018B4C0) so it stays at r1+8, and the
  dispatch offset at 0xA8 of the node's 0x14 sub-object is `s16` (`lha`).
- **fn_800A49EC** (200B) — record-array destroy walk. The record STRIDE is
  0x14, so the struct needs a 4-byte tail pad or `p++` emits `addi ...,0x10`
  (98.0%); with the pad, one word left. Also: pass
  `fn_800A5BF4(*(s32 *)lbl_80301A78, p->unk0x0, arg1)` and
  `fn_8012701C(p->unk0xC, 3)` (the old draft used the loop's comparison result
  and the symbol's address), and write the match test as a plain `||` with the
  invariant half (`arg2 == QB_ALL_GROUPS`) left for the loop optimiser to hoist
  into cr4 (m2c's duplicated `(x != 0) || (x != 0)` does not match).
Parked with notes (best body kept in the draft):
- **fn_800137C4** (156B) 30.8% masked but **33-of-39 ALIGNED** — the low score
  is a pure 4-word block shift. want's `for (;;) { while (flag == 0); ... }`
  emits a NON-CSE'd loop-inversion: an entry test at the loop top plus a
  separate spin block that RE-MATERIALISES the address into a new register;
  ngccc folds the spin into the loop top (one `lwz`+`beq .L8`). Residual #2 is
  one `cmpw` vs `cmplw` on the table walk. Also a LINK HAZARD: 0x8030FF14 has
  no symbol of its own (it is +0x10 inside the registered `.data` object
  GXNtsc240IntAa) and want addresses it @h/@l — an `extern` at that address
  would emit @ha = 0x8031 and differ. Tried: plain while, hand-inverted
  if/do-while, raw literal, `goto retry`, signed-cast compare.
- **fn_8006150C** (196B) 26.5% — circular-list walk; the body matches
  instruction-for-instruction but want keeps the head/walker in STACK SLOTS
  (frame 0x48, `stmw r29`) while ngccc holds them in callee-saved registers
  (frame 0x30, `stmw r26`). Tried plain scalars (6.1%), a 2-pointer local
  struct (26.5%), a `Node *p[2]` array (26.5%), and 6 flag variants — a
  global-allocator decision, not source-reachable.
- **fn_8005BB50** (168B) 14.3% (ScriptSetLoadingBarStartColor) — fully decoded
  (three QB reads, byte-packed colour word, `li r0,-0x80` proves a SIGNED char
  field). Residual: stack-slot ORDER is order-independent in ngccc
  (spC=0x8..sp8=0x18 regardless of declaration order, vs want sp8=0x8..
  sp18=0x18), plus address rematerialisation at the call sites and `lbz`
  narrowing of the two word-loaded byte sources.
Also probed without movement: fn_8022ED20 (188B, capstone-stalls on PS ops in
its body — needs a PS-aware redraft), fn_80075854, fn_800602EC, fn_8022B2FC,
fn_80005E20, fn_80038094, fn_800F1790, fn_80025010, fn_8012EABC, fn_8003C2AC,
fn_80042F44, fn_8026E750 (all still DIFF, untouched beyond the initial score).

## 2026-09-18 — 13 promoted, 0 parked, NEW RECIPE: absolute addresses as `ldscript` symbols

**All 13 DOL-verified byte-identical** (`sha1 ff6faeb0f2b524ecbe1aeaff78ff154a284c27c9`).

### The lever: a raw MMIO/OS address literal can never match — only a symbol can

ngccc materialises an address *literal* as `lis rX,logical_hi` + `ori rX,rX,lo`
(and then `lwz/stb ...,0(rX)`), because the logical hi/lo split always fits.
Retail folds the address into the *displacement* of the access
(`lis rX,-0x8000` + `lwz r0,0xf8(rX)`, i.e. sign-adjusted `@ha`/`@l`) — the form
ngccc only produces for a **symbol reference**. So every draft that writes a
bare `*(T *)0xADDR` for an address with no section (MMIO at 0xCC00xxxx, OS/IPL
low memory at 0x80000xxx) is 2 words too long by construction, and those 2 extra
words also **rotate the register allocation of everything downstream**, which is
what got several of these parked under misleading diagnoses.

`config/G2TE52/ldscript.tpl` already carried two absolute symbols for exactly
this reason (`lbl_CC008000`, `lbl_CC006828`); this session added
`lbl_800000F8 = 0x800000F8; /* OS bus clock */`. Adding an absolute symbol
changes no existing output — the DOL stayed byte-identical.

A census of the no-park corpus for low-memory/hardware literals came back small
(0x800000F8 × 6 drafts, 0x800000D4/D8 × 2, the `0x8000Fxxx` MMIO bank × 2), so
this is a small but very cheap family: **before redrafting any draft whose want
contains `lis rX,-0x8000`/`-0x33ff`-style *folded* address materialisation, check
the draft isn't spelling the address as a literal.**

### Promoted

| addr | size | root cause of the old draft's failure |
|---|---|---|
| `fn_8001DC98` | 36B | GX `GX_LOAD_INDX_A` leaf — literal 0xCC008000 → `extern char lbl_CC008000[]` + `u16` stores (its sibling `fn_8001DCE0` was promoted the same way years earlier; `fn_8001DCBC`/`fn_8001DD04` are the B/D members of the same 4-leaf family) |
| `fn_8001DCBC` | 36B | same |
| `fn_8001DD04` | 36B | same |
| `fn_8003B9E0` | 104B | the 4-float stack buffer must be reached through a **pointer variable**. Passing the array by decay lets ngccc fold the address into the call (`addi r4,r1,8`), losing retail's `addi r9,r1,8` + `mr r4,r9` pair and shifting the whole tail by 4. Also drops m2c's phantom 3rd call arg (6.7 → 100) |
| `fn_8005A060` | 72B | the callee's 2nd argument is the **original `s32 *` argument**, not the record pointer m2c passed; per-record local structs replace the byte-swapped `Unk_*` types |
| `fn_8005DFD8` | 104B | the table walk is **bottom-tested** (`do {} while`). `while (p <= end)` makes ngccc synthesise the entry test *plus* a separate block, costing 4 registers of difference. Plus `lbl_803C9E18` (doc-51) instead of the literal |
| `fn_80098E64` | 92B | `lbl_800000F8` (new absolute symbol) |
| `fn_8007E89C` | 92B | **twin of fn_80098E64** (same tick-since-last helper, other stamp global) — same single lever |
| `fn_80120924` | 168B | **UNPARKED** (was 71.4%, "one allocator coin over three callee-saved registers — park on sight"): the tick loop's `*(u32 *)0x800000F8 >> 4` literal is 2 words too long, and *that* is what pushed the base out of r31. With `lbl_800000F8` the roles land exactly with no other change. Also had a **latent link bug**: it called `fn_80267848()` (not a symbol) instead of `OSGetTick` |
| `fn_8009C738` | 64B | the element must come **first** in the sum: `(Elem *)(i * 8 + arg0->unk0x34)` emits `add r9,r10,r9`; the m2c order `arg0->unk0x34 + i * 8` emits `add r9,r9,r10` (the only word wrong at 93.8%). `i * 8` must stay an induction expression — the stride is accumulated as `addi r10,r10,8` |
| `fn_80175410` | 64B | doc-52 phantom arg (m2c read the `lis 0x8030` half of the global's address as a literal 2nd argument; retail sets r3 only) + `lbl_80305F9C` |
| `fn_80042180` | 76B | the recursive call passed the **mask result** instead of the child pointer (`lwz r3,0x58(r3)` → `bl 0x80042180`), and the mask came from a `QB_*` placeholder instead of a foldable `& 0x10000000` |
| `fn_80013FB4` | 80B | retail keeps **two** advancing pointers (return ptr r3 + compare ptr r9 anchored at `-4(r9)`/`0(r9)`). Only two independent base+index expressions reproduce that split: `(s32 *)((char *)arg0 + 0x24) + i * 4` and `(char *)arg0 + 0x18 + i * 0x10`; `p += 4` / `&arg0->arr[i]` collapse it to one pointer (65% / 10%) |

### Tool note
`promote_wip.py` reads the range marker with
`range=0xADDR-0xADDR size=NNB`. Hand-written drafts in the corpus use a colon
(`size:168B`) and are therefore **unpromotable as-is** — the assert fires after
the draft has already been re-verified. Worth a `:` → `=` normalisation pass.

### Continuation — 1 more promoted, 1 re-parked, 1 re-scored

* **`fn_801FC1D0` (180B) promoted** — TWO defects. (a) doc-63 again, in its
  *increment* flavour: the m2c draft indexed the table as
  `(s32 *)((s32 *)(t * 4) + (s32)lbl_80305F60)`, i.e. a scaled index cast to a
  pointer and then offset by the symbol — one extra `slwi` and two registers
  (frame 0x18/`stmw r28` vs retail 0x10/`stmw r30`). The byte spelling
  `*(s32 *)(lbl_80305F60 + t * 4)` with `lbl_80305F60` as `char[]` gives
  retail's `addi r9,r9,@l; slwi r0,t,2; lwzx r31,r9,r0`. (b) the draft called
  `fn_800120EC` with no prototype → `crclr cr1eq` (doc-56). Also note the m2c
  `||` + comma-assignment trick is NOT needed: two plain sequential
  `if (v != 0 && f(v) != 0) { g(v); return; }` statements give the same single
  `bl` (see the fn_80153844 entry below for when that merge happens).
* **`fn_80032588` (136B) re-scored 47.1% → 76.5%, still parked** with the new
  best body and a full diagnosis in the draft. Core finding: it had the doc-63
  defect in the `void **p; p += 4;` shape (scales to +0x10, wrong array stride),
  and the array base must be computed INSIDE the loop body (hoisted `base`
  changes the entry test and invents a `cmpwi r0,0` guard). Residual = 4
  clusters, documented in the draft. Doc 63 got a "Related" note that the
  scanner's two cast-offset passes do not cover `+= N` increments.
* **`fn_80153844` (176B) re-scored 39.5% → 42.2%, still parked.** Was worth a
  re-look because `fn_801FC1D0` promoted with a two-call-site body: the blanket
  claim in its old park note ("ngccc crossjumping NEVER merges call
  instructions") is wrong. Refined rule now recorded in the draft: the two
  argument-setup blocks must be inside-identical. One call site with different
  arg staging per path needs call-level tail merging, which is the real wall.

## 2026-09-19 (no-park sweep + SDA-route retest + odemuexi2 wiring)

**6 promotions (DOL byte-identical `ff6faeb0…`).**

| fn | size | key fix |
|---|---|---|
| `fn_80274B10` (16B) + `lbl_80274B20` (44B) | 60B total | **doc 65 — map-merged second entry point.** The map's `fn_80274B10` (0x3C) is really TWO functions: a noreturn `abort()` stub (prologue kept, epilogue dropped) plus an entry point that `fn_802740DC` calls with `bl 0x80274B20`. Split into two objects/splits, `symbols.txt` sizes fixed, non-`fn_*` name registered by hand. Keeping both functions in ONE object links byte-identical but scores 26.67% (objdiff only resolves relocations inside the unit's own range). |
| `fn_80069D24` | 68B | **form, not flags.** The old draft's `-fno-schedule-insns` recipe (38.9%) was chasing an addressing-form problem: index the struct base (`((s32 *)arg0)[0x4F + arg1]`) instead of a sub-array member, which makes ngccc emit `slwi/add/stw disp(rBase)` and frees r9 for the interface pointer. |
| `fn_80249A00` | 16B | §5q SDA route (`-msdata=eabi -G4`, `sda_verify` LINK-SIM EXACT); s32 externs, no casts. |
| `fn_8024C5D4` | 20B | SDA route + store-run rotation (doc 09 addendum): three stores to *distinct* globals, written rotated. |
| `fn_8024C294` | 280B | Was parked at 93% with ONE word left. SDA route + store the **call expression straight into the global** and read the global back into the local, so store-to-load forwarding keeps r3 (caller-saved) instead of a callee-saved copy. |

**SDA-route retest of the whole un-parked pool: nothing new.** Scanned
every wip draft whose *retail* body has r13-relative accesses (102 drafts, 32 unparked)
and ran all four flag sets through `tools/sda_verify.py`. No EXACT: the msdata-header
drafts were already harvested and the rest are genuine walls. Ten of the 0x8028Dxxx
"stub" drafts turned out to be odemuexi2 (see 107c) — deleted as superseded.

**odemuexi2 lib was never compiled: 17 units / 23 functions credited.**
Diagnosis: `configure.py`'s odemuexi2 module listed its objects as bare
`Object(Matching, "DBGFlushBuffer.c")` while `splits.txt` names those splits
`odemuexi2/DBGFlushBuffer.c` (the lib-dir-prefixed convention every other lib module
uses: cf. `Object(Matching, "libgcc/__divdi3.c", source="__divdi3.c")`). dtk matches
module objects to splits **by name**, so all 17 silently fell through to the
unmatched path: no `build/G2TE52/src/odemuexi2/*.o` rule existed, objdiff.json had
**no `base_path`/`scratch`** for those units (report showed `total_code` but no
`match_percent` — "⏳ assembly" in PROGRESS.md), and the linker linked the
**extracted original** `obj/odemuexi2/*.o`, so the byte-identical DOL proved nothing
about `libs/odemuexi2/src`. Fix = name the objects `odemuexi2/<file>.c` +
`source="<file>.c"` (also for the Vtable unit; `DebuggerDriver.c` stays NonMatching).
Reconfigure → 80 new src/ rules + base_path in objdiff.json → rebuild → **DOL still
byte-identical** → 8498 → **8521 matched**, +2820 code bytes. The lib sources are real
matches, not extracted code. 22 superseded wip drafts deleted (all the 0x8028Dxxx
stubs) plus their WIP.md rows.

Hazard to carry forward: **"Missing configuration for <lib>/<file>.c" in a configure
run means the split has no matching Object entry and its code comes from the extracted
original — a vacuous DOL identity.** Verify lib work with `objdiff.json`'s `base_path`,
not with `cmp`.

**Parks (best body + note):** `fn_800699A8` / `fn_80069C58` / `fn_8007D330` (16-byte
`__ps_t` pair copies; only two ngccc-policy residuals — the psq_st displacement fold and
a hoisted first psq_l; all five ProDG point-versions identical, so not a version wall;
doc 06 addendum); `fn_8007B8F0` (9/10 words — `stwx` RA/RB role split); `fn_80031FA0`
(6/9 — the double store across the branch is if-converted away by ngccc);
`fn_8028E038` (NOT a function: the 8-byte trailing zero pad of `.text`, already named
`pad_01_8028E038_text`).

## 2026-09-19 (named-function seam: carving real-named functions out of the auto blobs)

**Why this seam.** Measuring where the remaining work actually is (report.json):
unmatched code = **1.80 MB in 1502 `main/auto_NN_XXXXXXXX_*` units** vs only ~15 KB in
the ~45 *source* units that are near-misses. The wip pool is worked out; the mass is in
blobs. Within the blobs there is a self-documenting subset: of the **2013 `.text`
functions in `symbols.txt` with a real (non-`fn_`/`lbl_`/`pad_`) name, 1789 are already
matched and the remaining 224 (~97 KB) are ALL inside auto blobs** — not one of them sits
in a carved source unit. A real name is a free identification, so these are the
cheapest blobs to attack and they already tell you what the function is.

Rescan recipe (the one used here): walk `report.json` units, keep `.text`/`.init`
sections with `complete_code_percent < 99.999`, index them by address, then take every
`symbols.txt` line that is `type:function` with a non-`fn_` name and look up its
containing unit. `complete_code_percent` — **not** `fuzzy_match_percent` — is the
matched/not signal (a promoted file showed 99.86% fuzzy while being complete: 100%).
Note the vtable-stub names (`Vtable0x80308A40_m*`, 40–88B) use a non-standard `r31`-rooted
convention (`mflr r30`/`blrl` fragments of one shared body) — deprioritise those.

**15 promotions (DOL byte-identical `ff6faeb0…`), 8521 → 8536 matched.**

| fn (symbol @ addr) | size | key fix |
|---|---|---|
| `ScriptExists` 0x80117418 | 88B | node lookup + `fn_80125480(handle)->unk2 == 7` |
| `ScriptGetUpperCaseString` 0x80117220 | 100B | `strcpy` into a 0x80 stack buffer, upper-case in place, publish under 0xFE366B7B |
| `ScriptIsSoundPlaying` 0x80113654 | 88B | needs the **if/else assignment** form; the early `return 0` gives the mirrored layout |
| `ScriptClearSoundBank` 0x8011372C | 72B | out-slot left **uninitialised** (retail has no `stw` for it) |
| `ScriptStreamExists` 0x80112DDC | 92B | declare+zero `ret` **before** `sp8` so ngccc reuses one `li r31,0` for both zeros |
| `ScriptSetSfxDropoff` 0x8011385C | 116B | early `<=` return to get the NaN-safe `cror cr0un,cr0eq,cr0lt; bso`; constants are 0x8029D0FC/0x8029D100/0x8029D104 |
| `ScriptLoadMusicHeader` 0x80113ADC | 120B | **two-arg** allocator enter `fn_8000F2F8(mgr, mgr->unk0x11C)` + inverted early return |
| `ScriptLoadStreamHeader` 0x80113B54 | 120B | twin of the above, loader `fn_8011E500` |
| `ScriptIntegerEquals` 0x80114BAC | 116B | second slot zeroed **after** the first lookup (keeps the shared 0 in a callee-saved reg → 0x20 frame) |
| `ScriptChecksumEquals` 0x80114C20 | 116B | same shape via `fn_801286D0` |
| `ScriptChangeTrackState` 0x80113C5C | 104B | the lookup must be **inlined as the argument**, not stored in a local |
| `ScriptSetReferenceChecksum` 0x80118868 | 112B | allocator ref hoisted before the fetch |
| `ScriptInitLightManager` 0x80112274 | 112B | two params 0x50228D9E / 0x701C70AC → `fn_80059048` |
| `ScriptPrintMemInfo` 0x801182BC | 120B | NULL-guarded fetch, then mgr stats → `strcpy` into a 0x40 buffer |
| `ScriptAddCollision` 0x80118D70 | 136B | two objects 0x26861025 / 0x02E58C18, bind the second to the first's collision |

**Hazard confirmed by this batch — reloc-masked constants.** `ScriptSetSfxDropoff`
scored 100% under the masked compare with the **wrong** constants (I mis-decoded the
`lis/addi` pair as `lbl_8029D0F8`/`lbl_8029D0F4`); the object still linked and only the
post-promotion DOL byte-compare caught it (4 bytes at 0x8011398E). Two more of the same
kind here: `lis r4,-0x6bac` is **0x9454**, not 0x9453, and `0x8029D100` is not a
neighbour of `0x8029D0FC`. Rule: for any `lis`/`ori`/`lfs`/`lwz` operand you derived by
hand, re-derive the full 32-bit address from the pair before trusting a 100% masked
score — the masked scorer and `br_targets` are blind to reloc fields.

**+1 promotion, +1 park, +1 tooling gotcha.**
`ScriptBindControllerToSkater` 0x801603C0 (124B) **PROMOTED** — two params
0xB30D9965 / 0xC52D1A41, bind on `lbl_8030191C`, then refresh the skater manager held
by `lbl_80305EAC` (load hoisted before the bind call).
`ScriptSetModelFaceTexturePoints` 0x8003E554 (88B) **parked at 81.8%** (18/22 words):
param fetch `fn_80128558` with the `lbl_802921CC` name string, `sp40` guard, then
`fn_8003E328` + `fn_8003DAA0` on a 0x38 stack buffer. Two residuals, one scheduling
domino: retail runs `addi r4,r4,@l` **before** `stw r0,0x40(r1)` (ngccc always stores
first), and consequently reloads as `lwz r4,…; cmpwi r4,0` where ngccc picks r0.
Five spellings tried (param type, `(s32)`/`(void *)` cast, separate `sp40 = 0`, bare
`if (sp40)`), all identical.

**Tooling gotcha — `tools/disasm.py` silently truncates at a paired-single op.**
`ScriptGetParkEditorCursorPos` (0x80233B4C, 108B) dumped as only 8 instructions: capstone
stops at the `psq_l` at +0x28 (`e0090000`) and returns, so a PS-using function looks short
and ends mid-body. Raw words confirm the rest (`psq_l/psq_st` pairs, then `lfs f3,f1,f2` and
a `bl 0x8012788C`). Read the raw words (`struct.unpack_from(">I", …)` per 4 bytes) for any
function whose dump ends early — and treat PS bodies as `-mps-float` + `__ps_t` work
(doc 06), not as small functions.

**Parks (best body + note):** `fn_801171A0` `ScriptAppendSuffixToChecksum` — 93.75%
(30/32 words) — **SINCE SOLVED AND PROMOTED; the "swapped instruction" was a
MISREAD hash constant.** m2c's third-call literal (0xAFB8EE3A) is wrong; decoding want's
`lis r4,-0x5047` + `ori r4,r4,0x11c6` gives 0xAFB911C6 = `QB_APPENDED_ID` and the body
goes 93.75% -> 100.0% with NO other edit. See §6o-102/§6y-133: the last two diffs of a
script wrapper are almost always the hash pair, not arg setup.
`fn_80159BEC` `ScriptGoalsGreaterThan` — 61.3%; a **codegen wall**: retail materialises
the float predicate with `li r3,1` preloaded + `bgt`, ngccc always emits the SETCC form
(`fcmpu cr7` / `mfcr r3` / `rlwinm`). Tried `return a > b;`, `if (a > b) return 1;
return 0;`, if/else assign, `ret = 1; if (!(a > b)) ret = 0;`, `?:`, `sp8 < a`, `!(sp8 >= a)`;
`ret=1`-default and ternary are byte-identical to each other, so it is a policy wall of the
same family as docs/parkings/06.

**random no-park sweep: 4 EXACT promotions (DOL byte-identical
`ff6faeb0…`; report regenerated at 8643/11494, 75.20%) + 5 parks with notes.**

Landscape first: an 8-slice sweep of all 2,838 drafts plus a per-draft score of
the **1,116 no-park non-stub** drafts (top score 51.2%) showed the no-park set
is now almost all structurally-wrong m2c bodies — only two clear NEAR and no
EXACT. Every promotion below came from genuinely re-decoding the function from
the disassembly (no flag/statement brute force).

Promoted (all byte-verified by promote_wip's full relink):
- **fn_80081630** (124B) — per-object mask-update loop + one s16-offset vtable
  dispatch.  Three stacked m2c defects: a top-tested `for` (count RE-READ at
  the bottom) instead of the `count > 0` guard + do-while; the dispatch offset
  at 0x188 is `s16` (want `lha`) not the shared Unk_31DE137E `s32`
  (fn_8004CC88 lesson); and m2c invented a phantom 2nd dispatch arg
  (`mr r4,r9`) — want sets only r3.
- **fn_8003E914** (164B) — sprintf template into a stack buffer.  m2c typed
  the destination as ONE `s32` (frame 0x18); retail has a **0x200-byte char
  buffer** at r1+8 with the out-size at r1+0x208 (frame 0x218).  With the
  array local, GCC stops CSE-ing the buffer address into r30 (r30 is the
  fn_80012E88 result) and recomputes `addi r3,r1,8` per call.  Both format
  strings are SYMBOLS (→ lis+addi), not the raw `0x802921F4` literal.
- **fn_80184EB4** (108B) — delegated dispatch.  m2c ROTATED the param names
  (`arg2,arg3,arg4,arg0,arg1`) so the forwarded args left in the wrong
  registers; real signature is (arg0..arg4), `fn_801839F0(arg0,arg1,0)`, and
  the dispatch offset 0xA0 is `s16` (`lha`) → per-record typedef.
- **fn_801B8018** (88B) — m2c split the fn_80126EAC/FF4 pair wrong: the first
  `fn_80126FF4` call consumes the PREVIOUS call's return (want keeps r3, only
  sets r4 = arg1), i.e. `fn_80126FF4(temp_r30, arg1)`.

Parked (best body + note in each draft):
- **fn_800AC9B4** 82.8% (46.7 → 82.8; byte-offset `stwx` + first-call arg
  fix; residual = arg1/offset r28/r29 home swap).
- **fn_800F1DB0** 70.4% (40.7 → 70.4; `char *` walker stride + 2-arg
  `fn_800F16C8(arg0, i)`; residual = i/base r10/r11 home swap).
- **fn_80193770** 41.9% (walker stride + store order decoded; residual =
  zero/one/walker register permutation).
- **fn_80185B4C** 40.7% (semantic decode corrected — 3-arg fn_8018B4C0 and a
  chained fn_8018E584 call — but the corrected bodies score WORSE: the
  address-taken counter then needs a 2nd callee-saved register; keep the m2c
  body).
- **fn_8009D91C** 47.6% (m2c read-offset/width artifact; honest byte reads
  regress to 2.4%; needs a from-disasm redraft).

Reusable lesson (fn_801B8018 + fn_80081630): when m2c drops or adds a call
argument, the tell is a DEAD `mr` of an incoming/return register in want, and
fixing the call shape alone restores the whole body's register allocation.

## 2026-09-21 (continuation: 2 EXACT promotions + 2 parks)

**2 promotions, DOL byte-identical.**  A full parallel re-score of all 1,109
no-park drafts confirmed the no-park set tops out at 50.0% (only fn_8003EB5C
is NEAR), so every win below is a from-disassembly redraft.

Promoted (verified by promote_wip's full relink → `main.dol: OK`):
- **fn_80206C48** (228B, 50.9% → EXACT 57/57) — a 22-entry dual-array clear.
  Four independent m2c defects: (1) the 0x9A8 descending clear walks a BYTE
  pointer (`addi r9,r9,-4`); m2c's `s32 *` made `-= 4` stride 0x10; (2) the
  main loop is INDEXED (`stwx r0,r9,r10` / `stfsx f0,r9,r11`), so it needs two
  typed base pointers + an int index — m2c's byte-offset expression folded
  into `stw r0,0xa04(r9)`; (3) the store block is not ascending: want emits
  0x1374 first, then 0x12F0/130C/1310/1314/1318/131C/1370 (see the store-order
  rule below); (4) `li r0,0` must materialise BETWEEN the two base addresses —
  a `z = 0;` statement between the `p1`/`p2` assignments puts it there.  Also
  unk0x1314 is `u32`, so the m2c pointer cast was unnecessary.
- **fn_800542DC** (172B, 46.7% → EXACT 43/43) — two strstr probes then a
  formatted print into a stack buffer.  m2c had BOTH callee roles shifted:
  both comparisons are the same callee, `strstr(arg1, sym)` (0x8026B550), and
  the format call is `sprintf` (0x80269F4C — the `crclr cr1eq` is the varargs
  float marker) with the BUFFER first; there is no phantom argument.  The
  local is a **0x200-byte char buffer** (frame 0x218), not `s32 sp8`.  NOTE:
  the WIP leaf compile reloc-masks every `bl`, so a wrong callee NAME scores
  fine but breaks the real link — 0x80269F4C must be spelled `sprintf`.

Parked (best body + note in each draft):
- **fn_8001593C** 46.7% → **63.3%** (19/30).  Decode fixes: the callee is
  `BannerCheck` (0x80015870) called with ONE arg (`li r3,0`) — m2c's
  `(0, lbl_80290B50)` phantom paints a live r4; the local is a SMALL object
  (frame 0x28 ⇒ ≤0x14 bytes), not m2c's Unk_59AB5482.  Residual = pure
  callee-saved REGISTER CHOICE: retail keeps `&sp8` in r29 (so both 0xC
  stores share that base) and arg0 in r30 with stmw r29..r31; ngccc picks
  r31 for `&sp8` and folds to r1 displacements.  Local-size and
  pointer-vs-array spellings all stay on r31 — allocator, not source.
- **fn_801FA1EC** 46.3% (re-measured; the 50.0% in its old header is stale) —
  three structural defects documented in the draft: `arg0->unk0x38` is a
  **s16** store (`sth`) while Unk_C7387A53 declares it s32; the descend loop's
  fused `or. r31,r9,r9` + shared `beq` is only approximated by the m2c
  `goto loop_2` shape; and the preheader order (fn_801FB334 call → load
  arg0->unk0x24 → store 0x38) can't be forced without dropping the call one
  instruction early.

**Store-order rotation (doc-09 addendum, re-confirmed on fn_80206C48).**  The
run of independent constant stores to one base is emitted **rotated right by
one** (last source store first), so the target emission `[X, a, b, c, ...]`
is matched by writing the source run as `[a, b, c, ..., X]` (X last).  This
is already law in `docs/parkings/solved/09-init-struct-store-order.md`; what
was wrong on fn_80206C48 was the *body* — m2c had emitted the run in ascending
field order, and `store_order_search`'s sweeps only permute sorted orders, so
they never reached `rot_left(want)`.  Use the doc-09 recipe directly instead
of those sweeps when the diff is one same-base store run.

**Constant materialisation slot (new lever, fn_80206C48).**  A `li r0,0`
that must sit BETWEEN two `addi rB,r31,imm` base computations is produced by
inserting an explicit `s32 z = 0;` assignment between the two pointer setup
statements and storing `p1[i] = z;`.  Six other spellings (while / do-while /
u32 index / countdown / `f32` constant / typed cast) all left the constant
after both bases and capped the draft at 55/57.  Related to doc-47
(preheader placement) but a different lever: doc-47 moves base
*address arithmetic* in or out of the loop, this one moves a *constant*.

## 2026-09-21 (continuation: 1 EXACT promotion, 2 parks)

Promoted (verified by promote_wip's full relink → `main.dol: OK`):
- **fn_80216D10** (184B, 46.8% → EXACT 46/46) — a two-level list walk that
  virtual-calls a release-ish method on each node.  Two decode fixes:
  (1) the fn_8013E098 call's FIRST argument is `arg0->unk0x8` (want
  `lwz r3,8(r28)`), not arg0 itself, and its second argument is the NODE
  POINTER `temp_r30->unk0x14` — m2c dereferenced one level too deep;
  (2) the vtable's +8 field is an **s16** this-adjustment (want `lha r3,8(r9)`
  + `add r3,r31,r3`) while +0xC is the method pointer, so a file-local
  typedef is needed — the shared Unk_C8FEE62D has s32 fields and emits `lwz`.
  (Same root cause as fn_8002F9C4 below: one offset, two widths, two types.)

Parked (best body + note in each draft):
- **fn_8016D470** 46.8% → **63.8%** (30/47).  Real decode fix: the loop read
  happens BEFORE the walker advance (`temp_r3 = p->unk0x0; p += 0x190;
  fn_8012705C(temp_r3);`) — m2c advanced first, so it read `*(p+0x190)`.
  Residual is pure scheduling: want hoists the loop-invariant constants
  (0xEA60/0x7530/0x577B39EE in r26/r25/r27) above `addi r31,r30,0x154`
  while ngccc emits them after; want keeps `lwz r3,0(r31)` at the bottom of
  the loop body and issues the tail `lwz r3,8(r30)` before the tail stores.
  Naming the constants as locals is strictly worse (21/47) and re-homes arg0.
- **fn_8002F9C4** 49.0% (no gain; body kept).  Findings recorded in the
  draft: the element's +0x18 is a WORD load (vtable pointer) while the
  vtable's own +0x18 is an **s16** this-offset (`lha`) with the method at
  +0x1C; the two `addi r30,±4` are BYTE offsets (struct-pointer `± 4` scales);
  the first walk is emitted loop-ROTATED (entry `b` over the advance into a
  shared bottom test) with the count in r11 — ngccc emits the un-rotated form
  with the count in r10, and all three loop spellings probed (goto / while
  with duplicated conversion / entry-guarded do-while) keep that shape.

## 2026-09-22 (random no-park sweep: 7 EXACT promotions, 2 parks)

Random pick from the 1,082 drafts that carry no park note (`src/wip` drafts
without "park" anywhere).  Scored the whole pool with
`tools/test_wip_drafts.test_one` (8 parallel slices, ~20 s); the pool's best
score was **49.4%** — the no-park residue is now uniformly hard, so the work
was full re-decodes against the disassembly rather than small tweaks.

Continuation same day: after scoring, the whole pool was re-binned by score and
the **>=85% band** was worked (that band is where the m2c-dropped-argument and
pointer-spelling levers live); `tools/fix_call_arity.py` was also run over the
sub-50% drafts — it found nothing, because a dropped argument is only *visible*
in the prologue schedule, not in any argument move.

Promoted — all 7 verified by promote_wip's full relink
(`DOL BYTE-IDENTICAL`):

| addr | size | what actually fixed it |
|---|---|---|
| `fn_801A397C` | 140B | per-record field widths: 0x28/0x2C/0x34/0x38/0x3C are **f32** but the shared Unk_C7387A53 types them s32, so the m2c body emitted `fctiwz` + `stw`; a file-local f32 struct fixes it.  Plus the 5-arg prototype for fn_80131008 (an undeclared call adds `crclr cr1eq`).  Residual = the 8-store block order, which want emits in exact SOURCE order and ngccc's pre-RA scheduler permutes — **not source-reachable**, so `-fno-schedule-insns` (58 precedents in src/) |
| `fn_80236E70` | 132B | (1) the false arm is a **12-byte STRUCT COPY** of the registered global `lbl_802B0D08` (`lbl_802B0D08` is a `.rodata2` object; m2c emitted three indexed loads) — the struct spelling is what produces want's `[lwz 0][lwz 8][lwz 4]` / `[stw 0x60(r30)][stw 8(r10)][stw 4(r10)]` pair; (2) the destination buffer is **0x28 bytes** (frame 0x38 = 0x28 + linkage; 12B gives 0x20, 0x30 gives 0x40); (3) `sprintf` arg order was inverted by m2c (dst is the LOCAL, not arg0) and the varargs call stays unprototyped (want's `crclr cr1eq`) |
| `fn_8001E1D4` | 116B | the switch has a **third explicit case** (0x16 = 22) whose body is the same `v = 2` as the default.  With two cases + default, ngccc's decision tree pivots on 0x11 and the body is 3 insns short (104B); with 0x16 present the pivot is the median 0x13 and the dead `cmpwi r4,0x16` probe appears — want's exact tree |
| `fn_800A3D8C` | 156B | four decode fixes: element field is **+0xC** (m2c's `(s32 *)(base) + 0xC` is pointer arithmetic = +0x30); the guarded call passes the **tested value** as arg1 (`fn_8012701C(v, 3)`); `Mem_Free2` is **1-arg** (see src/fn_80009AD8.c); and the loop guard must be written against the loop variable (`i = 0; if (i < n)`, not `n > 0`) to get `cmpw r30,r0 / bge`.  Final word = **RTL plus-operand order**: `*(s32 *)(off + base + 0xC)` → `add r9,r29,r9`; `base + off + 0xC` → `add r9,r9,r29` (doc-51-adjacent lesson) |
| `fn_8011ECA0` | 160B | five fixes: the clear loop walks **-8 BYTES** (m2c's `s32*` decrement scaled by 4); the base is a **TWO-STATEMENT** symbol+offset (`p = lbl; p += 0x1D0;` emits the symbol's OWN lis/addi then a second addi — a single initialiser folds to one addi, 1 insn short); `AXRegisterCallback` takes the registered `fn_8011E8D0` address; the sound-mode flag is an **if/else with the `== 0` arm first** (that is what puts the value in the VOLATILE r0 and emits `li r0,1 / bne / li r0,0`; the reversed polarity mirrors it and the `v=1; if(…)v=0;` toggle pins `v` to a callee-saved reg, +8 frame); buffer 0x400 at r1+8 |
| `fn_800AF938` | 140B | derived-ctor init.  The m2c draft had dropped the base ctor's ARGUMENT — `fn_800AB0F0` really is `void *fn_800AB0F0(Unk_C8FEE62D *)` (src/fn_800AB0F0.c), and passing `arg0` is the WHOLE residual: with the single-arg prototype the shared 0 constant is materialised BEFORE the call (`mr r30,r3 / mr r29,r4 / li r28,0 / bl`); without it ngccc emits the identical `li r28,0` after the bl and parks at 94.3% looking like a scheduler coin.  Plus the 0x14 address store, the 12-byte struct copy at +0x60 (that is what emits `addi r10,r30,0x60`; three field stores are 136B) and the chained `fn_80126EAC(fn_80019D08(8))` |
| `fn_8003FB80` | 112B | leaf float-setter mirroring one value into base+0xD0 and base+0x88.  The three constants are real f32 externs (m2c used raw literal addresses) and the compares are `fcmpu`.  LEVER: the sub-object pointer must be a named `f32 *` indexed as `p[0xF]` — `*p` lets ngccc fold the whole thing into one `0x10C(r3)` displacement and the `addi r11,r3,0xD0` vanishes (104B); the indexed spelling keeps the base in a register and folds only `0x3c(r11)` |

Parked (best body + note in each draft):

| addr | best | why it stops |
|---|---|---|
| `fn_8009636C` | **88.0%** (22/25, was 12%) | field-init helper.  Fixed `fn_800145AC()` arity (no args), the u16 at 0x4, and the four BYTE stores at 0x18..0x1B.  Residual = the three one-use constants are emitted by want in REVERSE of their store order (`li 0 / li 2 / li 0xff` with stores 0x4,0x8,0x14) while ngccc ties `li` order to source order — every source order gives one or the other, never both.  8 flags tested |
| `fn_80129AFC` | **11.8%** (honest re-score; see the draft) | guard + two-call wrapper.  The old "44.12%" was a **positional artifact** of the m2c body's missing callee prototypes: an unprototyped `bl` emits `crclr cr1eq`, shifting the tail and scoring 15/34 by coincidence.  WANT HAS NO crclr, so that body can never be exact.  With real prototypes the correct body scores 4/34.  Residual: want keeps TWO copies of a2 (one staging for the call's r3, one surviving for `subf r31,r28,r4`) and speculates `li r3,0` between `cmplwi` and `ble`; ngccc coalesces the a2 ranges and sinks the constant (2 insns short) |

Reusable levers recorded (worth folding into a parking doc if this family is
hit again):
1. **symbol + offset: one statement or two is a real codegen choice.**
   `p = sym; p = (char*)p + K;` emits the symbol's own lis/addi PLUS a second
   addi (want's shape in fn_8011ECA0); the single-expression form folds into
   one lis/addi with the addend in the reloc.  This is the same axis as the
   doc-51 literal-vs-symbol lesson and it applies to *any* interior offset.
2. **A 12-byte object copy is a struct assignment.**  `*(T *)(dst) = *src;`
   reproduces GCC's `[0][8][4]` load/store rotation *and* its mixed
   `disp(base)`/`disp(ptr)` addressing; three field stores do not
   (fn_80236E70, fn_800AF938).
3. **A switch leaf whose body equals the default still shapes the tree.**
   Adding the explicit `case 0x16: v = 2;` moved the decision-tree pivot to
   the median and produced want's dead probe (fn_8001E1D4).
4. **The `lis` half disassembles SIGNED.**  `lis r3, -0x7fee` is
   0x8012_0000, not 0x8022_0000.  Misreading it as a 0x8022xxxx callback
   address cost a promote round-trip (2-byte DOL diff at 0x8011EDEB) before
   the registered `fn_8011E8D0` was recognised.  Always recompute
   `(u16)imm << 16`, do not "un-negate" by eye.
5. **A named pointer used as `p[K]` keeps its base register; `*p` does not.**
   `f32 *p = (f32 *)((char *)arg0 + 0xD0); p[0xF] = v;` emits a real
   `addi r11,r3,0xD0` plus `0x3c(r11)`; `*p = v;` folds into `0x10C(r3)` and
   loses two instructions (fn_8003FB80).  Mirror image of the fn_8003B9E0
   note where a pointer variable was needed so the address is NOT folded
   into a call.
6. **A call with NO argument setup is not proof of zero arity.**
   fn_800AF938 sat at 94.3% (2 words) because m2c had dropped the base
   ctor's argument: want's `bl` genuinely takes `arg0` in r3 already, so
   nothing in the disassembly *looks* like argument setup.  The tell is the
   promoted callee: check `src/fn_XXXXXXXX.c` for its real signature before
   accepting a zero-arg call, and note that the arity fix is only *visible*
   in the prologue schedule (the constant hoist), not in any argument move.
7. **Masked-EXACT hides wrong symbol CHOICE, not just displacements.**
   Both `fn_8011E8D0` and a bogus `fn_8021E18C + 0xD744` scored 40/40 masked
   (both are relocations); only the relink caught it.  For any promoted body
   whose arg is an address, prefer a REGISTERED symbol and re-promote.

| fn_801AC66C | 0x801AC66C | m2c |
| fn_801AC9CC | 0x801AC9CC | m2c |
| fn_801ACBC0 | 0x801ACBC0 | m2c |
| fn_801ACF84 | 0x801ACF84 | m2c |
| fn_801B23FC | 0x801B23FC | m2c |
| fn_801B4404 | 0x801B4404 | m2c |
| fn_801B7C80 | 0x801B7C80 | m2c |
| fn_801B99A8 | 0x801B99A8 | m2c |
| fn_801ADCE4 | 0x801ADCE4 | m2c |
| fn_801B8678 | 0x801B8678 | m2c |
| fn_8014E440 | 0x8014E440 | m2c |

## 2026-09-22 (small-draft sweep: 4 more EXACT promotions)

Follow-on: Two targeting facts learned this round:

* **The >=85% band is now 100% parked drafts.**  Re-scoring the whole pool and
  keeping drafts that carry no park note leaves NOTHING above 49.4%; every high
  scorer is one of the 1-word optimizer walls from earlier batches (1737 of
  2814 `src/wip` files contain "park").  Do not re-rank the pool by score and
  expect a free win — the productive territory is the **small** no-park drafts:
  207 of the 1,077 no-park drafts are <=180B, and those are 0-40% simply
  because nobody has decoded them yet.
* `tools/fix_call_arity.py` over the no-park pool finds nothing: a dropped
  argument is visible only in the *prologue schedule* (fn_800AF938), not in any
  argument move, so the arity tool cannot see it.

Promoted — all 4 verified by promote_wip's full relink (DOL BYTE-IDENTICAL):

| addr | size | what actually fixed it |
|---|---|---|
| `fn_8001EC60` | 80B | pure **argument passthrough thunk** (no body at all).  Recovered the 16-arg signature from BOTH ends: the callee `fn_8001EA14` (588B) reads r3-r10 + stack 0x58 (word), 0x5f (byte = u8 param 10), 0x63 (byte = u8 param 11), 0x64, 0x68 and f1/f2/f3, and every direct call site (0x800985F4, 0x8009BE24, ...) sets exactly r3-r10 + the five words at 8/0xc/0x10/0x14/0x18(r1) + f1,f2,f3.  So the body is one 16-argument call and the only instructions are the five incoming stack slots re-emitted into the outgoing arg area (slots 0x3c/0x40 read as bytes and widened back to words).  RESIDUAL/LEVER: `-fno-schedule-insns` — without it the body is byte-identical except that the pre-RA scheduler gives the a12/a13 copies r28/r29 instead of retail's r29/r28 (retail allocates those temps top-down, same as promoted fn_80131714 does); no source spelling reaches it |
| `fn_800F0740` | 76B | m2c had **mangled the first call's argument**: `fn_800F06A8(fn_800F0F84(1), fn_800F0F84(arg1, 1))`.  want is `s32 t = fn_800F0F84(arg0, 1); fn_800F06A8(t, fn_800F0F84(arg1, 1));` — 1 is the SECOND argument of both walker calls, and the first call's arg is arg0 (r3 is never reloaded: `bl` uses the incoming r3) |
| `fn_800F3A6C` | 72B | slot-release bit clearer over the .bss array `lbl_803CA080` (0x180B = four 0x60 slots) with mask `lbl_80301BB8`.  Three source details, all load-bearing (all other shapes 0-16%): the counter is a plain `i` tested at the BOTTOM — `do { ... } while (i < 4)` — which is what becomes `mtctr`/`bdnz` while BOTH the pointer IV (`p += 0x60`) and the index IV (`i++`) survive (the m2c `ctr`-goto form is 10.5%); the match arm **returns** rather than breaking; and the global is written **in place** (`lbl_80301BB8 &= ~(1 << i)`) — caching it in a local re-colours everything and loses the `slw`/`andc` pair |
| `fn_8012DF28` | 80B | hash-bucket chain lookup.  The `clrlwi/mulli/add.` sequence is **pointer arithmetic on a 12-byte struct** (`p + (arg0 & 0xFFF)`), not `(char *)p + (arg0 & 0xFFF) * 0xC` — the char* spelling is 72B/15% because the `add.`-folded null test disappears.  Second lever: the lookup must be a `for` (entry null test separate, `p = p->unk8` as the increment) so that GCC lays the `return p->unk4` block BETWEEN the two `return 0` blocks; the m2c `if (p != NULL) { while ... }` re-brackets it and is 15% |

Recipe additions for the small-draft sweep (all reusable):
1. `tools/dump.sh ADDR` prints want disasm + the comment-stripped draft in one
   shot; `tools/vs.py` (its `try_body(addr, body)`) scores a candidate body through the
   same ngccc flags as every other tool (masked compare, size report), so a
   decode can be probed without writing a draft file per iteration.
2. **A passthrough thunk has no body to find — find its signature instead.**
   Read the callee's prologue for its stack reads (the byte-in-slot offsets give
   you the u8 parameters) and one direct call site for the register/stack/FPR
   split, then write the single forwarding call.  Two independent sources must
   agree before the draft is worth promoting.
3. **`do { } while (cond-at-bottom)` is what produces `mtctr`+`bdnz`**, and it
   keeps a source with two induction variables (pointer + index) intact; a
   `for` over an indexed address silently drops one of them.
4. **Write globals in place.**  `g &= ~(1 << i)` matches; `s32 v = g; ...; g = v;`
   re-colours the function (this is the third time this file has recorded it).
| fn_8003FE18 | 0x8003FE18 | stub |
| fn_8003E6C8 | 0x8003E6C8 | stub |
| fn_801280E0 | 0x801280E0 | stub |
