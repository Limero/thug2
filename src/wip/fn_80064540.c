// WIP DRAFT (non-matching) — hand-rebuilt 2026-09-28, smallest-first sweep.
// family=m2c range=0x80064540-0x800645D8 size=152B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PAIRED-SINGLE adjacency: want contains psq_l/psq_st (from a 16-byte
// `__ps_t` pair copy), so the body must be compiled with `-mps-float`
// (tools/venv/bin/python tools/score_body.py 0x80064540 <file> does this
// automatically because the body mentions `__ps_t`).
//
// STATUS: PARKED. Best body below = DIFF 13.2% (36 words vs want's 38).
// The *structure* is fully decoded and reproduced; the function resists on
// pure register-allocation + scheduling grounds.
//
// DECODE OF WANT (at 0x80064540, 38 words, via the paired-single disassembler):
// the floats at 0xB4, 0xB8 and 0xB0 are loaded into f0, f13 and f12 and their
// absolute values taken; f13 is copied to f11 as the running maximum, which is
// conditionally replaced from f0 when f0 exceeds f13, and f11 is copied to f10
// as the running second maximum, itself conditionally replaced from f12 when
// f12 exceeds f11. Next the pair at 0x28 is loaded and stored to 0x58 with the
// float at 0xA8 reloaded into f13 between the two halves, then the pair at 0x30
// is loaded and stored to 0x60 with f13 copied to f12 and the float at 0xD4
// loaded into f9 between the halves. The floats at 0x9C and 0xA4 are then loaded
// into f0 and f11 and a multiply-add of the 0xD4 value times the second maximum
// plus the 0x9C value is issued; the 0xA4 value is compared against the reloaded
// 0xA8 value and conditionally replaces the running maximum, after which the
// float at 0xA0 is loaded and the running values shuffled through f11 and f12
// with a second compare-and-select. A high half is then loaded into r9, the
// multiply-add result is multiplied by the 0xD4 value, a second multiply-add
// combines it with the pool float at 0x4098 off r9 and the second chain's
// result, and the final value is stored to 0x64 before returning.
//
// So:  n1  = max(|fB8|, |fB4|, |fB0|)          (the classic m=b / n=m chain)
//      n2  = max(fA8, fA4, fA0)               (same chain shape, b reused)
//      *(f32*)(self+0x64) = ((k*n1 + f9C) * k) * lbl_80294098 + n2,  k = fD4
//      *(V4*)(self+0x58) = *(V4*)(self+0x28)  -> psq_l 0x28 / 0x30, psq_st 0x58 / 0x60
// NOTE the 16-byte copy overlaps the result store at 0x64 (the pair at 0x60
// covers 0x60..0x67) — the game's copy is a fused `__ps_t` pair whose high
// half the tail store then overwrites; modelling it as 4 `f32` copies emits
// stfs×4 instead of the psq pair and scores worse.
//
// RESIDUALS (each independently kills the match):
//  1. GCC coalesces the `m = b` copy away (got `fcmpu;ble;fmr m,b`), want
//     keeps it as a real `fmr f11,f13` *before* the compare. Same for the
//     second chain (`fmr f12,f13` at 0x88). Reusing one variable for b/fB8
//     and later fA8 does not stop the coalescing.
//  2. The three initial loads schedule differently: want fB4,fB8,fB0; got
//     often fB8,fB4,fB0 (the fabs register roles invert with it).
//  3. want computes n1 (`fmadds f0,f9,f10,f0`) BEFORE the n2 chain but
//     loads fA4 late (0x98, after f9C); got hoists the fA4 load early.
//  4. `lis r9` + `lfs f13,lbl` sit between the two `fmuls/fmadds` tail ops
//     in want (0xC0/0xC8), got emits them together earlier.
//  Net: got is 36 words, want 38 — the coalescing in (1) removes ~2 words
//  and shifts every downstream word, which is why the masked percentage
//  reads as low as 13% despite a structurally identical body.
//
// TRIED (all land on 13.2%): `if` vs ternary for both substitutions; `>`
// vs `<` / `>=` spellings; comparing against `b` vs the accumulator `m`;
// separate load statements followed by `a = fabsf(a)` (same 13.2%); decl
// order permutations; `__builtin_fabsf`; modeling the copy as a 16-byte
// `V4 {__ps_t lo,hi;}` assignment (=> scalar lwz/stw, 4.8%), as four `f32`
// copies (=> stfs×4, 12.5%), and as two `__ps_t` temp assignments (13.2%,
// the best — reproduces the psq pair). Flags not yet swept exhaustively;
// a full flag sweep is the obvious next lever, plus trying to force the
// `m = b` copy with an opaque barrier (avoided here: user constraint).
#include "types.h"
extern f32 lbl_80294098;
void fn_80064540(void *arg0) {
    f32 a, b, c;
    f32 m, n, m2, n2;
    f32 k;
    __ps_t t;

    a = __builtin_fabsf(*(f32 *)((char *)arg0 + 0xB4));
    b = __builtin_fabsf(*(f32 *)((char *)arg0 + 0xB8));
    c = __builtin_fabsf(*(f32 *)((char *)arg0 + 0xB0));
    m = b;
    if (a > b) { m = a; }
    n = m;
    if (c > n) { n = c; }

    t = *(__ps_t *)((char *)arg0 + 0x28);
    *(__ps_t *)((char *)arg0 + 0x58) = t;
    t = *(__ps_t *)((char *)arg0 + 0x30);
    *(__ps_t *)((char *)arg0 + 0x60) = t;

    b = *(f32 *)((char *)arg0 + 0xA8);
    k = *(f32 *)((char *)arg0 + 0xD4);
    m2 = b;
    if (*(f32 *)((char *)arg0 + 0xA4) > b) { m2 = *(f32 *)((char *)arg0 + 0xA4); }
    n2 = m2;
    if (*(f32 *)((char *)arg0 + 0xA0) > n2) { n2 = *(f32 *)((char *)arg0 + 0xA0); }

    *(f32 *)((char *)arg0 + 0x64) =
        ((k * n + *(f32 *)((char *)arg0 + 0x9C)) * k) * lbl_80294098 + n2;
}
