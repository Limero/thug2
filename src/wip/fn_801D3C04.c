// REWRITE 2026-10-19 from a full want disassembly (ps_disasm + hand op4
// decode; op4 fields via tools/ps_diff.py afields). Previous hand rebuild
// (2026-10-18) was 240B vs want 276B; this body 264B vs 276B (12 words
// short). PARKED here: prologue FPR-allocation wall (below).
// Key want facts the old body missed:
//   * second len chain has NO merge00: s = madd(s1,s1,t0), so len2
//     includes the w lane (draft merged with k0 in both chains);
//   * s1 (sp8) is NOT reloaded for the delta: it survives in f10 from the
//     `psq_l f10,8(r1)` after t0, so the delta must spell `- s1r` (the live
//     var), while s2 IS reloaded (`psq_l f13,8(r7)`) because f0 was reused;
//   * newv is computed SCALAR (fmuls/fdivs), spilled (stfs 0x20), reloaded
//     as a pair (`psq_l f0,32(r1)`, lane1 don't-care) and copied (ps_mr f12);
//   * both len reads round-trip through stack unions (`psq_st` + `lfs`),
//     so two separate union locals (slots 0x18 / 0x28) are needed;
//   * the first compare is strict `<` (fcmpu + blt), the second `<=` (ble).
// family=hand range=0x801D3C04-0x801D3D18 size=276B
// extra_cflags: -mps-float
// PARKED 2026-10-19 (264B/276B): prologue FPR-allocation wall. Want's first
// three loads are a->f0, k0->f8, b->f0(reuse); this build emits a->f13,
// k0->f0, b->f8, and everything downstream inherits the shift (chain tail
// madd/sum/rsqrte/res/u1/len/compare DOES match, incl. a2=f9 and len=f10).
// Insensitive to: k0 as var vs inline global (identical), k0 assigned
// first / after-t0 / just-before-merge (identical — scheduler always hoists
// the k0 load to 2nd), eliminating the `a` var (f13, same class), plain
// vars + memory barrier instead of volatile (1.7% collapse — volatile is
// load-bearing for the traffic). Mechanism hypothesis: the spill/reload
// traffic (spa/spb/u1/u2/newvw slots) only emits because plain __ps_t
// vars CSE-fold without calls to clobber them (proven: plain+barrier drops
// to 236B, volatile restores 264B); but volatile's transients then lose f0
// to k0's hoisted load. Untried: force k0-load late via an address
// dependence, or shrink the long-range FPR webs (a2/s1r/len/f11v) so the
// shorts win f0. Full want decode (opcodes+regs) is in this header above.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "dolphin/SN_PS.h"

extern __ps_t lbl_802AD278;
extern f32 lbl_802AD45C;
extern f32 lbl_802AD460;
extern f32 lbl_802AD464;
extern f32 lbl_802AD468;

typedef struct NodeD3C04 {
    char pad0x0[0xB8];
    __ps_t p0;
    __ps_t p1;
} NodeD3C04;

typedef struct {
    char pad0x0[0xC];
    NodeD3C04 *unk0xC;
    char pad0x10[0x84];
    f32 unk0x94;
    char pad0x98[0x2E0];
    f32 unk0x378;
} Arg0_D3C04;

typedef union {
    __ps_t ps;
    f32 f[2];
} PairU;

void fn_801D3C04(Arg0_D3C04 *arg0) {
    NodeD3C04 *node = arg0->unk0xC;
    __ps_t b;
    __ps_t a2;
    __ps_t s1;
    __ps_t s1r;
    __ps_t b2;
    __ps_t s2;
    __ps_t s2r;
    __ps_t t0;
    __ps_t m;
    __ps_t s;
    __ps_t h;
    __ps_t r;
    __ps_t rr;
    __ps_t nb;
    volatile __ps_t spa;
    volatile __ps_t spb;
    __ps_t p0r;
    __ps_t p1r;
    PairU u1;
    PairU u2;
    PairU newvw;
    f32 len;
    f32 len2;
    f32 f11v;
    f32 newv;

    spa = node->p0;
    b = node->p1;
    spb = b;
    t0 = b * b;
    a2 = spa;
    m = __builtin_ps_merge00(t0, lbl_802AD278);
    s = __builtin_ps_madd(a2, a2, m);
    h = __builtin_ps_sum0(s, s, s);
    r = __builtin_ps_rsqrte(h);
    rr = __builtin_ps_res(r);
    u1.ps = rr;
    len = u1.f[0];
    if (len < lbl_802AD45C) {
        goto store_def;
    }
    f11v = len * len;
    newv = ((arg0->unk0x378 * lbl_802AD468) * arg0->unk0x94) / len;
    newvw.f[0] = newv;
    nb = newvw.ps;
    s1 = __builtin_ps_muls0(a2, nb);
    spa = s1;
    b2 = spb;
    s2 = __builtin_ps_muls0(b2, nb);
    spb = s2;
    t0 = s2 * s2;
    s1r = spa;
    s = __builtin_ps_madd(s1r, s1r, t0);
    h = __builtin_ps_sum0(s, s, s);
    u2.ps = h;
    len2 = u2.f[0];
    if (len2 > f11v) {
        goto store_def;
    }
    p0r = node->p0;
    node->p0 = p0r - s1r;
    s2r = spb;
    p1r = node->p1;
    node->p1 = p1r - s2r;
    return;
store_def:
    ((f32 *)&node->p0)[0] = lbl_802AD460;
    ((f32 *)&node->p0)[1] = lbl_802AD460;
    ((f32 *)&node->p1)[0] = lbl_802AD460;
    ((f32 *)&node->p1)[1] = lbl_802AD464;
}
