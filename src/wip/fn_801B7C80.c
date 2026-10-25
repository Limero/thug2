// WIP DRAFT (non-matching) — hand-rebuilt paired-single vector pipeline
// PARKED 2026-10-05 (agent 801B7C80): best measured 12.93% masked
// (tools/score_wip.py, got 588B vs symbol 596B — a 2-word shortfall).
//
// RESIDUAL, in order of the residual block:
//  (1) DOC-30 HARD WALL — the self-targeting countdown window. The original
//      address range holds a 4-iteration counter setup, a matrix-base load,
//      counter-register init, four buffer-pointer materialisations (two stack
//      slots, one heap-offset, one more stack slot), then a self-targeting
//      loop-branch whose label sits ON the branch itself. Every plain-C
//      spelling (for/while/do-while/countdown, s32/u32, +-1/--i, with and
//      without empty loop bodies, and with the arg-pointer inits hoisted in
//      front of it) lowers to a counter setup sunk past the window and
//      re-points the branch past the window — recipes 131 +
//      docs/parkings/solved/30. Verified here for 16 loop forms; only the
//      documented escape hatch (a `volatile` asm window ending in a
//      self-targeting branch word) produces displacement 0, and that is a
//      multi-instruction asm body, which the brief bans. Everything else in
//      the window now matches word-for-word.
//  (2) The 2-word length shortfall + everything after it: the pair/float
//      register assignment and interleave inside the 74-instruction body
//      differ. The original uses low/high float registers for the
//      cross-product web and a second set in the normalise block; this build
//      picks different registers and hard-register pair colour is SILENTLY
//      DROPPED by cc1 2.95.2/3.9.3 (doc 06 M5.0v) so pair colour can only be
//      steered by source shape. Two further allocator artifacts this build
//      cannot reproduce: the original keeps pair-copy operations after the
//      stack reloads and wants the second constant reloaded instead of
//      CSE'd into a register.
//  (3) The 4-lane negation block (four scalar loads, four negations, four
//      stores, contiguous) is emitted at the correct offsets but interleaved
//      with the surrounding pair-multiply / vector-accumulate run.
//
// RULED OUT (all measured, all worse or semantically wrong):
//  - OBJ field offsets: matrix is O+0xD0..0x110 (pad2[0x28]); the two scalars
//    are arg0+0xDC / arg0+0xE0, i.e. fields of the OUTER struct, not of `o`.
//  - fr[] array: 22 x PSU at r1+0x08 => fr[6..13]=0x38..0x70 (matrix copies),
//    fr[14/15]=0x78/0x80, fr[16/17]=0x88/0x90 (the lane-negation temps must BE
//    the array slots — a separate PSU local pushes the frame to 0xd8),
//    fr[18/19]=0x98/0xA0, fr[20]/fr[21]=0xA8/0xB0. `&fr[0]/&fr[2]/&fr[4]` are
//    the three out-params (16B apart), cs+0x48 the 4th.
//  - return type: want has NO `li r3,0` in the epilogue -> `void`.
//  - fr[14] = muls0(fr[8]) and fr[15] = muls0(fr[9]) (NOT the other way round);
//    the negation feeds the SECOND muls0 pair, so out1/out2 use the negated
//    values and the post-call store writes fr[4]/fr[5].
//  - An intermediate variant scored 15.75% only because a bad scripted patch
//    had silently dropped one lane-constant store; that body is semantically
//    wrong and was NOT kept.
//  - `volatile` re-reads of lbl_802AC20C, `m` pinned to r11, `p4` pinned to
//    r6, an explicit `OBJ *o` local, and store/statement-order permutations of
//    the cross-product web: all neutral or worse.
// family=m2c range=0x801B7C80-0x801B7ED4 size=596B
// FLAG: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"

s32 GetChecksum_3(void *, s32);
s32 fn_801B7A90(void *, void *, void *, void *, void *);

extern f32 lbl_802AC20C;
extern f32 lbl_802AC210;
extern __ps_t lbl_802ABFB8;

typedef union {
    __ps_t ps;
    f32 f[2];
} PSU;

typedef struct {
    char pad0[0x58];
    __ps_t v58;
    __ps_t v60;
    char pad1[0x10];
    __ps_t v78;
    __ps_t v80;
    __ps_t v88;
    __ps_t v90;
    __ps_t v98;
    __ps_t vA0;
    char pad2[0x28];
    __ps_t m[8];
} OBJ;

