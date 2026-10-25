// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801EC7C4-0x801ECD84 (1472B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"

extern __ps_t lbl_802AD278;
extern f32 lbl_802AD8F0;
extern f32 lbl_802AD8F4;
extern f32 lbl_802AD8F8;
extern f32 lbl_802AD8FC;
extern s32 lbl_80303150;
extern char lbl_802AD9EC[];
extern char lbl_802ADA70[];

s32 Tmr_GetTime(void);
s32 ContainsFlag(void *, s32);
f32 fn_801417B8(void *, s32);
s32 fn_80125A3C(void *, s32);
s32 GetFloat(void *, s32, f32 *, s32);
void fn_801C1FA4(void *, s32, f32);
void fn_801D657C(void *);
void fn_801D1458(void *, s32);
void fn_801EB624(void *);
void fn_801EC3F0(void *, void *);
void fn_8009F054(void *, s32, s32, f32);
void fn_800DF004(void *, void *, void *);

typedef union {
    f32 f;
    __ps_t p;
} F_PS;

typedef struct {
    char pad0x0[0x58];
    SN_PS_type unk0x58;
    SN_PS_type unk0x60;
    char pad0x68[0x20];
    SN_PS_type unk0x88;
    SN_PS_type unk0x90;
    char pad0x98[0x20];
    SN_PS_type unk0xB8;
    SN_PS_type unk0xC0;
} SkaterData;

typedef struct {
    char pad0x0[0x1C];
    s32 unk0x1C;
    char pad0x20[4];
    s32 unk0x24;
    s32 unk0x28;
    s32 unk0x2C;
    char pad0x30[0xC];
    s32 unk0x3C;
    s32 unk0x40;
    s32 unk0x44;
    char pad0x48[0x10];
    s32 unk0x58;
    char pad0x5C[4];
    s32 unk0x60;
    s32 unk0x64;
    s32 unk0x68;
    char pad0x6C[0xDC];
    u8 unk0x148;
} SkaterSub;

typedef struct {
    char pad0x0[0x5A];
    u8 unk0x5A;
} T170;

typedef struct {
    char pad0x0[0x30];
    s32 unk0x30;
} T15C4;

typedef struct {
    char pad0x0[0xC];
    SkaterData *unk0xC;
    char pad0x10[0x50];
    SN_PS_type unk0x60;
    SN_PS_type unk0x68;
    char pad0x70[0x2C];
    s32 unk0x9C;
    char pad0xA0[0xD0];
    T170 unk0x170;
    char pad0x1CB[0x149];
    s32 unk0x314;
    char pad0x318[0x24];
    s32 unk0x33C;
    char pad0x340[0x60];
    SN_PS_type unk0x3A0;
    SN_PS_type unk0x3A8;
    char pad0x3B0[0x40];
    s32 unk0x3F0;
    char pad0x3F4[0x178];
    s32 unk0x56C;
    char pad0x570[0x1034];
    void *unk0x15A4;
    void *unk0x15A8;
    char pad0x15AC[0x10];
    SkaterSub *unk0x15BC;
    char pad0x15C0[4];
    T15C4 *unk0x15C4;
} Arg0;

