// WIP DRAFT (non-matching) — hand reconstruction of PS vector-normalize script cmd
// family=m2c range=0x801B6F8C-0x801B7484 size=1272B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// PARKED 2026-10-16: still DIFF (~8%), 1272B. Re-verified; the stmw-r30-only
// prologue wall holds — no C shape reaches it without a ground-up rewrite.
// PARKED: allocator-order wall (§6y big-fn signature) @7.7% (-mps-float,
// tools/venv/bin/python <scratch> 0x801B6F8C -mps-float -d).
// Structure/semantics fully reconstructed (copy loop, cross+normalize ×2,
// clamp path, 3 equality chains, bdnz spin, w[] fan-out) but want spills
// intermediates to 0x38-0x50 BETWEEN ops with stmw r30-only prologue; every
// C shape tried saves >=3 GPRs and hoists/sinks the dead-looking stores.
// Volatile-lane unions are REQUIRED for per-use reloads; lane extracts via
// *((f32*)&__ps_t) ICE expmed.c — union round-trip only.
// FLAG: -mps-float
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 8.6% ([0]desc->8.0% [7]rev->8.3% [20]rev->8.6%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 GetChecksum_3(Unk_6A70655D *, s32);
extern void fn_8002B8E4(s32);
extern void fn_8002B8E8(void *, void *);
extern void fn_80004518(s32, s32);
extern f32 lbl_802AC1DC;
extern f32 lbl_802AC1E0;
extern f32 lbl_802AC1E4;
extern f32 lbl_802AC1E8;
extern char lbl_802ABFB8[];

typedef volatile union { __ps_t p; f32 f[2]; } PU;

void fn_801B6F8C(Unk_2124B462 *arg0) {
    struct {
        PU mat[6];   /* 0x08 */
        char pad38[0x20];
        PU v[2];     /* 0x58 */
        PU n[2];     /* 0x68 */
        PU t[2];     /* 0x78 */
        PU w[8];     /* 0x88 */
        PU q[4];     /* 0xC8 */
    } fr;
    union { __ps_t ps; f32 f[2]; } uv;
    void *temp_r3;
    __ps_t A, B, C, D, x, y, z, zz, e10, yy, B2, B3, C2, CC, DDc, EE, FF, pk;
    f32 k1, k2, mag;
    __ps_t rr, sc, rd, g, n0, n1;
    f32 v0, v1, old, prod, chk;
    s32 var_r0;
    __ps_t h, m12, m10, mA8, mB0, sA, sB;
    __ps_t nq0, nq1, rq, sc2, rq2, fin;
    __ps_t o0, o1, o2, o3, o4, o5, o6, o7;

    temp_r3 = (void *)GetChecksum_3(*((s32 *)&arg0->unk0xC), QB_MOTION);
    if (temp_r3 != NULL) {
        __ps_t *dst = &fr.mat[0].p;
        __ps_t *src = (__ps_t *)((char *)temp_r3 + (s32)0x48);
        s32 i;
        for (i = 3; i != 0; i--) {
            dst[0] = src[0];
            dst[1] = src[1];
            dst += 2;
            src += 2;
        }
        __asm__("" : "+r"(dst), "+r"(src));
        A = __builtin_ps_sub(fr.mat[2].p, fr.mat[1].p);
        B = __builtin_ps_sub(fr.mat[3].p, fr.mat[1].p);
        C = __builtin_ps_sub(fr.mat[4].p, fr.mat[1].p);
        pk = *(__ps_t *)&lbl_802ABFB8;
        D = __builtin_ps_sub(fr.mat[5].p, fr.mat[1].p);
        x = __builtin_ps_merge10(C, D);
        y = __builtin_ps_merge10(A, B);
        z = __builtin_ps_mul(A, x);
        fr.q[0].f[1] = lbl_802AC1DC;
        z = __builtin_ps_sub(z, y);
        zz = __builtin_ps_merge00(z, z);
        fr.q[0].p = zz;
        C2 = __builtin_ps_merge00(C, D);
        k1 = lbl_802AC1E0;
        B2 = __builtin_ps_merge00(B, A);
        B2 = __builtin_ps_mul(B2, C2);
        e10 = fr.q[0].p;
        yy = __builtin_ps_merge10(B2, B2);
        fr.n[1].p = e10;
        CC = __builtin_ps_mul(e10, C2);
        B3 = __builtin_ps_sub(B2, yy);
        x = __builtin_ps_merge10(z, B3);
        DDc = __builtin_ps_merge00(CC, pk);
        fr.n[0].p = x;
        EE = __builtin_ps_madd(x, x, DDc);
        FF = __builtin_ps_sum0(EE, EE, EE);
        uv.ps = FF;
        mag = uv.f[0];
        if (!(mag <= k1)) {
            rr = __builtin_ps_rsqrte(FF);
            sc = __builtin_ps_muls0(x, rr);
            fr.q[1].p = rr;
            fr.q[1].f[1] = lbl_802AC1DC;
            fr.n[0].p = sc;
            rd = fr.q[1].p;
            g = __builtin_ps_mul(e10, rd);
            fr.n[1].p = g;
        }
        n0 = fr.n[0].p;
        n1 = fr.n[1].p;
        fr.v[0].p = n0;
        fr.v[1].p = n1;
        if (fr.v[0].f[1] < k1) {
            fr.v[1].p = n1;
            fr.v[0].p = n0;
            n1 = fr.n[1].p;
            n0 = fr.n[0].p;
            fr.n[0].f[0] = -fr.v[0].f[0];
            fr.n[1].f[1] = -fr.v[1].f[1];
            fr.n[1].f[0] = -fr.v[1].f[0];
            fr.n[0].f[1] = -fr.v[0].f[1];
        }
        var_r0 = 0;
        if ((fr.v[0].f[0] == *((f32 *)&((Unk_4169B2AE *)arg0)->unk0xB8)) && (fr.v[0].f[1] == arg0->unk0xBC) && (fr.v[1].f[0] == *((f32 *)&((Unk_4169B2AE *)arg0)->unk0xC0))) {
            chk = fr.v[1].f[1] == arg0->unk0xC4;
            var_r0 = chk;
        }
        if (var_r0 == 0) {
            n0 = fr.v[0].p;
            k2 = lbl_802AC1DC;
            ((Unk_4169B2AE *)arg0)->unk0xB8 = n0;
            nq0 = ((Unk_4169B2AE *)arg0)->unk0xC8;
            n1 = fr.v[1].p;
            nq1 = ((Unk_4169B2AE *)arg0)->unk0xD0;
            ((Unk_4169B2AE *)arg0)->unk0xC0 = n1;
            arg0->unk0xD8 = k2;
            arg0->unk0xB0 = nq1;
            arg0->unk0xA8 = nq0;
        }
        v0 = arg0->unk0xD8;
        old = v0;
        k1 = lbl_802AC1E0;
        if (v0 != k1) {
            volatile PU *ap = (volatile PU *)((char *)arg0 + (s32)0xA8);
            var_r0 = 0;
            if ((ap->f[0] == *((f32 *)&((Unk_4169B2AE *)arg0)->unk0xB8)) && (ap->f[1] == arg0->unk0xBC) && (ap[1].f[0] == *((f32 *)&((Unk_4169B2AE *)arg0)->unk0xC0))) {
                chk = ap[1].f[1] == arg0->unk0xC4;
                var_r0 = chk;
            }
            if (var_r0 != 0) {
                arg0->unk0xD8 = k1;
            } else {
                prod = arg0->unk0xA4;
                prod = prod * lbl_802AC1E4;
                k1 = lbl_802AC1E0;
                prod = prod * lbl_802AC1E8;
                v0 = old - prod;
                arg0->unk0xD8 = v0;
                if (!(v0 > k1)) {
                    nq0 = ((Unk_4169B2AE *)arg0)->unk0xB8;
                    nq1 = ((Unk_4169B2AE *)arg0)->unk0xC0;
                    arg0->unk0xD8 = k1;
                    ((Unk_4169B2AE *)arg0)->unk0xC8 = nq0;
                    ((Unk_4169B2AE *)arg0)->unk0xD0 = nq1;
                } else {
                    fn_8002B8E4(&fr.t[0]);
                    fr.q[2].f[0] = v0;
                    h = fr.q[2].p;
                    m12 = ((Unk_4169B2AE *)arg0)->unk0xC0;
                    m10 = ((Unk_4169B2AE *)arg0)->unk0xB8;
                    mA8 = ap[0].p;
                    mB0 = ap[1].p;
                    sA = __builtin_ps_sub(mA8, m10);
                    sB = __builtin_ps_sub(mB0, m12);
                    sB = __builtin_ps_madds0(sB, m12, h);
                    fr.t[1].p = sB;
                    sA = __builtin_ps_madds0(sA, m10, h);
                    fr.t[0].p = sA;
                    fn_8002B8E8(&fr.n[0], &fr.t[0]);
                    nq0 = fr.n[0].p;
                    nq1 = fr.n[1].p;
                    ((Unk_4169B2AE *)arg0)->unk0xC8 = nq0;
                    fin = fr.n[1].p;
                    ((Unk_4169B2AE *)arg0)->unk0xD0 = fin;
                    CC = __builtin_ps_mul(nq1, nq1);
                    pk = *(__ps_t *)&lbl_802ABFB8;
                    DDc = __builtin_ps_merge00(CC, pk);
                    EE = __builtin_ps_madd(nq0, nq0, DDc);
                    FF = __builtin_ps_sum0(EE, EE, EE);
                    uv.ps = FF;
        mag = uv.f[0];
                    if (!(mag <= k1)) {
                        rq = __builtin_ps_rsqrte(FF);
                        sc2 = __builtin_ps_muls0(nq0, rq);
                        ((Unk_4169B2AE *)arg0)->unk0xC8 = sc2;
                        fr.q[3].p = rq;
                        fr.q[3].f[1] = lbl_802AC1DC;
                        rq2 = fr.q[3].p;
                        fin = __builtin_ps_mul(nq1, rq2);
                        ((Unk_4169B2AE *)arg0)->unk0xD0 = fin;
                    }
                }
            }
        }
        {
            char *p = arg0->unk0xC + (s32)0xD0;
            s32 i2;
            for (i2 = 4; i2 != 0; i2--) {
            }
            var_r0 = 0;
            fr.w[3].p = ((Unk_C1F9F519 *)p)->unk0x18;
            fr.w[2].p = ((Unk_C1F9F519 *)p)->unk0x10;
            fr.w[1].p = ((Unk_C1F9F519 *)p)->unk0x8;
            chk = *((f32 *)&((Unk_4169B2AE *)arg0)->unk0xC8);
            fr.w[0].p = ((Unk_C1F9F519 *)p)->unk0x0;
            {
                volatile PU *wp = (volatile PU *)&fr.w[2];
                if ((wp->f[0] == chk) && !((wp->f[1] != arg0->unk0xCC) || (wp[1].f[0] != *((f32 *)&((Unk_4169B2AE *)arg0)->unk0xD0)))) {
                    chk = wp[1].f[1] == arg0->unk0xD4;
                    var_r0 = chk;
                }
            }
            fr.w[4].p = ((Unk_C1F9F519 *)p)->unk0x20;
            fr.w[5].p = ((Unk_C1F9F519 *)p)->unk0x28;
            fr.w[6].p = ((Unk_C1F9F519 *)p)->unk0x30;
            fr.w[7].p = ((Unk_C1F9F519 *)p)->unk0x38;
            if (var_r0 == 0) {
                nq0 = ((Unk_4169B2AE *)arg0)->unk0xC8;
                nq1 = ((Unk_4169B2AE *)arg0)->unk0xD0;
                fr.w[2].p = nq0;
                fr.w[3].p = nq1;
                fn_80004518((s32)&fr.w[0], 1);
                o0 = fr.w[0].p;
                p = arg0->unk0xC;
                ((Unk_C1F9F519 *)p)->unk0xD0 = o0;
                o1 = fr.w[1].p;
                ((Unk_C1F9F519 *)p)->unk0xD8 = o1;
                o2 = fr.w[2].p;
                ((Unk_C1F9F519 *)p)->unk0xE0 = o2;
                o3 = fr.w[3].p;
                ((Unk_C1F9F519 *)p)->unk0xE8 = o3;
                o4 = fr.w[4].p;
                ((Unk_C1F9F519 *)p)->unk0xF0 = o4;
                o5 = fr.w[5].p;
                ((Unk_C1F9F519 *)p)->unk0xF8 = o5;
                o6 = fr.w[6].p;
                ((Unk_C1F9F519 *)p)->unk0x100 = o6;
                o7 = fr.w[7].p;
                ((Unk_C1F9F519 *)p)->unk0x108 = o7;
                arg0->unk0x180 = o7;
                arg0->unk0x148 = o0;
                arg0->unk0x150 = o1;
                arg0->unk0x158 = o2;
                arg0->unk0x160 = o3;
                arg0->unk0x168 = o4;
                arg0->unk0x170 = o5;
                arg0->unk0x178 = o6;
            }
        }
    }
}
