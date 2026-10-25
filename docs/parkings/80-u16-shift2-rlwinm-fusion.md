# 80 — ngccc fuses `(u16)x << 2` into one `rlwinm rA,rS,2,0xe,0x1d`; the `clrlwi`+`slwi` split needs a 2-use u16

**Date:** 2026-10-02 · **Found on:** `fn_80079300` (356 B, 19.1% DIFF → **78.7% NEAR**;
the whole function matches except the loop-latch step) · **Applies to:** every want
whose disassembly contains `rlwinm rX,rX,2,0xe,0x1d`, and every m2c draft that
renders that instruction as `((x * 4) & 0x3FFFC)`.

## The rule (both halves)

**1. `rlwinm rA,rS,2,0xe,0x1d` IS `(u16)x << 2`, and it is the ONLY way ngccc
compiles it.** m2c decodes the mask as `& 0x3FFFC` and emits

```c
((1 << dim->w) * 4) & 0x3FFFC          /* WRONG */
```

which cc1 folds the other way — it pushes the `* 4` into the shift and emits
`li rX,4 / slw r3,rX,dim->w / rlwinm r3,r3,0,0xe,0x1d` (the `1` in a register is
gone). The correct spelling is a **narrowing cast on the shift's operand**:

```c
(u16)(1 << dim->w) << 2                 /* -> li one,1 ; slw ; rlwinm rX,rX,2,0xe,0x1d */
```

(`* 4`, `sizeof(u32)`, `u16`/`u32`/`s16` locals, `u32 *` pointer scaling and
`<< 2` are all the same expression to cc1 and all produce the same fused
`rlwinm`; verified with a 30-case `-S` probe, not by guessing.)

**2. The reverse never happens: there is no source spelling of a SINGLE-use
`(u16)x << 2` that yields `clrlwi rX,rX,0x10` + `slwi rY,rX,2`.** The
`(and x 0xFFFF)` and the `<<2` are always merged into the `rlwinm` by `combine`.
The only way to keep them apart is for the **u16 value to have two uses that
`cse` cannot merge** — then the AND is a real register and the shift is separate:

```c
u16 n = 1 << w;  return n * 4 + n;   /* -> li; slw; rlwinm 0,0,0,0xffff; slwi; add */
u16 n = 1 << w;  return n << 2;     /* -> li; slw; rlwinm 3,0,2,14,29   (fused) */
```

Corollary: a want that shows `slw; clrlwi …,0x10; slwi` is telling you the u16
count has a **second, instruction-free consumer** that is not the visible shift
— go looking for it rather than re-spelling the same expression. In the DOL that
triple occurs only twice (`fn_80079300` tail and `fn_8007A108`), and neither
function is matched, so there is no in-tree example of the winning source yet.

## The other half of `fn_80079300`'s jump (both are reusable)

* **`// FLAG: -Os` in an m2c draft is often just wrong.** This body wants plain
  `-O2 -G0`: re-measured `-Os` 65.5% / `-O2` 78.7% / `-O1` 16.9%. Re-measure the
  flag on the *rewritten* body before accepting the draft's guess.
* **A bare `(T *)0xADDR` global loses the HI16/LO16 pair.** `*(Arena **)&lbl_XXX`
  (address-of a `SYMBOL_REF`) gives retail's
  `lis rX,%ha / lwz r3,%l(rX) / lwz r4,0x118(r3)` with the HI16 CSE'd across
  every later use; the numeric literal folds to `lis`+`ori` and, once the value is
  also indexed, splits into **two** base registers. Same rule as doc 51, but the
  load-through-a-pointer case (not just `mgr = lbl_...`) is the one that bites
  here.
* **`void memcpy();` must stay unprototyped** when the want has
  `crclr cr1eq` before the call (recipes §4n item 21). Every other callee in this
  function must stay *prototyped* — a mixed body is exactly right here and got
  both the three `crclr`s and the four crclr-free calls simultaneously.

## Residual of `fn_80079300` (honest)

1. The loop-latch step: want `slw r0,r28,r0 / clrlwi r0,r0,0x10 / slwi r9,r0,2 /
   mr r0,r9 / subf r30,r9,r30 / add r29,r29,r0`; got `slw / rlwinm / subf / add`.
   Object is 2 words (8 B) short and the 15 words after the latch are shifted by
   that — that single residual is the whole 78.7 → 100 gap.
2. The 2nd `memcpy`'s argument stores: want `mr r4,r30` then `mr r3,r29`, got the
   reverse. Calls 1 and 3 already agree, so it is a `sched` free-register
   ordering artifact, not an argument-spelling problem — do not churn the memcpy
   argument order chasing it.