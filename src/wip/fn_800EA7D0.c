// WIP DRAFT (non-matching) — hand-rebuilt from the PS disassembly.
// family=m2c range=0x800EA7D0-0x800EA994 size=452B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
//
// PARKED 2026-10-02 (w75/0x800EA7D0): DIFF 46.9% (53/113 words), pure C,
// object .text 452B == the want size exactly, zero emitted instructions and
// zero `register`/hard-register pins. The previous body scored NEAR 50.4% but
// only because it leaned on inline asm + `register __asm__("frN"/"r30")` pins,
// which the asm ban forbids; pure C costs ~3.5 points and the honest verdict
// therefore drops NEAR -> DIFF. Do not "restore" the pins: the ban is absolute.
//
// SEMANTICS (all recovered, want-verified): args (a0 unused, b, c, d, e);
// b.y > c.y -> 0; d = c.xy-b.xy kept in a volatile pair array; length
// |d|^2 via mul/merge00(k=0)/madd/sum0, normalise with ps_rsqrte +
// lbl_8029AC2C(1.0f) when > lbl_8029AC28(0.0f); bail if normalised y <
// lbl_8029AC30(0.995f); then GetFloat(GetStructure(0x6775E538,0),
// 0x76BF49E0)->scale, offset the segment, then GetFloat(...,0x35B3BBDA)-
// >scale, offset again, emit d->@0x20/@0x28 as e->p2/p3, return 1.
// lbl_8029ABB0[0] = {0.0f,0.0f} is the merge00 filler.
//
// LOAD-BEARING FIX (worth +17 points, 30.1% -> 46.9%): the three bare `ps_mr`
// sites (0x78 `ps_mr f11,f0`, 0x108 `ps_mr f10,f13`, 0x16C `ps_mr f10,f13`)
// need a PS->SF (or PS->PS) copy with NO spill and NO dead load. Every other
// spelling of a scalar lane extract ICEs in cc1 2.95.2/3.9.3
// (optabs.c:4111 = no move pattern for SF <- PS): `(f32)t`, `*(f32 *)&t`,
// `S s; v = s.w[0]`, `__ps_t t; v = t.w[0]`, and even
// `volatile S s; v = s.w[0]` (which costs a `psq_st`+`lfs` pair where retail
// has one `ps_mr`, i.e. +1 word = 456B = total collapse). The ONLY spelling
// that compiles AND emits a single bare `ps_mr` is a *plain, non-volatile*
// union container local: `S mc; mc.p = t; magx = mc.w[0];` (same container
// reused for the W1/W2 slot reads gives the other two `ps_mr`s). Caveat: in
// a standalone probe function that same spelling still ICEs — it only
// survives inside a real function, so re-test in situ, never in isolation.
// (recipes 17802-17820 / 10900 record the psq_l+ps_mr variant with a dead
// psq_l; here not even the psq_l is emitted.)
//
// ROOT CAUSE of the residual 55 words: pure FPR/GPR register allocation plus
// one scheduler decision that cc1 makes differently from retail.
//   1. GPR: retail c->r29, d->r28, e->r31, pv(&V[0])->r30; we get c->r30,
//      pv->r29 (a swap of two callee-saved picks). ~10 words.
//   2. Block 1 load order: retail loads b->p[0], b->p[1], c->p[0], c->p[1].
//      We load b->p[0], c->p[0], c->p[1], b->p[1] — i.e. cc1 reverses the two
//      ps_sub operand pairs and groups them by statement. That 4-word reorder
//      also drives the FPR picks (retail b1->f10/c0->f12/c1->f0, we get
//      b1->f11 and never touch f10), which then cascades through the whole
//      length web and both GetFloat blocks (~40 words). Tried and rejected:
//      pre-loading b->p[0..1] (2 temps) or b/c all four (4 temps) into named
//      locals (46.0%), swapping the two ps_sub statements (loads then come out
//      b1,c1,c0,b0 — 46.0%), grouping both subs before both volatile stores
//      (no change, cc1 re-interleaves them), volatile-qualified argument reads
//      to force the order (45.1%), `register` on pv/w10 (no change, dropped),
//      moving `pv = &V[0]` to the top of the body (42.5%).
//   3. Block 2: we emit a dead duplicate `psq_l f13,8(r1)` for V[0] and hoist
//      c->p[0] above the call's `li r4,0`; retail does neither. Removing
//      either one shortens the object to 110 words (score collapses to 31.9%),
//      so both are length-load-bearing. Reordering either muls0 or hoisting
//      V[0] into a temp also drops to 31.9%.
// Tried and rejected: -fno-schedule-insns (42.5%), -fno-schedule-insns2
// (38.9%), both (27.4%), -O1 (12.8%), -Os (45.1%); ProDG 3.5 / 3.5b140 / 3.7
// / 3.8.1 all FAIL to compile this body (only 3.9.3 has the PS templates).
// Default -O2 -mps-float is best. Applies to the whole 0x800EA4D8/0x800EA7D0
// normalized-distance PS family (sibling fn_800EA4D8: 51.6% -> same wall).
#include "types.h"
#include "qb_constants.h"

