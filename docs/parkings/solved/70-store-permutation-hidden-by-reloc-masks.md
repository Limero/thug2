# 70 — a run of global stores: `100%` masked, wrong linked DOL (base-register pairing)

**Status: SOLVED 2026-09-20 — `fn_800231C4` 25.0 % → 100 % AND DOL byte-identical,
promoted.** Also a process fix: the score alone is not sufficient evidence for
this shape — verify with `tools/reloc_diff.py` (or the promote step's full-DOL
compare) before believing it.

## The shape

A run of independent stores to distinct globals, all with the same value:

```c
lbl_80300360 = arg4;
lbl_80362CB0 = 1;
lbl_80362CB4 = 1;
lbl_80362CB8 = 1;
lbl_80362CBC = 1;
fn_80022A34(arg0, arg1, arg2, arg3, arg5);
```

Every one of those stores compiles to `stw r0, SYM@l(rN)`: the displacement
field carries a relocation (`R_PPC_ADDR16_LO`). The masked scorer blanks that
field, so **all 24 statement permutations score 22/22 = 100 %** — while the real
object differs in *which base register each symbol gets*: with the ascending source order both sides agree on the address materialisation (r11 for 0x80362CB0, r10 for 0x80362CB4, r30 for 0x80362CB8, r9 for 0x80362CBC) and on the store stream pairing each zero store with its matching base plus the interleaved register copy. But with the wrong source order (0x2CB0, 0x2CBC, 0x2CB4, 0x2CB8 — the first spelling tried) the same 100% masked score hid a base-register swap: the build assigned r10 to 0x80362CBC, r30 to 0x80362CB4 and r9 to 0x80362CB8, pairing r9 with the wrong symbol where want pairs it with 0x2CBC and likewise swapping the r30/r10 pairings.

The promote step caught it (`3 differing bytes`, first at the `stw` offsets) and
reverted the whole batch; `tools/test_wip_drafts.py --addr 0x800231C4` said
`EXACT m2c (88B)` for **all four** orderings.

## What actually decides it

Two separate mechanisms, both driven by the **source statement order**:

1. **Base-register assignment follows source order.** ngccc materialises the
   four addresses in the order the statements are written, and hands out the
   base registers in that order: statement 1 → `r11`, 2 → `r10`, 3 → `r30`,
   4 → `r9` (here; the last one is the one that gets re-used/clobbered first).
   So to match want's pairing you must write the stores in the order that
   corresponds to want's registers. In this function that is **ascending
   address order** (`0x2CB0, 0x2CB4, 0x2CB8, 0x2CBC`) — verified by testing the
   descending order, which simply followed *its* source order
   (`r11→0x2CBC, r10→0x2CB8, r30→0x2CB4, r9→0x2CB0`).
2. **The store order in the instruction stream is then a scheduler
   permutation**: the *last* source statement's store is hoisted to position 2
   (right after the shared `li r0,1`), the rest keep their relative order. For
   the ascending source this reproduces want exactly: the 0x2CB0 store through r11 first, then the 0x2CBC store through r9, the register copy, and the 0x2CB4 and 0x2CB8 stores through r10 and r30.
   Descending source order gave the mirror stream (0x2CBC through r11, 0x2CB0 through r9, the copy, 0x2CB8 through r10, 0x2CB4 through r30) — so the stream order is a permutation of
   whatever was written, never a re-sort by address.

## Recipe

- Any function whose body is "N stores of the same value to N globals" must be
  validated with `tools/reloc_diff.py 0xADDR body.c`: it prints the reloc SYMBOL
  behind each got instruction, so a swapped pair is visible as
  `stw r0, 0(r9) [lbl_80362CB8@2:4]` against want's `stw r0, 0x2cbc(r9)`.
- To fix, permute the *source statements* so the base registers land on want's
  symbols; the ascending-address spelling is a good first guess (compilers emit
  address materialisation in address order when the source does not force
  anything else) and was correct here.
- `tools/test_wip_drafts.py` reporting `EXACT` is NOT evidence for this shape.
  Neither is `tools/br_targets.py` (no branches are involved). The full-DOL
  compare in `tools/promote_wip.py` is the only end-to-end check.

## Companion fixes in the same function (score 25 % → 100 %)

