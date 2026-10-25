// fn_80040BE8 — WIP draft (non-matching).
// Status: 36.75% masked, 1864B (want 1872B). The local frame layout now
// matches the original (byte-lerp scratch at 0x18/0x38/0x3c, struct fields
// 0x88/0xd0/0x128): feeding the colour words through one `u32` local keeps
// the stack slots at the original offsets even though the callee saves ten
// GPRs (want six). The copy path reaches the 0x454 marker at the same
// length, the final colour pack is exact, and the interpolation block reads
// each pair's four operands before computing, so the f18/f1C pair stores
// 0x1C then 0x18 as in the original. The parent transform uses the G2
// p-local form and is 69 insns (want 71; the G1/G4 parent-pointer
// materialisations are missing).
//
// Verified: prototypes and struct offsets; byte-lerp xor form (one
// 0x4330000080000000 constant); frame-local offsets; colour pack order;
// interpolation pair order.
//
// Open: saved-register set is larger than the original (the colour-loop
// pool-base materialisations and the b2 xor-conversion keep extra GPRs
// live); transform is two insns short; the fn_80024344 result is copied to
// a temp instead of staying in f1; the flags check lacks a dead register
// copy; o-copy/tail still shifted.
//
// Ruled out: (f32)(f64) casts (two-constant form); s8 union fields (sign
// extensions); all-channel word shifts (larger frame); scheduling and
// optimisation flags; result-temp-only transform; G1/G4 p-locals; struct
// copies (integer copies); separate word locals for cd/cs (loses the stack
// alignment).
// family=m2c range=0x80040BE8-0x80041338 size=1872B
// FLAG: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_80292350;
extern f32 lbl_80292354;
extern f32 lbl_80292358;
extern f64 lbl_80292360;
extern f32 lbl_80292368;
extern f32 lbl_8029236C;
extern f64 lbl_80292370;

s32 fn_800145AC(void);
f32 cosf(f32);
f32 sinf(f32);
void CScreenElement_SetChildLockState(void *, s32);
s32 fn_8005DD6C(s32);
f32 fn_80024344(s32, s32, void *, void *, void *);
void CScreenElement_SetScale(void *, s32, s32, f32, f32);
void fn_8004195C(void *, void *);

typedef union {
    s32 w;
    struct { u8 b0; u8 b1; u8 b2; u8 b3; } b;
} CU;

typedef struct {
    f32 f00;
    char pad04[4];
    __ps_t p08;
    __ps_t p10;
    f32 f18;
    f32 f1C;
    s32 f20;
    f32 f24;
    f32 f28;
    f32 f2C;
    f32 f30;
    f32 f34;
    f32 f38;
    f32 f3C;
    CU f40;
    s32 f44;
} VT;

typedef struct {
    char pad00[0x0C];
    s32 flags;
    char pad10[0x118];
    VT v128;
} ParS;

typedef struct {
    char pad00[0x58];
    s16 vtOff;
    char pad5A[2];
    void (*vtFn)(void *);
} VObj;

struct SelfS {
    char pad00[8];
    VObj *vt;
    s32 flags;
    char pad10[0x34];
    s32 cnt;
    char pad48[0x10];
    ParS *par;
    char pad5C[8];
    struct SelfS *child;
    char pad68[8];
    struct SelfS *next;
    char pad74[0x14];
    VT v88;
    VT vD0;
    s32 t118;
    u32 t11C;
    f32 a120;
    f32 a124;
    VT v128;
};

