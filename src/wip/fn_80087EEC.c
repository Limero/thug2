// PARKED 2026-10-05 (m2c-rewrite-partial): best measured 16.29% masked (was 1.4%),
// object 2308B vs want 2360B (13 words short). Full from-scratch C rewrite of the
// function from the retail disassembly: correct 0x1c8 frame + LR slot, correct
// callee arity/prototypes (8-arg fn_800231C4, non-variadic fn_8001E6F0/1FAA4,
// 3-float fn_8001F0F8), real P107C2266/SCR field types (f32 not s32 at +0x28/+0x48
// /+0x68/+0xF4/+0x110), the if(0x138) dot product via the house
// __builtin_ps_madd/ps_sum0/ps_merge00 idiom, the inline paired-single cross product,
// the quad-corner +-PS region, the (i&3) switch, and the 4x colour lerp with
// (f32)(f64) int->double conversions (signed -> xoris 0x8000 + lbl_802967A0 pool,
// unsigned -> no xoris + lbl_802967A8 pool, which is exactly retail's split).
// RESIDUAL: (a) object is 13 words short inside the colour-loop/tail region, so the
// tail is index-shifted; (b) prologue saves f28-f31 (4) where retail saves f27-f31
// (5) - adding the two loop-invariant 0.0/1.0 float locals that retail keeps in
// f28/f27 pushes the frame to 0x1d0/0x1d8 (one extra 8B spill home) and drops the
// score to ~4%, so the FPR count and the frame size trade off; (c) both PS regions
// (the 0x800880BC-0x80088194 cross product and 0x80088338-0x800883B4 quad) come out
// the right LENGTH but with a different operand order/schedule - the float-extraction
// .w[] reads make gcc round-trip through extra stack slots instead of keeping the
// values in FPRs; (d) retail's four-store v98 init ({0,1,0,0}) is store-merged to two
// by gcc; marking it volatile stops the merge but also kills the later psq_l CSE and
// costs ~12 points; (e) the dead-looking `mr r3..r8,r11,r30, r9` block at 0x8008844C
// DID reproduce from plain C, so it is not a dead-store puzzle.
// RULED OUT: explicit-union int->f64 (loses xoris -> xori, 5 sites); store-order and
// flag permutations; 8th arg on fn_800231C4 any other way; the two extra 8B cvt
// homes at 0x128/0x150 in the got (retail has one slot at 0x150).
// WIP DRAFT (non-matching) — C body reconstructed from the retail disassembly
// family=m2c range=0x80087EEC-0x80088824 size=2360B
// extra_cflags: -mps-float
#include "types.h"
#include "dolphin/SN_PS.h"
#include "qb_constants.h"
#include "structs.h"

typedef union { __ps_t p; f32 w[2]; } PSU;
typedef struct { PSU ps[2]; } V4;
typedef struct { f32 x, y, z; } V3;
typedef struct { char pad[0x18]; f32 f18, f1C, f20, f24, f28, f2C; } SCR;

typedef struct P107C2266 {
    char pad00[0x28];
    f32 f28;
    f32 f2C;
    f32 f30;
    char pad34[0x14];
    V4 v48;
    char pad58[0x10];
    f32 f68;
    f32 f6C;
    f32 f70;
    char pad74[0x20];
    s32 n94;
    char pad98[0x5C];
    f32 fF4;
    char padF8[0x8];
    SCR *p100;
    char pad104[0xC];
    f32 f110;
    u32 *p114;
    u32 *p118;
    u32 *p11C;
    char pad120[0x4];
    V3 *p124;
    s32 f128;
    char pad12C[0x8];
    s32 f134;
    s32 f138;
    char pad13C[0x34];
    u8 b170;
    u8 b171;
    char pad172[0x2];
    s32 f174;
} P107C2266;

typedef struct {
    s32 magic;
    u8 f04;
    u8 f05;
    u8 f06;
    char pad07[0x19];
    s32 v174;
    s16 kind;
    u8 b0;
    u8 b1;
    char pad28[4];
    u8 c0;
    u8 c1;
    u8 c2;
    u8 c3;
    s16 zero;
    char pad32[4];
    s8 flag;
    char pad3F[0x9];
} PT;

extern f32 lbl_80296794;
extern f32 lbl_80296798;
extern f32 lbl_802967B0;
extern f32 lbl_802967B4;
extern char lbl_80296758[];
extern char lbl_8037B674[];

