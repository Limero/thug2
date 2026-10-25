// PARKED 2026-09-25 — FDLIBM atan(f64): source-shape/FPR-allocation wall.
// REVIEWED 2026-10-18 (random triage): needs the original GET_HIGH_WORD
// source shape + f64 live ranges; no new lever. Body untouched.
// IDENTITY CORRECTED: this is atan(double), not tanh. The proof is the data
// layout, not a guessed name: lbl_803CB340=pi/2 high, lbl_803CB360=atanlo[3],
// lbl_803CB328/348 are atanhi/atanlo, and lbl_803CB368..3B8 are the alternating
// aT[0..10] coefficients. fn_80270254 is f64 fabs(f64), and the five reductions
// four range reductions plus the tiny class are the canonical Sun fdlibm
// s_atan.c shape.
// Re-score: tools/score_body.py -> DIFF 20.6% (29/141 words).
// SDA link-sim with the recorded flags: .text 548B vs 564B retail; 105/137
// emitted words mismatch (32 exact slots, 22.7% normalized). The historical
// "105/141 diffs = 25.5%" figure ignored the 16B size shortfall and is stale.
// A genuine nested s_atan.c rewrite was tried with f64 w,s1,s2,z, the exact
// f64 fabs signature, shared conversion/table declarations, and both odd/even
// Horner expressions. It regressed under ProDG 3.9.3: the arithmetic identity is
// confirmed, but cc1 collapses the two long f64 webs into a different load,
// operand, and FPR schedule. The best staged body is retained below.
// First divergence is at 0x8026FF5C (high-word load/home registers); the small
// branch at 0x8026FFF8, the reduction blocks, the 0x802700B8 polynomial, and
// the indexed atanhi/atanlo correction tail then drift together. This is not a
// fake-ASM target: only a fr4 declaration pin, a four-instruction GET-word
// expansion, and one empty identity barrier remain. Exact recovery needs the
// original GET_HIGH_WORD/GET_LOW_WORD source shape and f64 live ranges, not
// arbitrary casts or statement permutations.
// family=m2c range=0x8026FF40-0x80270174 size=564B
// Callee: fn_80270254 = f64 fabs(f64). lbl_803CA618..638 are .sdata; the atan
// tables and coefficients are .sdata2. SDA route requires the recorded flags.
// FLAG: -msdata=eabi -G256 -fno-schedule-insns -fno-schedule-insns2
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
extern f64 lbl_803CA618;      /* huge = 1.0e300 */
extern f64 lbl_803CA620;      /* one */
extern f64 lbl_803CA628;      /* two */
extern f64 lbl_803CA630;      /* 1.5 */
extern f64 lbl_803CA638;      /* -one */
extern f64 lbl_803CB340;      /* atanhi[3] */
extern f64 lbl_803CB360;      /* atanlo[3] */
extern f64 lbl_803CB368;      /* aT[0] */
extern f64 lbl_803CB370;      /* aT[1] */
extern f64 lbl_803CB378;      /* aT[2] */
extern f64 lbl_803CB380;      /* aT[3] */
extern f64 lbl_803CB388;      /* aT[4] */
extern f64 lbl_803CB390;      /* aT[5] */
extern f64 lbl_803CB398;      /* aT[6] */
extern f64 lbl_803CB3A0;      /* aT[7] */
extern f64 lbl_803CB3A8;      /* aT[8] */
extern f64 lbl_803CB3B0;      /* aT[9] */
extern f64 lbl_803CB3B8[24];  /* aT[10] head */
extern f64 lbl_803CB348[3];   /* atanlo[0..2] */
extern f64 lbl_803CB328[3];   /* atanhi[0..2] */

extern f64 fn_80270254(f64);

f64 fn_8026FF40(f64 farg0) {
    s32 jx;
    s32 ix;
    s32 lx;
    s32 k;
    f64 t2;
    f64 t4;
    f64 num;
    f64 den;
    register f64 x __asm__("fr4"); x = farg0;

    {
        s32 hi;
        s32 lo;
        __asm__ volatile("fmr 0, %2\n\tstfd 0, 8(1)\n\tlwz %0, 8(1)\n\tlwz %1, 0xc(1)" : "=r"(hi), "=r"(lo) : "f"(x) : "fr0", "memory");
        jx = hi;
        __asm__ volatile("" : "+r"(jx));
    }
    ix = jx & QB_UNKNOWN_0x7FFFFFFF;
    if (ix > QB_UNKNOWN_0x440FFFFF) {
        {
            union {
                f64 d;
                s32 w[2];
            } u2;
            u2.d = x;
            lx = u2.w[1];
        }
        if ((ix > QB_UNKNOWN_0x7FF00000) || ((ix == QB_UNKNOWN_0x7FF00000) && (lx != 0))) {
            return x + x;
        }
        if ((s32)jx > 0) {
            return lbl_803CB340 + lbl_803CB360;
        }
        return -lbl_803CB340 - lbl_803CB360;
    }
    if (ix > QB_UNKNOWN_0x3FDBFFFF) {
        x = fn_80270254(x);
        if (ix > QB_UNKNOWN_0x3FF2FFFF) {
            if (ix > QB_UNKNOWN_0x40037FFF) {
                k = 3;
                x = lbl_803CA638 / x;
            } else {
                k = 2;
                x = (x - lbl_803CA630) / (x * lbl_803CA630 + lbl_803CA620);
            }
        } else if (ix > QB_UNKNOWN_0x3FE5FFFF) {
            k = 1;
            x = (x - lbl_803CA620) / (x + lbl_803CA620);
        } else {
            k = 0;
            x = (x + x - lbl_803CA620) / (x + lbl_803CA628);
        }
    } else if (ix > QB_UNKNOWN_0x3E1FFFFF) {
        k = -1;
    } else {
        if (x + lbl_803CA618 <= lbl_803CA620) {
            k = -1;
        } else {
            return x;
        }
    }
    t2 = x * x;
    t4 = t2 * t2;
    num = lbl_803CB3B8[0];
    num = num * t4 + lbl_803CB3A8;
    num = num * t4 + lbl_803CB398;
    num = num * t4 + lbl_803CB388;
    num = num * t4 + lbl_803CB378;
    num = num * t4 + lbl_803CB368;
    den = lbl_803CB3B0;
    den = den * t4 + lbl_803CB3A0;
    den = den * t4 + lbl_803CB390;
    den = den * t4 + lbl_803CB380;
    den = den * t4 + lbl_803CB370;
    if (k < 0) {
        return x - x * (t2 * num + t4 * den);
    } else {
        f64 res;
        res = t2 * num + t4 * den;
        res = x * res - lbl_803CB348[k];
        res = lbl_803CB328[k] - (res - x);
        if ((s32)jx < 0) {
            res = -res;
        }
        return res;
    }
}
