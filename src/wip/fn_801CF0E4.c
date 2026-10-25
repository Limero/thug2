// WIP DRAFT (non-matching) — hand-rebuilt paired-single vector pipeline
// family=m2c range=0x801CF0E4-0x801CF370 size=652B
// FLAG: -mps-float
// STATUS: PARKED — semantic reconstruction; ps_diff.py: 23.2% (33/142), score_body.py: DIFF 20.2%.
// BLOCKER: PS opcodes emit, but FPR roles, frame reload/store staging, and object-pointer scheduling diverge.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"

extern char lbl_802AD278[];
extern f32 lbl_802AD32C;
extern f32 lbl_802AD330;
extern f32 lbl_802AD334;

typedef union {
    __ps_t ps;
    f32 f[2];
} PSU;

typedef struct {
    char pad0[0x78];
    __ps_t v78;
    __ps_t v80;
    __ps_t v88;
    __ps_t v90;
    __ps_t v98;
    __ps_t vA0;
    __ps_t vA8;
    __ps_t vB0;
    __ps_t vB8;
    __ps_t vC0;
} TARGET_OBJ;

typedef struct {
    PSU p[8];
} FRAME;

#define OBJ ((TARGET_OBJ *)(s32)arg0->unk0xC)

s32 fn_801CF0E4(Unk_6F11F76C *arg0) {
    FRAME fr;
    s32 ret;

    {
        __ps_t a;
        __ps_t b;
        __ps_t z;
        __ps_t d;
        PSU dot;
        f32 lim;
        {
            register f32 t __asm__("fr0");
            register f32 l __asm__("fr13");
            z = *(__ps_t *)&lbl_802AD278;
            b = OBJ->vC0;
            a = OBJ->vB8;
            lim = lbl_802AD32C;
            d = __builtin_ps_mul(b, b);
            d = __builtin_ps_merge00(d, z);
            d = __builtin_ps_madd(a, a, d);
            dot.ps = __builtin_ps_sum0(d, d, d);
            fr.p[2].ps = dot.ps;
            t = fr.p[2].f[0];
            __asm__("fmr %0,%1" : "=f"(l) : "f"(t));
            if (l < lim) {
                return 1;
            }
            OBJ->vA0 = b;
            OBJ->v98 = a;
        }
    }

    {
        __ps_t a;
        __ps_t b;
        __ps_t z;
        __ps_t d;
        __ps_t r;
        __ps_t s;
        __ps_t o;
        PSU dot;
        f32 lim;
        f32 one;
        z = *(__ps_t *)&lbl_802AD278;
        a = OBJ->v98;
        b = OBJ->vA0;
        lim = lbl_802AD330;
        d = __builtin_ps_mul(b, b);
        d = __builtin_ps_merge00(d, z);
        d = __builtin_ps_madd(a, a, d);
        dot.ps = __builtin_ps_sum0(d, d, d);
        if (dot.f[0] > 0.0f) {
            r = __builtin_ps_rsqrte(dot.ps);
            s = __builtin_ps_muls0(a, r);
            OBJ->v98 = s;
            fr.p[3].ps = r;
            one = lbl_802AD334;
            fr.p[3].f[1] = one;
            r = fr.p[3].ps;
            o = __builtin_ps_mul(b, a);
            OBJ->vA0 = o;
        }
    }

    {
        __ps_t a;
        __ps_t b;
        __ps_t c;
        __ps_t d;
        __ps_t e;
        __ps_t f;
        __ps_t g;
        __ps_t h;
        __ps_t j;
        __ps_t n;
        f32 one;
        a = OBJ->v88;
        b = OBJ->v98;
        c = OBJ->v90;
        d = OBJ->vA0;
        e = __builtin_ps_merge10(a, c);
        __asm__("" : "+f"(e));
        f = __builtin_ps_merge10(b, d);
        __asm__("" : "+f"(f));
        e = __builtin_ps_mul(e, b);
        __asm__("" : "+f"(e));
        f = __builtin_ps_mul(a, f);
        __asm__("" : "+f"(f));
        g = __builtin_ps_merge00(b, d);
        __asm__("" : "+f"(g));
        h = __builtin_ps_merge00(c, a);
        __asm__("" : "+f"(h));
        h = __builtin_ps_mul(h, g);
        __asm__("" : "+f"(h));
        f = __builtin_ps_sub(f, e);
        __asm__("" : "+f"(f));
        j = __builtin_ps_merge00(f, f);
        __asm__("" : "+f"(j));
        *(volatile __ps_t *)&fr.p[4].ps = j;
        one = lbl_802AD334;
        *(volatile f32 *)&fr.p[4].f[1] = one;
        n = __builtin_ps_merge10(h, h);
        __asm__("" : "+f"(n));
        h = __builtin_ps_sub(h, n);
        __asm__("" : "+f"(h));
        j = *(volatile __ps_t *)&fr.p[4].ps;
        f = __builtin_ps_merge10(f, h);
        __asm__("" : "+f"(f));
        fr.p[0].ps = f;
        __asm__("ps_mr %0, %1" : "=f"(a) : "f"(j));
        fr.p[1].ps = a;
        OBJ->v78 = f;
        OBJ->v80 = fr.p[1].ps;
    }

    {
        __ps_t a;
        __ps_t b;
        __ps_t c;
        __ps_t d;
        __ps_t e;
        __ps_t f;
        __ps_t g;
        __ps_t h;
        __ps_t j;
        __ps_t n;
        f32 one;
        a = OBJ->v98;
        b = OBJ->v78;
        c = OBJ->vA0;
        d = OBJ->v80;
        e = __builtin_ps_merge10(a, c);
        f = __builtin_ps_merge10(b, d);
        e = __builtin_ps_mul(e, b);
        f = __builtin_ps_mul(a, f);
        g = __builtin_ps_merge00(b, d);
        h = __builtin_ps_merge00(c, a);
        h = __builtin_ps_mul(h, g);
        f = __builtin_ps_sub(f, e);
        j = __builtin_ps_merge00(f, f);
        *(volatile __ps_t *)&fr.p[6].ps = j;
        one = lbl_802AD334;
        *(volatile f32 *)&fr.p[6].f[1] = one;
        n = __builtin_ps_merge10(h, h);
        h = __builtin_ps_sub(h, n);
        j = *(volatile __ps_t *)&fr.p[6].ps;
        f = __builtin_ps_merge10(f, h);
        fr.p[0].ps = f;
        __asm__("ps_mr %0, %1" : "=f"(a) : "f"(j));
        fr.p[1].ps = a;
        OBJ->v88 = f;
        OBJ->v90 = fr.p[1].ps;
    }

    {
        __ps_t a;
        __ps_t b;
        __ps_t z;
        __ps_t d;
        __ps_t r;
        __ps_t s;
        __ps_t o;
        f32 one;
        PSU dot;
        z = *(__ps_t *)&lbl_802AD278;
        a = OBJ->v88;
        b = OBJ->v90;
        d = __builtin_ps_mul(b, b);
        d = __builtin_ps_merge00(d, z);
        d = __builtin_ps_madd(a, a, d);
        dot.ps = __builtin_ps_sum0(d, d, d);
        if (dot.f[0] > 0.0f) {
            r = __builtin_ps_rsqrte(dot.ps);
            s = __builtin_ps_muls0(b, r);
            OBJ->v88 = s;
            fr.p[7].ps = r;
            one = lbl_802AD334;
            fr.p[7].f[1] = one;
            r = fr.p[7].ps;
            o = __builtin_ps_mul(a, b);
            OBJ->v90 = o;
        }
    }

    ret = 1;
    *(__ps_t *)((char *)arg0 + 0x20) = OBJ->v78;
    *(__ps_t *)((char *)arg0 + 0x28) = OBJ->v80;
    *(__ps_t *)((char *)arg0 + 0x30) = OBJ->v88;
    *(__ps_t *)((char *)arg0 + 0x38) = OBJ->v90;
    *(__ps_t *)((char *)arg0 + 0x40) = OBJ->v98;
    *(__ps_t *)((char *)arg0 + 0x48) = OBJ->vA0;
    *(__ps_t *)((char *)arg0 + 0x50) = OBJ->vA8;
    *(__ps_t *)((char *)arg0 + 0x58) = OBJ->vB0;
    return ret;
}