void fn_800231C4(void *, void *, s32, s32, s32, s32, s32, s32);
void fn_8001E6F0(s32, s32, s32, s32, s32);
void fn_8001FAA4(s32, s32, s32, s32, s32);
void *fn_8001D440(void *, f32, f32, f32);
void *fn_8001D424(void *);
void PSVEC_CrossProduct(s32, s32, s32);
void PSVEC_Normalize(void *);
void PSVECScale(void *, void *, f32);
void fn_8001F2D8(s32, ...);
void fn_8001F0A0(s32, s32, s32);
void fn_8001F0F8(f32, f32, f32);
void fn_8001F1D4(s32);
void fn_8001F200(f32, f32);
void fn_8001F0F4(void);

void fn_80087EEC(P107C2266 *arg0) {
    PT pt;
    V4 v48;
    V4 v58;
    V4 v68;
    V4 v78;
    V4 v88;
    V4 v98;
    union { u32 c[4]; V4 v; } buf;
    V4 vB8;
    V4 vC8;
    V4 vD8;
    V4 vE8;
    V4 vF8;
    s32 c108;
    s32 c10C;
    SN_PS_type dot;
    PSU t118;
    f32 f11C;
    PSU t120;
    f32 f124;
    SCR *p;
    V3 *q;
    u32 *ca;
    u32 *cb;
    u8 *cp;
    u8 *ba;
    u8 *bb;
    s32 i;
    f32 t;
    f32 x;
    f32 y;
    f32 f4;
    f32 g29;
    f32 g30;
    f32 g31;
    s32 k;
    s32 jj;
    s32 d;
    s32 e;
    s32 m;
    s32 n;
    f32 s0;
    f32 s1;
    f32 s2;
    f32 cv;
    f32 cr;
    PSU A0;
    PSU A1;
    PSU V0;
    PSU V1;
    PSU t1;
    PSU t2;
    PSU t3;
    PSU t4;
    PSU t5;
    PSU t6;
    PSU t7;
    PSU t8;
    PSU t9;
    PSU u1;
    PSU u2;
    PSU u3;
    PSU u4;
    PSU u5;
    PSU u6;

    pt.magic = QB_PARTICLE;
    pt.f05 = 1;
    pt.f06 = 2;
    pt.f04 = 1;
    pt.v174 = arg0->f174;
    pt.kind = (arg0->f174 != 0) ? 0x61 : 0x60;
    pt.b0 = arg0->b170;
    pt.b1 = arg0->b171;
    pt.c2 = 0x80;
    pt.c0 = 0x80;
    pt.c1 = 0x80;
    pt.c3 = 0xFF;
    pt.zero = 0;
    pt.flag = 0;
    fn_800231C4(&pt, &pt.v174, 1, 1, 0, 0, 0x80, arg0->b171);
    fn_8001E6F0(0, 1, 4, 0, 0x7D);
    fn_8001FAA4(0, 0x3C, 0x3C, 0x3C, 0x3C);
    fn_8001D440(&v48, lbl_80296794, lbl_80296798, lbl_80296794);
    fn_8001D424(&v58);
    fn_8001D424(&v68);
    if (arg0->f138 != 0) {
        v98.ps[0].w[0] = lbl_80296794;
        v98.ps[0].w[1] = lbl_80296798;
        v98.ps[1].w[0] = lbl_80296794;
        v98.ps[1].w[1] = lbl_80296794;
        A1.p = arg0->v48.ps[1].p;
        t2.p = v98.ps[1].p;
        t1.p = __builtin_ps_mul(t2.p, A1.p);
        t1.p = __builtin_ps_merge00(t1.p, *(const __ps_t *)lbl_80296758);
        A0.p = arg0->v48.ps[0].p;
        t2.p = v98.ps[0].p;
        dot.ps = __builtin_ps_madd(t2.p, A0.p, t1.p);
        dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
        if (dot.flt.hi == lbl_80296798) {
            v98.ps[0].w[0] = lbl_80296798;
            v98.ps[1].w[1] = lbl_80296798;
            v98.ps[0].w[1] = lbl_80296794;
            v98.ps[1].w[0] = lbl_80296794;
        }
        A0.p = arg0->v48.ps[0].p;
        A1.p = arg0->v48.ps[1].p;
        buf.v.ps[0].w[0] = A0.w[0];
        buf.v.ps[0].w[1] = A0.w[1];
        buf.v.ps[1].w[0] = A1.w[0];
        buf.v.ps[1].w[1] = lbl_80296794;
        V0.p = v98.ps[0].p;
        V1.p = v98.ps[1].p;
        t1.p = __builtin_ps_merge10(A0.p, A1.p);
        t2.p = __builtin_ps_mul(t1.p, V0.p);
        t3.p = __builtin_ps_merge10(V0.p, V1.p);
        t3.p = __builtin_ps_mul(A0.p, t3.p);
        t4.p = __builtin_ps_merge00(A1.p, A0.p);
        t5.p = __builtin_ps_sub(t3.p, t2.p);
        t6.p = __builtin_ps_merge00(t5.p, t5.p);
        t118.p = t6.p;
        t7.p = __builtin_ps_merge00(V0.p, V1.p);
        t7.p = __builtin_ps_mul(t4.p, t7.p);
        t8.p = __builtin_ps_merge10(t7.p, t7.p);
        t7.p = __builtin_ps_sub(t7.p, t8.p);
        t9.p = __builtin_ps_merge10(t5.p, t7.p);
        t8.p = __builtin_ps_mul(t9.p, t1.p);
        v78.ps[0].p = t9.p;
        v78.ps[1].p = t6.p;
        u1.p = __builtin_ps_merge10(t9.p, t6.p);
        u2.p = __builtin_ps_merge00(t6.p, t9.p);
        u1.p = __builtin_ps_mul(u1.p, A0.p);
        t4.p = __builtin_ps_merge00(A0.p, A1.p);
        u2.p = __builtin_ps_mul(u2.p, t4.p);
        u3.p = __builtin_ps_sub(t8.p, u1.p);
        u4.p = __builtin_ps_merge00(u3.p, u3.p);
        t120.p = u4.p;
        u5.p = __builtin_ps_merge10(u2.p, u2.p);
        u6.p = __builtin_ps_sub(u2.p, u5.p);
        u5.p = __builtin_ps_merge10(u3.p, u6.p);
        v88.ps[0].p = u5.p;
        v88.ps[1].p = u4.p;
        v58.ps[0].w[0] = t9.w[0];
        v58.ps[0].w[1] = t9.w[1];
        v58.ps[1].w[0] = t6.w[0];
        v68.ps[0].w[0] = u5.w[0];
        v68.ps[0].w[1] = u5.w[1];
        v68.ps[1].w[0] = u4.w[0];
        buf.v.ps[0].p = u5.p;
        buf.v.ps[1].p = u4.p;
        f11C = lbl_80296798;
        f124 = lbl_80296798;
    } else {
        PSVEC_CrossProduct((s32)&v58, (s32)((char *)lbl_8037B674 + 0x20), (s32)&v48);
        PSVEC_CrossProduct((s32)&v68, (s32)&v58, (s32)((char *)lbl_8037B674 + 0x20));
    }
    PSVEC_Normalize(&v58);
    PSVEC_Normalize(&v68);
    if (arg0->f174 != 0) {
        fn_8001F2D8(3, 9, 1, 0xB, 1, 0xD, 1);
    } else {
        fn_8001F2D8(2, 9, 1, 0xB, 1);
    }
    if (arg0->n94 > 0) {
        fn_8001F0A0(0x80, 0, (arg0->n94 * 4) & 0xFFFC);
    }
    g31 = lbl_80296798;
    g30 = lbl_80296794;
    p = arg0->p100;
    q = arg0->p124;
    for (i = 0; i < arg0->n94; i++) {
        t = p->f28 / p->f2C;
        x = ((p->f20 - p->f18) * t) + p->f18;
        y = ((p->f24 - p->f1C) * t) + p->f1C;
        if (arg0->f134 != 0) {
            v78.ps[0].w[0] = q->x;
            v78.ps[0].w[1] = q->y;
            v78.ps[1].w[0] = q->z;
        } else {
            v78.ps[0].w[0] = q->x + arg0->f28;
            v78.ps[0].w[1] = q->y + arg0->f2C;
            v78.ps[1].w[0] = q->z + arg0->f30;
        }
        v78.ps[1].w[1] = g31;
        for (jj = 4; jj != 0; jj--) {
        }
        PSVECScale(&v58, &v88, x);
        PSVECScale(&v68, &v98, y);
        f4 = arg0->f110;
        v88.ps[1].w[1] = g30;
        v98.ps[1].w[1] = g30;
        A0.p = v78.ps[0].p;
        A1.p = v78.ps[1].p;
        V0.p = v88.ps[0].p;
        V1.p = v88.ps[1].p;
        t1.p = __builtin_ps_sub(A0.p, V0.p);
        t2.p = __builtin_ps_sub(A1.p, V1.p);
        t3.p = __builtin_ps_add(A0.p, V0.p);
        t4.p = __builtin_ps_add(A1.p, V1.p);
        vB8.ps[0].p = t3.p;
        vB8.ps[1].p = t4.p;
        V0.p = v98.ps[0].p;
        V1.p = v98.ps[1].p;
        t5.p = __builtin_ps_add(t3.p, V0.p);
        t6.p = __builtin_ps_add(t4.p, V1.p);
        vF8.ps[0].p = t5.p;
        vF8.ps[1].p = t6.p;
        buf.v.ps[0].p = t5.p;
        buf.v.ps[1].p = t6.p;
        t7.p = __builtin_ps_add(t1.p, V0.p);
        t8.p = __builtin_ps_add(t2.p, V1.p);
        vE8.ps[0].p = t7.p;
        vE8.ps[1].p = t8.p;
        t9.p = __builtin_ps_sub(t3.p, V0.p);
        u1.p = __builtin_ps_sub(t4.p, V1.p);
        vC8.ps[0].p = t9.p;
        vC8.ps[1].p = u1.p;
        u2.p = __builtin_ps_sub(t1.p, V0.p);
        u3.p = __builtin_ps_sub(t2.p, V1.p);
        vD8.ps[0].p = u2.p;
        vD8.ps[1].p = u3.p;
        if (!(f4 <= lbl_80296794)) {
            if (t < f4) {
                t = t / f4;
                ca = arg0->p114;
                cb = arg0->p118;
            } else {
                ca = arg0->p118;
                cb = arg0->p11C;
                t = (t - f4) / (g31 - f4);
            }
        } else {
            ca = arg0->p114;
            cb = arg0->p11C;
        }
        s0 = arg0->fF4 * arg0->f68;
        s1 = arg0->fF4 * arg0->f6C;
        s2 = arg0->fF4 * arg0->f70;
        cp = (u8 *)buf.c;
        ba = (u8 *)&c108;
        bb = (u8 *)&c10C;
        for (k = 0; k < 4; k++) {
            c108 = *(s32 *)&ca[0];
            c10C = *(s32 *)&cb[0];
            ca++;
            cb++;
            d = ba[0];
            cp[0] = (u8)(d + (s32)((f32)((f64)((s32)bb[0] - (s32)ba[0])) * t));
            e = ba[1];
            m = bb[1];
            cp[1] = (u8)(e + (s32)((f32)((f64)((s32)bb[1] - (s32)ba[1])) * t));
            n = ba[2];
            d = bb[2];
            cp[2] = (u8)(n + (s32)((f32)((f64)((s32)bb[2] - (s32)ba[2])) * t));
            n = ba[3];
            cp[3] = (u8)(n + (s32)((f32)((f64)((s32)bb[3] - (s32)ba[3])) * t));
            cr = cp[0];
            cv = (f32)((f64)cr) * s0;
            y = lbl_80296794;
            if (!(cv < lbl_80296794)) {
                y = cv;
                if (cv > lbl_802967B0) {
                    y = lbl_802967B0;
                }
            }
            cp[0] = (u8)(s32)y;
            cr = cp[1];
            cv = (f32)((f64)cr) * s1;
            y = lbl_80296794;
            if (!(cv < lbl_80296794)) {
                y = cv;
                if (cv > lbl_802967B0) {
                    y = lbl_802967B0;
                }
            }
            cp[1] = (u8)(s32)y;
            cr = cp[2];
            cv = (f32)((f64)cr) * s2;
            if (cv < lbl_80296794) {
                y = lbl_80296794;
            } else {
                y = cv;
                if (cv > lbl_802967B0) {
                    y = lbl_802967B0;
                }
            }
            cp[2] = (u8)(s32)y;
            cp += 4;
        }
        g29 = g30;
        g31 = lbl_80296798;
        g30 = lbl_80296794;
        if (arg0->f128 & 0x4000) {
            switch (i & 3) {
            case 0:
                g30 = lbl_802967B4;
                g29 = g30;
                break;
            case 2:
                g30 = lbl_802967B4;
                break;
            case 3:
                g29 = lbl_802967B4;
                break;
            }
            g31 = lbl_802967B4;
        }
        fn_8001F0F8(vC8.ps[0].w[0], vC8.ps[0].w[1], vC8.ps[1].w[0]);
        fn_8001F1D4((s32)buf.c[0]);
        if (arg0->f174 != 0) {
            fn_8001F200(g29 + g31 * g30, g30 + g31 * g30);
        }
        fn_8001F0F8(vD8.ps[0].w[0], vD8.ps[0].w[1], vD8.ps[1].w[0]);
        fn_8001F1D4((s32)buf.c[1]);
        if (arg0->f174 != 0) {
            fn_8001F200(g29 + g31, g31 * g30 + g30);
        }
        fn_8001F0F8(vE8.ps[0].w[0], vE8.ps[0].w[1], vE8.ps[1].w[0]);
        fn_8001F1D4((s32)buf.c[2]);
        if (arg0->f174 != 0) {
            fn_8001F200(g29 + g31, g30 + g31);
        }
        fn_8001F0F8(vF8.ps[0].w[0], vF8.ps[0].w[1], vF8.ps[1].w[0]);
        fn_8001F1D4((s32)buf.c[3]);
        if (arg0->f174 != 0) {
            fn_8001F200(g31 * g30 + g29, g30 + g31);
        }
        p++;
        q++;
    }
    if (arg0->n94 > 0) {
        fn_8001F0F4();
    }
}