- **Index-shifted parameter list** (doc [52](52-m2c-spurious-call-args.md)):
  m2c's `arg4` was the *fourth machine argument* (`r6`), so the draft stored
  `r6` into `lbl_80300360`; want stores `r7` (the fifth). Realising this also
  fixes the call: want's `mr r7,r8` passes the *sixth* incoming value as the
  call's fifth argument.
- **Phantom label arguments** (doc 52 §2): `fn_80022A34(arg5, 0x80360000,
  0x80360000)` — want does not touch `r3`-`r6` before the `bl`, so those are the
  first four parameters and the two constants (2 words each, `lis`+`addi`) are
  noise; the draft was 96B vs want's 88B.

---

## Addendum 2026-09-20 — the same permutation, but VISIBLE (`fn_80204684`, 64.9 % parked)

`fn_80204684` is a 15-store field-init whose stores all go through a
**parameter** (`arg0`), so no displacement carries a relocation and the masked
score *does* show the order. Two useful facts fall out:

1. Copying want's disassembly order into the source is **not** the answer. With
   the source written in want's own order, sched2 re-emits
   `C4 C8 A8 30 BC 34 20 28 2C AC B4 B8 C0` where want has
   `BC 34 C4 C8 20 28 2C A8 AC B4 B8 C0 30` — it hoists the four stores whose
   operands become ready first in the RTS: both `QB_*` constants (ready after
   their `ori`), the `f0` store fed by the `lfs`, and the **last** statement's
   store (`0x30`), ahead of the rest. Every non-store instruction matches
   exactly (64.9 %, size- and frame-exact).
2. Feeding got's own output order back as the source does not converge: 16.2 %.
   Nor do a readiness-sorted order (21.6 %), an operands-ready-last order
   (16.2 %), or two positional-inverse guesses (21.6 %). The m2c/most-likely
   descending order is 45.9 %.

So for parameter-based store runs the doc-70 hazard has a mirror image: the
reloc masks are silent here, but the *permutation itself* is baked in by the
pre-RA/RA+post-RA scheduler, and inverting it needs the real source order, not
enumeration. Two other real defects in the same draft were worth fixing on the
way (both doc-53-family retypes): fields `0xA8`/`0xBC` are `f32` (the shared
Unk_ struct says `s32`, which emits an `fctiwz` and shrinks the frame), and the
whole `lis`/`ori` setup order then lines up.

Closest parked members of this visible-permutation class: `fn_80204684` (64.9),
`fn_8003FF04` (91.7, 2-word arg-setup order) — the pattern to recognise is
"every instruction matches except a slice of independent stores".

## Addendum 2026-09-24 — REVERSED pair of global zero-stores, read off `.rela.text` (`fn_8000AC98` PROMOTED)

`fn_8000AC98` (760 B Okumura LZSS encoder) scored masked-EXACT for a long time
while every promote attempt was reverted by the linked-DOL `cmp`. The whole
residue was **one instruction**: `0x8000ACB8` wanted `stw r30,-0x1c0(r11)` and
got `-0x1c4(r11)` — i.e. the two same-page global zero-inits were swapped:

```c
/* parked body (emits PFE3C first) */     /* want's reloc order */
lbl_802FFE40 = 0;   /* reloc +0x22 */     source:  lbl_802FFE3C = 0;
lbl_802FFE3C = 0;   /* reloc +0x32 */              lbl_802FFE40 = 0;
lbl_802FFE44 = 0;   /* reloc +0x3a */              lbl_802FFE44 = 0;
```

ngccc emits this **pair** in reverse source order, so writing `PFE3C` first
then `PFE40` makes the object's reloc slots match retail's exactly and the
function links byte-identical. Two transferable practices:

1. **Read the object's `.rela.text` order, not the masked score.**
   `readelf -r <obj>` lists ADDR16_LO relocs in emission order; for a store
   whose displacement carries the symbol (`stw rN,SYM@l(rB)`) the reloc order
   *is* the store order, and the reloc masks hide it completely.
   (`objcopy --only-section=.text` fails on these ProDG objects —
   `Unable to recognise the architecture` — so `readelf -r` is the way in.)
2. **When two same-page symbol stores are the only defect, try the swapped
   statement order before anything else.** It is a one-line edit with a
   deterministic answer, and a single-address promote settles it in one build.

Corollary for triage: a masked-EXACT draft whose header already says "masked
EXACT but the link differs" should be checked for a *pair* of same-page
symbol accesses (stores or loads) before being written off as doc-50 linker
relaxation or a folded-address (`*(f32 *)(base - K)`) artifact.
