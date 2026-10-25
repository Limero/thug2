// WIP DRAFT (non-matching) — hand reconstruction of 0x801ACF84
// family=ps range=0x801ACF84-0x801AD3DC size=1112B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// ------------------------------------------------------------------
// PARKED 2026-10-04. Measured: DIFF, 1080B object vs 1112B want (8
// instructions short), 4.07% masked (test_wip_drafts.py --addr
// 0x801ACF84). Semantics are fully decoded (see below) and the whole
// 456-byte stack layout now matches the want EXACTLY (all 20 locals at
// 0x08/0x18/0x28/0x38/0x48/0x68/0x78/0x88/0x98/0xa8/0xb8/0xf0/0x100/
// 0x110/0x114/0x118/0x120/0x128/0x130), but the frame is still 0x1b8
// vs the want's 0x1c8, and because the frame size changes EVERY stack
// displacement the byte score stays ~4%.
//
// Blockers, all measured, none of them type/declaration-fixable:
//  (1) callee-saved FPR count 4 vs 5. The want keeps f27=0.017453292f,
//      f28=same-scale, f29=90.0f, f30=radius*radius and f31=radius
//      live across the 8 calls in the loop body; ngccc always folds my
//      `rsq = radius` into the incoming f1 (fmr-coalesced), so only 4
//      FPRs end up needing a save. Tried: separate rsq variable, inline
//      `radius*radius`, in-place `rsq = rsq*rsq`, hoisting/not hoisting
//      — always 4. The in-place `rsq = rsq*rsq` form is the best
//      variant and is what this draft keeps: it reproduces the want's
//      `fmuls f30,f30,f30` shape and moves the GPR save area onto r17
//      like the want.
//  (2) three register copies in the original that no C shape produced:
//      `fmr f13,f0` after the dot1 lane-0 reload, `fmr f0,f9` after
//      the dot2 reload, `fmr f31,f11` before the 90.0 compare.
//  (3) `fmr f29,f31` at 0x801AD350 inside the hit branch: the original
//      OVERWRITES the loop-invariant 90.0f constant register with the
//      current dot3 value, and the loop keeps running, so the next
//      iteration compares against the previous hit's dot3 instead of
//      90.0f. That is a loop-invariant-restore bug in the retail
//      compiler build; no correct C can be miscompiled that way.
//  (4) arg-setup/load coin-flips (recipe family §6b-51): `li r9,1` for
//      fn_80006C64's 7th arg lands before vs after the `node->partner`
//      reload (mine then reloads partner one extra time), and the
//      preheader constant-load schedule differs.
//  (5) 8 bytes of unexplained slack: the want's local area ends at
//      0x163 with the last scalar at 0x130 (dot3), i.e. 0x138..0x163
//      (44B) is unused frame. My locals produce the same used offsets
//      but only 32B of slack, so even a perfect pass-1/pass-2 set would
//      need one more 4-byte slot I cannot justify from the code.
//
// Decoded semantics (for whoever retries): arg0 = {0x48 node array,
// 0x50 count}; each node is 0x60B {0x08..0x20 = box lo/hi as two
// Vec4 pairs (0x4-byte gap at 0x14), 0x28/0x30 = two pairs,
// 0x48 = partner, 0x50 = flags}. arg1/arg2 are the segment endpoints,
// fn_801AAE94 makes their AABB (4th lane = 1.0f @0x802ABFFC), expanded
// by +-radius; the loop rejects nodes failing either flag test
// (0x20/8), fn_800E9D30, a NULL partner, or a box that does not fit
// inside. fn_80006C64(&p1,&q,&hit1,&hit2,&t1,&t2,1) is the ray/box
// query; d = hit2-hit1, then three
// __builtin_ps_sum0/__builtin_ps_madd/__builtin_ps_merge00/__builtin_ps_mul
// dot products vs radius*radius, 0.017453292f (scaled by -90.0f) and
// 90.0f; the 0x98/0xa0 psq_sts are the WANT's spills of the two
// __builtin_ps_muls0 products into the *same* local that later receives
// the world position, and 0x88/0x90 are the dead spills of d (both
// pairs stay live in registers until the reloads after the if-branch),
// so d must be ONE 16-byte aggregate local, not two scalars.
// ------------------------------------------------------------------
typedef union {
    __ps_t ps;
    struct {
        f32 hi;
        f32 lo;
    } flt;
} PSV;

