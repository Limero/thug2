// PARKED 2026-10-17: DIFF 3.9% (7/178 words), got 712B vs want 780B.
// Full hand rebuild from a complete PS decode of want (see notes below);
// compiles clean and is structurally faithful, but the allocator diverges
// globally: got frame 0x108 vs want 0xD0 (+56B: union t0/t1 take frame
// homes at 0xB8/0xC0 plus tail-spill slots), head temps land in f5 (want
// never uses f5 in the head) and the whole schedule cascades from there.
// Next lever (not yet tried): recycle tail temps into 6-7 live pairs
// (reassign tA/v0/tB/tC in place per want's reg reuse; reuse union t1
// itself as the point2.x scratch so it stays in f0) and drop the Cs temp
// (fold C' load/copy if the fmr can be forced another way); re-measure
// frame first (must be 0xD0 before word-diff is readable). Do NOT re-add
// implicit f32<->__ps_t conversions (assigning f32 to __ps_t var or vice
// versa): they ICE ngccc at haifa-sched.c:7798 — always use an explicit
// f32 temp or union member. The old m2c statics-DCE husk (2.2%) is gone;
// this rebuild replaces it.
// WIP DRAFT — full hand rebuild from decoded want (ray/sphere quadratic
// solver, heavy paired-single).
// family=m2c range=0x800F94FC-0x800F9808 size=780B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Reconstruction notes (all offsets verified against the DOL):
//   arg0 (r31) / arg1 (r4) supply input pairs; arg2 (r30, s32*) takes the
//   hit-count flag; arg3 (r29, pair*) takes up to 4 output pairs.
//   Frame 0xD0, saves f29-f31 (eps/A/B, live across sqrtf) + r29-r31.
//   Coefficients: A=sum0 pair @0x48, B=@0x50, C=@0x58, all stored as pairs
//   then re-read as scalars (strict-aliasing blocks store->load forwarding,
//   so the lfs reloads + fmr homes are real). Roots t0/t1 stored to
//   0x60/0x64 and explicitly re-read for the range checks. Each output
//   block stages its broadcast scalar through a union (stfs then psq_l).
//   The t1>1 one-point path joins the t0<0 path at 0x9744 (shared stores).
#include "types.h"

typedef union {
    __ps_t p;
    f32 s[2];
} Pair94;

typedef struct {
    char _00[8];
    Pair94 h08, h10, h18, h20;
    Pair94 o28, o30;
    Pair94 o38, o40;
    Pair94 h48, h50, h58;
    f32 t60, t64;
    Pair94 u68, u70, u78, u80, u88;
    char _90[28];
} Fr94FC;

typedef struct {
    __ps_t p0, p1, p2, p3;
} Vec4p;

typedef struct {
    __ps_t p0, p1;
    f32 f10;
} Arg1Ly;

extern __ps_t lbl_8029C060;
extern f32 lbl_8029C0DC;
extern f32 lbl_8029C0E0;
f32 sqrtf(f32);

