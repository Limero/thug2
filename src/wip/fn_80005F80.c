// WIP DRAFT (rebuilt 2026-09-29 from the DOL disassembly — full typed
// paired-single reconstruction, was an inert m2c husk).
// family=m2c range=0x80005F80-0x80006094 size=276B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Identification: angle-equality test between two unit vectors.
//   s32 fn_80005F80(Vec4 *a, Vec4 *b, f32 angle_in_degrees)
// Both arguments are 4-float (two-pair) vectors; the routine
//   * builds the 3-component dot products a.a and a.b through paired
//     single arithmetic (ps_mul / ps_merge00 with the (0,0) shuffle mask
//     lbl_8028FCC8 / ps_madd / ps_sum0),
//   * takes rsqrte+ps_res of each (the reciprocal length) and spills both
//     pairs to the stack, reading only the .lo lane back,
//   * rejects a length with `if (rsqrt < 0.5f) return 0;`  (lbl_8028FD50),
//   * computes  d = dot(a,b) / rsqrt(a) / rsqrt(b),
//     c = cosf(angle * DEG2RAD)   (lbl_8028FD54 = 0.017453292…,
//                                  fn at 0x80271070 = cosf),
//   * returns (d < c), except that it returns 1 outright when d < 0 <= c.
//     Both zero tests are the NaN-aware `>=` form, i.e. retail's
//     `cror cr0un,cr0eq,cr0gt; bso` idiom.
// Decoded from tools/ps_disasm.py + tools/ps_diff.py; every word of the
// prologue, both PS dot-product chains, the stack round-trips and the whole
// three-way tail below are accounted for.
//
// PARKED — NEAR 94.2% (65/69 masked words), object size byte-exact at 276B.
// Everything matches except TWO adjacent-instruction transpositions inside the
// first PS block; see the residual list at the bottom.  Object .text order:
//
//   want 17 sum0(f0) 18 merge00(f12) 19 rsqrte 20 res 21 madd(f13) 22 psq_st
//   got  17 sum0(f0) 18 rsqrte      19 merge00(f12) 20 res 21 psq_st 22 madd
//
// Levers that moved the pct (all measured with test_wip_drafts/score_body
// under -mps-float):
//   0.1%  m2c husk (psq pairs decoded as garbage, stack values as statics)
//   19.1% typed __ps_t body, but `ret` declared s32 held cosf's f32 result ->
//         int->float dance (fctiwz/stfd/lfd/fsub/frsp) + 8 phantom bytes of
//         frame; splitting the f32 result into its own `c` fixed both.
//   27.8% source order of the two PS chains (mul-u / sum0 / merge00-u /
//         rsqrte / res / madd-dot / sum0-dot) picked to mirror the want order.
//   39.1% tail `r = 1; if (!(f31v < 0)) r = (f31v < c); else if (c < 0) …`
//         — the only tail that keeps ONE shared `fcmpu cr7/f31,f1` block.
//   69.6% ONE recycled f32 scalar `k` for both reciprocal lengths (kills the
//         duplicate reloads of 0x10(r1)/0x18(r1)); declaring it inline instead
//         costs two `lfs` and 30.4%.
//   94.2% `register f32 t0 __asm__("fr0")` staging the three stack->lane reads
//         through a pinned f0 scratch, which reproduces retail's
//         `lfs f0,X(r1); fmr fD,f0` load+copy pair three times (and, with it,
//         the f12 = farg0 / f13 = k role split, which a plain named temp
//         swaps: 30.4%).  Pinning k to fr13 or a copy of farg0 to fr12 both
//         LOSE (21.7% / 27.5%) — the pins must stay on f0 only.
//   + tail shape `if (f31v >= 0) return (f31v < c); if (c >= 0) return 1;
//     return (f31v < c);` (+22.6%): `>=` (rather than `<`/`!(<)`) is what makes
//     cc1 emit the `cror; bso` pair and put the shared compare block first;
//     10 other spellings all land at 28-30% (blt/bge/bns, duplicated block,
//     `r = 1` pre-init hoisted before the call, goto forms).
//
// RESIDUAL (4 words, two transpositions, 94.2%):
//   * `ps_merge00 f12,f12,f9` vs `ps_rsqrte f0,f0` — cc1's sched1 emits the
//     rsqrte one slot earlier no matter what the source order is.  Tried and
//     ruled out: all 4 interleavings of the u-chain / len-chain (incl. building
//     the whole dot chain before rsqrte), all 4 interleavings of the two
//     frame stores, 24 declaration orders of {t,u,len,dot}, madd operand
//     swap, and 9 scheduler flags (-fno-schedule-insns/-insns2/-sched-spec/
//     -gcse/-expensive-optimizations/-thread-jumps/…; -fno-schedule-insns is
//     catastrophic at 52.2%).  Diagnostic builds: deleting only the
//     `fr.rsq_a.f[0]` READ moves merge00 into slot 18 (correct) but then
//     pulls `ps_madd` ahead of rsqrte/res — so the two transpositions are
//     coupled to how many users the length/dot webs have at that point.
//   * `ps_madd f13,f13,f10,f12` vs `psq_st f0,16(r1)` — same cause, opposite
//     slot.
//   * Inline-asm barriers (`__asm__("" : "+r"(len|u))`) are NOT a way in:
//     cc1 2.95 miscompiles the whole PS block when a PS-typed pseudo is tied
//     to an asm operand (6.8-17.8%).  A 2-word asm transcription of the two
//     ops would fit the <30% density rule but would be faking the match for
//     real math, so it was not used.
// Root cause as understood: a sched1 priority tie between the two PS chains
// that this ProDG build resolves the other way round from retail's build;
// the source shapes that would shift the user counts are exactly the ones
// GCC then folds away.
//
// Load-bearing scaffolding (disclosed, zero instructions emitted):
//   * `register f32 t0 __asm__("fr0")` — pins the three stack->scalar lane
//     reads to f0 so cc1 emits the load+copy pair instead of loading straight
//     into the consumer's register (39.1% -> 94.2%).
//   * no `__asm__` blocks at all in this file.
//   * `volatile Frame fr` — the retail psq_st/lfs round-trips through
//     sp+0x08/0x10/0x18 are intentional, not a reload artifact.
#include "types.h"
#include "dolphin/SN_PS.h"

