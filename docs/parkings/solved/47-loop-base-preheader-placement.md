# 47 — Loop-base pointer placed AFTER the entry guard (preheader scheduling)

**Status: CLOSED (2026-09-02) — all members solved with the doc-49 in-body
base lesson.** First catalogued on `fn_8000C6A0` (156B, a state/motor mutator
that zero-fills a byte buffer then calls `PADControlMotor`). Doc kept for the
recipe + the historical dead ends.

This is a *placement* variant of the branchy-loop base-hoist documented in
AGENTS.md recipe 232 (fn_800AE250's `base54`): the divergence was whether the
hoisted base lands relative to the **entry guard**, independent of loop
shape.

## The shape (as originally seen)

Want initialises the index to zero, runs the guard compare of the index against the count in r0 with a branch-to-skip on greater-or-equal, and only AFTER the guard materialises the base as self plus 0x60, zeroes a second register, and performs the indexed byte zero-store before entering the loop body. Got (every source form tried before the fix) instead materialises the base before the guard, so the index init is followed by the base computation and only then the guard compare and skip branch.

Same byte count in both (the words reorder within the preheader), so the
functions were **size-exact but word-short** — real instruction-order
differences GCC 2.95 refused to emit in the retail order from the naive
source forms.

## The fix (2026-09-02, generalized doc-49/F9C4 lesson)

The retail placement is reproduced by expressing the base/walker as a NAMED
pointer **derived from the loop index** and declared as the **first
statement(s) of the for-body** — NOT as a pre-loop local and NOT in the
for-header. ngccc then hoists/strength-reduces it into want's slot (once,
below the entry guard). Same lesson, three shapes:

- **`fn_8000C6A0`** — base+index zero-store: `for (i = 0; i < count; i++) {
  char *b = self + 0x60; b[i] = 0; }` → the `addi r11,r31,0x60` lands at
  want's below-guard slot with the per-iteration count reload.
  **Promoted EXACT (src/fn_8000C6A0.c, DOL byte-identical).**
- **`fn_8000C938`** — TWO bases: both named and declared in-body
  (`char *b1 = self + 0x60;` then the zero value as a variable
  `char z = 0;` then `char *b2 = self + 0xa0;`) → `addi r8` / `li r11` /
  `addi r10` in want's exact preheader order. **EXACT 37/37 in wip, no
  flags.** (Micro-lever: `z` between the two base decls orders the `li`
  between the two `addi`s; a literal `b1[i] = 0` puts it last. Also the
  tail call MUST have its real prototype — an implicit int declaration makes
  ngccc emit a spurious `crclr cr1eq` → 152B vs 148B.)
- **`fn_8000FA70`** — walker (stepping pointer): `for (i = 0; i < n; i++) {
  s32 *p = (s32 *)(self + 8 + 4 * i); if (*(p - 1) == key) return *p; }`
  → ngccc strength-reduces the affine address into the walking pointer with
  the init below the guard, AND emits the guard-into-latch rotation want has
  (the one shape that had resisted every for-header/while/do-while form).
  **EXACT 17/17 in wip, no flags.**
- **`fn_800394CC`** — LOADED base (found during the close-out sweep): the
  base is `*(self+0x8) + 0x508`, so split it — the memory LOAD stays a
  pre-loop temp (`char *p0 = *(char **)(arg0+0x8);`, want loads it first
  anyway before its null guard), and the pure `+0x508` addi is declared
  in-body (`f32 *arr = (f32 *)(p0 + 0x508);` first stmt of the for-body) →
  the addi lands below the guard. (The load itself must NOT be in-body:
  ngccc would reload it per iteration past the in-loop store.)
  **EXACT 20/20 in wip, no flags.**
- **`fn_80032610`** (found in the follow-up sweep, was parked 2026-09-02 at
  30/34 under "doc-15 scheduling") — element-clear loop with an in-loop
  vtable CALL (array at self+0x40, count at self+0x58): same walker-init
  placement wall. Winning variant = the ELEMENT-INDEXED in-body base
  (`s32 *arr = (s32 *)((char *)arg0 + 0x40); ... arr[i] ...`) — ngccc
  strength-reduces arr[i] into want's pointer-walker in r31 while self
  stays in r29 (live for the post-loop count clear), surviving the call.
  **EXACT 34/34 in wip, no flags.** IMPORTANT counter-example: the
  FA70-style AFFINE in-body form (`s32 *p = arg0 + 0x40 + 4*i`) regresses
  to 22/34 — with self live after the loop ngccc decomposes it as
  self + offset-walker (`li r30,0x40; lwzx r11,r30,r31`) instead of want's
  pointer-walker, cascading the regalloc. Rule: when the base object is
  live past the loop (or a call is in the body), prefer the const-base +
  `arr[i]` element form over the affine walker form.

Recipe summary: base pointer expressions must live **inside the loop body**
(index-derived or pure-offset over a pre-loop temp), never hoisted into a
pre-loop local by hand. If the base involves a memory LOAD, keep the load
pre-loop (it lands at want's position anyway) and declare only the
address-arithmetic in-body.

## Historical members / scale (for the record)

- **fn_8000C6A0** (156B) — mutation of a PAD motor command object:
  zero-fill + `PADControlMotor(chan, 0)` gated by (`unkc8 == 0 &
  unkdc == 2 & (unkcc & 2)`). SOLVED → promoted.
- **fn_8000F9C4** (0x90) — array remove-by-value on a `void**` at self+4
  (count at self+0xc4) + optional virtual dispatch. Listed here 08-30 at
  24/36, but its "base" was actually RE-materialized in-body by retail (not
  a below-guard hoist) — solved via the F9C4-specific byte-biv recipe
  (`k += 4` + named in-loop base + `-fno-gcse`), EXACT 36/36 in wip. See
  docs/parkings/solved/49 §2026-09-02.
- **fn_8000C938** (0x94) — state-gated double-buffer zero + subsystem call
  (family twin of C6A0). SOLVED → EXACT in wip (above).
- **fn_8000FA70** (0x44) — pool lookup sibling of F9C4. SOLVED → EXACT in
  wip (above). Note this one also carried want's guard-into-latch loop
  rotation, which the in-body index-derived form reproduces for free.
- **fn_800394CC** (0x50) — find-first-float-array-index over
  `(*(self+0x8)) + 0x508`; parked 2026-09-01 at 17/20, header referenced
  this doc. SOLVED during the close-out (loaded-base split variant) →
  EXACT in wip (above).

## Pre-fix history (dead ends — do not re-grind)

- The 2026-08-30 recipe-99 / asm-barrier / volatile route does NOT fix the
  placement on the naive shapes: memory clobbers pin order, not values, so
  barriers cannot stop ngccc's LICM of an *address* — but this was the wrong
  target. The real lever is the in-body index-derived declaration above, not
  a barrier.
- FA70's for-header `p = self+8; p++` and byte-biv `arr + k` (F9C4 recipe)
  forms collapse (13/17 and 5.9% respectively) — the affine in-body
  declaration is the only shape that triggers ngccc's below-guard placement.
- The C6A0 `&2`-flag materialization requirement (`flag = 1; if (!(cc & 2))
  flag = 0;`) remains real for the C6A0/C938 gate (without it the whole
  block layout shifts) — that is a separate bool-materialization lever
  (AGENTS §4p-7 family), not the doc-47 placement.
