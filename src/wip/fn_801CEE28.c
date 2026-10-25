// WIP DRAFT (non-matching) — hand-rebuilt from disasm; SNAPS paired-single twin-arm body.
// family=m2c range=0x801CEE28-0x801CEF64 size=316B
// PS ops: ps_mr(xo10=72)/ps_muls0 x4/ps_sub|ps_add — all emittable
// (__builtin_ps_muls0/mr-asm/+-operators). Twin arms differ only by
// {sp40 vs sp48 staging slot} and {ps_sub vs ps_add}.
// FLAG: -mps-float
// PARKED (1.2% first-shot; structural draft only): twin-arm SNAPS PS body,
// all ops emittable but stack layout (sp8..sp37 pairs+staging slots, frame
// 0x60, stw-r31-only prologue) plus per-arm FPR coloring need the full
// pin/barrier grind that stalled fn_801CE3E4 and zone
// sibling fn_8015E868 (83.6%, doc 06 M5.0o FPR-coloring wall).
// Retry hints: two-web pointer prologue §6s-1; scalar-first slot placement
// (CD414 notes); arms share tail — crossjump should merge after both arms
// byte-align individually.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 10.1% ([0]rev->10.1%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AD324;
extern f32 lbl_802AD328;
extern f32 lbl_802AD330;
s32 fn_801288C4(CStruct *, s32);
s32 fn_801EC684(Unk_E2C810EF *, s32, s32);

s32 fn_801CEE28(Unk_1292C674 *arg0, CStruct *arg1) {
    struct {
        char _0[8];
        __ps_t p8;
        __ps_t p10;
        __ps_t p18;
        __ps_t p20;
        f32 v28;
        f32 v2C;
        f32 v30;
        f32 v34;
    } loc;
    Unk_64D775D7 *o;
    __ps_t pair, v120, v128, p96, p88, mr;
    f32 k;

    k = lbl_802AD324;
    if (fn_801288C4(arg1, QB_RIGHT) != 0) {
        pair = *(__ps_t *)((char *)&loc.v28);
        loc.v28 = k;
        k = k + k;
        o = arg0->unk0xC;
        __asm__("ps_mr %0, %1" : "=&f"(mr) : "f"(pair));
        v120 = o->unk0x78;
        v128 = o->unk0x80;
        v120 = __builtin_ps_muls0(v120, mr);
        v128 = __builtin_ps_muls0(v128, mr);
        *(__ps_t *)&loc.p18 = v120;
        *(__ps_t *)&loc.p20 = v128;
        p96 = o->unk0x60;
        p88 = o->unk0x58;
        p96 = p96 - v128;
        *(__ps_t *)&loc.p10 = p96;
        p88 = p88 - v120;
    } else {
        o = arg0->unk0xC;
        k = k + k;
        loc.v30 = k;
        pair = *(__ps_t *)((char *)&loc.v30);
        __asm__("ps_mr %0, %1" : "=&f"(mr) : "f"(pair));
        v120 = o->unk0x78;
        v128 = o->unk0x80;
        v120 = __builtin_ps_muls0(v120, mr);
        v128 = __builtin_ps_muls0(v128, mr);
        *(__ps_t *)&loc.p18 = v120;
        *(__ps_t *)&loc.p20 = v128;
        p96 = o->unk0x60;
        p88 = o->unk0x58;
        p96 = p96 + v128;
        *(__ps_t *)&loc.p10 = p96;
        p88 = p88 + v120;
    }
    arg0->unk0x230 = p88;
    *(__ps_t *)&loc.p8 = p88;
    {
        __ps_t q = *(__ps_t *)&loc.p10;
        arg0->unk0x238 = q;
    }
    {
        f32 t = ((Unk_39999125 *)arg0)->unk0x234;
        __ps_t r568;
        t = t + lbl_802AD328;
        ((Unk_39999125 *)arg0)->unk0x234 = t;
        r568 = arg0->unk0x238;
        *(__ps_t *)((char *)&loc.p18) = r568;
    }
    {
        __ps_t r230 = arg0->unk0x230;
        f32 t = ((Unk_39999125 *)arg0)->unk0x244;
        arg0->unk0x248 = arg0->unk0x238;
        arg0->unk0x240 = r230;
        t = t - lbl_802AD328;
        ((Unk_39999125 *)arg0)->unk0x244 = t;
    }
    return (fn_801EC684(arg0, 0x10, 0) != 0) ? 1 : 0;
}
