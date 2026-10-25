// family=m2c range=0x80005C28-0x80005E20 size=504B
// extra_cflags: -mps-float
//
// fn_80005C28 — signed angle between two matrix rows, measured through one
// vector.  Typed SNAPS/paired-single reconstruction (all arithmetic and all
// call shapes are now recovered from the DOL disassembly).
//
//   1. v' = fn_80005854(v, M[idx1])            (in-place 2-pair transform)
//   2. len2 = dot(v',v');  if (len2 < 1e-4) return 0.0f
//   3. v'  *= rsqrte(len2)                      (guarded by len2 > 0.0f)
//   4. a    = acosf(clamp(dot(M[idx2], v'), -1, 1))
//   5. c    = cross(M[idx2], v')  (lane-rotated; retail computes the three
//          live components through merge10/merge00 shuffles)
//   6. the dominant component of c decides the sign: if sign(c[dom]) differs
//      from sign(M[idx1][dom]) return -a, else return +a.
//
// Constants (read out of .rodata2): lbl_8028FCC8 = (0.0f, 0.0f) shuffle mask,
// lbl_8028FD30 = 1e-4f, lbl_8028FD34 = 0.0f, lbl_8028FD38 = 1.0f,
// lbl_8028FD3C = -1.0f.  acosf is acosf; fn_80005B00 returns the
// largest-|.| component of a 3-float vector and writes its index.
//
// PARKED.  59/125 masked words (was 40/125).  Everything structural is now
// byte-exact: frame (0x90), stmw r27 / stfd f29-f31, the whole prologue, the
// row-pointer web (r29/r30/r27/r28/r31), both dot-product chains, the
// clamp + acosf call sequence, the complete sign-test tail (mfcr/rlwinm/xori/
// cmpw/bne/fmr) and the epilogue.  Three residual blocks, all register/PS
// lowering artifacts rather than logic:
//
//   0x78-0x9c, 0xa0-0xc8 (19 words) — the length squared.  Retail keeps it in
//     f0 and *rematerializes* the paired-single -> scalar conversion as
//     `ps_mr f13,f0` at each of the two compares.  Every C spelling tried
//     (inline (f32) cast, named f32 temp, PSUnion lane pun, separate PS copy,
//     register-var pin on the PS value, dropping the FPR pins) makes GCC 2.95
//     give the variable an 8-byte STACK home instead and emit
//     `psq_st f0,0x48(r1)` + `psq_l f13,0x48(r1)`, which also flips the
//     rsqrte/muls0 FPR roles for the rest of the normalize block.  No
//     scheduling flag (-fno-sched-*, -fno-gcse, -fno-rerun-cse-after-loop,
//     -fno-expensive-optimizations, -fno-schedule-insns2) changes it.
//   0x10c-0x134 (10 words) — the acosf clamp.  Identical instruction sequence,
//     but the clamped value is homed in f0/f13 instead of f1 with neg_one in
//     f0.  Pinning the temp to fr1 fixes the size (504B) but not the load's
//     destination register; nested ternaries / two-argument comma forms each
//     cost 2-4 words somewhere else.
//   0x17c-0x1f4 (30 words) — cross-product webs.  a0/mb are swapped
//     (f10/f11 vs f11/f10), am00 and merge10(t3,t3) land one slot late, and
//     retail's `ps_mr f0,f13` between the two `fr.cross` pair stores is not
//     reproducible: the volatile reload and the volatile store coalesce onto
//     one register.  A ps_mr there is only obtainable with inline asm
//     (the previous draft's `__asm__("ps_mr ...")` produced it and scored
//     62/126 with the correct 504B size); per the no-inline-asm rule for this
//     pass it was removed, so the block is 1 word short and the tail is
//     shifted with it.
//
// Retry hints: the 0x78 spill is the single highest-value item (19 words).
// The only untried lever is giving the length a stack slot *declared* in
// PSFrame and reading it back as a union lane, which would make the store
// intentional rather than a reload artifact.
#include "types.h"
#include "dolphin/SN_PS.h"

extern __ps_t lbl_8028FCC8;
extern f32 lbl_8028FD30;
extern f32 lbl_8028FD34;
extern f32 lbl_8028FD38;
extern f32 lbl_8028FD3C;

typedef struct { __ps_t p[2]; } PSVec4;
typedef struct { PSVec4 row[4]; } PSMatrix4;
typedef union { __ps_t ps; f32 f[2]; } PSUnion;

/* Frame template: the exact retail slot map (offsets from sp8) is
   vec 0x00/0x10, cross 0x10/0x18, dom_idx 0x20, rsq 0x28, dot 0x30,
   work 0x38 — i.e. 0x40 bytes total, which lands the stmw at 0x64. */
typedef struct {
    PSVec4 vec;
    volatile PSVec4 cross;
    s32 dom_idx;
    f32 pad;
    PSUnion rsq;
    PSUnion dot;
    PSUnion work;
} PSFrame;

void fn_80005854(PSVec4 *v, PSVec4 *m);
f32 fn_80005B00(f32 *v, s32 *idx_out);
f32 acosf(f32 x);

