# Issue 32 — List-walker saved-register role rotation + prologue scratch-store idiom

**Status: PARKED (2026-08-23) — 5 members, one shared compiler-behavior
root cause in two flavors. Flavor A partially cracked 2026-09-16; a THIRD
flavor (memory-homed walkers) added 2026-09-18 — see the dated sections at the
end of this doc. Structure/CFG/calls verified correct in every member;
only register homing differs. Revisit if a future function cracks either flavor.**

**2026-10-08: FLAVOR A GENERALLY CRACKED — the HARD `__asm__("rN")` pin on the
walker (2 members promoted, one with two pins). See the last section; the
"single pins resist" notes below were written against soft `register` hints and
must be re-measured with the hard pin before a member is considered parked.**

## Flavor A — role-rotation cascade (multi-value cyclic permutation)

In FindFirst/FindNext-style list-walker script commands, GCC homes SEVERAL
independent values (array base, hash, threshold/count, walker pointers) into
callee-saved registers that are CYCLICALLY PERMUTED vs the game:

- fn_80159078 `ScriptAnySkaterTotalScoreAtLeast` (50.0%): want `{hash=r29,
  thr=r28, arrBase=r26}` vs got `{r28, r26, r29}`; want also keeps TWO separate
  `[lis; li r3,1]` hit blocks where GCC merges one.
- fn_80158C2C `ScriptEliminateLastPlacePlayer` (60.5%): count/min/max land in a
  rotated r26/r27/r28 vs want; walkers shift by one reg.
- fn_80158EC8 `ScriptOnlyOnePlayerLeft` (64.8%): qA/qB/pB bases homed r29/r9/r30
  vs want r10/r26/r30-ish; GCC drops the `mr r27,r30` pA copy via coalescing.
- (adjacent single-swap member: fn_8015AE3C 78.6% — zero-reg↔ret2 r28↔r31 swap;
  same family, one axis.)

### What was tried (all resisted)
- Full block-scope pin sets → over-constrain: alloc collapses to ~15%, or frame
  balloons to stmw-r19/0x90 states.
- Single pins (var→want-reg): gain +1 insn then rotate OTHER roles further.
- All declaration-order permutations (no-op), statement-order splits around the
  call (16-combo brute force on C2C init placement: 59.9–60.5% band).
- Schedule-flag matrix (`-fno-schedule-insns/-insns2/-sched-spec/
  -interblock/-gcse`, pairs): neutral.
- goto/done single-tail vs inline-tail-per-hit rewrites, early-return tail
  reorder, two-web variable births to force separate webs.
- NOTE: the pA/pB asm barriers in these drafts are LOAD-BEARING — removing them
  collapses EC8-class bodies to ~16%. Keep them when retrying.

### Retry hints
A pin that lands ONE value correctly while leaving the allocator freedom for the
rest is the only lever that ever gained ground (EC8 var_r29 pin). A future crack
likely needs either (a) a way to pin a value WITHOUT forcing its web to be born
early, or (b) discovering that the game's source ordered declarations so each
role's FIRST USE falls in an order GCC preserves.

## Flavor B — prologue scratch-store idiom

Want initializes a stack out-param struct through a scratch register and keeps a saved-register copy: the frame address at offset 8 is materialized into r9 as the scratch, copied from r9 into saved register r24, then one word from r11 is stored via the scratch at offset 8 and another word from r0 is stored via the scratch at offset 4.

Members:
- fn_80159A48 `ScriptInSecondToLastPlace` (~11–29.6% DIFF): additionally want
  keeps THREE unmerged `[lis; li r3,0; b tail]` fail blocks; GCC merges ours.
