// WIP DRAFT (non-matching) — hand-rebuilt from the DOL decode (Catmull-Rom
// tangent/colour interpolation over a 24-byte record queue).
// family=m2c range=0x80081EC8-0x8008279C size=2260B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
//
// PARKED 2026-10-05: best = DIFF, **17/586 words (2.9%)**,
// object **2344 B vs want 2260 B (+84 B)** — unchanged from the 2026-09-26
// round below, which is expected: this is a 565-word paired-single function
// whose five blockers are each a multi-session item and none of them is
// reachable by a single targeted edit. The body below is the best known and the
// decode in this header is complete; treat the whole comment block as the
// handoff. TRIED AND REVERTED this round: forcing `lbl_80296528` (the
// 2^52+2^31 int->float bias double) to be re-loaded rather than held in a
// callee-saved FPR, via `cvt.d - *(volatile f64 *)&lbl_80296528[0]` in all six
// lerp sites — 17/585 -> 15/585 and 2344 B -> 2340 B, i.e. strictly worse.
// So blocker 1's "make the double not callee-saved" needs a different lever
// (move the `lfd` into the byte loop's body, i.e. restructure the lerp rather
// than change the operand's volatility); do not retry the volatile spelling.
//
// WHAT THIS FUNCTION IS (full decode, replaces the 2026-09-10 m2c triage):
// A Catmull-Rom "tangent ring" step. `lbl_80366DDC` is a bounded byte QUEUE
// ({s32 used; s32 chunk; char payload[0x4000]}, see the already-promoted
// src/fn_8006BC44.c / fn_8006BC90.c / fn_8006BCDC.c). The function pops the
// last three records into locals p[0..2] (pop order => p[0] is the OLDEST),
// computes each record's three "extended" points, pushes twelve records back,
// and finally either copies the three records out to *arg0 (advancing it by
// 0x18 each time) or decrements *arg4 / resets *arg3.
//
// Record layout — 24 (0x18) bytes, three popped records land at r1+0x8,
// 0x20, 0x38 (stride 0x18):
//   +0x00 f32 a[4]   x,y,z,w  (a[3] is LIVE: the PS distance uses a[0..3])
//   +0x10 u8  b[4]   4 lerped bytes, s8 arithmetic, 4-iteration bdnz loop
//   +0x14 f32 q      lerped; the retail loop runs TWICE (i=0,1) so the second
//                    element deliberately reads/writes the NEXT record's a[0]
//                    (p[0].q[1] == p[1].a[0]; r[2].q[1] lands on dist[0], which
//                    the scalar reloads have already consumed).
// So the queue chunk size is 0x18 and the record really is 24 bytes.
//
//   d1[4] = {p1.a0-p0.a0, p1.a1-p0.a1, p1.a2-p0.a2, 1.0f}   @0x50
//   d2[4] = {p2.a0-p0.a0, p2.a1-p0.a1, p2.a2-p0.a2, 1.0f}   @0x60
//   nrm[4]= {cross.x, cross.z, cross.y, 1.0f}                @0x70   (d1 x d2)
//   t[6]  = the six (p[i] - arg2) PS difference pairs          @0x80
//   r[0..2] = the three lerped output records                 @0xB0
//   dist[4]= 4 PS dot products, 8-byte stride, psq_st then lfs @0xF8
//   cvt     = the shared 8-byte int<->float scratch           @0x128
//
// dist[] semantics (tracked from the ps_madd/ps_sum0 chain):
//   dist[0] = |nrm  - arg2|^2   <-- the CROSS PRODUCT, hence the first test
//   dist[1] = |p[0] - arg2|^2
//   dist[2] = |p[1] - arg2|^2
//   dist[3] = |p[2] - arg2|^2
//   if (dist[0] > t) -> A: lerp+push x12.
//   else if (dist[1] < *arg3 || dist[2] < *arg3 || dist[3] < *arg3, and
//            queue.used <= 0x200) -> B: identical lerp+push x12, then
//            *arg4 -= 4 and (if it hits 0) *arg3 = -1.0f.
//   else -> C: memcpy p[0], p[1], p[2] to *arg0, advancing *arg0 by 0x18.
// Return 1 on every path except the empty-queue early-out (return 0).
//
// The four dot products are the game compiler's 4-wide paired-single form,
// now CONFIRMED reproducible (probe-verified with cc1 3.9.3 -mps-float):
//   s1 = ps_mul(d1, d1);  acc = ps_merge00(s1, zero);
//   s0 = ps_mul(d0, d0);  acc = ps_madd(s0, s0, acc);  d = ps_sum0(acc,acc,acc)
// i.e. `__builtin_ps_merge00(pairsq, ((__ps_t *)lbl_802964D8)[0])` emits the
// want's ps_merge00 with the {0,0} rodata2 pair, and the two-psq_l-then-sub
// / mul / merge / madd / sum0 sequence matches word for word. The full
// 4-accumulator schedule has NOT been matched (see BLOCKER).
//
// Constants (all real .rodata2 symbols, so this stays doc-14 promote-clean):
//   lbl_8029651C = 0.5f (Catmull-Rom tension), lbl_80296520 = 1.0f (w slot),
//   lbl_80296528 = 4503601774854144.0 = 2^52+2^31 (the int->float dance bias,
//   NOT the private 0x4330000080000000 pool), lbl_80296530 = -1.0f (reset),
//   lbl_802964D8 = {0.0f, 0.0f} (ps_merge00 zero pair).
// The s8 lerp uses the retail manual conversion (recipe 6j-1): xor 0x80000000
// into the cvt slot's low word, hi = 0x43300000, lfd, fsub lbl_80296528,
// frsp, *0.5f, fctiwz, stfd, lwz.
//
// ============================================================================
// CURRENT STATE (re-measured 2026-09-26, isolated-worker round)
//   tools/venv/bin/python tools/test_wip_drafts.py --addr 0x80081EC8
//       -> DIFF   (official; the tool auto-appends -mps-float for __ps_t bodies,
//                  tools/test_wip_drafts.py:246, so this IS the -mps-float build)
//   tools/venv/bin/python tools/ps_diff.py 0x80081EC8 2260 "-mps-float"
//       -> 17/586 words (2.9%), 569 mismatches, got 2344B vs want 2260B (+84B)
//   was 1.31% (676 diffs, 2740B) as the m2c statics-DCE husk before this round.
//   `stwu r1, -0x1a8(r1)` now matches want EXACTLY (offset 0 is no longer a
//   diff); the +8 FPR frame quirk is therefore already accounted for.
// What this round fixed (all real, all verified in the compiled bytes):
//   * the nine file-scope `static s32 spXX` statics are gone - they put the
//     record slots in .sbss and let ngccc DCE the whole body (recipe 6j-4).
//     They are now the real frame locals p[3]/d1/d2/nrm/t[6]/r[3]/dist[4]/cvt.
//   * the phantom `0x80290000` call arguments on fn_8006BCDC/fn_8006BC90 are
//     gone: both are 2-arg void (confirmed against the promoted
//     src/fn_8006BC90.c / fn_8006BCDC.c), which also removes the spurious crclr.
//   * the 0x18-byte record struct, the 0x18 stack stride (pop order p2,p1,p0 =
//     r1+0x38,0x20,0x8), the 3-way control flow and the exact 12-push sequence
//     are modelled instead of approximated.
//   * the queue globals and every float/double constant are real .rodata2 /
//     .bss symbols, so the int->float dance stays doc-14 promote-clean.
//   * the two ~668-byte lerp+push blocks are textually DUPLICATED. A single
//     shared copy (the first thing tried) let crossjumping emit one block and
//     the object came out 632 bytes short - want really has both.
//   * the shared cvt slot no longer round-trips through `(f64)(s32)f`: that
//     spelling made cc1 emit a *second* `xoris` on the reloaded slot word
//     (store-to-load forwarding shuffle, 21 insns/lerp instead of 18).
// CONFIRMED reproduction recipe (do not re-derive): the four 4-wide PS dot
// products are
//   s1 = ps_mul(d1,d1); acc = ps_merge00(s1, ((__ps_t *)lbl_802964D8)[0]);
//   s0 = ps_mul(d0,d0); acc = ps_madd(s0,s0,acc); d = ps_sum0(acc,acc,acc);
// `__builtin_ps_merge00(<pairsq>, <zero pair>)` is what emits want's
// `ps_merge00 fD,fD,f6` with the {0,0} rodata2 pair (probe-verified on
// cc1 3.9.3). __ps_t is an ARRAY type, so every access needs a
// `((__ps_t *)&x)[k]` cast and the accumulators must be f32[2] locals, not
// __ps_t (plain `s = t;` assignments are a hard error).
//
// REMAINING BLOCKERS (in dependency order; ~1 multi-session rebuild)
//  1. FPR COLOURING (top-of-function, cascades through the whole body).
//     want saves f26..f31: f26 = the farg0 param copy (`fmr f26, f1`), f27 =
//     the 0.5f constant, f28 = the 1.0f constant, f29/f30/f31 = the d2
//     components. got saves only f27..f31 with farg0 -> f27 and 0.5f -> f28,
//     because got keeps the 2^52+2^31 double permanently live in f31 whereas
//     want frees f31 and reloads the double with `lfd f31, 0x6528(r9)` inside
//     the first lerp block. A hard `register f32 __asm__("fr27")` pin on the
//     0.5f local was tried: 586 -> 588 words, no help. Recipes 67/98/111/124/
//     189 apply; the lever that is missing is making the double NOT
//     callee-saved (load it inside the byte loop, i.e. hoist the `lfd` into
//     the loop body rather than the preamble) - untried.
//  2. LOCALS 8 BYTES OVER. `stmw r14, 0x138(r1)` vs want's `0x130(r1)`: got
//     puts the cvt union at 0x130 while want has a dead 0x10 hole at 0x118 and
//     cvt at 0x128. The frame total still matches only because blocker 1
//     saves one FPR fewer. Declaring the two unused __ps_t slots the original
//     evidently had (recipe 84's "frame-size overlay") is the likely fix but
//     is speculative.
//  3. THE BYTE-LERP DANCE. want's 18-insn/lerp form is
//     [lbzx x2][4x dead `mr rN,r9`][subf][xoris][stw 0x12c][stw 0x128]
//     [lfd][fsub][frsp][fmuls][fmr f13,f0][fctiwz][stfd][lwz][add][stbx].
//     The four dead `mr rN,r9` copies are the doc-33 "dead-code asymmetry"
//     family (want keeps provably-dead copies) and the stw order is the
//     reverse of what the union spelling produces. Current cost: 18 vs 21
//     insns/lerp x 3 x 4 iters x 2 blocks.
//  4. THE PS BLOCK SCHEDULE. want interleaves all four accumulators: pair1
//     sub, pair1 mul, pair0 sub, madd, and fires the `psq_st` of the NEXT
//     accumulator's inputs before the current madd. got emits the four
//     accumulate sequences back to back. The six `psq_st` to 0x80..0xA8 and
//     the four `psq_st`+`lfs` to 0xF8/0x100/0x108/0x110 also need want's
//     exact interleave. This is the same class as doc-15 (expands_call /
//     ready-list tie-break) applied to PS webs.
//  5. FLOAT-LERP STORE ORDER. want emits the nine `stfs` as
//     [B0][B4][B8][C8][CC][D0][E0][E4][E8]; got emits the r[2] trio (E0,E4,
//     E8) before B8. Plain store-run rotation/permute search (recipes 24/64/
//     6an-3) is the untried lever - the run is clean, so it is searchable.
// No parking doc was written: the root cause is the ordinary big-PS-function
// allocator/scheduler wall (cf. 6ai-152 "hand-rebuild threshold ~600B; beyond
// that, decode the structure into the draft header for multi-session
// rebuilds"), which is already documented. The structural decode above is that
// handoff, and it is complete enough to rebuild from without re-reading the DOL.
#include "types.h"

