// Historical 2026-09-11 store-order search: 14.5% PS-aware; superseded by
// the semantic paired-single reconstruction below.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
// WIP DRAFT (non-matching) — semantic PS reconstruction
// family=m2c range=0x801F8250-0x801F839C size=332B
// FLAG: -mps-float
// PARKED 2026-09-25: 16/87 aligned words (18.4%), got 348B vs 332B.
// Verify: tools/venv/bin/python tools/ps_diff.py 0x801F8250 332 -mps-float
// Recovered control/data flow:
//   - guard is fn_801F8170(arg0,arg1), forwarding both point arguments;
//   - subtract the y pair, then x pair, and store dl/r1+8 and dh/r1+0x10;
//   - dot = sum0(madd(dl,dl,merge00(mul(dh,dh),lbl_802AE430)));
//   - min distance = res(rsqrte(dot)) at r1+0x18; reject below the
//     QB_RAILEDITORMINIMUMPOINTSEPARATION query result;
//   - recompute dot, compare its low lane with lbl_802AE4FC, and on the
//     large-dot path store rsqrte at r1+0x20, muls0(dl,rsq) at r1+8,
//     overwrite the inverse pair's low word at r1+0x24 with
//     lbl_802AE500, reload that mixed pair, then multiply it into dl;
//   - tail uses fabs(dl.flt.lo at r1+0xC), the
//     QB_RAILEDITORMAXSLOPE query, lbl_802AE504, and sinf, returning 0
//     only when the absolute slope is greater than the sine limit.
// The exact 0x48 frame, r29 frame base, r29/r30 save, lone f31 save,
// and f31/r1+0x40 epilogue now match. The old FPR-homing blocker is
// solved by volatile dl/dh/inverse members. Remaining blockers:
//   1) each volatile field occurrence reloads from the stack, so both dot
//      blocks contain extra psq_l/reordering and the object is 16 bytes
//      longer; the first staged ps_sub also gets reversed register operands;
//   2) retail's second threshold is ps_sum0 -> ps_mr -> bare fcmpu on a
//      live pair, while a PSValue accessor/local makes cc1 save f14-f31
//      (472B object); a nonvolatile stack member instead adds psq_st+lfs;
//   3) scalar tail semantics are correct, but GCC moves fabs/constant
//      materialization around the two calls instead of retail's exact order.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.

typedef float sn_ps __attribute__((mode(PS)));

extern sn_ps lbl_802AE430;
extern f32 lbl_802AE4FC;
extern f32 lbl_802AE500;
extern f32 lbl_802AE504;

typedef union {
    sn_ps ps;
    struct {
        f32 hi;
        f32 lo;
    } flt;
} PSValue;

typedef struct {
    sn_ps x;
    sn_ps y;
} RailPoint;

typedef struct {
    volatile PSValue dl;
    volatile PSValue dh;
    PSValue min_distance;
    volatile PSValue inverse_distance;
} Frame;

extern s32 fn_801F8170(RailPoint *arg0, RailPoint *arg1);
extern f32 fn_8012570C(s32 hash, s32 flag);
extern f32 sinf(f32 x);

s32 fn_801F8250(RailPoint *arg0, RailPoint *arg1) {
    Frame fr;
    f32 distance;
    f32 saved_distance;
    f32 limit;
    f32 slope;
    f32 sine;

    if (fn_801F8170(arg0, arg1) != 0) {
        return 0;
    }
    {
        sn_ps dh;
        sn_ps dl;

        dh = arg0->y;
        fr.dh.ps = __builtin_ps_sub(dh, arg1->y);
        dl = arg0->x;
        fr.dl.ps = __builtin_ps_sub(dl, arg1->x);
        dh = fr.dh.ps;
        dl = fr.dl.ps;
        fr.min_distance.ps = dh * dh;
        fr.min_distance.ps = __builtin_ps_merge00(fr.min_distance.ps, lbl_802AE430);
        fr.min_distance.ps = __builtin_ps_madd(dl, dl, fr.min_distance.ps);
        fr.min_distance.ps = __builtin_ps_sum0(fr.min_distance.ps, fr.min_distance.ps,
                                              fr.min_distance.ps);
        fr.min_distance.ps = __builtin_ps_res(__builtin_ps_rsqrte(fr.min_distance.ps));
    }
    distance = fr.min_distance.flt.hi;
    saved_distance = distance;
    limit = fn_8012570C(QB_RAILEDITORMINIMUMPOINTSEPARATION, 0);
    if (saved_distance < limit) {
        return 0;
    }
    fr.min_distance.ps = fr.dh.ps * fr.dh.ps;
    fr.min_distance.ps = __builtin_ps_merge00(fr.min_distance.ps, lbl_802AE430);
    fr.min_distance.ps = __builtin_ps_madd(fr.dl.ps, fr.dl.ps, fr.min_distance.ps);
    fr.min_distance.ps = __builtin_ps_sum0(fr.min_distance.ps, fr.min_distance.ps,
                                          fr.min_distance.ps);
    if (fr.min_distance.flt.lo > lbl_802AE4FC) {
        fr.inverse_distance.ps = __builtin_ps_rsqrte(fr.min_distance.ps);
        fr.dl.ps = __builtin_ps_muls0(fr.dl.ps, fr.inverse_distance.ps);
        fr.inverse_distance.flt.lo = lbl_802AE500;
        fr.dl.ps = fr.dl.ps * fr.inverse_distance.ps;
    }
    slope = __builtin_fabsf(fr.dl.flt.lo);
    limit = fn_8012570C(QB_RAILEDITORMAXSLOPE, 0);
    sine = limit * lbl_802AE504;
    sine = sinf(sine);
    if (slope > sine) {
        return 0;
    }
    return 1;
}