- (fn_80159894 `ScriptInLastPlace` was listed here originally (~18% DIFF); it
  was re-scoped to **doc 36** (enumerator fresh-addi-vs-mr) where it now sits
  at ~97% with that doc's signature — do not double-track it.)

ngccc 3.9.3 ALWAYS folds these stores to `stw disp(r24)` displacement form or
rewrites their base to the saved reg — no source shape reproduces
store-via-scratch-then-copy. Distinct from solved issue 03 (that was a
table-dispatch temp fixed by an r0-wedge pin assigned first; here the base is
frame-derived `r1+N`, and pins on r9/r24/r25 swap rather than stick).

### What was tried (all resisted)
psp named struct var + r24/r25/r9/r11 register pins, `"+r"` asm barriers,
volatile-cast store serialization, inline-asm address materialization (ngcas
rejects `%0` forms), multi-return fail blocks with per-path restore, if/else
chain, ternary-init, `-fforce-addr` (not accepted), `-fno-gcse`,
`-fno-schedule-insns(+2/-spec/-interblock)` — best 29.6% (pins +
-fno-schedule-insns).

### Retry hints
If any future function shows want storing via a frame-derived scratch, try:
`Sp8 * volatile psp = ...` decl order variants; declaring the struct BEFORE the
first callee call vs after; and check whether issue-03's r0-wedge recipe
transfers when the copy target happens to be r0.

## additions (2026-08-23)

Two more members from script-zone batch fn_80173C5C–fn_8017792C:

- fn_8017755C (180B, 68.9%): everything SEMANTIC matches (3-arg sig
  `(unused, s32, ptr)`, u16 lhz loads, `%20`, lwzx form); residual is ONE
  cyclic role rotation cnt/idx/base = want r10/r9/r11 vs got r9/r11/r10.
  Smallest member yet — best first target for a future crack attempt.
- fn_80175690 `ScriptChangeLevel` (724B, ~12%): structurally complete but
  WHOLE-function callee-saved role rotation resists every shape/pin/flag;
  additionally want recomputes `&fr.sp58` in-loop where ngccc hoists it into
  an 11th saved reg. Also listed under doc-15.

Note for retry attempts: recipe §6y-124's scratch-web pins (r9/r11 register
vars) cracked a DIFFERENT coloring family this same batch (fn_801742C8,
EXACT) — worth one try here before concluding, but Flavor A members above
already resisted equivalent pins.

 adjacent member (2026-08-24): fn_80163E3C `ScriptSwapObjectModels`
(1364B, ~25%) — swap-section `[base,+4,+8]` parallel derivation compiles as
chained `[+8,-4]` in every expression grouping (3 variants normalize
byte-identically); mid-function null-guards invert vs want's two
beq-to-shared-ret0; scheduler hoists the loop-2 table-base lis/addi into the
guard region where want keeps it inside the fill block. Register pins cracked
the saved-reg map (temp_r28→r28 keystone) — see the draft header for the full
resist list before retrying.

## addition (2026-08-24, skater-state zone)

- fn_8017B7EC (472B, 62.2%): guard region CRACKED (duplicated tests +
  mid-function shared fail block; case-A double plain returns, case-B v=4
  shadow li). Residual is flavor-A cyclic role rotation on the walker webs —
  resists pins/barriers/decl orders like the members.
- Adjacent (role-rotation COMPONENT, primary park elsewhere): fn_8017BB28
  (1488B, 51.6% — rotation across 8 webs + want `lwzu` walker fusion vs
  ngccc rotated do-while), fn_8017C2CC (1576B, 34.3% — rotation plus
  doc-28 residue, memory-reload compares removed the CR machinery).

 member (2026-08-25): fn_80220C0C `ScriptNetworkFlagSomething`
(188B, 61.7%) — want homes ctx→r31 / label→r28 / base-scratch→r30 /
base-home→r29 with the label materialized as the FIRST instruction; GCC
insists on swapped ctx/base-home slots in every decl-order and
creation-order mirroring tried; a third pin collapsed allocation entirely
(brittle-allocator signature). stwx byte-IV indexed store and exact frame
already reproduced.

**2026-09-09 — partial breakthrough (61.7% → 95.7%, 45/47):** the role
rotation was NOT a rotation — the m2c body simply needed
`temp_r31 = lbl_80305F9C;` as the FIRST statement (before the sp8 stores);
that fixes the whole callee-saved map (ctx→r31 / label→r28 /
base-scratch→r30 / base-home→r29) with no pins. The frame is reproduced by
`s64 sp8; volatile double mid; s32 sp18;` (frame 0x30, stmw r28 — the
volatile dummy supplies want's 8-byte slot at 0x10). Residual = 2 words:
GCC places the volatile pad at r1+0x8 (sp8 lands at 0x10; want has sp8 at
0x8, pad at 0x10), and the back-edge call-arg then reuses the r29 home
(`mr r4,r29`) where want remats `addi r4,r1,8`. The pad slot tracks code
creation order — a non-volatile `s64 mid` + `"m"`-constraint asm placed at
the start/end/middle each either keeps the pad at 0x8 or flips call-arg
scheduling (87.2%/43/47 best); 16-byte struct/array sp8 collapses the
allocation (176B, r28/r29 dropped). No asm in the parked body. Best body:
`src/wip/fn_80220C0C.c`.

## 2026-09-16 — Flavor A cracked (1 member): the `mr` is a LIVE-RANGE EXTENSION

`fn_800A3528` (172B, doubly-linked-list unlink walker) promoted to EXACT.  Want
keeps a copy - `lwz r9,0x3c(r3) / lwz r0,4(r9) / mr r31,r9 / cmpwi r0,-1` - where
the draft's `p = arg0->unk0x3C; v = p;` lets ngccc coalesce the copy away (load
straight into r31).  Hoisting the FIELD READ into its own local *before* the copy

    p = *(T **)&arg0->unk0x3C;
    t = p->unk0x4;          /* the read comes first ...                */
    v = p;                  /* ... so p stays live across this copy    */
    if (t == -1) v = NULL;

