// PARKED 31.8%: PS FPR-pair coloring + frame-slot wall (doc-06 family).
// Structure fully decoded & semantically correct: guards on *(arg0+0x1998)
// and 0x2C>0x19B4 float pair; block A = ps_mul/ps_merge00(K)/ps_madd/
// ps_sum0 dot vs *(arg0+0x19B0); two chained GetFloat(GetStructure(...))
// script calls (hashes 0xA20C43B7 / 0x4D16F37D) bracketing NaN-guard
// t<=-sp18; tail = muls0/sub vec4 relax over object pairs 0x28..0x44 with
// ps_sum0 result tested against lbl_802AF6B8 const.
// Tried: frame-template struct (fr ends 0x34 + union dot -> exact 56B
// locals predicted, got still 0x60); register pins k->fr12/c->fr11 (pin
// cascade shifted ps_mul operand instead); "+f" barrier + explicit fmr asm
// for the temp/t split; -ffast-math/-funsafe-math (worse, 16%);
// whole-pair stores vs lane splits (lane splits split ALL pairs).
// Residual: every shape shifts {f12,f11,f10} scratch colors by one and
// keeps one extra 8-byte stack slot vs want.
// family=m2c range=0x80214308-0x802144B8 size=432B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -mps-float
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 35.2% ([7]rev->35.2%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AF450[];
extern f32 lbl_802AF6B8;
extern s32 GetStructure(s32 hash, s32 flag);
extern s32 GetFloat(CStruct * arg0, s32 hash, f32 * out, s32 flag);

void fn_80214308(Unk_BBEFE3F6 *arg0) {
    struct {
        f32 p8[2];
        f32 p10[2];
        f32 sp18;
        f32 sp1C;
        f32 p20[2];
        f32 s28;
        f32 pad2C;
        f32 s30;
    } fr;
    typedef union { __ps_t ps; struct { f32 hi; f32 lo; } flt; } PSX;
    PSX dot;
    char *kp;
    char *r29p;
    char *r30p;
    f32 t;
    f32 temp;
    f32 fv;
    f32 prod;
    f32 konst9;
    __ps_t a;
    __ps_t k;
    __ps_t c;
    __ps_t d;
    __ps_t w0;
    __ps_t v7;
    __ps_t v8;
    __ps_t w1;
    __ps_t h;
    __ps_t i;

    if (arg0->unk0x1998 == 0) {
        return;
    }
    if (((Unk_F6393DBC *)arg0)->unk0x2C > arg0->unk0x19B4) {
        arg0->unk0x1998 = 0;
        return;
    }
    r29p = (char *)arg0 + 0x19A8;
    r30p = (char *)arg0 + 0x19A0;
    kp = lbl_802AF450;

    a = *(__ps_t *)(r29p);
    a = __builtin_ps_mul(a, arg0->unk0x30);
    k = *(__ps_t *)kp;
    c = arg0->unk0x28;
    a = __builtin_ps_merge00(a, k);
    d = *(__ps_t *)(r30p);
    d = __builtin_ps_madd(d, c, a);
    dot.ps = __builtin_ps_sum0(d, d, d);
    *(__ps_t *)&fr.p20[0] = dot.ps;
    temp = fr.p20[0];
    t = temp;
    t = t - arg0->unk0x19B0;

    GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_PUSH_FEELER_LENGTH, &fr.sp18, 1);
    if (t <= -fr.sp18) {
        return;
    }
    GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_PUSH_STRENGTH, &fr.sp1C, 1);

    fv = arg0->unk0x88;
    prod = fr.sp1C * fv;
    fr.s28 = prod;

    k = *(__ps_t *)(r30p);
    v7 = arg0->unk0x40;
    v8 = arg0->unk0x38;
    w1 = arg0->unk0x30;
    h = *(__ps_t *)&fr.s28;
    i = *(__ps_t *)(r29p);
    dot.ps = h;
    w0 = __builtin_ps_muls0(k, dot.flt.hi);
    d = __builtin_ps_muls0(i, dot.flt.hi);
    *(__ps_t *)&fr.p8[0] = w0;
    *(__ps_t *)&fr.p10[0] = d;
    h = h - w0;
    arg0->unk0x28 = h;
    i = *(__ps_t *)&fr.p10[0];
    w1 = w1 - i;
    arg0->unk0x30 = w1;
    i = *(__ps_t *)(r29p);
    k = *(__ps_t *)kp;
    v7 = v7 * i;
    w0 = *(__ps_t *)(r30p);
    v8 = v8 * w0 + __builtin_ps_merge00(v7, k);
    dot.ps = __builtin_ps_sum0(v8, v8, v8);
    konst9 = lbl_802AF6B8;
    if (dot.flt.hi == konst9) {
        return;
    }
    fr.s30 = dot.flt.hi;
    h = *(__ps_t *)&fr.s30;
    dot.ps = h;
    w1 = __builtin_ps_muls0(i, dot.flt.hi);
    w0 = __builtin_ps_muls0(v7, dot.flt.hi);
    *(__ps_t *)&fr.p10[0] = w1;
    *(__ps_t *)&fr.p8[0] = w0;
    arg0->unk0x40 = v7;
    v7 = v7 - h;
    h = *(__ps_t *)&fr.p10[0];
    arg0->unk0x38 = v8;
    v8 = v8 - *(__ps_t *)&fr.p8[0];
}