typedef struct {
    __ps_t a;
    __ps_t b;
} Pair;

typedef struct {
    PSV q0;
    PSV q1;
} Vec4;

typedef struct {
    __ps_t q[4];
} Quad;

typedef struct {
    __ps_t q[4];
    f32 a;
    f32 b;
    f32 c;
    s32 i0;
    s32 i1;
} Hit;

typedef struct Node {
    s32 unk0x00;
    s32 unk0x04;
    f32 bx;
    f32 by;
    f32 bz;
    s32 unk0x14;
    f32 cx;
    f32 cy;
    f32 cz;
    __ps_t v0;
    __ps_t v1;
    s32 unk0x38;
    s32 unk0x3C;
    s32 unk0x40;
    s32 unk0x44;
    struct Node *partner;
    s32 unk0x4C;
    s32 flags;
} Node;

typedef struct World {
    s32 unk0x00;
    char pad0x04[0x44];
    Node *nodes;
    s32 unk0x4C;
    s32 count;
} World;

/* rodata2 pair { 176.0f, -0.0f } */
extern __ps_t lbl_802AB778;
extern f32 lbl_802ABFFC; /* 1.0f */
extern f32 lbl_802AC000; /* 90.0f */
extern f32 lbl_802AC004; /* 0.017453292f */
extern f32 lbl_802AC008; /* -90.0f */

void fn_800063B4(void *);
void fn_801AAE94(Vec4 *, Vec4 *, Vec4 *, Vec4 *);
s32 fn_800E9D30(Node *, s32);
s32 fn_80006C64(Vec4 *, Quad *, Vec4 *, Vec4 *, f32 *, f32 *, s32);
void fn_801AE5A4(Vec4 *, World *, Node *);
s32 fn_801ADCE4(Vec4 *, Vec4 *);
void fn_801AE4CC(Vec4 *, World *, Vec4 *);
s32 fn_800E6A08(void *, Vec4 *, Vec4 *, Vec4 *, Vec4 *, Hit *, s32, f32);

