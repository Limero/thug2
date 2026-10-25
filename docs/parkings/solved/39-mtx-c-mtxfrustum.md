# 39 — mtx: C_MTXFrustum operand-order vs register-allocation coin-flip

**Status: SOLVED.** All **21 of 21 mtx functions are now byte-exact from C**
(`libs/dolphin/src/mtx/`: mtx.c, mtxvec.c, mtx44.c, vec.c — all 100% in
objdiff) and the DOL is **byte-clean**. `C_MTXFrustum` (0x8025E774, 0x9C) was
the last park; the fix is wired at the top of `libs/dolphin/src/mtx/mtx44.c`.
(Pre-solution reconstructions lived in `docs/parkings/mtx-reconstruction/`,
removed after the solve; they survive in git history — see
`git log -- docs/parkings/mtx-reconstruction/`.)

> Formerly documented only as `mtx-reconstruction/README.md` (unindexed);
> given parking-doc number 39 in the 2026-08-26 docs audit.

## Symptom

Two mutually exclusive partial matches, both pure mwcc scheduling artifacts:

1. **Baseline `tmp`-statement form** (`tmp = 2.0f/(r-l); m[0][0] = 2.0f*n*tmp;`)
   compiles with **retail's exact register allocation** but emits both
   `fmuls` with the commutative operands swapped:
   `fmuls f0, f11(div), f8(prod)` instead of retail's
    `fmuls f0, f8(prod), f11(div)` (same at m[1][1]) — 2 words off.
2. **Inline-division form** (fixes the operand order at BOTH sites):
   ```c
   __REGISTER f32 c_div = lbl_803CB010;   // 1.0
   __REGISTER f32 c_mul = lbl_803CB014;   // 2.0
   m[0][0] = (c_mul * n) * (c_div / (r - l));
   ```
   …but that structure rotates the register allocation
   (r-l→f8 vs f9, 2.0→f9 vs f8, div1→f8 vs f11, div2→f11 vs f9) →
   11 pure-regalloc diffs (33 bytes).

## What was tried and failed

- `__REGISTER` on constants in both orders, on the fsub results (rl/tb/fn),
  on `n`; padding `__REGISTER` declarations to shift virtual numbering
- plain (non-`__REGISTER`) constant locals; plain externs inline
- inline asm `fmuls` blocks (any `asm` is a scheduling barrier and destroys
  retail's division/store interleaving — 33+ diffs)
- `-schedule off`, `#pragma scheduling off`, `#pragma peephole off`,
  `#pragma optimize_time on`, `-O4,s`, `extern __const`

Best pre-solution forms (both removed with `mtx-reconstruction/`; in git history):

| Form | Result |
|---|---|
| inline-division `mtx44.c` reconstruction | operand order fixed, 11 regalloc diffs |
| baseline `tmp` form (git history of `libs/dolphin/src/mtx/mtx44.c`) | perfect allocation, 2 operand swaps |

## Sibling solved the same session (context)

**C_MTXLightOrtho** (0x8025E60C, 0x88) had the same swapped-`fmuls`
symptom and is now **SOLVED byte-exact**: the SDK original was itself an
inline-asm body — recovered verbatim from SFA-Decomp
(`~/ai/SFA-Decomp/src/dolphin/mtx/mtx.c`, lines 480-517),
wired into `mtx/mtx.c` as an `asm void` block with thug2's r13 externs
(`lbl_803CAFB0`=1.0, `lbl_803CAFC0`=2.0, `lbl_803CAFB4`=0.0). Wiring gotcha: mwcc requires
`asm void C_MTXLightOrtho(__REGISTER Mtx m, ...)` — the param used as an asm
base register must carry `__REGISTER`.

## Extern route (why the pool is auto-asm)

Retail's `.sdata2` pool at `0x803CAF80..0x803CB210` carries constants for the
live functions **and** dead-function constants a fresh compile cannot
reproduce. Any C literal in the mtx sources emits a compact C pool that lands
at wrong addresses and shifts the r2/r13 base — hundreds of text diffs. All
constants are therefore `extern`ed into inner labels added to the auto-asm
blob:
`lbl_803CAFB0=1.0, 803CAFB4=0.0, 803CAFC0=2.0, 803CB010=1.0, 803CB014=2.0,
803CB018=0.0, 803CB01C=-1.0, 803CB06C=0.5, 803CB070=3.0`;
`lbl_803CA358`/`lbl_803CA360` (.sdata, Unit01 `{0.0, 1.0}`) feed PSMTXConcat's
`psq_l`.

## Solution (wired)

Name each site's `(2.0*n)` product in its own short-lived temp and multiply
`prod * tmp`:

```c
tmp = lbl_803CB010 / (r - l);
prod0 = lbl_803CB014 * n;
m[0][0] = prod0 * tmp;
...
tmp = lbl_803CB010 / (t - b);
prod1 = lbl_803CB014 * n;
m[1][1] = prod1 * tmp;
```

Naming the product keeps mwcc from re-associating the anonymous `a*b*c`
chain, so both final multiplies emit prod-first like retail with zero
allocation drift (`tools/mwcc_verify.py 0x8025E774` → EXACT 308B for the
whole mtx44 TU). Constraints discovered by variant sweep: a single reused
`prod` rotates the allocation (7 diffs); anonymous inline products swap the
fmuls back (2 diffs); `(n * const)` product order swaps the prod's own fmuls;
variable names don't matter. Split re-claimed to `0x8025E774..0x8025E8A8`;
DOL stays byte-clean
(`cmp orig/G2TE52/sys/main.dol build/G2TE52/main.dol`).