s32 fn_800F94FC(void *arg0, void *arg1, s32 *arg2, __ps_t *arg3) {
    Fr94FC fr;
    Vec4p *a0 = (Vec4p *)arg0;
    Arg1Ly *a1 = (Arg1Ly *)arg1;
    __ps_t d, e, g, u, v, w, q, t, tA, tB, tC, tD;
    __ps_t v0, v1, v2, v3, v4, v5, w0, w1, zero;
    f32 f8v, eps, A, B, C, Cs, disc, sq, one, invA, nB, t0n, t1n;
    union {
        f32 s;
        __ps_t p;
    } t0, t1;
    f32 ts;

    d = a1->p1;
    e = a0->p1;
    zero = lbl_8029C060;
    g = a0->p3;
    t = __builtin_ps_sub(e, d);
    fr.h10.p = t;
    u = __builtin_ps_sub(g, e);
    v = a1->p0;
    e = __builtin_ps_mul(u, u);
    w = a0->p0;
    eps = lbl_8029C0DC;
    q = a0->p2;
    d = t;
    t = __builtin_ps_mul(d, d);
    f8v = a1->f10;
    q = __builtin_ps_sub(q, w);
    w = __builtin_ps_sub(w, v);
    fr.h18.p = q;
    t = __builtin_ps_merge00(t, zero);
    t = __builtin_ps_madd(w, w, t);
    fr.h20.p = u;
    d = __builtin_ps_mul(d, u);
    t = __builtin_ps_sum0(t, t, t);
    e = __builtin_ps_merge00(e, zero);
    d = __builtin_ps_merge00(d, zero);
    e = __builtin_ps_madd(q, q, e);
    w = __builtin_ps_madd(w, q, d);
    Cs = fr.h58.s[0];
    e = __builtin_ps_sum0(e, e, e);
    fr.h48.p = e;
    w = __builtin_ps_sum0(w, w, w);
    C = Cs;
    fr.h50.p = w;
    A = fr.h48.s[0];
    f8v = f8v * f8v;
    B = fr.h50.s[0];
    C = C - f8v;
    disc = B * B - A * C;
    if (disc < eps) {
        *arg2 = 0;
        return 0;
    }
    if (disc <= eps) {
        goto single;
    }
    sq = sqrtf(disc);
    one = lbl_8029C0E0;
    nB = -B;
    t0n = nB - sq;
    t1n = nB + sq;
    invA = one / A;
    t0.s = t0n * invA;
    t1.s = t1n * invA;
    fr.t60 = t0.s;
    fr.t64 = t1.s;
    if (t0.s > one) {
        *arg2 = 0;
        return 0;
    }
    if (t1.s < eps) {
        *arg2 = 0;
        return 0;
    }
    t0.s = fr.t60;
    if (!(t0.s >= eps)) {
        goto nan;
    }
    t1.s = fr.t64;
    if (t1.s <= one) {
        goto twopt;
    }
    fr.u68.s[0] = t0.s;
    *arg2 = 1;
    tA = fr.u68.p;
    tB = tA;
    v0 = fr.h18.p;
    v1 = fr.h20.p;
    v0 = __builtin_ps_muls0(v0, tB);
    w0 = a0->p0;
    v1 = __builtin_ps_muls0(v1, tB);
    fr.o38.p = v0;
    w1 = a0->p1;
    w1 = __builtin_ps_add(w1, v1);
    fr.o40.p = v1;
    goto join;
twopt:
    fr.u70.s[0] = t0.s;
    *arg2 = 2;
    fr.u78.s[0] = t1.s;
    tA = fr.u70.p;
    v0 = fr.h18.p;
    tB = fr.u78.p;
    tC = tA;
    v2 = __builtin_ps_muls0(v0, tC);
    v1 = fr.h20.p;
    tD = tB;
    w1 = a0->p1;
    w0 = a0->p0;
    v3 = __builtin_ps_muls0(v1, tC);
    w0 = __builtin_ps_add(w0, v2);
    t1.p = __builtin_ps_add(t1.p, v3);
    arg3[0] = w0;
    arg3[1] = t1.p;
    v4 = __builtin_ps_muls0(v1, tD);
    w1 = a0->p1;
    v5 = __builtin_ps_muls0(v0, tD);
    w0 = a0->p0;
    w1 = __builtin_ps_add(w1, v4);
    fr.o38.p = v5;
    w0 = __builtin_ps_add(w0, v5);
    arg3[3] = w1;
    arg3[2] = w0;
    fr.o40.p = v4;
    fr.o28.p = w0;
    fr.o30.p = w1;
    return 1;
nan:
    fr.u80.s[0] = t1.s;
    *arg2 = 1;
    tA = fr.u80.p;
    tB = tA;
    v1 = fr.h20.p;
    v0 = fr.h18.p;
    v1 = __builtin_ps_muls0(v1, tB);
    w0 = a0->p0;
    v0 = __builtin_ps_muls0(v0, tB);
    fr.o40.p = v1;
    w1 = a0->p1;
    w1 = __builtin_ps_add(w1, v1);
    fr.o38.p = v0;
join:
    w0 = __builtin_ps_add(w0, v0);
    arg3[1] = w1;
    arg3[0] = w0;
    fr.o28.p = w0;
    fr.o30.p = w1;
    return 1;
single:
    nB = -B;
    ts = nB / A;
    fr.t60 = ts;
    if (!(ts >= eps)) {
        *arg2 = 0;
        return 0;
    }
    one = lbl_8029C0E0;
    if (!(ts <= one)) {
        *arg2 = 0;
        return 0;
    }
    fr.u88.s[0] = ts;
    *arg2 = 1;
    tA = fr.u88.p;
    tB = tA;
    v0 = __builtin_ps_muls0(u, tB);
    w1 = a0->p1;
    w0 = a0->p0;
    v1 = __builtin_ps_muls0(q, tB);
    w1 = __builtin_ps_add(w1, v0);
    w0 = __builtin_ps_add(w0, v1);
    arg3[1] = w1;
    arg3[0] = w0;
    fr.o28.p = w0;
    fr.o30.p = w1;
    return 1;
}