typedef union {
    __ps_t p[2];
    f32 f[4];
} Vec4;

typedef union {
    __ps_t p;
    f32 f[2];
} PSU;

/* retail stack map: dot @sp+0x08, rsq(a) @sp+0x10, rsq(b) @sp+0x18,
   f31 saved @sp+0x28, LR @sp+0x34, frame 0x30 */
typedef struct {
    PSU dot;
    PSU rsq_a;
    PSU rsq_b;
} Frame;

extern __ps_t lbl_8028FCC8;   /* (0.0f, 0.0f) lane mask */
extern f32 lbl_8028FD50;       /* 0.5f  — length guard */
extern f32 lbl_8028FD54;       /* 0.017453292f — DEG2RAD */
extern f32 lbl_8028FD58;       /* 0.0f  — sign test */

f32 cosf(f32 x);

s32 fn_80005F80(Vec4 *arg0, Vec4 *arg1, f32 farg0) {
    volatile Frame fr;
    __ps_t a0;
    __ps_t a1;
    __ps_t b0;
    __ps_t b1;
    __ps_t t;
    __ps_t u;
    __ps_t len;
    __ps_t dot;
    f32 f31v;
    f32 half;
    f32 k;
    f32 c;
    register f32 t0 __asm__("fr0");
    s32 r;

    a1 = arg0->p[1];
    a0 = arg0->p[0];
    b1 = arg1->p[1];
    b0 = arg1->p[0];

    /* len2 = a.a and dot = a.b, 3 live components each (w lane zeroed) */
    t = __builtin_ps_mul(a1, a1);
    t = __builtin_ps_merge00(t, lbl_8028FCC8);
    t = __builtin_ps_madd(a0, a0, t);
    u = __builtin_ps_mul(a1, b1);
    len = __builtin_ps_sum0(t, t, t);
    u = __builtin_ps_merge00(u, lbl_8028FCC8);
    len = __builtin_ps_rsqrte(len);
    len = __builtin_ps_res(len);
    dot = __builtin_ps_madd(a0, b0, u);
    dot = __builtin_ps_sum0(dot, dot, dot);
    dot = __builtin_ps_madd(a0, b0, u);
    dot = __builtin_ps_sum0(dot, dot, dot);

    half = lbl_8028FD50;
    fr.rsq_a.p = len;
    t0 = fr.rsq_a.f[0];
    k = t0;
    fr.dot.p = dot;
    t0 = fr.dot.f[0];
    f31v = t0;
    if (k < half) {
        return 0;
    }

    t = __builtin_ps_mul(b1, b1);
    t = __builtin_ps_merge00(t, lbl_8028FCC8);
    t = __builtin_ps_madd(b0, b0, t);
    t = __builtin_ps_sum0(t, t, t);
    t = __builtin_ps_rsqrte(t);
    t = __builtin_ps_res(t);
    fr.rsq_b.p = t;
    f31v = f31v / k;
    t0 = fr.rsq_b.f[0];
    k = t0;
    if (k < half) {
        return 0;
    }
    f31v = f31v / k;

    c = cosf(farg0 * lbl_8028FD54);
    if (f31v >= lbl_8028FD58) {
        return (f31v < c);
    }
    if (c >= lbl_8028FD58) {
        return 1;
    }
    r = (f31v < c);
    return r;
}