f32 fn_80005C28(PSMatrix4 *obj, PSVec4 *vec, s32 idx2, s32 idx1) {
    PSFrame fr;
    PSVec4 *row1;
    PSVec4 *row2;
    __ps_t *buf;
    register s32 base_addr __asm__("r29");
    register s32 idx2_addr __asm__("r30");
    __ps_t dot;
    __ps_t dot2;
    __ps_t lenp;
    f32 d;
    f32 neg_one;
    f32 cross_value;
    f32 row_value;
    s32 sign_cross;
    s32 sign_row;
    __ps_t a0;
    __ps_t a1;
    __ps_t b0;
    __ps_t b1;
    __ps_t mb;
    __ps_t mb_rev;
    __ps_t am;
    __ps_t am00;
    __ps_t p0;
    __ps_t p1;
    __ps_t p2;
    __ps_t d0;
    __ps_t d1;
    __ps_t work_copy;
    __ps_t work_out;
    register f32 zero __asm__("fr29");
    register f32 one __asm__("fr30");
    register f32 result __asm__("fr31");

    /* v' = M[idx1] * v  (fn_80005854 rewrites its first argument in place) */
    base_addr = (s32)obj;
    row1 = (PSVec4 *)(base_addr + (idx1 << 4));
    idx2_addr = idx2;
    buf = fr.vec.p;
    buf[0] = vec->p[0];
    buf[1] = vec->p[1];
    fn_80005854((PSVec4 *)buf, row1);

    /* len2 = dot(v',v'): square the low pair, zero its .lo lane with the
       (0,0) mask, add the high pair's square, horizontal-reduce. */
    dot = __builtin_ps_mul(buf[1], buf[1]);
    dot = __builtin_ps_merge00(dot, lbl_8028FCC8);
    dot = __builtin_ps_madd(buf[0], buf[0], dot);
    lenp = __builtin_ps_sum0(dot, dot, dot);
    if ((f32)lenp < lbl_8028FD30) {
        return lbl_8028FD34;
    }
    zero = lbl_8028FD34;
    if ((f32)lenp > zero) {
        fr.rsq.ps = __builtin_ps_rsqrte(lenp);
        buf[0] = __builtin_ps_muls0(buf[0], fr.rsq.ps);
        fr.rsq.f[1] = lbl_8028FD38;
        buf[1] = __builtin_ps_mul(buf[1], fr.rsq.ps);
    }

    /* d = dot(M[idx2], v'), clamped to [-1,1], then acosf. */
    one = lbl_8028FD38;
    row2 = (PSVec4 *)(base_addr + (idx2_addr << 4));
    dot2 = __builtin_ps_mul(row2->p[1], buf[1]);
    dot2 = __builtin_ps_merge00(dot2, lbl_8028FCC8);
    dot2 = __builtin_ps_madd(row2->p[0], buf[0], dot2);
    fr.dot.ps = __builtin_ps_sum0(dot2, dot2, dot2);
    d = fr.dot.f[0];
    if (d > one) {
        d = one;
    }
    neg_one = lbl_8028FD3C;
    result = acosf((d < neg_one) ? neg_one : d);

    /* cross = M[idx2] x v', built from the lane-rotated product pairs;
       the .lo lane of the working pair is overwritten with 1.0f, and the
       pair is round-tripped through the stack before it lands in cross.p[1]. */
    b0 = row2->p[0];
    b1 = row2->p[1];
    a1 = buf[1];
    a0 = buf[0];
    mb = __builtin_ps_merge10(b0, b1);
    mb_rev = __builtin_ps_merge00(b1, b0);
    am = __builtin_ps_merge10(a0, a1);
    p0 = __builtin_ps_mul(b0, am);
    p1 = __builtin_ps_mul(mb, a0);
    am00 = __builtin_ps_merge00(a0, a1);
    d0 = __builtin_ps_sub(p0, p1);
    work_copy = __builtin_ps_merge00(d0, d0);
    *(volatile __ps_t *)&fr.work.ps = work_copy;
    *(volatile f32 *)&fr.work.f[1] = one;
    p2 = __builtin_ps_mul(mb_rev, am00);
    p2 = __builtin_ps_sub(p2, __builtin_ps_merge10(p2, p2));
    d1 = __builtin_ps_merge10(d0, p2);
    work_out = *(volatile __ps_t *)&fr.work.ps;
    one = -result;
    fr.cross.p[0] = d1;
    *(volatile __ps_t *)&fr.cross.p[1] = work_out;

    /* Sign: -a when the dominant cross component disagrees in sign with the
       same-indexed component of M[idx1].  Both signs are materialised as
       value-context booleans; the cross one is stored inverted. */
    cross_value = fn_80005B00((f32 *)&fr.cross, &fr.dom_idx);
    sign_cross = (cross_value > zero);
    sign_cross = sign_cross ^ 1;
    cross_value = result;
    row_value = ((f32 *)row1)[fr.dom_idx];
    sign_row = (row_value > zero);
    if (sign_cross == sign_row) {
        cross_value = one;
    }
    return cross_value;
}
