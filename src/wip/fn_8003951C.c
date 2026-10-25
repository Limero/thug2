// WIP DRAFT (non-matching, PARKED) - hand-rebuilt from the DOL;
// all 323 words read with tools/ps_diff.py's dec() because
// tools/want_dis.py stalls at the first paired-single word.
// family=m2c range=0x8003951C-0x80039A28 size=1292B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py - never compiled,
// not counted in objdiff progress.  activate via tools/wip.py.
//
// WHAT THIS FUNCTION IS (recovered from the DOL, verified against every word):
//
//   0x80039550  if (fn_80036328(o,key) == 0) return 0;   (2 args: the want
//               reloads r3/r4 from r31/r30 before the second call, so BOTH
//               take (arg0,arg1) - m2c gave fn_80036328 no arguments at all)
//   0x80039574  idx = fn_80036810(o,key);   (index, -1 on miss)
//   0x80039594  A <- world[idx]              A   = r1+0x08 (64 B, 8 pairs)
//   0x800395dc  lmat = fn_8003A428(o->unk0x8)   (= o->unk0x58c, 8-byte fn)
//   0x800395f0  B <- lmat[idx]                B   = r1+0x48 (64 B)
//   0x80039658  last[0..1] = B[6..7]          r1+0x88, DEAD in the want
//   0x80039688  t[0] = dot3(&B[12], &B[0])    t   = r1+0xE0, 8-byte stride
//               t[1] = dot3(&B[12], &B[4])
//               t[2] = dot3(&B[12], &B[8])
//   0x800396c8  B[12] = -t[0]; B[13] = -t[1]; B[14] = -t[2];  (B[15] kept)
//   0x800396dc  swap B[1]<->B[4], B[2]<->B[8], B[6]<->B[9]
//   0x8003970c  C = B * A                     C   = r1+0x98 (64 B),
//               C[i+4j] = sum_k B[i+4k] * A[4j+k]   (column-major, unrolled)
//   0x800399ac  B = C ; out[0..3] = B[12..15]  (the last ROW of the product,
//               i.e. the translation in this column-major layout)
//   0x800399fc  return 1
//
// The B fixup (last row := -(row3 . row0, row3 . row1, row3 . row2) plus the
// 2x2 index swap) is the same code the bigger sibling fn_80050868 runs.
//
// BREAKTHROUGH - `__builtin_ps_sum0` IS EMITTABLE, it just takes
// THREE arguments on ngccc 3.9.3 (-mps-float):
//
//     t.p = __builtin_ps_sum0(q, q, q);     ->  ps_sum0 f13,f13,f13,f13
//
// One- and two-argument forms produce an EMPTY .text with NO diagnostic at
// all (silent frontend failure - tools/errlines.py reports "COMPILES" and
// gen_leaves.compile_fn then returns None, which is what made the earlier
// draft call it un-emittable); sum2/sum3 ICE at optabs.c:4116.  With the
// 3-arg form the whole Gram-Schmidt block lowers correctly:
//     ps_mul -> ps_merge00(., {0,0}) -> ps_madd -> ps_sum0 .->. .->.
// matching the want's 0x8003966c-0x800396b4 word for word in SHAPE (the
// operands/f colours still differ).  `ps_sum0 %0,%0,%0` is the TFmode-pair
// broadcast (both lanes = lane0+lane1), which is why `q,q,q` is the spelling
// and not `q,zero`.
//
// MEASURED (tools/venv/bin/python tools/test_wip_drafts.py --addr 0x8003951C):
//   verdict DIFF.  Body is now SIZE-EXACT: 1292 B / 323 words vs want 1292 B /
//   323 words (earlier m2c husk: 136 B).  Masked word score is still ~0.6% and
//   is dominated by the prologue, not by the body (see blocker 1).
//
// REMAINING BLOCKERS - each one alone is fatal for a byte-exact match:
//  1. TWO self-targeting `bdnz .` windows (0x80039590 and 0x800395ec, raw word
//     0x42000000), i.e. the docs/parkings/solved/30 class: an empty countdown
//     loop whose delay slot already carries the first real instruction.
//     RE-MEASURED, doc 30 holds: the empty loop itself DOES
//     survive -O2 in every plain-C spelling (`for (i=4;i!=0;i--) ;`,
//     `do {} while (--i)`, `while (i!=0) i--`, `volatile` counter all emit
//     `li rN,4 / mtctr / bdnz <+0x20..0x24>`), but cc1 ALWAYS re-points the
//     branch PAST the following block; it never emits the displacement-0
//     self-target.  The only known route is doc 30's inline-asm window, which
//     this reconstruction is not permitted to use.
//  2. Prologue/FPR frame.  The want saves SIX callee-saved FPRs (f26-f31,
//     stfd 0x110-0x138) and four GPRs (r26-r29, stmw 0xf8) on a 0x140 frame;
//     this body reaches 1292 B only because GCC happens to pick a 0x130 frame
//     with ZERO callee-saved FPRs, because the `fa/fb/fc` pointer views let it
//     reload B/A from the frame instead of keeping 16 matrix elements live.
//     The want keeps a whole A column in f26-f31 across the 16 products
//     (see the lfs f26..f31 hoists at 0x80039710-0x80039780); reproducing that
//     exact FPR colouring + the resulting 0x140 frame is a separate allocator
//     problem (recipes docs 73/75/85).
//  3. The 32 psq_l/psq_st pair copies (two 64 B matrices + the tail C->B copy)
//     ride at exactly the retail offsets in this body, but their interleaving
//     with the unrelated lfs/stfs (e.g. `lfs f4,0x4c` / `lfs f5,0x58` between
//     pair 2 and pair 3) is not landed.
//
// Verdict: PARKED.  Do NOT re-run the flag / permutation / register-pin
// levers - none of them addresses blockers 1-3.
// Side-by-side residual: tools/venv/bin/python tools/want_got.py 0x8003951C
#include "types.h"
#include "structs.h"