extern f32 lbl_8029AC28;
extern f32 lbl_8029AC2C;
extern f32 lbl_8029AC30;
extern __ps_t lbl_8029ABB0[15];

s32 GetStructure(s32 arg0, s32 arg1);
s32 GetFloat(void *arg0, s32 arg1, f32 *arg2, s32 arg3);

typedef union {
    __ps_t p;
    f32 w[2];
} S;

typedef union {
    __ps_t p[2];
    f32 f[4];
} Vec4;

typedef struct {
    char pad0x00[0x20];
    __ps_t d32;
    __ps_t d40;
} Seg;

typedef struct {
    __ps_t p0;
    __ps_t p1;
    __ps_t p2;
    __ps_t p3;
} Out;

s32 fn_800EA7D0(void *a0, Vec4 *b, Vec4 *c, Seg *d, Out *e) {
    volatile S V[6];
    volatile f32 o[2];
    volatile S W0;
    volatile S W1;
    volatile S W2;
    S mc;
    S w1c;
    S w2c;
    __ps_t t;
    __ps_t u;
    __ps_t x;
    __ps_t y;
    __ps_t z;
    __ps_t r;
    volatile S *pv;
    __ps_t w10;
    f32 magx;

    if (!(b->f[1] > c->f[1])) {
        u = __builtin_ps_sub(c->p[0], b->p[0]);
        V[0].p = u;
        t = __builtin_ps_sub(c->p[1], b->p[1]);
        V[1].p = t;
        pv = &V[0];
        t = pv[1].p;
        t = __builtin_ps_mul(t, t);
        t = __builtin_ps_merge00(t, lbl_8029ABB0[0]);
        t = __builtin_ps_madd(u, u, t);
        t = __builtin_ps_sum0(t, t, t);
        mc.p = t;
        magx = mc.w[0];
        if (magx > lbl_8029AC28) {
            r = __builtin_ps_rsqrte(t);
            W0.p = r;
            z = __builtin_ps_muls0(u, r);
            V[0].p = z;
            W0.w[1] = lbl_8029AC2C;
            w10 = W0.p;
            t = __builtin_ps_mul(pv[1].p, w10);
            pv[1].p = t;
        }
        if (!(V[0].w[1] < lbl_8029AC30)) {
        GetFloat((void *)GetStructure(QB_WALK_PARAMETERS, 0), QB_LADDER_TOP_OFFSET_UP, &o[0], 1);
        W1.w[0] = o[0];
        w1c.p = W1.p;
        w10 = w1c.p;
        t = __builtin_ps_muls0(pv[1].p, w10);
        z = __builtin_ps_muls0(V[0].p, w10);
        V[5].p = t;
        V[4].p = z;
        y = __builtin_ps_sub(c->p[0], z);
        x = __builtin_ps_sub(c->p[1], t);
        V[2].p = y;
        V[3].p = x;
        e->p0 = y;
        e->p1 = x;
        GetFloat((void *)GetStructure(QB_WALK_PARAMETERS, 0), QB_LADDER_CLIMB_OFFSET, &o[1], 1);
        W2.w[0] = o[1];
        w2c.p = W2.p;
        w10 = w2c.p;
        t = __builtin_ps_muls0(d->d32, w10);
        z = __builtin_ps_muls0(d->d40, w10);
        V[2].p = t;
        V[3].p = z;
        y = __builtin_ps_sub(e->p0, t);
        x = __builtin_ps_sub(e->p1, z);
        e->p0 = y;
        e->p1 = x;
        e->p2 = d->d32;
        e->p3 = d->d40;
        return 1;
        }
    }
    return 0;
}