s32 fn_801ACF84(World *arg0, Vec4 *arg1, Vec4 *arg2, Vec4 *arg3, void *arg4,
                Hit *arg5, f32 radius) {
    Vec4 p1;
    Vec4 p2;
    Vec4 lo;
    Vec4 hi;
    Quad q;
    Vec4 hit1;
    Vec4 hit2;
    Pair d;
    Vec4 p1w;
    Vec4 p2w;
    Hit hit;
    Vec4 v;
    Vec4 w;
    f32 t1;
    f32 t2;
    PSV dot1;
    PSV dot2;
    PSV dot2b;
    PSV dot3;
    f32 rsq;
    f32 maxdeg;
    f32 deg2rad;
    f32 rad2deg;
    s32 off;
    s32 idx;
    s32 res;
    s32 ok;
    Node *node;
    Vec4 *bhi;
    Vec4 *blo;
    __ps_t t;

    fn_800063B4(&p1);
    p1.q0.ps = arg1->q0.ps;
    p1.q1.ps = arg1->q1.ps;
    p2.q0.ps = arg2->q0.ps;
    p2.q1.ps = arg2->q1.ps;
    lo.q1.flt.lo = lbl_802ABFFC;
    hi.q1.flt.lo = lbl_802ABFFC;
    fn_801AAE94(&p1, &p2, &lo, &hi);
    rsq = radius;
    lo.q0.flt.hi -= rsq;
    lo.q0.flt.lo -= rsq;
    lo.q1.flt.hi -= rsq;
    hi.q0.flt.hi += rsq;
    hi.q0.flt.lo += rsq;
    hi.q1.flt.hi += rsq;
    rsq = rsq * rsq;
    maxdeg = lbl_802AC000;
    deg2rad = lbl_802AC004;
    rad2deg = lbl_802AC008;
    res = 0;
    idx = 0;
    off = 0;
    for (; idx < arg0->count; idx++, off += 0x60) {
        node = (Node *)((char *)arg0->nodes + off);
        ok = 1;
        if (!(node->flags & 0x20)) {
            ok = 0;
        }
        if (ok != 0) {
            continue;
        }
        ok = 1;
        if (!(node->flags & 8)) {
            ok = 0;
        }
        if (ok != 0) {
            continue;
        }
        if (fn_800E9D30(node, 2) == 0) {
            continue;
        }
        if (node->partner == NULL) {
            continue;
        }
        bhi = (Vec4 *)((char *)node + 0x18);
        blo = (Vec4 *)((char *)node + 8);
        if (lo.q0.flt.hi > bhi->q0.flt.hi) {
            continue;
        }
        if (hi.q0.flt.hi < blo->q0.flt.hi) {
            continue;
        }
        if (lo.q1.flt.hi > bhi->q1.flt.hi) {
            continue;
        }
        if (hi.q1.flt.hi < blo->q1.flt.hi) {
            continue;
        }
        if (lo.q0.flt.lo > bhi->q0.flt.lo) {
            continue;
        }
        if (hi.q0.flt.lo < blo->q0.flt.lo) {
            continue;
        }
        fn_800063B4(&q);
        q.q[0] = node->v0;
        q.q[1] = node->v1;
        q.q[2] = node->partner->v0;
        q.q[3] = node->partner->v1;
        if (fn_80006C64(&p1, &q, &hit1, &hit2, &t1, &t2, 1) == 0) {
            continue;
        }
        d.b = __builtin_ps_sub(hit2.q1.ps, hit1.q1.ps);
        d.a = __builtin_ps_sub(hit2.q0.ps, hit1.q0.ps);
        t = __builtin_ps_madd(d.a, d.a,
                              __builtin_ps_merge00(__builtin_ps_mul(d.b, d.b),
                                                   lbl_802AB778));
        dot1.ps = __builtin_ps_sum0(t, t, t);
        if (dot1.flt.hi > rsq) {
            continue;
        }
        t = __builtin_ps_madd(arg3->q0.ps, d.a,
                              __builtin_ps_merge00(
                                  __builtin_ps_mul(arg3->q1.ps, d.b),
                                  lbl_802AB778));
        dot2.ps = __builtin_ps_sum0(t, t, t);
        if (dot2.flt.hi > deg2rad) {
            dot2b.flt.hi = dot2.flt.hi * rad2deg;
            t = dot2b.ps;
            p1w.q0.ps = __builtin_ps_muls0(arg3->q0.ps, t);
            p1w.q1.ps = __builtin_ps_muls0(arg3->q1.ps, t);
            d.a = __builtin_ps_sub(d.a, p1w.q0.ps);
            d.b = __builtin_ps_sub(d.b, p1w.q1.ps);
        }
        t = __builtin_ps_madd(d.a, d.a,
                              __builtin_ps_merge00(__builtin_ps_mul(d.b, d.b),
                                                   lbl_802AB778));
        dot3.ps = __builtin_ps_sum0(t, t, t);
        if (dot3.flt.hi > maxdeg) {
            continue;
        }
        fn_801AE5A4(&p1w, arg0, node);
        fn_801AE5A4(&p2w, arg0, node->partner);
        if (fn_801ADCE4(&p1w, &p2w) != 1) {
            continue;
        }
        hit.i1 = (s32)node;
        fn_801AE5A4(&p1w, arg0, node);
        fn_801AE5A4(&p2w, arg0, node->partner);
        fn_801AE4CC(&v, arg0, &hit2);
        fn_801AE4CC(&w, arg0, &hit1);
        if (fn_800E6A08(arg4, &p1w, &p2w, &v, &w, &hit, 0, t2) == 1) {
            res = 1;
            arg5->q[0] = hit.q[0];
            arg5->q[1] = hit.q[1];
            arg5->q[2] = hit.q[2];
            arg5->q[3] = hit.q[3];
            arg5->a = hit.a;
            arg5->b = hit.b;
            arg5->c = hit.c;
            arg5->i0 = hit.i0;
            arg5->i1 = hit.i1;
        }
    }
    return res;
}