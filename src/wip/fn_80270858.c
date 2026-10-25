// WIP DRAFT (non-matching) — hand reconstruction from the WANT disassembly.
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 5.7554% -> 6.5089% per-object flags: -msdata=eabi -G8 -> -fno-gcse
// family=m2c range=0x80270858-0x80270A84 size=556B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// IDENTITY: asinf (Neversoft single-precision float lib; see
// docs/neversoft-math-lib.md §3.1). Callee fn_8027114C = fabsf (AGENTS-recipes
// §3 "fabsf = fn_8027114C"), sqrtf = 0x80270CA4. Constant block is the .sdata2
// pool lbl_803CA6B8..lbl_803CA6F4 (16 floats), read disp(r13) — the same
// SDA21 form as the acosf twin (src/wip/fn_8027060C.c), so the
// -msdata=eabi/-G route is required for the r13-relative lfs.
//
// 2026-10-06. The old body was fill_wip_drafts
// output: it read every constant through a bogus file-scope `static s32
// saved_reg_r13` / `saved_reg_f31`, computed in double (lfd/fctiwz/frsp) and
// sized the frame 0x88 (9 FPR saves) instead of 0x30 — 0.72%, 138/139 words
// wrong. Replaced with the real fdlibm-shaped body, decoded off the WANT:
//
//   ix = bits(x) & 0x7FFFFFFF
//   ix==0x3F800000 : return x*pio2_lo + x*pio2_hi        (asin(±1) = ±pi/2)
//   ix >0x3F800000 : return (x-x)/(x-x)                  (NaN)
//   ix<=0x3EFFFFFF : asin(x) = x + x*(t*P(t)/Q(t)), t = x*x
//                    (tiny path ix<=0x31FFFFFF: if (huge+x > 1.0f) return x)
//   else           : y = fabsf(x); t = (1.0f - y)*0.5f;
//                    asin(x) = pio2 - 2*asin(sqrt(t)), with
//                    asin(w) ~= wt + r*w + (t - wt*wt)/(w+wt) (wt = w with the
//                    low 12 mantissa bits cleared, ix<=0x3F799999 only)
//   tail           : sign of the raw bits of x (cmpwi on hx, fneg).
// P has 6 coeffs (t^0..t^5, constant term 1/6 = the pool's lbl_803CA6DC),
// Q has 4 (t^1..t^4) + the 1.0 at lbl_803CA6C4. Frame must be -0x30 with
// stmw r30 and stfd f29/f30/f31: t (t^0), num (t*P) and den (t*Q+1) are the
// three values that stay live across the bl sqrtf, which is exactly what
// forces those three FPR saves; hx/ix force the r30/r31 pair.
//
// PARKED 2026-10-06: body is semantically complete and size-exact
// 556B by construction (symbols.txt size:0x22C == 139 words), but NOT verified —
// this worker slice has no compiler. Expected residual: the per-window sched /
// local-alloc placement plus the Horner operand order, i.e. the same class the
// acosf twin parked at 73.47% (§6ec declaration/birth order, §6gp arg interleave).
// The two constants this reconstruction is least sure of are lbl_803CA6F4 (the
// second pio2 accumulator in the <=0.975 correction — a pio2_hi/lo-half) and the
// P/Q coefficient split (values not independently confirmed to the last bit).
// It is still strictly better than the previous body, which was structural
// garbage. Re-measure with test_wip_drafts.py --addr 0x80270858 (the SDA21
// caveat of the acosf header applies: verify with tools/sda_verify.py).
//
// No inline asm. No transcribed instructions. No casting of the WANT's types:
// the two bit probes go through the fdlibm union (GET_FLOAT_WORD style), the
// float types are all f32.
// FLAG: -fno-gcse
#include "types.h"

