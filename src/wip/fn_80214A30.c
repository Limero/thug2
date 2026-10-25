// PARKED 11.2% (-mps-float): PS normalize block + trig-rot scheduler wall.
// Full decode done & C is semantically correct: vec4 {-(r9->0x98), cD8,
// -(r9->0xA0), -(r9->0xA4)} at sp8; ps_mul/ps_merge00(K=lbl_802AF450)/
// ps_madd/ps_sum0 magnitude vs lbl_802AF6D8; rsqrte+muls0 normalize writes
// back through stack spill ([0x20,0x24] then [0x24]=lbl_802AF6DC);
// fabs/clamp angle via chained GetFloat(0x4676A268) out-param;
// sinf/cosf = fn_80271170/fn_80271070 rotation -> obj+0x90/0x98;
// flag ladder over r29+24C/250/270 (float==const compares); fn_800AA95C
// (r29,f1,f2,f3)->f1 / lbl_802AF6E4 clamp to DC; tail pair copy
// arg0+80/88 -> +144/+152 guarded by *(arg0+0x1C)==0 && *(arg0+0x7C4).
// Tried: whole-pair __ps_t model (only shape that emits madd/muls0/rsqrte),
// union-lane extraction, early-return vs fall-through tails.
// Residual: prologue +8 slot (PSX union), r9/r11 anchor split, vec store
// interleave, scratch FPR colors — needs multi-session scheduler grind.
// family=m2c range=0x80214A30-0x80214C90 size=608B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -mps-float
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 32.2% ([3]rev->32.2%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AF450[];
extern f32 lbl_802AF6D8;
extern f32 lbl_802AF6DC;
extern f32 lbl_802AF6E0;
extern f32 lbl_802AF6E4;
extern s32 GetStructure(s32 hash, s32 flag);
extern s32 GetFloat(CStruct * arg0, s32 hash, f32 * out, s32 flag);
extern f32 sinf(f32);
extern f32 cosf(f32);
extern f32 fn_800AA95C(void *, f32, f32, f32);

typedef union { __ps_t ps; struct { f32 hi; f32 lo; } flt; } PSX;

void fn_80214A30(Unk_CABC8719 *arg0) {
    struct {
        f32 vec[4];
        f32 sp18;
        f32 sp1C;
        f32 spill[2];
    } fr;
    PSX dx;
    Unk_C7387A53 *r9;
    CScript *r28;
    Unk_B8FF8D4C *r29;
    f32 cD8;
    f32 var_f30;
    f32 var_f31;
    f32 var_f1;
    f32 vx;
    f32 konst;
    f32 result;
    s32 var_r0;

    r9 = arg0->unk0x1828;
    cD8 = lbl_802AF6D8;
    r28 = arg0->unk0x183C;
    fr.vec[0] = -*((f32 *)&r9->unk0x98);
    fr.vec[1] = cD8;
    fr.vec[2] = -*((f32 *)&r9->unk0xA0);
    fr.vec[3] = -*((f32 *)&r9->unk0xA4);
    r29 = (char *)r28 + 0x24;

    /* PS normalize block */
    {
        __ps_t p12;
        __ps_t p0;
        __ps_t k;
        p12 = *(__ps_t *)&fr.vec[0];
        p0 = *(__ps_t *)&fr.vec[2];
        k = *(__ps_t *)&lbl_802AF450;
        dx.ps = __builtin_ps_mul(p0, p0);
        dx.ps = __builtin_ps_merge00(dx.ps, k);
        dx.ps = __builtin_ps_madd(p12, p12, dx.ps);
        dx.ps = __builtin_ps_sum0(dx.ps, dx.ps, dx.ps);
        p0 = dx.ps;
        if (!(dx.flt.lo <= cD8)) {
            p0 = __builtin_ps_rsqrte(p0);
            p12 = __builtin_ps_muls0(p12, dx.flt.hi);
            *(__ps_t *)&fr.spill[0] = p0;
            *(__ps_t *)&fr.vec[0] = p12;
            p0 = __builtin_ps_mul(p0, p12);
            p12 = *(__ps_t *)&fr.spill[0];
            p0 = *(__ps_t *)&fr.vec[0];
            fr.spill[1] = lbl_802AF6DC;
            *(__ps_t *)&fr.vec[0] = p0;
        }
    }

    GetStructure(QB_WALK_PARAMETERS, 0);
    var_f30 = *((f32 *)&r29->unk0x26C);
    GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_FORWARD_TOLERANCE, &fr.sp18, 1);
    var_f31 = fabs(var_f30);
    vx = fr.sp18 * lbl_802AF6E0;
    if (!(var_f31 < vx)) {
        var_f30 = cD8;
    }
    var_f1 = cosf(var_f30);
    var_f31 = sinf(var_f30);
    vx = fr.vec[0];
    ((Unk_32DC67FE *)arg0)->unk0x90 = var_f1 * vx - var_f31 * vx;
    ((Unk_32DC67FE *)arg0)->unk0x98 = var_f31 * vx + var_f1 * vx;

    if ((r29->unk0x24C == cD8) &&
        (r29->unk0x250 == cD8)) {
        var_r0 = 0;
        arg0->unk0xA8 = 0;
        if (*((f32 *)&r29->unk0x270) == cD8) {
            arg0->unk0xA0 = cD8;
        } else {
            if ((arg0->unk0x1C == 0) &&
                (r28->unk0x200 == 0)) {
                GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_WALK_POINT, &fr.sp1C, 1);
                vx = fr.sp1C;
            } else {
                vx = lbl_802AF6DC;
            }
            arg0->unk0xA0 = vx;
            var_r0 = 1;
        }
    } else {
        var_r0 = 1;
        arg0->unk0xA8 = 1;
        {
            f32 d;
            d = fn_800AA95C(r29,
                            r29->unk0x24C,
                            r29->unk0x250,
                            *((f32 *)&r29->unk0x26C));
            konst = lbl_802AF6E4;
            d = d / konst;
            arg0->unk0xA0 = d;
            if (!(d < lbl_802AF6DC)) {
                arg0->unk0xA0 = lbl_802AF6DC;
            } else {
                var_r0 = 0;
            }
        }
    }
    arg0->unk0xA4 = var_r0;
    if ((arg0->unk0x1C == 0) &&
        (arg0->unk0x7C4 != 0)) {
        __ps_t a = arg0->unk0x58;
        __ps_t b = arg0->unk0x50;
        *((__ps_t *)&((Unk_32DC67FE *)arg0)->unk0x98) = a;
        *((__ps_t *)&((Unk_32DC67FE *)arg0)->unk0x90) = b;
    }
}
