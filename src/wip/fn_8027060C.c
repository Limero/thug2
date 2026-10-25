// PARKED 2026-10-30: FAIL/0.00% -> 73.47% (masked, SDA21-resolved)
// REFRESHED 2026-10-07 (FPR-pin RETARGET sweep): 6.8421% -> 6.9519%
//   the `w` pin was retargeted fr6 -> fr10 (nothing else touched).  fr-pin REMOVAL
//   had been swept; retargeting had not.  Checked NOT size-exact before or after.  §6hk.
// family=m2c range=0x8027060C-0x80270858 size=588B
// WHY PARKED: acosf (Neversoft single-precision math lib, NOT fdlibm, per
// docs/neversoft-math-lib.md). ProDG/ngccc 3.9.3 (want: stwu r1,-0x28 FIRST,
// mflr second, LR at 0x2c(r1); mwcc would put mflr/stw first). All 20 float
// constants are .sdata lbl_803CA670..lbl_803CA6B4, read disp(r13), so the
// SDA21 route (-msdata=eabi -G8) is MANDATORY; -G0 objects can never emit
// r13-relative lfs, and test_wip_drafts.py does not mask type-109 relocs
// (verify with tools/sda_verify.py). Semantics are now fully correct and the
// object is EXACT size 588B = 0x24C = symbols.txt size:0x24C. The remaining
// 39/147 word diffs are pure sched/local_alloc placement, in 4 windows:
//  (1) 5w entry block: `lis r0,0x3f80` hoisted to the first slot of the entry
//      block instead of slot 5 (after clrlwi). Same 6 slots, only the lis
//      moves -> 5 differing words, no index shift.
//  (2) 10w small path: the two final Horner steps (P2 step3 -> f0, P1 step5
//      -> f13) are emitted in the opposite order and P1's accumulator ends
//      in f10 instead of f13.
//  (3) 20w POS path: the stack-pun truncation loads into r9/masks in place
//      (stw r0) where want uses r0 -> r9 (stw r9); `wt` lands in f9 instead
//      of f1; one further fmadds/fmuls pair is transposed.
//  (4)  3w NEG path: P1 accumulator f10 vs f13, and `fmsubs` destination
//      f1 vs f0.
// LEVERS TRIED (all measured, see <scratch>):
//  +20 semantic rebuild steps: full acosf formula (P1 deg5 / P2 deg3 Horner,
//    t=y*y, r=(t*P1)/(t*P2+1)), in-place (y-y)/(y-y) NaN (a named temp adds an
//    fmr and changes the length), `if (hx<=0) return PI; return 0.0f;` early-
//    return form (reproduces want's 5-insn |x|==1 block incl. bgt+load order),
//    y dying before sqrtf (else frame 0x30 + a 4th saved FPR), POS text placed
//    after the `if (hx<0) {NEG}` block so POS falls through and NEG is out of
//    line, and w = sqrtf((1-y)*0.5) NOT y (a real semantic bug in the earlier
//    draft, worth 4 words).
//  +4 register pins, all load-bearing: p2->fr0 (+10.2), w->fr6 (recovered the
//    exact frame from 0x30/4-FPR, +9.6), r->fr10, res->fr1. Full ablation at
//    73.47%: p1->fr13 INERT, den->fr29 hurts, num->fr31 neutral, t->fr30
//    catastrophic (+8 frame), wt->fr1 regresses to 0.66% (600B), wt->fr13
//    1.33%, i->r0 compile-fails.
//  +statement order: THE single biggest remaining lever, +19.7 net.
//    p1-before-p2 in all three poly groups 53.74% -> 73.47% (measured 2x2
//    matrix: 00=53.74 01=56.46 10=70.75 11=73.47). This is §6ec's DECLARATION/
//    BIRTH-order axis, not a codegen lever.
//  +scheduling/GCSE flag sweep: all neutral or worse (-fno-schedule-insns,
//    -fno-schedule-insns2, -fno-sched-spec, -fno-sched-interblock, -fno-gcse,
//    -fno-thread-jumps, -fno-expensive-optimizations, -fno-rerun-cse-after-loop,
//    -O1/-Os/-O3, -mcpu=603/750).
//  +rejected for the lis: 1-word `__asm__("lis %0,0x3f80")` birth (+8 bytes),
//    the same with __volatile__ (compile-fails), named constant local (neutral),
//    the same with an r0 hard pin (neutral), volatile compare operand (600B),
//    `"+r"` barrier on ix (+2w worse), volatile version (-1w), the sibling's
//    `"+r"` barrier pair from src/fn_8027052C.c and src/cosf.c (+4/-44B).
//  +two-name trick for the r0/r9 truncation swap (i -> jx): neutral.
// INLINE ASM: 0 instructions emitted. Only 4 `register ... __asm__("frN")`
//   declaration attributes. Far below the 30% transcription bar.
// NOTE: this body needs the SDA21 flags to compile at all; a -G0 sweep will
// report FAIL/DIFF for the wrong reason (unmasked type-109 reloc words).
#include "types.h"
#include "qb_constants.h"

