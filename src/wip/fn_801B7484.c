// WIP DRAFT (non-matching) — hand reconstruction of PS matrix/vec script cmd (big)
// family=m2c range=0x801B7484-0x801B7A48 size=1476B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// PARKED: allocator-order wall, same class as fn_801B6F8C @6.0% (-mps-float;
// tools/venv/bin/python <scratch> 0x801B7484 -mps-float -d).
// Full structure reconstructed: entry bdnz$ spin, THEN arm (16-float const
// init via r30 pointer web bp[2], 3x dot+normalize with rsqrte spill/reload,
// arg1 diff vec, clamp chain + acosf sqrt helper, lbl_803A2F2C lazy
// gate, fdivs scale, madds+b8e8), ELSE arm (8-pair copy, guard-gated arg1
// writes, dot+normalize, two PS cross products via merge10/00), shared
// fn_80004518(&c[0],2) + double fan-out. Remaining gaps are spill placement /
// saved-reg homes (want stmw r29 + f29/f30/f31 const caching across bl),
// frame -0x40 vs want 0x118.
// RECONSTRUCTION NOTES: rebuilt from PS disasm (m2c stub was empty). Same idiom
// set as parked fn_801B6F8C: dot+normalize blocks, clamp chain, lazy-init bss
// gate (lbl_803A2F2C/F28), entry bdnz$ spin window, two PS cross products in
// the flag!=0 arm, helper calls + double fan-out tail. Needs -mps-float.
// FLAG: -mps-float
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 6.2% ([11]rev->6.2%).
#include "types.h"
#include "structs.h"

extern void fn_8002B8E4(s32);
extern void fn_8002B8E8(void *, void *);
extern void fn_80004518(s32, s32);
extern f32 acosf(f32);
extern char lbl_802ABFB8[];
extern f32 lbl_802AC1EC;
extern f32 lbl_802AC1F0;
extern f32 lbl_802AC1F4;
extern f32 lbl_802AC1F8;
extern f32 lbl_802AC1FC;
extern f32 lbl_802AC200;
extern f32 lbl_802AC204;
extern f32 lbl_802AC208;
extern bool lbl_803A2F2C;
extern f32 lbl_803A2F28;

typedef volatile union { __ps_t p; f32 f[2]; } PU;

