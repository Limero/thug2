// WIP DRAFT (non-matching) — hand rewrite of fn_8008D0A4 (2026-10-04)
// family=m2c range=0x8008D0A4-0x8008D868 size=1988B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
//
// PARKED. Best measured: tools/want_got.py -> 3.7% masked, object 1820B vs want
// 1988B (42 words SHORT). The m2c draft this replaces scored 1.2%.
//
// WHAT IS NOW SOLVED (the body is semantically complete, not a guess):
//   * full frame/prologue: 0x1a8, callee-saved f29/f30/f31 + r16..r31, GPR
//     save area at 0x150 — the first 8 instructions are byte-identical.
//   * local-slot map matches the want exactly: spawn struct 0x08(0x38),
//     out[4] 0x48, cf[4] 0x58, A 0x68, B 0x78, dd 0x88/0x90, n 0x98/0xA0,
//     o1..o4 0xA8/0xB8/0xC8/0xD8, uz 0x110, sc 0x118, ww 0x120..0x138,
//     f64 scratch 0x148.
//   * semantics fully recovered: d = B-A over 4 lanes; n = normalize((d x C))
//     with the 4th lane = 1.0; ww = lerp(node.f18,node.f20,t); four ribbon
//     verts A±n*ww, B±n*ww; per-vertex RGBA lerp on 4 colour stops chosen by
//     the arg0->0x110 reparam of t; RGB clamped to [0,255] after scaling by
//     vF4*v68/v6C/v70; then 6x fn_8001F0F8(xyz)+fn_8001F1D4(arg0x48+i*4).
//   * the 5 setup calls (fn_800231C4/1EDE0/1E6F0/1FAA4/1F2D8) and their
//     prototypes/arg-setup sequences.
//   * ngccc 2.95 emits `(double)(s32)v` as `xoris v,0x8000` + magic
//     0x4330000080000000 and `(double)(unsigned char)v` with magic
//     0x4330000000000000 (lbl_80296CF8 / lbl_80296D00 in this function) —
//     reproduced by writing `f32 d = (f64)(int)(b-a); ... d*tt`.
//   * ps_mergeXY(A,B) = {A[X], B[Y]} with X the high/low selector for A and Y
//     for B (0 = PS0/hi lane); merge00/merge10 reproduce the want's cross
//     product exactly.
//
// BLOCKERS (in order of cost):
//   1. REGISTER ALLOCATION over the ~150-instruction PS block. The op sequence
//      now matches op-for-op, but ngccc picks f0..f13 differently (e.g. want
//      `ps_mul f0,f0,f12` vs got `ps_mul f13,f13,f11`) and stores the pair
//      temporaries to different slots (want 0x110/0x118, got 0xc8/0xd0).
//      Needs the *exact* original statement shape for the cross-product
//      block; not reachable by tuning the current expression.
//   2. CONSTANT-POOL BASE SELECTION. The want hoists lbl_80376D08[0..2] onto
//      base 0x80376CE8 (`lis r9,-0x7fc8; addi r9,r9,-0x498c` + offsets
//      0x20/0x24/0x28) and materialises lbl_80296CEC etc. from a separate
//      0x80290000 base in r9/r10/r11/r16/r23/r24. Reproducing that needs the
//      same literal-symbol declarations/aliasing the original used; with
//      `extern f32 lbl_80376D08[]` ngccc picks the exact address instead.
//   3. `li r9,4; mtctr r9; ...; bdnz` with the branch displacement 0 (i.e.
//      branching to ITSELF, 0x8008D400) sits between the loop-latch addis and
//      the ww computation, once per outer iteration. That is an infinite
//      loop on the 4th outer iteration unless arg0->0x94 <= 3 — either a
//      latent game bug or an ngccc 2.95 loop-layout artefact. No C form was
//      found that emits it; probe results are in the recipes notes below.
//   4. The colour loop's 8 `mr rN,r9` dreg-pair copies (r9 = 0x80290000, kept
//      live across the whole loop for the (double) magic-constant stores) and
//      its `bdnzlt` back-edge are not reproduced.
//
// NEGATIVE RESULTS (measured, don't repeat):
//   * hoisting lbl_80296D08 / lbl_80296CEC / arg0->0x110 into locals is what
//     buys the 3 callee-saved FPRs (and thus the exact 0x1a8 frame); without
//     at least two of them the frame is 0x1a0 and the whole body shifts.
//   * keeping the colour pointers pa/pb live across the loop is what buys
//     `stmw r16` instead of `stmw r18`; dropping them loses one GPR and the
//     save area moves to 0x158.
//   * a variant with 2 FPRs (frame 0x1a0) measures 7.3% because its 2-word
//     shorter prologue phase-shifts the fn_800231C4/1EDE0/1E6F0/1FAA4/1F2D8
//     arg-setup block into alignment. That number is an artefact — those 33
//     words are `li`/`lbz`/`bl` coincidences — and the prologue itself can
//     never match, so the structurally-correct body above was kept instead.
//   * reordering S.a/S.b/S.c assignments: no effect (GCC always sinks the
//     `li 2` past the `ori`).
//   * the want's `stfs f29, 0xc(r17)` / `0xc(r18)` (r17 = r1+0x68,
//     r18 = r1+0x78, both hoisted before the loop) vs a plain `stfs ..0x74(r1)`
//     could not be forced from C; GCC folds the offset unless the address is
//     taken through a pointer.
#include "types.h"
#include "qb_constants.h"