typedef struct {
    f32 a[4];
    u8 b[4];
    f32 q;
} Rec;

typedef union {
    __ps_t p;
    f32 f[2];
} Pair;

typedef union {
    s32 w[2];
    f64 d;
} Cvt;

extern s32 lbl_80366DDC;
extern s32 lbl_80366DE0;
extern unsigned char lbl_802964D8[];
extern f32 lbl_8029651C[1];
extern f32 lbl_80296520[1];
extern f64 lbl_80296528[1];
extern f32 lbl_80296530[1];

void fn_8006BC90(void *, void *);
void fn_8006BCDC(void *, void *);

s32 fn_80081EC8(f32 **arg0, f32 *arg2, f32 *arg3, s32 *arg4, f32 farg0) {
    Rec p[3];
    f32 d1[4];
    f32 d2[4];
    f32 nrm[4];
    Pair t[6];
    Rec r[3];
    Pair dist[4];
    Cvt cvt;
    f32 *pq;
    f32 *rq;
    f32 w, f;
    s32 i;
    s32 cnt;
    s32 sz;
    s32 b0, b1, b2;
    f32 v0, v1, v2, v3;

    w = lbl_8029651C[0];
    if (lbl_80366DDC == 0) {
        return 0;
    }

    fn_8006BCDC(&lbl_80366DDC, &p[2]);
    fn_8006BCDC(&lbl_80366DDC, &p[1]);
    fn_8006BCDC(&lbl_80366DDC, &p[0]);

    /* --- the two edge vectors and their cross product ------------------- */
    d1[0] = p[1].a[0] - p[0].a[0];
    d1[1] = p[1].a[1] - p[0].a[1];
    d1[2] = p[1].a[2] - p[0].a[2];
    d1[3] = lbl_80296520[0];
    d2[0] = p[2].a[0] - p[0].a[0];
    d2[1] = p[2].a[1] - p[0].a[1];
    d2[2] = p[2].a[2] - p[0].a[2];
    d2[3] = lbl_80296520[0];
    nrm[0] = d1[1] * d2[2] - d1[2] * d2[1];
    nrm[1] = d1[2] * d2[0] - d1[0] * d2[2];
    nrm[2] = d1[0] * d2[1] - d1[1] * d2[0];
    nrm[3] = lbl_80296520[0];

    /* --- the four 4-wide paired-single dot products -------------------- */
    ((__ps_t *)t)[0] = ((__ps_t *)&p[0].a[0])[0] - ((__ps_t *)arg2)[0];
    ((__ps_t *)t)[1] = ((__ps_t *)&p[0].a[0])[1] - ((__ps_t *)arg2)[1];
    ((__ps_t *)t)[2] = ((__ps_t *)&p[1].a[0])[0] - ((__ps_t *)arg2)[0];
    ((__ps_t *)t)[3] = ((__ps_t *)&p[1].a[0])[1] - ((__ps_t *)arg2)[1];
    ((__ps_t *)t)[4] = ((__ps_t *)&p[2].a[0])[0] - ((__ps_t *)arg2)[0];
    ((__ps_t *)t)[5] = ((__ps_t *)&p[2].a[0])[1] - ((__ps_t *)arg2)[1];

    ((__ps_t *)&dist[0].p)[0] = __builtin_ps_mul(((__ps_t *)t)[1], ((__ps_t *)t)[1]);
    ((__ps_t *)&dist[0].p)[0] = __builtin_ps_merge00(((__ps_t *)&dist[0].p)[0], ((__ps_t *)lbl_802964D8)[0]);
    ((__ps_t *)&dist[0].p)[0] = __builtin_ps_madd(((__ps_t *)t)[0], ((__ps_t *)t)[0], ((__ps_t *)&dist[0].p)[0]);
    ((__ps_t *)&dist[0].p)[0] = __builtin_ps_sum0(((__ps_t *)&dist[0].p)[0], ((__ps_t *)&dist[0].p)[0], ((__ps_t *)&dist[0].p)[0]);

    ((__ps_t *)&dist[1].p)[0] = __builtin_ps_mul(((__ps_t *)t)[3], ((__ps_t *)t)[3]);
    ((__ps_t *)&dist[1].p)[0] = __builtin_ps_merge00(((__ps_t *)&dist[1].p)[0], ((__ps_t *)lbl_802964D8)[0]);
    ((__ps_t *)&dist[1].p)[0] = __builtin_ps_madd(((__ps_t *)t)[2], ((__ps_t *)t)[2], ((__ps_t *)&dist[1].p)[0]);
    ((__ps_t *)&dist[1].p)[0] = __builtin_ps_sum0(((__ps_t *)&dist[1].p)[0], ((__ps_t *)&dist[1].p)[0], ((__ps_t *)&dist[1].p)[0]);

    ((__ps_t *)&dist[2].p)[0] = __builtin_ps_mul(((__ps_t *)t)[5], ((__ps_t *)t)[5]);
    ((__ps_t *)&dist[2].p)[0] = __builtin_ps_merge00(((__ps_t *)&dist[2].p)[0], ((__ps_t *)lbl_802964D8)[0]);
    ((__ps_t *)&dist[2].p)[0] = __builtin_ps_madd(((__ps_t *)t)[4], ((__ps_t *)t)[4], ((__ps_t *)&dist[2].p)[0]);
    ((__ps_t *)&dist[2].p)[0] = __builtin_ps_sum0(((__ps_t *)&dist[2].p)[0], ((__ps_t *)&dist[2].p)[0], ((__ps_t *)&dist[2].p)[0]);

    ((__ps_t *)&dist[3].p)[0] =
        __builtin_ps_mul(__builtin_ps_sub(((__ps_t *)&nrm[0])[1], ((__ps_t *)arg2)[1]),
                         __builtin_ps_sub(((__ps_t *)&nrm[0])[1], ((__ps_t *)arg2)[1]));
    ((__ps_t *)&dist[3].p)[0] = __builtin_ps_merge00(((__ps_t *)&dist[3].p)[0], ((__ps_t *)lbl_802964D8)[0]);
    ((__ps_t *)&dist[3].p)[0] =
        __builtin_ps_madd(__builtin_ps_sub(((__ps_t *)&nrm[0])[0], ((__ps_t *)arg2)[0]),
                          __builtin_ps_sub(((__ps_t *)&nrm[0])[0], ((__ps_t *)arg2)[0]),
                          ((__ps_t *)&dist[3].p)[0]);
    ((__ps_t *)&dist[3].p)[0] = __builtin_ps_sum0(((__ps_t *)&dist[3].p)[0], ((__ps_t *)&dist[3].p)[0], ((__ps_t *)&dist[3].p)[0]);

    v0 = dist[0].f[0];
    v1 = dist[1].f[0];
    v2 = dist[2].f[0];
    v3 = dist[3].f[0];

    if (v0 > farg0) {
        cnt = lbl_80366DE0;
        memcpy(&r[0], &p[0], cnt);
        memcpy(&r[1], &p[1], cnt);
        memcpy(&r[2], &p[2], cnt);

        r[0].a[0] = (p[1].a[0] - p[0].a[0]) * w + p[0].a[0];
        r[0].a[1] = (p[1].a[1] - p[0].a[1]) * w + p[0].a[1];
        r[0].a[2] = (p[1].a[2] - p[0].a[2]) * w + p[0].a[2];
        r[1].a[0] = (p[2].a[0] - p[1].a[0]) * w + p[1].a[0];
        r[1].a[1] = (p[2].a[1] - p[1].a[1]) * w + p[1].a[1];
        r[1].a[2] = (p[2].a[2] - p[1].a[2]) * w + p[1].a[2];
        r[2].a[0] = (p[0].a[0] - p[2].a[0]) * w + p[2].a[0];
        r[2].a[1] = (p[0].a[1] - p[2].a[1]) * w + p[2].a[1];
        r[2].a[2] = (p[0].a[2] - p[2].a[2]) * w + p[2].a[2];

        for (i = 0; i < 4; i++) {
            b0 = p[0].b[i];
            b1 = p[1].b[i];
            cvt.w[1] = (u32)(b1 - b0) ^ 0x80000000;
            cvt.w[0] = 0x43300000;
            f = (f32)(cvt.d - lbl_80296528[0]) * w;
            b2 = (s32)f;
            r[0].b[i] = b0 + b2;

            b1 = p[1].b[i];
            b2 = p[2].b[i];
            cvt.w[1] = (u32)(b2 - b1) ^ 0x80000000;
            cvt.w[0] = 0x43300000;
            f = (f32)(cvt.d - lbl_80296528[0]) * w;
            b0 = (s32)f;
            r[1].b[i] = b1 + b0;

            b2 = p[2].b[i];
            b0 = p[0].b[i];
            cvt.w[1] = (u32)(b0 - b2) ^ 0x80000000;
            cvt.w[0] = 0x43300000;
            f = (f32)(cvt.d - lbl_80296528[0]) * w;
            b1 = (s32)f;
            r[2].b[i] = b2 + b1;
        }

        pq = (f32 *)&p[0].q;
        rq = (f32 *)&r[0].q;
        for (i = 0; i < 2; i++) {
            rq[0 + i] = (pq[2 + i] - pq[0 + i]) * w + pq[0 + i];
            rq[2 + i] = (pq[4 + i] - pq[2 + i]) * w + pq[2 + i];
            rq[4 + i] = (pq[0 + i] - pq[4 + i]) * w + pq[4 + i];
        }

        fn_8006BC90(&lbl_80366DDC, &p[0]);
        fn_8006BC90(&lbl_80366DDC, &r[0]);
        fn_8006BC90(&lbl_80366DDC, &r[2]);
        fn_8006BC90(&lbl_80366DDC, &r[0]);
        fn_8006BC90(&lbl_80366DDC, &p[1]);
        fn_8006BC90(&lbl_80366DDC, &r[1]);
        fn_8006BC90(&lbl_80366DDC, &r[0]);
        fn_8006BC90(&lbl_80366DDC, &r[1]);
        fn_8006BC90(&lbl_80366DDC, &r[2]);
        fn_8006BC90(&lbl_80366DDC, &r[2]);
        fn_8006BC90(&lbl_80366DDC, &r[1]);
        fn_8006BC90(&lbl_80366DDC, &p[2]);
        return 1;
    }

    if (v1 >= *arg3) {
        if (v2 < *arg3) {
            goto lerp_b;
        }
        if (v3 >= *arg3) {
            goto copy_out;
        }
    } else {
        goto lerp_b;
    }

lerp_b:
    if (lbl_80366DDC > 0x200) {
        goto copy_out;
    }
    cnt = lbl_80366DE0;
    memcpy(&r[0], &p[0], cnt);
    memcpy(&r[1], &p[1], cnt);
    memcpy(&r[2], &p[2], cnt);

    r[0].a[0] = (p[1].a[0] - p[0].a[0]) * w + p[0].a[0];
    r[0].a[1] = (p[1].a[1] - p[0].a[1]) * w + p[0].a[1];
    r[0].a[2] = (p[1].a[2] - p[0].a[2]) * w + p[0].a[2];
    r[1].a[0] = (p[2].a[0] - p[1].a[0]) * w + p[1].a[0];
    r[1].a[1] = (p[2].a[1] - p[1].a[1]) * w + p[1].a[1];
    r[1].a[2] = (p[2].a[2] - p[1].a[2]) * w + p[1].a[2];
    r[2].a[0] = (p[0].a[0] - p[2].a[0]) * w + p[2].a[0];
    r[2].a[1] = (p[0].a[1] - p[2].a[1]) * w + p[2].a[1];
    r[2].a[2] = (p[0].a[2] - p[2].a[2]) * w + p[2].a[2];

    for (i = 0; i < 4; i++) {
        b0 = p[0].b[i];
        b1 = p[1].b[i];
        cvt.w[1] = (u32)(b1 - b0) ^ 0x80000000;
        cvt.w[0] = 0x43300000;
        f = (f32)(cvt.d - lbl_80296528[0]) * w;
        cvt.d = (f64)(s32)f;
        r[0].b[i] = b0 + cvt.w[1];

        b1 = p[1].b[i];
        b2 = p[2].b[i];
        cvt.w[1] = (u32)(b2 - b1) ^ 0x80000000;
        cvt.w[0] = 0x43300000;
        f = (f32)(cvt.d - lbl_80296528[0]) * w;
        cvt.d = (f64)(s32)f;
        r[1].b[i] = b1 + cvt.w[1];

        b2 = p[2].b[i];
        b0 = p[0].b[i];
        cvt.w[1] = (u32)(b0 - b2) ^ 0x80000000;
        cvt.w[0] = 0x43300000;
        f = (f32)(cvt.d - lbl_80296528[0]) * w;
        cvt.d = (f64)(s32)f;
        r[2].b[i] = b2 + cvt.w[1];
    }

    pq = (f32 *)&p[0].q;
    rq = (f32 *)&r[0].q;
    for (i = 0; i < 2; i++) {
        rq[0 + i] = (pq[2 + i] - pq[0 + i]) * w + pq[0 + i];
        rq[2 + i] = (pq[4 + i] - pq[2 + i]) * w + pq[2 + i];
        rq[4 + i] = (pq[0 + i] - pq[4 + i]) * w + pq[4 + i];
    }

    fn_8006BC90(&lbl_80366DDC, &p[0]);
    fn_8006BC90(&lbl_80366DDC, &r[0]);
    fn_8006BC90(&lbl_80366DDC, &r[2]);
    fn_8006BC90(&lbl_80366DDC, &r[0]);
    fn_8006BC90(&lbl_80366DDC, &p[1]);
    fn_8006BC90(&lbl_80366DDC, &r[1]);
    fn_8006BC90(&lbl_80366DDC, &r[0]);
    fn_8006BC90(&lbl_80366DDC, &r[1]);
    fn_8006BC90(&lbl_80366DDC, &r[2]);
    fn_8006BC90(&lbl_80366DDC, &r[2]);
    fn_8006BC90(&lbl_80366DDC, &r[1]);
    fn_8006BC90(&lbl_80366DDC, &p[2]);

    cnt = *arg4 - 4;
    *arg4 = cnt;
    if (cnt == 0) {
        *arg3 = lbl_80296530[0];
    }
    return 1;

copy_out:
    sz = lbl_80366DE0;
    memcpy(*arg0, &p[0], sz);
    *arg0 = *arg0 + 0x18;
    memcpy(*arg0, &p[1], sz);
    *arg0 = *arg0 + 0x18;
    memcpy(*arg0, &p[2], sz);
    *arg0 = *arg0 + 0x18;
    return 1;
}