void fn_801B7484(Unk_0EAAF5DE *arg0, Unk_EA529D06 *arg1) {
    struct {
        volatile f32 c[16]; /* 0x08, 4B stride */
        PU p48;      /* 0x48 */
        PU p50;      /* 0x50 */
        PU v58;      /* 0x58 */
        PU v60;      /* 0x60 */
        PU d68;      /* 0x68 */
        PU d70;      /* 0x70 */
        PU n78;      /* 0x78 */
        PU p80;      /* 0x80 */
        PU m88;      /* 0x88 */
        PU m90;      /* 0x90 */
        PU sp98;     /* 0x98 */
        PU spA0;     /* 0xA0 */
        PU sA8;      /* 0xA8 */
        PU rbB0;     /* 0xB0 */
        PU spB8;     /* 0xB8 */
        PU spC0;     /* 0xC0 */
        PU spC8;     /* 0xC8 */
        PU spD0;     /* 0xD0 */
    } fr;
    union { __ps_t ps; f32 f[2]; } uv;
    __ps_t pk, tA, tB, CC, DD, EE, FF, rr, sc, rd, g;
    __ps_t dv1, dv2, e11, e12, ee, ff;
    __ps_t t1, t2, t3, t4, r1, r2, r3, u1, u2, u3, u4, q1, q2, q3, q4, sq, s1;
    __ps_t h, m10, m12v, mA, mB, sA, sB, w0, w1;
    __ps_t o0, o1, o2, o3, o4, o5, o6, o7;
    f32 k1, k2, k3, k4, k5, k6, k7, mag, prod, res, fv, gv;
    s32 flag, guard, i;

    flag = arg0->unk0x1C;
    {
        char *r8 = arg0->unk0xC;
        for (i = 4; i != 0; i--) {
        }
        fr.p48.p = ((Unk_D3AB821A *)r8)->unk0x58;
        fr.p50.p = ((Unk_D3AB821A *)r8)->unk0x60;
    }
    if (flag == 0) {
        k1 = lbl_802AC1F0;
        k2 = lbl_802AC1EC;
        pk = *(__ps_t *)&lbl_802ABFB8;
        {
            volatile f32 *bp = &fr.c[0];
            fr.c[1] = k1;
            fr.c[0] = k2;
            bp[2] = k1;
        }
        fr.c[3] = k1;
        fr.c[4] = k1;
        fr.c[5] = k1;
        fr.c[6] = k1;
        fr.c[7] = k1;
        fr.c[8] = k1;
        fr.c[9] = k1;
        fr.c[10] = k2;
        fr.c[11] = k1;
        fr.c[12] = k1;
        fr.c[13] = k1;
        fr.c[14] = k1;
        fr.c[15] = k2;
        /* dot #1 on (ret+0xF0, ret+0xF8) -> normalize into v58/v60 */
        tA = ((Unk_DF2324A8 *)arg0->unk0xC)->unk0xF0;
        fr.v58.p = tA;
        tB = ((Unk_DF2324A8 *)arg0->unk0xC)->unk0xF8;
        fr.v60.p = tB;
        CC = __builtin_ps_mul(tB, tB);
        DD = __builtin_ps_merge00(CC, pk);
        EE = __builtin_ps_madd(tA, tA, DD);
        FF = __builtin_ps_sum0(EE, EE, EE);
        uv.ps = FF;
        mag = uv.f[0];
        if (mag > k1) {
            rr = __builtin_ps_rsqrte(FF);
            g = rr;
            fr.sp98.p = g;
            sc = __builtin_ps_muls0(tA, rr);
            fr.v58.p = sc;
            fr.sp98.f[1] = k2;
            rd = fr.sp98.p;
            g = __builtin_ps_mul(tB, rd);
            fr.v60.p = g;
        }
        /* diff vec vs arg1 */
        fr.d68.f[0] = fr.p48.f[0] - *((f32 *)arg1);
        fr.d68.f[1] = k1;
        fr.d70.f[0] = fr.p50.f[0] - *((f32 *)arg1 + 2);
        fr.d70.f[1] = k2;
        /* dot #2 on (d68,d70) -> normalize */
        dv2 = fr.d70.p;
        pk = *(__ps_t *)&lbl_802ABFB8;
        dv1 = fr.d68.p;
        CC = __builtin_ps_mul(dv2, dv2);
        DD = __builtin_ps_merge00(CC, pk);
        EE = __builtin_ps_madd(dv1, dv1, DD);
        FF = __builtin_ps_sum0(EE, EE, EE);
        uv.ps = FF;
        mag = uv.f[0];
        if (mag > k1) {
            rr = __builtin_ps_rsqrte(FF);
            g = rr;
            fr.spA0.p = g;
            sc = __builtin_ps_muls0(dv1, rr);
            fr.d68.p = sc;
            fr.spA0.f[1] = k2;
            rd = fr.spA0.p;
            g = __builtin_ps_mul(dv2, rd);
            fr.d70.p = g;
        }
        /* dot of normalized vecs -> clamp -> sqrt helper -> threshold gate */
        e12 = fr.d70.p;
        e11 = fr.v60.p;
        ee = __builtin_ps_mul(e11, e12);
        ff = fr.v58.p;
        e12 = fr.d68.p;
        pk = *(__ps_t *)&lbl_802ABFB8;
        ee = __builtin_ps_merge00(ee, pk);
        ee = __builtin_ps_madd(ff, e12, ee);
        FF = __builtin_ps_sum0(ee, ee, ee);
        k3 = lbl_802AC1F8;
        k4 = lbl_802AC1F4;
        fr.sA8.p = FF;
        res = fr.sA8.f[0];
        if (res < k3) {
            res = k3;
        }
        fv = acosf(res);
        if (fv < k4) {
            fv = k4;
        }
        prod = prod * k5;
        k5 = k5 * k6;
        prod = arg0->unk0xA4;
        fv = __builtin_fabs(fv);
        k6 = lbl_802AC200;
        k5 = lbl_802AC1FC;
        if (!(fv > prod)) {
            fr.m88.p = fr.d68.p;
            fr.m90.p = fr.d70.p;
        } else {
            if (lbl_803A2F2C == 0) {
                f32 kf;
                lbl_803A2F2C = 1;
                kf = lbl_802AC204;
                lbl_803A2F28 = k6 * kf;
            }
            gv = lbl_803A2F28;
            k7 = lbl_802AC208;
            if (fv > gv) {
                gv = fv / gv;
                k7 = gv * k7;
            }
            fn_8002B8E4(&fr.m88);
            fr.rbB0.f[0] = k7;
            h = fr.rbB0.p;
            m10 = fr.v58.p;
            m12v = fr.v60.p;
            mA = fr.d68.p;
            mB = fr.d70.p;
            sA = __builtin_ps_sub(mA, m10);
            sB = __builtin_ps_sub(mB, m12v);
            sB = __builtin_ps_madds0(sB, m12v, h);
            fr.m90.p = sB;
            sA = __builtin_ps_madds0(sA, m10, h);
            fr.m88.p = sA;
            fn_8002B8E8(&fr.n78, &fr.m88);
            w0 = fr.n78.p;
            w1 = fr.p80.p;
            *(__ps_t *)((char *)fr.c + 32) = w0;
            pk = *(__ps_t *)&lbl_802ABFB8;
            CC = __builtin_ps_mul(w1, w1);
            DD = __builtin_ps_merge00(CC, pk);
            EE = __builtin_ps_madd(w0, w0, DD);
            FF = __builtin_ps_sum0(EE, EE, EE);
            uv.ps = FF;
            mag = uv.f[0];
            if (!(mag <= k1)) {
                rr = __builtin_ps_rsqrte(FF);
                g = rr;
                fr.spB8.p = g;
                sc = __builtin_ps_muls0(w0, rr);
                fr.n78.f[1] = k2;
                *(__ps_t *)((char *)fr.c + 32) = sc;
                rd = fr.spB8.p;
                g = __builtin_ps_mul(w1, rd);
                *(__ps_t *)((char *)fr.c + 40) = g;
            }
        }
    } else {
        char *r8 = arg0->unk0xC;
        guard = arg0->unk0x24 & 0x8000;
        *(__ps_t *)((char *)fr.c) = ((Unk_D3AB821A *)r8)->unk0xD0;
        *(__ps_t *)((char *)fr.c + 8) = ((Unk_D3AB821A *)r8)->unk0xD8;
        *(__ps_t *)((char *)fr.c + 16) = ((Unk_D3AB821A *)r8)->unk0xE0;
        *(__ps_t *)((char *)fr.c + 24) = ((Unk_D3AB821A *)r8)->unk0xE8;
        *(__ps_t *)((char *)fr.c + 32) = ((Unk_D3AB821A *)r8)->unk0xF0;
        *(__ps_t *)((char *)fr.c + 40) = ((Unk_D3AB821A *)r8)->unk0xF8;
        *(__ps_t *)((char *)fr.c + 48) = ((Unk_D3AB821A *)r8)->unk0x100;
        *(__ps_t *)((char *)fr.c + 56) = ((Unk_D3AB821A *)r8)->unk0x108;
        if (guard != 0) {
            arg1->unk0x0 = arg0->unk0x68;
            arg1->unk0x8 = arg0->unk0x70;
            fr.p48.p = arg0->unk0x78;
            fr.p50.p = arg0->unk0x80;
        }
        /* dot+normalize E1: ((p48-arg1lo), (p50-arg1hi)) -> v58/v60 */
        tB = arg1->unk0x8;
        dv2 = __builtin_ps_sub(fr.p50.p, tB);
        pk = *(__ps_t *)&lbl_802ABFB8;
        tA = arg1->unk0x0;
        dv1 = __builtin_ps_sub(fr.p48.p, tA);
        CC = __builtin_ps_mul(dv2, dv2);
        k1 = lbl_802AC1F0;
        DD = __builtin_ps_merge00(CC, pk);
        fr.v60.p = dv2;
        EE = __builtin_ps_madd(dv1, dv1, DD);
        fr.v58.p = dv1;
        FF = __builtin_ps_sum0(EE, EE, EE);
        uv.ps = FF;
        mag = uv.f[0];
        if (mag > k1) {
            rr = __builtin_ps_rsqrte(FF);
            k2 = lbl_802AC1EC;
            sc = __builtin_ps_muls0(dv1, rr);
            g = rr;
            fr.spC0.p = g;
            fr.spC0.f[1] = k2;
            fr.v58.p = sc;
            rd = fr.spC0.p;
            g = __builtin_ps_mul(dv2, rd);
            fr.v60.p = g;
        }
        /* cross product #1: A=v58 B=v60 C=c[2] D=c[3] */
        mA = fr.v58.p;
        mB = fr.v60.p;
        m10 = *(__ps_t *)((char *)fr.c + 16);
        m12v = *(__ps_t *)((char *)fr.c + 24);
        t1 = __builtin_ps_merge10(mA, mB);
        *(__ps_t *)((char *)fr.c + 32) = mA;
        t1 = __builtin_ps_mul(m10, t1);
        *(__ps_t *)((char *)fr.c + 40) = mB;
        t2 = __builtin_ps_merge10(m10, m12v);
        t2 = __builtin_ps_mul(t2, mA);
        t3 = __builtin_ps_merge00(mA, mB);
        t4 = __builtin_ps_merge00(m12v, m10);
        t4 = __builtin_ps_mul(t4, t3);
        r1 = __builtin_ps_sub(t1, t2);
        s1 = __builtin_ps_merge00(r1, r1);
        fr.spC8.p = s1;
        t3 = __builtin_ps_merge10(t4, t4);
        k2 = lbl_802AC1EC;
        r2 = __builtin_ps_sub(t4, t3);
        r3 = __builtin_ps_merge10(r1, r2);
        fr.spC8.f[1] = k2;
        *(__ps_t *)((char *)fr.c) = r3;
        s1 = fr.spC8.p;
        fr.v58.p = r3;
        mB = s1;
        fr.v60.p = mB;
        *(__ps_t *)((char *)fr.c + 8) = mB;
        /* cross product #2: A'=c[4] B'=c[5] G=c[0] S=c[1] */
        m10 = *(__ps_t *)((char *)fr.c + 32);
        mA = *(__ps_t *)((char *)fr.c);
        m12v = *(__ps_t *)((char *)fr.c + 40);
        u1 = __builtin_ps_merge10(mA, mB);
        u2 = __builtin_ps_merge10(m10, m12v);
        u2 = __builtin_ps_mul(u2, mA);
        u1 = __builtin_ps_mul(m10, u1);
        u3 = __builtin_ps_merge00(mA, mB);
        u4 = __builtin_ps_merge00(m12v, m10);
        q1 = __builtin_ps_sub(u1, u2);
        q2 = __builtin_ps_mul(u4, u3);
        sq = __builtin_ps_merge00(q1, q1);
        k2 = lbl_802AC1EC;
        fr.spD0.p = sq;
        fr.spD0.f[1] = k2;
        t3 = __builtin_ps_merge10(q2, q2);
        q3 = __builtin_ps_sub(q2, t3);
        q4 = __builtin_ps_merge10(q1, q3);
        sq = fr.spD0.p;
        *(__ps_t *)((char *)fr.c + 16) = q4;
        fr.v58.p = q4;
        m12v = sq;
        *(__ps_t *)((char *)fr.c + 24) = m12v;
        fr.v60.p = m12v;
    }
    /* shared tail: run helper over c[], double fan-out */
    fn_80004518((s32)&fr.c[0], 2);
    o0 = *(__ps_t *)((char *)fr.c);
    o1 = *(__ps_t *)((char *)fr.c + 8);
    o2 = *(__ps_t *)((char *)fr.c + 16);
    o3 = *(__ps_t *)((char *)fr.c + 24);
    o4 = *(__ps_t *)((char *)fr.c + 32);
    o5 = *(__ps_t *)((char *)fr.c + 40);
    o6 = *(__ps_t *)((char *)fr.c + 48);
    o7 = *(__ps_t *)((char *)fr.c + 56);
    {
        char *r9 = arg0->unk0xC;
        ((Unk_0B6E8BDA *)r9)->unk0x78 = o0;
        ((Unk_0B6E8BDA *)r9)->unk0x80 = o1;
        ((Unk_0B6E8BDA *)r9)->unk0x88 = o2;
        ((Unk_0B6E8BDA *)r9)->unk0x90 = o3;
        ((Unk_0B6E8BDA *)r9)->unk0x98 = o4;
        ((Unk_0B6E8BDA *)r9)->unk0xA0 = o5;
        ((Unk_0B6E8BDA *)r9)->unk0xA8 = o6;
        ((Unk_0B6E8BDA *)r9)->unk0xB0 = o7;
    }
    arg0->unk0x150 = o1;
    arg0->unk0x180 = o7;
    arg0->unk0x148 = o0;
    arg0->unk0x158 = o2;
    arg0->unk0x160 = o3;
    arg0->unk0x168 = o4;
    arg0->unk0x170 = o5;
    arg0->unk0x178 = o6;
}