extern const f32 lbl_803CA670; /* 0.0f      */
extern const f32 lbl_803CA674; /* 3.14159f  */
extern const f32 lbl_803CA678; /* 1.5708f   */
extern const f32 lbl_803CA67C;
extern const f32 lbl_803CA680;
extern const f32 lbl_803CA684;
extern const f32 lbl_803CA688;
extern const f32 lbl_803CA68C;
extern const f32 lbl_803CA690;
extern const f32 lbl_803CA694;
extern const f32 lbl_803CA698;
extern const f32 lbl_803CA69C;
extern const f32 lbl_803CA6A0;
extern const f32 lbl_803CA6A4; /* 1.0f */
extern const f32 lbl_803CA6A8;
extern const f32 lbl_803CA6AC; /* 1.5708f */
extern const f32 lbl_803CA6B0; /* 0.5f */
extern const f32 lbl_803CA6B4; /* 3.14159f */

f32 sqrtf(f32);

f32 acosf(f32 arg0) {
    union { f32 f; s32 i; } sp8;
    register f32 p2 __asm__("fr0");
    register f32 w __asm__("fr10");
    register f32 r __asm__("fr10");
    register f32 res __asm__("fr1");
    f32 y, t, p1, den, num, wt;
    s32 hx, ix, i;

    y = arg0;
    sp8.f = y;
    hx = sp8.i;
    ix = hx & QB_UNKNOWN_0x7FFFFFFF;

    if (ix == QB_UNKNOWN_0x3F800000) {
        if (hx <= 0) {
            return lbl_803CA674;
        }
        return lbl_803CA670;
    }
    if (ix > QB_UNKNOWN_0x3F800000) {
        return (y - y) / (y - y);
    }

    if (ix <= QB_UNKNOWN_0x3EFFFFFF) {
        if (ix <= QB_UNKNOWN_0x23000000) {
            return lbl_803CA678;
        }
        t = y * y;
        p1 = t * (t * (t * (t * (t * lbl_803CA67C + lbl_803CA680) + lbl_803CA684) +
                       lbl_803CA688) + lbl_803CA68C) + lbl_803CA690;
        p2 = t * (t * (t * lbl_803CA694 + lbl_803CA698) + lbl_803CA69C) + lbl_803CA6A0;
        den = t * p2 + lbl_803CA6A4;
        num = t * p1;
        r = num / den;
        res = lbl_803CA6A8 - y * r;
        res = y - res;
        res = lbl_803CA6AC - res;
        return res;
    }

    if (hx < 0) {
        t = (y + lbl_803CA6A4) * lbl_803CA6B0;
        p1 = t * (t * (t * (t * (t * lbl_803CA67C + lbl_803CA680) + lbl_803CA684) +
                       lbl_803CA688) + lbl_803CA68C) + lbl_803CA690;
        p2 = t * (t * (t * lbl_803CA694 + lbl_803CA698) + lbl_803CA69C) + lbl_803CA6A0;
        den = t * p2 + lbl_803CA6A4;
        num = t * p1;
        w = sqrtf(t);
        r = num / den;
        res = r * w - lbl_803CA6A8;
        res = w + res;
        res = res + res;
        return lbl_803CA6B4 - res;
    }

    t = (lbl_803CA6A4 - y) * lbl_803CA6B0;
    w = sqrtf(t);
    sp8.f = w;
    p1 = t * (t * (t * (t * (t * lbl_803CA67C + lbl_803CA680) + lbl_803CA684) +
                   lbl_803CA688) + lbl_803CA68C) + lbl_803CA690;
    p2 = t * (t * (t * lbl_803CA694 + lbl_803CA698) + lbl_803CA69C) + lbl_803CA6A0;
    i = sp8.i & ~0x1FFF;
    sp8.i = i;
    wt = sp8.f;
    den = t * p2 + lbl_803CA6A4;
    num = t * p1;
    r = num / den;
    res = r * w + (t - wt * wt) / (w + wt);
    res = wt + res;
    return res + res;
}
