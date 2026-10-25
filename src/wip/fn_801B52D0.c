// WIP DRAFT — PARKED: hand-rebuilt from disasm 2026-08-24 (m2c draft was
// corrupt via the statics-DCE pathology: sp100/spCC/spE0/spF8 file-scope
// statics modeled stack floats as dead statics; compiled 636B vs want
// 1016B). Needs -mps-float.
//
// Semantics (fully decoded): project arg0's point onto a segment using PS
// dot/cross products (wants ps_sub/mul3op/merge00/merge10/madd/sum0), walk
// the node table at (*(arg0->0xC))+0xd0 (8 pair copies), compute an angle
// via fn_80005E20 + fmod-style wrap (manual int->float cvt dance against
// lbl_802AC0C0), winding flip vs lbl_802AC0B0, two rsqrte/res distance
// chains, clamp vs fn_8012570C(0xA876AA2C,1) result, then conditionally
// fn_8012570C(0x81085734,0) -> fn_801B5EE8(arg0, var_f30*lbl_802AC0C8,
// clamped).
//
// PARK REASONS (supersede doc06 M5.0p claims):
// 1. The five opcode-4 words want shows (0x53F4/53FC/543C/544C/55B8,
//    xo5=8 C=2) are ps_mr (op4 XO10=72) — EMITTABLE via plain __ps_t
//    copies. cc1.exe also has __builtin_ps_abs/_nabs/_neg emitting C=1/4/8
//    of the same xo5=8 family (verified by probe compile). The old
//    "xo5=8 unemittable" claim is disproven; fn_801792D4/fn_8014E440-style
//    parks should be retried under this light.
// 2. Real walls: (a) doc-30 self-targeting bdnz window at 0x54B4
//    (li r0,4/mtctr/.../bdnz . — needs the 6ab-131 asm route);
//    (b) GCSE page-anchor hoisting + FPR/GPR coloring across ~14 calls'
//    worth of live PS webs (same class as parked fn_801B56C8: any C
//    reconstruction lands saved-reg sets r21-r28 that want never saves).
// Body below is faithful through the first hash call and structurally
// complete afterwards; mid-function PS blocks are semantic equivalents,
// not schedule matches (~3% masked on ps_diff).
// family=m2c range=0x801B52D0-0x801B56C8 size=1016B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
// FLAG: -mps-float -Os

extern f32 lbl_802AC0B0;
extern f32 lbl_802AC0B4;
extern f32 lbl_802AC0B8;
extern f64 lbl_802AC0C0;
extern f32 lbl_802AC0C8;
extern char lbl_802ABFB8[];

extern f32 fn_8012570C(s32, s32);
extern f32 fn_80005E20(void *, void *);
extern void fn_801B5EE8(void *, f32, f32);

typedef union { u32 w[2]; f64 d; } cvt_u;