extern const f32 lbl_803CA6B8; /* 1.5707963f   pio2_hi            */
extern const f32 lbl_803CA6BC; /* 7.5497894e-08f pio2_lo          */
extern const f32 lbl_803CA6C0; /* 1.0e+30f     huge               */
extern const f32 lbl_803CA6C4; /* 1.0f         one                */
extern const f32 lbl_803CA6C8; /* P t^5                           */
extern const f32 lbl_803CA6CC; /* P t^4                           */
extern const f32 lbl_803CA6D0; /* P t^3                           */
extern const f32 lbl_803CA6D4; /* P t^2                           */
extern const f32 lbl_803CA6D8; /* P t^1                           */
extern const f32 lbl_803CA6DC; /* 0.16666667f  P t^0               */
extern const f32 lbl_803CA6E0; /* Q t^4                           */
extern const f32 lbl_803CA6E4; /* Q t^3                           */
extern const f32 lbl_803CA6E8; /* Q t^2                           */
extern const f32 lbl_803CA6EC; /* Q t^1                           */
extern const f32 lbl_803CA6F0; /* 0.5f                            */
extern const f32 lbl_803CA6F4; /* pio2_lo half (correction tail)  */

f32 sqrtf(f32);
f32 fn_8027114C(f32);

f32 asinf(f32 x) {
    union {
        f32 f;
        s32 i;
    } sp8;
    f32 y;
    f32 t;
    f32 p;
    f32 q;
    f32 num;
    f32 den;
    f32 w;
    f32 wt;
    f32 resid;
    f32 r;
    f32 res;
    s32 hx;
    s32 ix;
    s32 i;

    y = x;
    sp8.f = y;
    hx = sp8.i;
    ix = hx & 0x7FFFFFFF;

    if (ix == 0x3F800000) {
        return x * lbl_803CA6BC + x * lbl_803CA6B8;
    }
    if (ix > 0x3F800000) {
        return (x - x) / (x - x);
    }

    if (ix <= 0x3EFFFFFF) {
        if (ix <= 0x31FFFFFF) {
            if (lbl_803CA6C0 + x > lbl_803CA6C4) {
                return x;
            }
        } else {
            t = x * x;
        }
        p = t * (t * (t * (t * (t * lbl_803CA6C8 + lbl_803CA6CC) + lbl_803CA6D0) +
                       lbl_803CA6D4) + lbl_803CA6D8) + lbl_803CA6DC;
        q = t * (t * (t * lbl_803CA6E0 + lbl_803CA6E4) + lbl_803CA6E8) + lbl_803CA6EC;
        den = t * q + lbl_803CA6C4;
        num = t * p;
        r = num / den;
        return x * r + x;
    }

    y = fn_8027114C(x);
    t = (lbl_803CA6C4 - y) * lbl_803CA6F0;
    p = t * (t * (t * (t * (t * lbl_803CA6C8 + lbl_803CA6CC) + lbl_803CA6D0) +
                   lbl_803CA6D4) + lbl_803CA6D8) + lbl_803CA6DC;
    q = t * (t * (t * lbl_803CA6E0 + lbl_803CA6E4) + lbl_803CA6E8) + lbl_803CA6EC;
    den = t * q + lbl_803CA6C4;
    num = t * p;
    w = sqrtf(t);

    if (ix > 0x3F799999) {
        r = num / den;
        res = lbl_803CA6B8 - (2.0f * (w + w * r) - lbl_803CA6BC);
    } else {
        sp8.f = w;
        i = sp8.i & ~0xFFF;
        sp8.i = i;
        wt = sp8.f;
        resid = (t - wt * wt) / (w + wt);
        r = num / den;
        res = lbl_803CA6F4 - ((2.0f * w * r - (lbl_803CA6BC - 2.0f * resid)) -
                              (lbl_803CA6F4 - 2.0f * wt));
    }

    if (hx > 0) {
        return res;
    }
    return -res;
}

// NOTE: the WANT at 0x802708D4 branches `bgt 0x802708F8` into the `t = x*x`
// setup, so the `t = x*x` really is the not-tiny arm (the tiny arm falls through
// to the shared Horner block with `t` dead) — see the header. Do not "fix" the
// apparent uninitialised use: it is dead on every reachable path.
