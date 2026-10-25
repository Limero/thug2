// WIP DRAFT (non-matching) — hand-written from disasm; PS-heavy hash switch.
// PARKED 8%: cases 0xA745C080/0xC8C4D2F4 contain retail-only XO5=8 PS opcodes
// (doc-06 hard wall, same word class as parked fn_801AD5DC), and case
// 0xA0551543 needs retail's ps_merge00+ps_sum0 dot-product staging which
// ngccc 3.9.3 provably fuses into ps_madd (doc-06 M5.0h). The five clean
// arms (B992F3CC/5E269B2B/D3313E92/97201739/8E7833BE) are structurally
// correct incl. callee arities: fn_80005F80 is (void*,void*,f32)->s32,
// fn_800058CC 2-arg void, Kenacosf (void*,f32)->f32, fn_8012772C
// (s32,s32,f32) void, fn_80271070 = cosf(f32)->f32.
// family=m2c range=0x801CB0C4-0x801CB5B0 size=1260B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 4.1% ([1]rev->4.1%).
#include "types.h"
#include "qb_constants.h"
#include "dolphin/SN_PS.h"
#include "structs.h"
extern char lbl_802ACFB8[];
extern f32 lbl_802ACFE4;
extern f32 lbl_802ACFE8;
extern f32 lbl_802ACFEC;
extern f32 lbl_802ACFF0;
extern f32 lbl_802ACFF4;
void fn_80125000(Unk_C71E6DE1 *);
s32 GetPair(s32, s32, void *, s32);
void fn_800058CC(CStruct *, CStruct *);
s32 fn_80005F80(void *, void *, f32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
f32 cosf(f32);
f32 Kenacosf(void *, f32);
f32 fn_80005E20(void *, void *);
void fn_8012772C(CStruct *, s32, f32);
typedef union { __ps_t p[2]; f32 f[4]; } U4;
s32 fn_801CB0C4(Unk_F45EEDBB *arg0, u32 arg1, CStruct *arg2, CScript *arg3) {
    U4 ctx8;
    U4 blk18;
    f32 sp38;
    f32 sp3C;
    f32 sp40;
    f32 spC;
    s32 var_r3;

    switch (arg1) {
    case QB_YAWBETWEEN: {
        char *p40 = (char *)arg0 + 0x20;
        void *out18 = &blk18;
        void *src;
        fn_80125000(&ctx8);
        GetPair(arg2, 0, &ctx8, 1);
        blk18.p[1] = ((Unk_073F5245 *)src)->unk0xC0;
        blk18.p[0] = ((Unk_073F5245 *)src)->unk0xB8;
        src = arg0->unk0xC;
        p40 += 0x20;
        fn_800058CC(out18, (char *)arg0 + 0x30);
        if (fn_80005F80(out18, p40, spC) == 0) {
            return 0;
        }
        if (fn_80005F80(out18, p40, ctx8.f[2]) == 0) {
            return 1;
        }
        var_r3 = 0;
        return var_r3;
    }
    case QB_YAWINGLEFT: {
        SN_PS_type v0;
        SN_PS_type v1;
        SN_PS_type c0;
        SN_PS_type c1;
        SN_PS_type pk;
        f32 mx;
        void *src = arg0->unk0xC;
        fn_800058CC(&ctx8, (char *)arg0 + 0x30);
        ctx8.p[0] = ((Unk_073F5245 *)src)->unk0xB8;
        ctx8.p[1] = ((Unk_073F5245 *)src)->unk0xC0;
        fn_800058CC(&ctx8, (char *)arg0 + 0x30);
        v0.ps = arg0->unk0x20;
        c0.ps = ctx8.p[0];
        v1.ps = arg0->unk0x28;
        c1.ps = ctx8.p[1];
        pk.ps = *(__ps_t *)(char *)lbl_802ACFB8;
        mx = v0.flt.hi * v1.flt.hi + c0.flt.hi * c1.flt.hi;
        if (mx > lbl_802ACFE8) {
            return 1;
        }
        return 0;
    }
    case QB_YAWINGRIGHT: {
        SN_PS_type v0;
        SN_PS_type v1;
        SN_PS_type c0;
        SN_PS_type c1;
        SN_PS_type pk;
        f32 mx;
        void *src = arg0->unk0xC;
        fn_800058CC(&ctx8, (char *)arg0 + 0x30);
        ctx8.p[0] = ((Unk_073F5245 *)src)->unk0xB8;
        ctx8.p[1] = ((Unk_073F5245 *)src)->unk0xC0;
        fn_800058CC(&ctx8, (char *)arg0 + 0x30);
        v0.ps = arg0->unk0x20;
        c0.ps = ctx8.p[0];
        v1.ps = arg0->unk0x28;
        c1.ps = ctx8.p[1];
        pk.ps = *(__ps_t *)(char *)lbl_802ACFB8;
        mx = v0.flt.hi * v1.flt.hi + c0.flt.hi * c1.flt.hi;
        if (mx > lbl_802ACFE8) {
            return 1;
        }
        return 0;
    }
    case QB_PITCHGREATERTHAN: {
        SN_PS_type p56;
        SN_PS_type q80;
        SN_PS_type q88;
        SN_PS_type pk;
        f32 ang;
        sp38 = lbl_802ACFE8;
        GetFloat(arg2, 0, &sp38, 1);
        q80.ps = *(__ps_t *)(arg0->unk0x64 + 128);
        q88.ps = *(__ps_t *)(arg0->unk0x64 + 136);
        pk.ps = *(__ps_t *)(char *)lbl_802ACFB8;
        p56.ps = arg0->unk0x38;
        ang = pk.flt.hi * p56.flt.hi;
        return sp38 < cosf(sp38 * lbl_802ACFEC) &&
               ang < q80.flt.hi + q88.flt.hi;
    }
    case QB_ABSOLUTEPITCHGREATERTHAN:
        sp3C = lbl_802ACFE8;
        GetFloat(arg2, 0, &sp3C, 1);
        return arg0->unk0x34 <
               cosf(sp3C * lbl_802ACFEC);
    case QB_ROLLGREATERTHAN:
        sp40 = lbl_802ACFE8;
        GetFloat(arg2, 0, &sp40, 1);
        ctx8.p[0] = arg0->unk0x20;
        ctx8.p[1] = arg0->unk0x28;
        fn_800058CC(&ctx8,
                    (char *)arg0->unk0x64 + 0x80);
        if (fn_80005F80(&ctx8, (char *)arg0 + 0x20, sp40) != 0) {
            var_r3 = 1;
            return var_r3;
        }
        var_r3 = 0;
        return var_r3;
    case QB_GETSLOPE: {
        s32 obj = arg3->unk0x18;
        void *o;
        f32 k = lbl_802ACFE8;
        f32 slope;
        o = arg0->unk0xC;
        ctx8.p[0] = *((__ps_t *)&((Unk_FFAD6788 *)o)->unk0x98);
        ctx8.p[1] = *((__ps_t *)&((Unk_FFAD6788 *)o)->unk0xA0);
        ((Unk_560A7BB5 *)&ctx8)->unk0x4 = k;
        slope = fn_80005E20((char *)o + 0x98, &ctx8);
        if (*((f32 *)&((Unk_FFAD6788 *)o)->unk0x9C) < k) {
            slope = -slope;
        }
        fn_8012772C(obj, QB_SLOPE, slope);
        fn_8012772C(obj, QB_CHANGEINSLOPE,
                    slope - arg0->unk0x60);
        arg0->unk0x60 = slope;
        return 1;
    }
    case QB_GETHEADING: {
        void *o = arg0->unk0xC;
        s32 obj = arg3->unk0x18;
        f32 v = Kenacosf(o, *((f32 *)&((Unk_FFAD6788 *)o)->unk0x98)) *
                lbl_802ACFF0;
        if (*((f32 *)&((Unk_FFAD6788 *)o)->unk0xA0) < lbl_802ACFE8) {
            v = lbl_802ACFF4 - v;
        }
        fn_8012772C(obj, QB_HEADING, v);
        fn_8012772C(obj, QB_COSINE, *((f32 *)&((Unk_FFAD6788 *)o)->unk0x98));
        fn_8012772C(obj, QB_SINE, *((f32 *)&((Unk_FFAD6788 *)o)->unk0xA0));
        return 1;
    }
    default:
        return 2;
    }
}