void fn_801EC7C4(Arg0 *arg0, void *arg1) {
    __ps_t v[2];
    f32 sp18;
    SN_PS_type dot0;
    SN_PS_type dot1;
    SN_PS_type dot2;
    F_PS s38;
    F_PS s40;
    f32 var_f31;
    f32 var_f1;
    s32 temp_r3;
    s32 t3f0;
    s32 temp_r30;
    s32 var_r30;
    T170 *p170;
    s32 z;
    f32 num;
    f32 den;
    f32 d0;

    temp_r30 = ContainsFlag(arg1, QB_NO_SOUND) ^ 1;
    switch (arg0->unk0x15BC->unk0x1C) {
    case 0:
        p170 = &arg0->unk0x170;
        fn_800DF004(arg0->unk0x15A4, lbl_802AD9EC, p170);
        if (arg0->unk0x15C4->unk0x30 != 0) {
            return;
        }
        arg0->unk0x3A0.ps = arg0->unk0xC->unk0x58.ps;
        arg0->unk0x3A8.ps = arg0->unk0xC->unk0x60.ps;
        if (temp_r30 != 0) {
            void *body0 = arg0->unk0x15A8;
            __ps_t A = arg0->unk0xC->unk0xB8.ps;
            __ps_t D = arg0->unk0xC->unk0xC0.ps;
            __ps_t t = __builtin_ps_merge00(__builtin_ps_mul(D, D), lbl_802AD278);
            dot0.ps = __builtin_ps_madd(A, A, t);
            dot0.ps = __builtin_ps_sum0(dot0.ps, dot0.ps, dot0.ps);
            dot0.ps = __builtin_ps_rsqrte(dot0.ps);
            dot0.ps = __builtin_ps_res(dot0.ps);
            num = dot0.flt.hi;
            den = fn_801417B8(arg0->unk0xC, QB_SKATER_MAX_MAX_SPEED_STAT);
            fn_801C1FA4(body0, p170->unk0x5A, num / den);
        }
        fn_801D657C(arg0);
        {
            s32 *p = (s32 *) ((u8 *) arg0->unk0x15BC + 0x60);
            if (p[1] != 1) {
                p[1] = 1;
                p[2] = lbl_80303150 + Tmr_GetTime();
            }
        }
        break;
    case 1:
        if (temp_r30 != 0) {
            void *body1 = arg0->unk0x15A8;
            __ps_t A = arg0->unk0xC->unk0xB8.ps;
            __ps_t D = arg0->unk0xC->unk0xC0.ps;
            __ps_t t = __builtin_ps_merge00(__builtin_ps_mul(D, D), lbl_802AD278);
            dot1.ps = __builtin_ps_madd(A, A, t);
            dot1.ps = __builtin_ps_sum0(dot1.ps, dot1.ps, dot1.ps);
            dot1.ps = __builtin_ps_rsqrte(dot1.ps);
            dot1.ps = __builtin_ps_res(dot1.ps);
            num = dot1.flt.hi;
            den = fn_801417B8(arg0->unk0xC, QB_SKATER_MAX_MAX_SPEED_STAT);
            fn_801C1FA4(body1, arg0->unk0x170.unk0x5A, num / den);
        }
        break;
    case 4:
        if (temp_r30 != 0) {
            void *body2 = arg0->unk0x15A8;
            __ps_t A = arg0->unk0xC->unk0xB8.ps;
            __ps_t D = arg0->unk0xC->unk0xC0.ps;
            __ps_t t = __builtin_ps_merge00(__builtin_ps_mul(D, D), lbl_802AD278);
            dot2.ps = __builtin_ps_madd(A, A, t);
            dot2.ps = __builtin_ps_sum0(dot2.ps, dot2.ps, dot2.ps);
            dot2.ps = __builtin_ps_rsqrte(dot2.ps);
            dot2.ps = __builtin_ps_res(dot2.ps);
            num = dot2.flt.hi;
            den = fn_801417B8(arg0->unk0xC, QB_SKATER_MAX_MAX_SPEED_STAT);
            fn_801C1FA4(body2, arg0->unk0x15BC->unk0x148, num / den);
        }
        break;
    }
    temp_r3 = fn_80125A3C((void *) QB_SKATER_MAX_TENSE_TIME, 1);
    t3f0 = arg0->unk0x3F0;
    arg0->unk0x3F0 = (temp_r3 <= t3f0) ? temp_r3 : t3f0;
    var_r30 = 0;
    if ((arg0->unk0x15BC->unk0x40 != 0) ||
        ((arg0->unk0x15BC->unk0x1C == 0) && (arg0->unk0x15BC->unk0x58 != 0))) {
        var_r30 = 1;
    }
    if (ContainsFlag(arg1, QB_BONELESSHEIGHT) != 0) {
        if (var_r30 != 0) {
            var_f31 = fn_801417B8(arg0->unk0xC, QB_PHYSICS_BONELESS_AIR_JUMP_SPEED_STAT);
            var_f1 = fn_801417B8(arg0->unk0xC, QB_PHYSICS_BONELESS_AIR_JUMP_SPEED_MIN_STAT);
        } else {
            var_f31 = fn_801417B8(arg0->unk0xC, QB_PHYSICS_BONELESS_JUMP_SPEED_STAT);
            var_f1 = fn_801417B8(arg0->unk0xC, QB_PHYSICS_BONELESS_JUMP_SPEED_MIN_STAT);
        }
    } else if (var_r30 != 0) {
        var_f31 = fn_801417B8(arg0->unk0xC, QB_PHYSICS_AIR_JUMP_SPEED_STAT);
        var_f1 = fn_801417B8(arg0->unk0xC, QB_PHYSICS_AIR_JUMP_SPEED_MIN_STAT);
    } else {
        var_f31 = fn_801417B8(arg0->unk0xC, QB_PHYSICS_JUMP_SPEED_STAT);
        var_f1 = fn_801417B8(arg0->unk0xC, QB_PHYSICS_JUMP_SPEED_MIN_STAT);
    }
    z = 0;
    d0 = lbl_802AD8F0;
    sp18 = ((var_f31 - var_f1) *
            (((f32) (f64) arg0->unk0x3F0 - d0) /
             ((f32) (f64) temp_r3 - d0))) + var_f1;
    GetFloat(arg1, QB_SPEED, &sp18, 0);
    {
        s32 *p = (s32 *) ((u8 *) arg0->unk0x15BC + 0x24);
        if (p[1] != 0) {
            p[1] = z;
            p[2] = lbl_80303150 + Tmr_GetTime();
        }
    }
    if ((arg0->unk0x15BC->unk0x40 != 0) &&
        (arg0->unk0xC->unk0xB8.flt.lo < d0)) {
        SN_PS_type *u;
        s38.f = sp18;
        v[0] = __builtin_ps_muls0(arg0->unk0x60.ps, s38.p);
        v[1] = __builtin_ps_muls0(arg0->unk0x68.ps, s38.p);
        u = &arg0->unk0xC->unk0xB8;
        u[0].ps = __builtin_ps_add(u[0].ps, v[0]);
        u[1].ps = __builtin_ps_add(u[1].ps, v[1]);
        sp18 = d0;
        {
            s32 *p = (s32 *) ((u8 *) arg0->unk0x15BC + 0x3C);
            if (p[1] != 0) {
                p[1] = z;
                p[2] = lbl_80303150 + Tmr_GetTime();
            }
        }
        arg0->unk0x314 = z;
    } else if (arg0->unk0xC->unk0xB8.flt.lo < lbl_802AD8F0) {
        arg0->unk0xC->unk0xB8.flt.lo = lbl_802AD8F0;
    }
    arg0->unk0xC->unk0xB8.flt.lo = arg0->unk0xC->unk0xB8.flt.lo + sp18;
    if (arg0->unk0xC->unk0x88.flt.lo < lbl_802AD8F4) {
        SkaterData *u;
        s40.f = lbl_802AD8FC;  /* MEASURED 2026-10-07: naming this broadcast (m40) was score-neutral (95.65%) -> reverted */
        arg0->unk0xC->unk0xB8.flt.lo =
            arg0->unk0xC->unk0xB8.flt.lo - (sp18 * lbl_802AD8F8);
        u = arg0->unk0xC;
        {
            __ps_t a0 = __builtin_ps_muls0(u->unk0x88.ps, s40.p);
            __ps_t a1 = __builtin_ps_muls0(u->unk0x90.ps, s40.p);
            v[0] = a0;
            v[1] = a1;
        }
        u->unk0x58.ps = __builtin_ps_add(u->unk0x58.ps, v[0]);
        u->unk0x60.ps = __builtin_ps_add(u->unk0x60.ps, v[1]);
    }
    if ((arg0->unk0x15BC->unk0x1C == 4) ||
        ((arg0->unk0x15BC->unk0x1C == 1) && (arg0->unk0x9C == 4))) {
        fn_801EB624(arg0);
    }
    if (arg0->unk0x33C != 0) {
        fn_801EC3F0(arg0, lbl_802ADA70);
    }
    fn_801D1458(arg0, 1);
    arg0->unk0x56C = lbl_80303150 + Tmr_GetTime();
    fn_8009F054(arg0->unk0xC, QB_SKATERJUMP, 0, lbl_802AD8F0);
}