extern __ps_t lbl_80296CB0;
extern f32 lbl_80296CEC;
extern f32 lbl_80296CF0;
extern f64 lbl_80296CF8;
extern f64 lbl_80296D00;
extern f32 lbl_80296D08;
extern f32 lbl_80376D08[];

void fn_800231C4(void *, void *, s32, s32, s32, s32, s32, u8);
void fn_8001EDE0(s32, s32, s32, s32);
void fn_8001E6F0(s32, s32, s32, s32, s32);
void fn_8001FAA4(s32, s32, s32, s32, s32);
void fn_8001F2D8(s32, ...);
void fn_8001F0A0(s32, s32, s32);
void fn_8001F0F8(f32, f32, f32);
void fn_8001F1D4(s32);
void fn_8001F0F4(void);

typedef struct {
    char pad[4];
    u8 b4, b5, b6, b7;
} info_t;

typedef struct {
    u32 f;
    u8 a, b, c;
    u8 pad0[0x19];
    void *p;
    s16 d;
    u8 e, g;
    u8 pad2[4];
    u8 h, i, j, k;
    s16 l;
    u8 pad3[4];
    u8 m;
} spawn_t;

typedef struct {
    u8 r, g, b, a;
} rgba_t;

typedef union {
    u32 w[4];
    rgba_t c[4];
} out_t;

typedef union {
    __ps_t ps[2];
    f32 f[4];
} v4_t;

typedef union {
    __ps_t ps;
    f32 f[2];
} ps2_t;

typedef struct {
    f32 x, y, z;
} v3_t;

typedef struct {
    f32 pad0[6];
    f32 f18;
    f32 pad1;
    f32 f20;
    f32 pad2;
    f32 f28, f2C;
} node_t;

typedef struct {
    char pad0[0x28];
    f32 v28, v2C, v30;
    char pad1[0x34];
    f32 v68, v6C, v70;
    char pad2[0x10];
    s32 v84;
    char pad3[0xC];
    s32 v94;
    char pad4[0x5C];
    f32 vF4;
    char pad5[8];
    node_t *nd;
    char pad6[0xC];
    f32 v110;
    u32 *cA;
    u32 *cB;
    u32 *cC;
    char pad7[4];
    v3_t *pts;
    char pad8[0xC];
    s32 v134;
    char pad9[0x38];
    s32 v170;
    char pad10[4];
    u8 v178, v179;
    info_t *inf;
} arg_t;