void fn_80040BE8(struct SelfS *arg0) {
    struct {
        f32 sp8;
        f32 spC;
        s32 sp10;
        CU sp14;
        CU cd;
        CU cs;
    } fr;
    s32 fl0;
    s32 var_r29 = 0;
    s32 t_28;
    u32 el;
    u32 dur;
    f32 f_0;
    f32 f_1;
    f32 f_2;
    f32 f_29;
    f32 f_30;
    f32 f_31;
    f32 f_11;
    ParS *par;
    u32 nu;
    s32 i_0;
    struct SelfS *cur;

    t_28 = fn_800145AC();
    arg0->cnt = arg0->cnt + 1;
    CScreenElement_SetChildLockState(arg0, 1);
    if (arg0->flags & 0x80000) {
        VT *s;
        s = &arg0->vD0;
        f_1 = fn_80024344(fn_8005DD6C(0), (s32)arg0 + 0xD8, &fr.sp8, &fr.spC, &fr.sp10);
        if (f_1 >= lbl_80292350) {
            i_0 = fr.sp10;
            f_0 = fr.sp8;
            f_2 = fr.spC;
            s->f20 = i_0;
            s->f18 = f_0;
            s->f1C = f_2;
            if (!(arg0->flags & 0x800000)) {
                CScreenElement_SetScale(arg0, 1, 0, f_1, f_1);
            }
            arg0->flags = arg0->flags & ~0x100000;
        } else {
            s->f18 = lbl_80292354;
            s->f1C = lbl_80292358;
            arg0->flags = arg0->flags | 0x100000;
        }
        fn_8004195C(arg0, s);
        arg0->flags = arg0->flags | 0x400;
    }
    fl0 = arg0->flags;
    if ((fl0 & 0x40400) == 0x400) {
        dur = arg0->t11C;
        if (dur != 0) {
            VT *d;
            VT *s;
            el = (u32)(t_28 - arg0->t118);
            f_30 = (f32)(f64)el / (f32)(f64)dur;
            if (el >= dur) {
                arg0->t11C = 0;
                f_30 = lbl_80292368;
            }
            switch ((arg0->flags >> 8) & 3) {
            case 1:
                f_29 = f_30 + f_30 - f_30 * f_30;
                break;
            case 2:
                f_29 = f_30 * f_30;
                break;
            case 3:
                f_29 = (lbl_8029236C - (f_30 + f_30)) * f_30 * f_30;
                break;
            default:
                f_29 = f_30;
                break;
            }
            d = &arg0->v88;
            s = &arg0->vD0;
            f_11 = (f_29 - arg0->a120) / (lbl_80292368 - arg0->a120);
            f_31 = (f_30 - arg0->a124) / (lbl_80292368 - arg0->a124);
            {
                f32 a, b, c, e;
                a = s->f18;
                b = s->f1C;
                c = d->f18;
                e = d->f1C;
                d->f1C = (b - e) * f_11 + e;
                d->f18 = (a - c) * f_11 + c;
            }
            {
                f32 a, b, c, e;
                a = s->f2C;
                b = s->f30;
                c = d->f2C;
                e = d->f30;
                d->f2C = (a - c) * f_31 + c;
                d->f30 = (b - e) * f_31 + e;
            }
            d->f3C = (s->f3C - d->f3C) * f_31 + d->f3C;
            d->f00 = (s->f00 - d->f00) * f_31 + d->f00;
            fn_8004195C(arg0, d);
            { u32 w; w = d->f40.w; fr.cd.w = w; w = s->f40.w; fr.cs.w = w; }
            fr.sp14.b.b0 = (u8)((s32)((u32)fr.cd.w >> 24) + (s32)((s32)((u32)fr.cs.w >> 24) - (s32)((u32)fr.cd.w >> 24)) * f_31);
            fr.sp14.b.b1 = (u8)(fr.cd.b.b1 + (fr.cs.b.b1 - fr.cd.b.b1) * f_31);
            fr.sp14.b.b2 = (u8)(fr.cd.b.b2 + (fr.cs.b.b2 - fr.cd.b.b2) * f_31);
            fr.sp14.b.b3 = (u8)(fr.cd.b.b3 + (fr.cs.b.b3 - fr.cd.b.b3) * f_31);
            {
                CU t;
                t.w = fr.sp14.w;
                d->f40.b.b0 = t.b.b0;
                d->f40.b.b1 = t.b.b1;
                d->f40.b.b2 = t.b.b2;
                d->f40.b.b3 = t.b.b3;
            }
            arg0->a120 = f_29;
            arg0->a124 = f_30;
        } else {
            VT *d;
            VT *s;
            d = &arg0->v88;
            s = &arg0->vD0;
            d->f00 = s->f00;
            d->p08 = s->p08;
            d->p10 = s->p10;
            d->f18 = s->f18;
            d->f1C = s->f1C;
            d->f20 = s->f20;
            d->f24 = s->f24;
            d->f28 = s->f28;
            d->f2C = s->f2C;
            d->f30 = s->f30;
            d->f34 = s->f34;
            d->f38 = s->f38;
            d->f3C = s->f3C;
            d->f40.w = s->f40.w;
            d->f44 = s->f44;
            arg0->flags = arg0->flags & ~0x400;
        }
        var_r29 = 1;
    }
    if ((arg0->par != NULL) && (arg0->par->flags & 0x800)) {
        var_r29 = 1;
    }
    arg0->flags = arg0->flags & ~0x800;
    if (var_r29 != 0) {
        par = arg0->par;
        if ((par != NULL) && !(arg0->flags & 0x80000)) {
            VT *o;
            VT *s;
            VT *p;
            f32 x;
            f32 y;
            o = &arg0->v128;
            s = &arg0->v88;
            x = s->f2C * arg0->par->v128.f2C;
            y = s->f30 * arg0->par->v128.f30;
            o->f2C = x;
            o->f30 = y;
            o->f3C = s->f3C + arg0->par->v128.f3C;
            f_31 = cosf(arg0->par->v128.f3C);
            f_1 = sinf(arg0->par->v128.f3C);
            p = &arg0->par->v128;
            x = s->f18 * p->f2C;
            y = s->f1C * p->f30;
            o->f1C = p->f28 + (f_1 * x + f_31 * y);
            o->f18 = p->f24 + (f_31 * x - f_1 * y);
            o->f00 = s->f00 * arg0->par->v128.f00;
            x = s->f24 * arg0->par->v128.f2C;
            y = s->f28 * arg0->par->v128.f30;
            o->f24 = arg0->par->v128.f24 + (f_31 * x - f_1 * y);
            o->f28 = arg0->par->v128.f28 + (f_1 * x + f_31 * y);
        } else {
            VT *o;
            VT *s;
            o = &arg0->v128;
            s = &arg0->v88;
            o->f00 = s->f00;
            o->p08 = s->p08;
            o->p10 = s->p10;
            o->f18 = s->f18;
            o->f1C = s->f1C;
            o->f20 = s->f20;
            o->f24 = s->f24;
            o->f28 = s->f28;
            o->f2C = s->f2C;
            o->f30 = s->f30;
            o->f34 = s->f34;
            o->f38 = s->f38;
            o->f3C = s->f3C;
            o->f40.w = s->f40.w;
            o->f44 = s->f44;
        }
        arg0->flags = arg0->flags | 0x800;
    }
    arg0->vt->vtFn((char *)arg0 + arg0->vt->vtOff);
    arg0->flags = arg0->flags & ~0x1000;
    if (arg0->flags & 0x20000) {
        arg0->flags = arg0->flags | 0x40000;
    }
    cur = arg0->child;
    for (; cur != NULL; cur = cur->next) {
        fn_80040BE8(cur);
    }
    if (arg0->cnt > 0) {
        arg0->cnt = arg0->cnt - 1;
    }
}