typedef struct {
    char pad0[0xC];
    OBJ *o;
    char pad1[0xCC];
    f32 fDC;
    f32 fE0;
} OUTER;

void fn_801B7C80(OUTER *arg0) {
    PSU fr[22];
    __ps_t *m;
    register char *p0 __asm__("r10");
    register char *p2 __asm__("r5");
    char *p4;
    s32 cs;
    s32 i;
    __ps_t a, b, c, d, e, f, g, h, j, n, r, s, w, u;
    __ps_t m2, m3;
    PSU dot;

    cs = GetChecksum_3(arg0->o, QB_MOTION);

    a = arg0->o->v88;
    b = arg0->o->v98;
    c = arg0->o->v90;
    d = arg0->o->vA0;
    f = __builtin_ps_merge10(b, d);
    e = __builtin_ps_merge10(a, c);
    e = __builtin_ps_mul(e, b);
    f = __builtin_ps_mul(a, f);
    g = __builtin_ps_merge00(c, a);
    h = __builtin_ps_merge00(b, d);
    h = __builtin_ps_mul(g, h);
    f = __builtin_ps_sub(f, e);
    j = __builtin_ps_merge00(f, f);
    fr[18].ps = j;
    fr[18].f[1] = lbl_802AC20C;
    n = __builtin_ps_merge10(h, h);
    h = __builtin_ps_sub(h, n);
    f = __builtin_ps_merge10(f, h);
    arg0->o->v78 = f;
    fr[2].ps = f;
    fr[3].ps = fr[18].ps;
    arg0->o->v80 = fr[3].ps;

    d = arg0->o->v80;
    e = arg0->o->v78;
    g = __builtin_ps_mul(d, d);
    g = __builtin_ps_merge00(g, lbl_802ABFB8);
    g = __builtin_ps_madd(e, e, g);
    dot.ps = __builtin_ps_sum0(g, g, g);
    if (dot.f[0] > lbl_802AC210) {
        r = __builtin_ps_rsqrte(dot.ps);
        s = __builtin_ps_muls0(e, r);
        arg0->o->v78 = s;
        fr[19].ps = r;
        fr[19].f[1] = lbl_802AC20C;
        s = fr[19].ps;
        g = __builtin_ps_mul(d, s);
        arg0->o->v80 = g;
    }

    p0 = (char *)&fr[0];
    p2 = (char *)&fr[2];
    p4 = (char *)&fr[4];
    m = arg0->o->m;
    for (i = 4; i != 0; i--)
        __asm__ volatile("" ::: "memory");

    m2 = m[2];
    m3 = m[3];
    fr[6].ps = m[0];
    fr[7].ps = m[1];
    fr[8].ps = m2;
    fr[9].ps = m3;
    fr[10].ps = m[4];
    fr[11].ps = m[5];
    fr[12].ps = m[6];
    fr[13].ps = m[7];
    fr[20].f[0] = arg0->fDC;
    g = *(volatile __ps_t *)&fr[20];
    fr[14].ps = __builtin_ps_muls0(m2, g);
    fr[15].ps = __builtin_ps_muls0(m3, g);
    w = __builtin_ps_add(arg0->o->v58, fr[14].ps);
    u = __builtin_ps_add(arg0->o->v60, fr[15].ps);
    fr[0].ps = w;
    fr[4].ps = w;
    fr[5].ps = u;
    fr[1].ps = u;
    fr[16].f[0] = -fr[8].f[0];
    fr[16].f[1] = -fr[8].f[1];
    fr[17].f[0] = -fr[9].f[0];
    fr[17].f[1] = -fr[9].f[1];
    fr[21].f[0] = arg0->fE0;
    g = *(volatile __ps_t *)&fr[21];
    fr[14].ps = __builtin_ps_muls0(fr[16].ps, g);
    fr[15].ps = __builtin_ps_muls0(fr[17].ps, g);
    fr[4].ps = fr[14].ps;
    fr[5].ps = fr[15].ps;
    u = __builtin_ps_add(arg0->o->v60, fr[15].ps);
    w = __builtin_ps_add(arg0->o->v58, fr[14].ps);
    fr[3].ps = u;
    fr[2].ps = w;
    fr[14].ps = w;
    fr[15].ps = u;
    if (fn_801B7A90(arg0, p0, p2, p4, (void *)((char *)cs + 0x48))) {
        arg0->o->v58 = fr[4].ps;
        arg0->o->v60 = fr[5].ps;
    }
}