void fn_801B52D0(Unk_0EAAF5DE *arg0) {
    volatile __ps_t w[26]; /* +0x08 .. +0xD7 region */
    f32 spE0;
    f32 spE8;
    f32 spF4;
    f32 spF8;
    f32 spCC;
    register f32 var_f29 __asm__("fr29");
    register f32 var_f30 __asm__("fr30");
    register f32 var_f31 __asm__("fr31");
    cvt_u cv;
    f32 K = lbl_802AC0B0;
    __ps_t tab;
    SN_PS_type dot;
    SN_PS_type dot2;
    Unk_DACD88AE *M;
    s32 i;

    /* pre-call gather; lanes 1 of pairs 0/2/4 overwritten with K */
    w[0] = arg0->unk0x68;
    w[1] = arg0->unk0x70;
    w[2] = arg0->unk0x78;
    w[3] = arg0->unk0x80;
    M = (void *)*((s32 *)&arg0->unk0xC);
    w[4] = M->unk0x58;
    w[5] = M->unk0x60;
    *(f32 volatile *)((char *)&w[0] + 4) = K;
    *(f32 volatile *)((char *)&w[2] + 4) = K;
    *(f32 volatile *)((char *)&w[4] + 4) = K;
    var_f29 = fn_8012570C(QB_PED_MAX_DISTANCE_TO_PATH, 1);

    /* dot/cross product block */
    {
        __ps_t P;
        __ps_t Q;
        __ps_t R;
        __ps_t S;
        __ps_t T;
        __ps_t U;
        __ps_t da;
        __ps_t db;
        __ps_t dc;
        __ps_t dd;
        __ps_t mx;
        __ps_t md;
        __ps_t m1;
        __ps_t m2;

        Q = w[1];
        P = w[0];
        R = w[2];
        S = w[3];
        da = R - P;
        T = w[4];
        db = S - Q;
        w[6] = da;
        w[7] = db;
        dc = T - P;
        U = w[5];
        mx = __builtin_ps_merge10(da, db);
        Q = w[1];
        m1 = __builtin_ps_mul(mx, dc);
        tab = *(__ps_t *)&lbl_802ABFB8;
        dd = U - Q;
        w[8] = dc;
        md = __builtin_ps_merge10(dc, dd);
        w[9] = dd;
        m2 = __builtin_ps_mul(da, md);
        mx = __builtin_ps_merge00(dc, dd);
        md = __builtin_ps_merge00(db, da);
        m1 = __builtin_ps_mul(md, mx); /* t3 */
        m2 = m2 - m1;                  /* t2' (recomputed shape) */
        /* NOTE: want interleaves t2/t3 lane math here (merge10/sub/
           reload of +0xD8); semantic result is the pair cross terms. */
        db = __builtin_ps_mul(db, db);
        md = __builtin_ps_merge00(db, tab);
        dot.ps = __builtin_ps_madd(da, da, md);
        dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
        w[10] = m2;
        w[11] = dot.ps;
    }
    if (dot.flt.hi == K && dot.flt.lo == K) {
        w[12] = arg0->unk0x68;
        w[13] = arg0->unk0x70;
    } else {
        /* projection: p += dir * (dot2 / dot) */
        __ps_t n1;
        __ps_t n2;
        __ps_t sc;
        f32 ratio;

        n1 = __builtin_ps_mul(w[9], w[7]);
        n1 = __builtin_ps_merge00(n1, tab);
        n1 = __builtin_ps_madd(w[8], w[6], n1);
        dot2.ps = __builtin_ps_sum0(n1, n1, n1);
        spE0 = dot2.flt.hi;
        ratio = spE0 / dot.flt.hi;
        spE8 = ratio;
        {
            f32 pair[2];
            pair[0] = spE8;
            pair[1] = spE8;
            sc = *(__ps_t *)pair;
        }
        n2 = __builtin_ps_muls0(w[7], sc);
        n1 = __builtin_ps_muls0(w[6], sc);
        w[15] = n2;
        w[13] = n2 + arg0->unk0x70;
        w[14] = n1;
        w[12] = n1 + arg0->unk0x68;
    }
    /* direction from projected points */
    w[14] = w[13] - w[12];
    /* empty countdown loop kept by ProDG (want: li r0,4/mtctr/bdnz.) */
    for (i = 4; i != 0; i--) {
    }
    M = (void *)(*((s32 *)&arg0->unk0xC) + 0xd0);
    w[16] = M->unk0x0;
    w[17] = M->unk0x8;
    w[18] = M->unk0x10;
    w[19] = M->unk0x18;
    w[20] = M->unk0x20;
    w[21] = M->unk0x28;
    w[22] = M->unk0x30;
    w[23] = M->unk0x38;
    var_f30 = fn_80005E20(&w[20], &w[14]);
    /* angle wrap: var_f30 -= (f32)((double)(int)(var_f30/K_B8) dance) * K_B8 */
    if (var_f30 > lbl_802AC0B8) {
        cv.w[1] = (u32)(s32)(var_f30 / lbl_802AC0B8) ^ 0x80000000;
        cv.w[0] = QB_INT_TO_DOUBLE_BIAS;
        var_f30 = var_f30 - (f32)((cv.d - lbl_802AC0C0) * lbl_802AC0B8);
    }
    /* winding flip (want reads +0xCC — never written in-function: stack
       garbage the original passed through; modeled as uninit local) */
    if (spCC > K) {
        var_f30 = lbl_802AC0B8 - var_f30;
    }
    /* two rsqrte/res distance chains; f31 = chain2/chain1 */
    {
        __ps_t e1;
        __ps_t e2;
        __ps_t e3;
        f32 den;
        f32 num;

        e1 = w[2] - w[0];
        e1 = __builtin_ps_mul(e1, e1);
        e2 = w[3] - w[1];
        e3 = __builtin_ps_merge00(e2, tab);
        e1 = __builtin_ps_madds0(e3, e3, e1);
        dot.ps = __builtin_ps_sum0(e1, e1, e1);
        dot.ps = __builtin_ps_rsqrte(dot.ps);
        dot.ps = __builtin_ps_res(dot.ps);
        den = dot.flt.hi;
        spF8 = den;
        e1 = w[11] - w[10];
        e1 = __builtin_ps_mul(e1, e1);
        e3 = __builtin_ps_merge00(e1, tab);
        e1 = __builtin_ps_madd(e2, e2, e3);
        dot.ps = __builtin_ps_sum0(e1, e1, e1);
        dot.ps = __builtin_ps_rsqrte(dot.ps);
        dot.ps = __builtin_ps_res(dot.ps);
        num = dot.flt.hi;
        var_f31 = (den != K) ? num / den : K;
    }
    if (var_f31 > var_f29) {
        var_f29 = lbl_802AC0B4;
    } else {
        var_f29 = lbl_802AC0B4 - ((var_f29 - var_f31) / var_f29);
    }
    if (var_f31 > fn_8012570C(QB_PED_MIN_DISTANCE_TO_PATH, 0)) {
        fn_801B5EE8(arg0, var_f30 * lbl_802AC0C8, var_f29);
    }
}