keeps the source value live across the copy and the `mr` survives.  This is a
**live-range extension, not a register pin** - no `__asm__` required.  The loop
body must also be written `while (v != NULL) { ... }`: the m2c
`loop_6: if (v != NULL) { ...; goto loop_6; }` shape makes ngccc duplicate the
guard (an inline `cmpwi` after the preheader plus the rotated one at the bottom),
while the plain `while` makes both preheader paths jump to the single rotated
guard, which is retail's layout.Both levers are needed: `if/else` preheader 90.7 %, while(1)+goto 9.3 %.

## 2026-09-18 — Flavor C (new): MEMORY-HOMED walkers (stack slots, not registers)

A distinct flavor found on the `0x8006A5F0 / fn_8006A67C / fn_8006A6F0`
for-each-link family (all random-sweep picks, all previously ~17%): want keeps
`arg0` in one callee-saved register and puts BOTH walker values in *stack slots*
`8(r1)` / `0x10(r1)` — 8 bytes apart, with the current link reloaded before AND
after each callback. The m2c draft's plain `void *sp8, *sp10;` locals make ngccc
allocate r30/r31 and shrink the frame (0x10 instead of want's 0x20), which reads
as an unbounded regalloc wall.

**The frame half is source-reachable (found + verified this session):**

* `void *volatile sp8; void *volatile sp10;` — the `volatile` must qualify the
  **pointer** (`void *volatile x`). `volatile void *x` (pointer-to-*volatile*)
  is silently useless: ngccc drops the stores and keeps everything in registers,
  which is why earlier volatile attempts on this family showed no movement.
* a single local array used at two non-adjacent indices —
  `void *sp8[4]; sp8[0] = n; sp8[2] = p;` — same 16-byte local area, and arrays
  cannot live in registers. This spelling additionally reproduces want's
  *pre-block schedule* (`cmpw` emitted before the two slot stores); the
  volatile-pointer spelling emits store/cmpw/store one word differently.
* `sp8[2]` is a dead store (want never reloads the head slot) — it survives
  because the array is memory, so the two-extra-slot frame materialises.

Result on fn_8006A67C: 17.2 % -> **65.5 %** size-exact, frame-exact
(`src/wip/fn_8006A67C.c`); sibling fn_8006A5F0 reaches 71.4 % with the same
recipe and its first miss at the same word.

**SOLVED 2026-09-28 — fn_8006A5F0 is now byte-exact (100%).** fn_8006A67C
remains parked at 65.5%; the two finally diverged on two points, and BOTH are
load-bearing, so the recipe needs both:

1. **The loop condition must RE-READ `*arg0` from memory** (retail's latch
   `lwz r0,0(r31)`), not reuse a staged value.
2. **Wrap the loop in a POSITIVE guard** — `if (sp8[0] != *arg0) { do {…} while
   (…); }` — instead of an early `return`.

Plus the two already documented above, and — the big one — **delete every
register pin and every `volatile`**. All four pins (a0/nd/nx/pg) had to go:
the pins were what kept the pre-header `cmpw`/`stw` transposition alive. With
them removed GCC picks r30 for the `lis -0x7fd0` anchor by itself. The init
is a single ternary `sp8[0] = *arg0 != 0 ? *(void **)((char *)*arg0 + 4) : 0;`
in ONE plain (non-volatile) `void *sp8[4]` array.

Sourcing the twin is the other lesson: the promoted sibling
`src/fn_8006A67C.c` is the same family, and the earlier "prologue twin" the
scanner offered (0x800626E8) was a FALSE twin. `tools/near_twin_scan.py
--addr 0x8006A5F0` found nothing; scanning the **DOL for a distinctive 4-word
BODY shape** instead (`cmpw,stw,stw,beq` — 15 hits, two in this zone) found
0x8006A67C. Prefer a body-shape scan over a prologue-shape scan.

**Residual on fn_8006A67C (still parked at 65.5%): one pure colour swap of `p`,**
want `p` in r9 (pre-block) / r0 (loop) and `n` in r0 / r11, ngccc `p` in r11 both
blocks and `n` in r0 both blocks. Every other word matches (loads, stores, both
compares, both branch operands, all slot offsets). Neutral (byte-identical
bodies): declaration and statement order of p/n, the volatile vs array
spelling, typed walkers (`void*`/`void**`/`struct L*`), ternary n-init,
`aligned(8)` slots, a `void *zero_p` separator, dead stores to the unused
slots, and the flag set `-O1/-Os/-O3/-fno-schedule-insns{,2}/`
`-fno-caller-saves/-fno-expensive-optimizations/-fomit-frame-pointer`. It has
NOT yet had the memory re-read or the positive guard tried — those are the two
levers that took fn_8006A5F0 the rest of the way.
A future crack needs a lever that changes which of the two reloaded-head / next
webs gets the lower colour without disturbing the solved frame.

## 2026-09-18 (b) — a "role-rotation coin" that was neither: a raw ADDRESS LITERAL (1 member unparked)

`fn_80120924` (168B) was parked on sight as *"one allocator coin over three
callee-saved registers: want r31=&sym, r29=base copy, r30=0x80000000 vs got
r30=&sym, r29=start tick, r31=0x80000000; all body levers tie at 71.4 %"*.  The
role set was not a coin at all: the tick loop's bound was written as the raw
literal `*(u32 *)0x800000F8 >> 4`, which ngccc materialises as `lis` + `ori` +
`lwz 0(rX)` — **two words more than retail's folded `lis r11,-0x8000` +
`lwz r0,0xf8(r11)`**.  Those two words are exactly what pushed the base register
out of r31, and removing them (by referencing the absolute linker symbol
`lbl_800000F8`, see the doc-51 addendum) makes every register land in retail's
slot with the body otherwise untouched: 71.4 % → **100 %, promoted**.

**Triage rule for this family:** before accepting any role-rotation / colour-swap
park, diff the *word count* between want and got and look for a
`lis rX,-0x8000`-style **folded** address in want whose draft spelling is a bare
literal (`*(T *)0xADDR`).  Two extra address-materialisation words ahead of the
loop change the live ranges of every induction value and read as an
unfalsifiable allocator decision.  This is why the old note's "all body levers
tie" observation was correct but irrelevant — the lever was in the *addressing*,
not in the body.

## 2026-10-08 — Flavor A cracked: the HARD asm pin on the walker (2 promoted)

**fn_8018D7BC** (276B, `qb` flag walker) sat at **88.41 %** with the note "needs a
new allocator-ordering idea".  The whole residual was the callee-saved role map.
Adding ONE local register pin on the *walking pointer* —

    register CStruct *var_r30 __asm__("r30");

— with the assignment left in the body (`var_r30 = fn_80127358(...)`) is
88.41 → **100 %**.  Promoted; `cmp` + sha1 + `ok` clean.

**fn_8012E0AC** (188B, hash-table node allocator) was parked at **66.0 %**
("pure saved-reg rotation; pins tried, ~14 flag combos, many shapes").  Retail
homes `arg1->r29 / entry->r31 / node->r30`; every unpinned shape homes
`arg1->r30 / entry->r29 / node->r31`.  Here **two** pins are needed and both are
free (the function already saves r22..r31, so neither pin touches the frame):

    register u8 *var_r29 __asm__("r29");        /* + var_r29 = arg1;  */
    register CStruct *var_r30 __asm__("r30");   /* the walker/node web */

Measured: both → **100 %**; r30-only → 76.60 % (11/47); r29-only → 78.72 %
(10/47).  Promoted; `cmp` + sha1 + `ok` clean.

### Why the earlier "pins resist" notes were wrong

* They were written against **soft** `register` hints (`register T *p;` with no
  `__asm__`) — ngccc is free to ignore those, and does.
* Where a hard pin *was* tried, it was placed on the wrong role (the short-lived
  temp, whose pin forces the value's web to be born early and rotates everything
  else).  Pin the **walker / long-lived pointer**, and pin the *second* web only
  if the map still reads rotated afterwards.
* Constraint from the C89 front end: the pin must be a **local declaration**
  (`register T *v __asm__("r30");` inside the body, followed by `v = expr;`); a
  `register` parameter is a `parse error before '__asm__'`.

### Retry order for the remaining members

1. Score the current draft (the pool file may be stale) and list which webs are
   rotated from the disassembly (`want rX / got rY` per web).
2. Add ONE hard pin on the longest-lived pointer web, to its *want* register.
3. Re-measure; then try adding a second pin on the next-worst web.
4. Only if the map is right and words still differ, go back to body shapes —
   check the doc-32 §2026-09-18(b) rule first (an unfolded address literal can
   masquerade as a rotation for two extra words).

Flavor A is now a *solved* family: the pin is a legitimate house lever
(`docs/parkings/`, ~657 promoted files use the same idiom).
