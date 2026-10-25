// PARKED 2026-10-03 — PS/paired-single function (`// extra_cflags: -mps-float`).
// NOT a compile failure: my single-variant harness simply omitted the draft's
// per-object flag.  Compile with `-mps-float` (tools/test_wip_drafts.py adds
// it automatically for `__ps_t` bodies).  FPR/VMX wall, not a candidate for
// plain GPR work.
//
// family=m2c range=0x80004518-0x800048A4 size=908B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "dolphin/SN_PS.h"

extern const sn_ps lbl_8028FBC8;
extern f32 lbl_8028FCA0;
extern f32 lbl_8028FCA4;

typedef struct { sn_ps a; sn_ps b; } Elem;

#define MADD3(x) x, x, x

#define LEN2(R) \
    __builtin_ps_sum0(MADD3(__builtin_ps_madd((R).a, (R).a, \
            __builtin_ps_merge00(__builtin_ps_mul((R).b, (R).b), lbl_8028FBC8))))

#define CROSS(P, Q) \
    __builtin_ps_sub( \
        __builtin_ps_mul((P).a, __builtin_ps_merge10((Q).a, (Q).b)), \
        __builtin_ps_mul(__builtin_ps_merge10((P).a, (P).b), (Q).a))

#define PROD(P, Q) \
    __builtin_ps_mul(__builtin_ps_merge00((P).b, (P).a), \
                     __builtin_ps_merge00((Q).a, (Q).b))

void fn_80004518(Elem *arg0, s32 arg1) {
    sn_ps t[2];
    SN_PS_type v0, v1;
    SN_PS_type sa1, na1, sa2, na2;
    SN_PS_type sb1, nb1, sb2, nb2;
    sn_ps p, q, rr, ln;
    s32 i1, i2;

    i1 = arg1 + 1;
    if (arg1 == 2) {
        i1 = 0;
    }
    i2 = i1 + 1;
    if (i1 == 2) {
        i2 = 0;
    }

    p = __builtin_ps_madd(arg0[i2].a, arg0[arg1].a,
            __builtin_ps_merge00(__builtin_ps_mul(arg0[i2].b, arg0[arg1].b),
                                 lbl_8028FBC8));
    v0.ps = __builtin_ps_sum0(p, p, p);
    p = __builtin_ps_madd(arg0[arg1].a, arg0[i1].a,
            __builtin_ps_merge00(__builtin_ps_mul(arg0[arg1].b, arg0[i1].b),
                                 lbl_8028FBC8));
    v1.ps = __builtin_ps_sum0(p, p, p);

    if (__builtin_fabsf(v0.flt.hi) < __builtin_fabsf(v1.flt.hi)) {
        p = CROSS(arg0[i2], arg0[arg1]);
        q = __builtin_ps_merge00(p, p);
        sa1.ps = q;
        sa1.flt.lo = lbl_8028FCA0;
        rr = PROD(arg0[i2], arg0[arg1]);
        rr = __builtin_ps_sub(rr, __builtin_ps_merge10(rr, rr));
        arg0[i1].a = __builtin_ps_merge10(p, rr);
        t[0] = arg0[i1].a;
        t[1] = sa1.ps;
        arg0[i1].b = t[0];

        ln = LEN2(arg0[i1]);
        if ((f32)ln > lbl_8028FCA4) {
            q = __builtin_ps_rsqrte(ln);
            arg0[i1].a = __builtin_ps_muls0(arg0[i1].a, q);
            na1.ps = q;
            na1.flt.lo = lbl_8028FCA0;
            arg0[i1].b = __builtin_ps_mul(arg0[i1].b, na1.ps);
        }

        p = CROSS(arg0[arg1], arg0[i1]);
        q = __builtin_ps_merge00(p, p);
        sa2.ps = q;
        sa2.flt.lo = lbl_8028FCA0;
        rr = PROD(arg0[arg1], arg0[i1]);
        rr = __builtin_ps_sub(rr, __builtin_ps_merge10(rr, rr));
        arg0[i2].a = __builtin_ps_merge10(p, rr);
        t[0] = arg0[i2].a;
        t[1] = sa2.ps;
        arg0[i2].b = t[0];

        ln = LEN2(arg0[i2]);
        if ((f32)ln > lbl_8028FCA4) {
            q = __builtin_ps_rsqrte(ln);
            arg0[i2].a = __builtin_ps_muls0(arg0[i2].a, q);
            na2.ps = q;
            na2.flt.lo = lbl_8028FCA0;
            arg0[i2].b = __builtin_ps_mul(arg0[i2].b, na2.ps);
        }
    } else {
        p = CROSS(arg0[arg1], arg0[i1]);
        q = __builtin_ps_merge00(p, p);
        sb1.ps = q;
        sb1.flt.lo = lbl_8028FCA0;
        rr = PROD(arg0[arg1], arg0[i1]);
        rr = __builtin_ps_sub(rr, __builtin_ps_merge10(rr, rr));
        arg0[i2].a = __builtin_ps_merge10(p, rr);
        t[0] = arg0[i2].a;
        t[1] = sb1.ps;
        arg0[i2].b = t[0];

        ln = LEN2(arg0[i2]);
        if ((f32)ln > lbl_8028FCA4) {
            q = __builtin_ps_rsqrte(ln);
            arg0[i2].a = __builtin_ps_muls0(arg0[i2].a, q);
            nb1.ps = q;
            nb1.flt.lo = lbl_8028FCA0;
            arg0[i2].b = __builtin_ps_mul(arg0[i2].b, nb1.ps);
        }

        p = CROSS(arg0[i2], arg0[arg1]);
        q = __builtin_ps_merge00(p, p);
        sb2.ps = q;
        sb2.flt.lo = lbl_8028FCA0;
        rr = PROD(arg0[i2], arg0[arg1]);
        rr = __builtin_ps_sub(rr, __builtin_ps_merge10(rr, rr));
        arg0[i1].a = __builtin_ps_merge10(p, rr);
        t[0] = arg0[i1].a;
        t[1] = sb2.ps;
        arg0[i1].b = t[0];

        ln = LEN2(arg0[i1]);
        if ((f32)ln > lbl_8028FCA4) {
            q = __builtin_ps_rsqrte(ln);
            arg0[i1].a = __builtin_ps_muls0(arg0[i1].a, q);
            nb2.ps = q;
            nb2.flt.lo = lbl_8028FCA0;
            arg0[i1].b = __builtin_ps_mul(arg0[i1].b, nb2.ps);
        }
    }
}