void fn_8008D0A4(arg_t *arg0) {
    spawn_t S;
    volatile ps2_t padA;
    out_t out;
    v4_t C;
    v4_t A, B, o1, o2, o3, o4;
    ps2_t dd0, dd1, nv, nw;
    SN_PS_type uz, sc, dot;
    __ps_t e0, e1, e2, e3, g0, g1;
    volatile ps2_t pd0, pd1, pd2, pd3;
    volatile ps2_t w0, w1, w2, w3;
    volatile ps2_t padB;
    ps2_t C0, C1;
    u32 colf, colt;
    f32 ww, d0, d1, d2, d3, dv, cl;
    f32 sr, sg, sb;
    u8 cr, cg, cb, ca, tr, tg, tb, ta;
    v3_t *p0, *p1;
    node_t *nd;
    u32 *pa, *pb;
    s32 i, j;
    f32 tt, one, zero, vv;
    info_t *ip;

    S.f = QB_PARTICLE;
    S.b = 1;
    S.d = (arg0->inf != NULL) ? 0x61 : 0x60;
    S.c = 2;
    S.a = 1;
    S.p = arg0->inf;
    S.l = 0;
    S.m = 0;
    S.e = arg0->v178;
    S.g = arg0->v179;
    S.j = 0x80;
    S.h = 0x80;
    S.i = 0x80;
    S.k = 0xFF;
    fn_800231C4(&S, &S.p, 1, 1, 0, 0, 0, arg0->v179);
    ip = arg0->inf;
    fn_8001EDE0(0, 1, (u16)((1 << ip->b6) - ip->b4), (u16)((1 << ip->b7) - ip->b5));
    fn_8001E6F0(0, 1, 4, 0, 0x7D);
    fn_8001FAA4(0, 0x3C, 0x3C, 0x3C, 0x3C);
    C.f[0] = lbl_80376D08[0];
    C.f[1] = lbl_80376D08[1];
    C.f[2] = lbl_80376D08[2];
    C.f[3] = lbl_80296CEC;
    fn_8001F2D8(2, 9, 1, 0xB, 1);

    nd = arg0->nd;
    p1 = arg0->pts + (arg0->v170 - 1) * 3 * arg0->v84;
    p0 = arg0->pts;
    one = lbl_80296CF0;
    zero = lbl_80296CEC;
    vv = arg0->v110;
    pa = arg0->cA;
    pb = arg0->cC;
    i = 0;
    while (i < arg0->v94) {
        tt = nd->f28 / nd->f2C;
        if (arg0->v134 != 0) {
            A.f[0] = p0->x;
            A.f[1] = p0->y;
            A.f[2] = p0->z;
            A.f[3] = one;
            B.f[0] = p1->x;
            B.f[1] = p1->y;
            B.f[2] = p1->z;
            B.f[3] = one;
        } else {
            A.f[0] = p0->x + arg0->v28;
            A.f[1] = p0->y + arg0->v2C;
            A.f[2] = p0->z + arg0->v30;
            A.f[3] = one;
            B.f[0] = p1->x + arg0->v28;
            B.f[1] = p1->y + arg0->v2C;
            B.f[2] = p1->z + arg0->v30;
            B.f[3] = one;
        }
        dd0.ps = __builtin_ps_sub(B.ps[0], A.ps[0]);
        dd1.ps = __builtin_ps_sub(B.ps[1], A.ps[1]);
        e0 = __builtin_ps_mul(__builtin_ps_merge10(dd0.ps, dd1.ps), C.ps[0]);
        e1 = __builtin_ps_sub(__builtin_ps_mul(dd0.ps, __builtin_ps_merge10(C.ps[0], C.ps[1])), e0);
        uz.ps = __builtin_ps_merge00(e1, e1);
        e2 = __builtin_ps_mul(__builtin_ps_merge00(dd1.ps, dd0.ps),
                              __builtin_ps_merge00(C.ps[0], C.ps[1]));
        e3 = __builtin_ps_sub(e2, __builtin_ps_merge10(e2, e2));
        uz.flt.lo = one;
        nv.ps = uz.ps;
        nw.ps = __builtin_ps_merge10(e1, e3);
        g0 = __builtin_ps_mul(uz.ps, uz.ps);
        g0 = __builtin_ps_merge00(g0, lbl_80296CB0);
        g1 = __builtin_ps_madd(nw.ps, nw.ps, g0);
        dot.ps = __builtin_ps_sum0(g1, g1, g1);
        if (dot.flt.hi > zero) {
            sc.ps = __builtin_ps_rsqrte(dot.ps);
            nw.ps = __builtin_ps_muls0(nw.ps, sc.ps);
            sc.flt.lo = one;
            nv.ps = __builtin_ps_mul(uz.ps, sc.ps);
        }
        ww = (nd->f20 - nd->f18) * tt + nd->f18;
        o1.ps[0] = __builtin_ps_add(A.ps[0], __builtin_ps_muls0(nv.ps, ww));
        o1.ps[1] = __builtin_ps_add(A.ps[1], __builtin_ps_muls0(nv.ps, ww));
        o2.ps[0] = __builtin_ps_sub(A.ps[0], __builtin_ps_muls0(nv.ps, ww));
        o2.ps[1] = __builtin_ps_sub(A.ps[1], __builtin_ps_muls0(nv.ps, ww));
        o3.ps[0] = __builtin_ps_sub(B.ps[0], __builtin_ps_muls0(nv.ps, ww));
        o3.ps[1] = __builtin_ps_sub(B.ps[1], __builtin_ps_muls0(nv.ps, ww));
        o4.ps[0] = __builtin_ps_add(B.ps[0], __builtin_ps_muls0(nv.ps, ww));
        o4.ps[1] = __builtin_ps_add(B.ps[1], __builtin_ps_muls0(nv.ps, ww));
        if (vv >= 0.0f) {
            if (tt < vv) {
                pa = arg0->cA;
                pb = arg0->cB;
                tt = tt / vv;
            } else {
                pa = arg0->cB;
                pb = arg0->cC;
                tt = (tt - vv) / (one - vv);
            }
        }
        sr = arg0->vF4 * arg0->v68;
        sg = arg0->vF4 * arg0->v6C;
        sb = arg0->vF4 * arg0->v70;
        for (j = 0; j < 4; j++) {
            colf = pa[j];
            colt = pb[j];
            cr = (u8)colf;
            cg = (u8)(colf >> 8);
            cb = (u8)(colf >> 16);
            ca = (u8)(colf >> 24);
            tr = (u8)colt;
            tg = (u8)(colt >> 8);
            tb = (u8)(colt >> 16);
            ta = (u8)(colt >> 24);
            d0 = (f64)(tr - cr);
            d1 = (f64)(tg - cg);
            d2 = (f64)(tb - cb);
            d3 = (f64)(ta - ca);
            out.c[j].r = cr + (s32)(d0 * tt);
            out.c[j].g = cg + (s32)(d1 * tt);
            out.c[j].b = cb + (s32)(d2 * tt);
            out.c[j].a = ca + (s32)(d3 * tt);
            dv = (f64)out.c[j].r;
            dv = dv * sr;
            cl = (dv < zero) ? zero : ((dv > lbl_80296D08) ? lbl_80296D08 : dv);
            out.c[j].r = (u8)cl;
            dv = (f64)out.c[j].g;
            dv = dv * sg;
            cl = (dv < zero) ? zero : ((dv > lbl_80296D08) ? lbl_80296D08 : dv);
            out.c[j].g = (u8)cl;
            dv = (f64)out.c[j].b;
            dv = dv * sb;
            cl = (dv < zero) ? zero : ((dv > lbl_80296D08) ? lbl_80296D08 : dv);
            out.c[j].b = (u8)cl;
        }
        fn_8001F0A0(0x98, 0, 6);
        fn_8001F0F8(o1.f[0], o1.f[1], o1.f[2]);
        fn_8001F1D4(out.w[1]);
        fn_8001F0F8(o4.f[0], o4.f[1], o4.f[2]);
        fn_8001F1D4(out.w[2]);
        fn_8001F0F8(A.f[0], A.f[1], A.f[2]);
        fn_8001F1D4(out.w[0]);
        fn_8001F0F8(B.f[0], B.f[1], B.f[2]);
        fn_8001F1D4(out.w[3]);
        fn_8001F0F8(o2.f[0], o2.f[1], o2.f[2]);
        fn_8001F1D4(out.w[1]);
        fn_8001F0F8(o3.f[0], o3.f[1], o3.f[2]);
        fn_8001F1D4(out.w[2]);
        fn_8001F0F4();
        nd++;
        p0++;
        p1++;
        pa++;
        pb++;
        i++;
    }
}