/* --- callees, signatures read off the callee prologues --------------------- */
void *fn_80036328(void *o, s32 key);   /* 0x48B: record ptr, NULL on miss   */
s32 fn_80036810(void *o, s32 key);     /* 0x44B: index, -1 on miss         */
__ps_t *fn_8003A428(void *o);          /* 8B: o->unk0x58c                  */

/* 8-byte paired single, and a 64-byte matrix seen both as 8 pairs (so the
   compiler keeps the psq_l/psq_st block) and as 16 floats (so the scalar
   matmul can read it). */
typedef union {
    __ps_t p[8];
    f32 f[16];
} MatP;

typedef union {
    __ps_t p[3];
    f32 f[6];
} Ps3;

/* the {0.0f, 0.0f} pair the want loads at 0x80291EA8 and merges into every
   third term */
extern f32 lbl_80291EA8[];

/* arg0: +0x04 is the bone WORLD matrix array (64 B stride, indexed by the
   lookup), +0x08 is handed straight to fn_8003A428. */
typedef struct {
    s32 unk0x0;
    __ps_t *unk0x4;      /* the pair view of the same 64 B matrix array */
    void *unk0x8;
} Unk_8003951C_Obj;

s32 fn_8003951C(Unk_8003951C_Obj *arg0, s32 arg1, f32 *arg2) {
    MatP A;                        /* r1+0x08 */
    MatP B;                        /* r1+0x48 */
    MatP last;                     /* r1+0x88 - dead in the want */
    MatP C;                        /* r1+0x98 */
    Ps3 t;                         /* r1+0xE0 */
    f32 *fa;
    f32 *fb;
    f32 *fc;
    __ps_t *lmat;
    __ps_t *lbase;
    __ps_t zz;
    __ps_t q;
    f32 tmp1;
    f32 tmp2;
    f32 tmp6;
    void *rec;
    s32 idx;

    rec = fn_80036328(arg0, arg1);
    idx = fn_80036810(arg0, arg1);
    if (rec == 0) {
        return 0;
    }

    /* 0x80039574: the index is scaled to a 64-byte stride (`slwi r30,r3,6`),
       and the three `addi` that follow are the &A / &B / &spD8 births.  The
       want's `li r0,4 / lwz r9,4(r31) / mtctr / slwi` preamble is the head of
       the first self-targeting bdnz window (blocker 1 in the header), which
       is why the scalar `idx*8` here compiles as plain address arithmetic. */
    lmat = arg0->unk0x4 + idx * 8;

    A.p[0] = lmat[0];
    A.p[1] = lmat[1];
    A.p[2] = lmat[2];
    A.p[3] = lmat[3];
    A.p[4] = lmat[4];
    A.p[5] = lmat[5];
    A.p[6] = lmat[6];
    A.p[7] = lmat[7];
    lbase = fn_8003A428(arg0->unk0x8);

    lmat = lbase + idx * 8;
    B.p[0] = lmat[0];
    B.p[1] = lmat[1];
    B.p[2] = lmat[2];
    B.p[3] = lmat[3];
    B.p[4] = lmat[4];
    B.p[5] = lmat[5];
    B.p[6] = lmat[6];
    B.p[7] = lmat[7];

    /* 0x80039658: saved, never read back. */
    last.p[0] = B.p[6];
    last.p[1] = B.p[7];

    /* 0x80039688: three 3-component dot products of B's last row onto its
       first three rows.  Each one is written as the exact PS sequence the want
       emits - ps_madd(row3.xy, rowi.xy, merge00(row3.zw*rowi.zw, {0,0}))
       then the TFmode-pair broadcast ps_sum0 - because the plain `f32` spelling
       lowers to scalar fmuls/fadds (probed) and cannot produce these words.
       `zz` is the {0.0f,0.0f} pair the want loads from lbl_80291EA8
       (0x800395f4: lis r9,-0x7fd7 / addi r9,r9,0x1ea8). */
    fa = A.f;
    fb = B.f;
    fc = C.f;
    zz = *(__ps_t *)lbl_80291EA8;
    q = __builtin_ps_madd(B.p[6], B.p[0],
            __builtin_ps_merge00(__builtin_ps_mul(B.p[7], B.p[1]), zz));
    t.p[0] = __builtin_ps_sum0(q, q, q);
    q = __builtin_ps_madd(B.p[6], B.p[2],
            __builtin_ps_merge00(__builtin_ps_mul(B.p[7], B.p[3]), zz));
    t.p[1] = __builtin_ps_sum0(q, q, q);
    q = __builtin_ps_madd(B.p[6], B.p[4],
            __builtin_ps_merge00(__builtin_ps_mul(B.p[7], B.p[5]), zz));
    t.p[2] = __builtin_ps_sum0(q, q, q);

    /* 0x800396c8: the negated projections, w kept from `last`. */
    B.f[12] = -t.f[0];
    B.f[13] = -t.f[2];
    B.f[14] = -t.f[4];

    /* 0x800396dc: three 2-element swaps. */
    tmp1 = B.f[1];
    B.f[1] = B.f[4];
    B.f[4] = tmp1;
    tmp2 = B.f[2];
    B.f[2] = B.f[8];
    B.f[8] = tmp2;
    tmp6 = B.f[9];
    B.f[6] = B.f[9];
    B.f[9] = tmp6;

    /* 0x8003970c: C = B * A, column-major, fully unrolled (the want hoists
       one whole A column into f26..f31 + f1..f5 and reuses it 4 times). */
    fc[0] = (((fb[0] * fa[0]) + (fb[1] * fa[4])) + (fb[2] * fa[8])) + (fb[3] * fa[12]);
    fc[1] = (((fb[0] * fa[1]) + (fb[1] * fa[5])) + (fb[2] * fa[9])) + (fb[3] * fa[13]);
    fc[2] = (((fb[0] * fa[2]) + (fb[1] * fa[6])) + (fb[2] * fa[10])) + (fb[3] * fa[14]);
    fc[3] = (((fb[0] * fa[3]) + (fb[1] * fa[7])) + (fb[2] * fa[11])) + (fb[3] * fa[15]);
    fc[4] = (((fb[4] * fa[0]) + (fb[5] * fa[4])) + (fb[6] * fa[8])) + (fb[7] * fa[12]);
    fc[5] = (((fb[4] * fa[1]) + (fb[5] * fa[5])) + (fb[6] * fa[9])) + (fb[7] * fa[13]);
    fc[6] = (((fb[4] * fa[2]) + (fb[5] * fa[6])) + (fb[6] * fa[10])) + (fb[7] * fa[14]);
    fc[7] = (((fb[4] * fa[3]) + (fb[5] * fa[7])) + (fb[6] * fa[11])) + (fb[7] * fa[15]);
    fc[8] = (((fb[8] * fa[0]) + (fb[9] * fa[4])) + (fb[10] * fa[8])) + (fb[11] * fa[12]);
    fc[9] = (((fb[8] * fa[1]) + (fb[9] * fa[5])) + (fb[10] * fa[9])) + (fb[11] * fa[13]);
    fc[10] = (((fb[8] * fa[2]) + (fb[9] * fa[6])) + (fb[10] * fa[10])) + (fb[11] * fa[14]);
    fc[11] = (((fb[8] * fa[3]) + (fb[9] * fa[7])) + (fb[10] * fa[11])) + (fb[11] * fa[15]);
    fc[12] = (((fb[12] * fa[0]) + (fb[13] * fa[4])) + (fb[14] * fa[8])) + (fb[15] * fa[12]);
    fc[13] = (((fb[12] * fa[1]) + (fb[13] * fa[5])) + (fb[14] * fa[9])) + (fb[15] * fa[13]);
    fc[14] = (((fb[12] * fa[2]) + (fb[13] * fa[6])) + (fb[14] * fa[10])) + (fb[15] * fa[14]);
    fc[15] = (((fb[12] * fa[3]) + (fb[13] * fa[7])) + (fb[14] * fa[11])) + (fb[15] * fa[15]);

    /* 0x800399ac: B = C, then the translation row out. */
    B.p[0] = C.p[0];
    B.p[1] = C.p[1];
    B.p[2] = C.p[2];
    B.p[3] = C.p[3];
    B.p[4] = C.p[4];
    B.p[5] = C.p[5];
    B.p[6] = C.p[6];
    B.p[7] = C.p[7];
    arg2[0] = B.f[12];
    arg2[1] = B.f[13];
    arg2[2] = B.f[14];
    arg2[3] = B.f[15];
    return 1;
}