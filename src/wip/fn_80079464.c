// PARKED 2026-10-30: FAIL (did not compile, duplicate file-scope
// statics + 4-arg memcpy) -> DIFF, object 1456 B vs want 1516 B (-60 B / -15
// words).  Frame `stwu -0x158` and LR slot are EXACT.  Masked sweep reads
// 1.65% but that number is meaningless: the object is 15 words short so the
// index-aligned compare is mis-parsed (AGENTS 6cs-1 / 6es).
//
// WHAT IT IS: bilinear RGBA texel resample.  Fully rebuilt by hand from want
// (tools/ps_disasm.py) + three PROMOTED callee sources + the family template
// in src/wip/fn_80078C5C.c (same fn_80078948-caller idiom, incl. the "ONE
// escaping frame struct" trick that keeps retail's dead weight stores alive).
//
// SEMANTIC FIXES THAT MATTERED (all measured, none are codegen levers):
//  * ONE escaping `struct frame` at r1+0x08 for the WHOLE frame.  That is
//    the only reason 20+ values stay in memory and the four never-read
//    `stw` of the bilinear weights at 0x28..0x34 survive; as separate locals
//    they are all promoted to callee-saved regs (frame 0xb0, object 336 B
//    short).  +476 B on its own.
//  * `fn_80078948` is 6-arg, not 7: (s32 *out, s32 base, s16 x, s16 y,
//    s32 w, s32 h) -- src/fn_80078948.c.  m2c's 7th phantom arg shifted the
//    whole arg window.
//  * The vtable call at +0x158/+0x15C is ONE arg with an `lha` offset
//    field: `((s32(*)(void*))*(s32*)((char*)pool+0x15C))(arg0 + *(s16*)((char*)pool+0x158))`.
//  * `fn_80006350(void*,f32)` returns arg0; `lbl_802FFE98` is a POINTER global
//    (L1 form, `extern Pool_t *lbl_802FFE98` + bare use).
//  * The dimension bytes are `lbz` off `arg0->unk0xC` (+6 = width, +7 = height)
//    and each is `(u16)(1 << b)`.
//  * The bilinear complements are `0x400 - f` (retail `subfic`), NOT `f - 0x400`
//    (which GCC emits as `addi -0x400` and is sign-wrong for w1/w2).
//  * The texel scratch is `u8 tex[16]` and the frac split is
//    `union { s32 i; u16 h[2]; } q[2]` read through `volatile u16 *` so the
//    two s16 args come out as retail's `lhz` + `extsh` (not one `lha`).
//  * Guarded-do-while on the row loop: guard tests the row VARIABLE (`fr.row
//    < fr.dimH`), not the literal (retail `cmpw r4,r9` at the head).
//  * The two empty spin loops are real: `do {} while (--spin != -1)` inside
//    `spin_next = spin_outer - 1; ... spin_outer = spin_next;` -- reproduces
//    retail's exact 10-word double-countdown.
//  * Source store order 0,1,2,3 emits 0,1,3,2 = want's.
//  * `memcpy` left IMPLICIT on purpose (retail keeps `crclr cr1eq` before it);
//    `Mem_Alloc`/`Mem_Free2` prototyped.
//  * pad2[N] tunes the frame: N=20 gives the exact `stwu -0x158`.
//
// RESIDUAL (15 words) -- do NOT re-grind these:
//  * 3 words: retail keeps `cmpwi cr4,r3,0` at the alloc and consumes it at
//    the very end (`mfcr r12/stw 0xe4` + `mtcrf 8`), i.e. doc-28 long-range CR
//    liveness across ~10 calls.  GCC 2.95 CSEs the compare down to its single
//    use (at the end), so there is no C spelling that keeps it at the alloc.
//  * 4 words: retail saves 5 callee-saved FPRs (f27..f31); got saves 3.  retail
//    keeps BOTH farg1 and -farg1 live across the whole prologue although the
//    negations die in the setup block -- a local-alloc tie-break.
//  * ~8 words: retail's first clamp is `or. r0,r19,r19` (a fresh COPY of the
//    position) while got tests/compares the position register in place, and
//    retail's two clamps stay in x-then-y order where got rotates y first.
//  * 5 dead `mr rX,r5` at 0x80079638..0x68 (r5 copied to r6,r7,r8,r10,r11)
//    and 2 more `addi` frame-base pointers that m2c never recovered; no
//    plausible C spelling found.
//  * object carries the 8 B `0x4330000080000000` int->f64 pool (doc 14);
//    `tools/fix_fp_pool.py` retargets it at promote time -- retail materialises
//    the 2^52 half inline with `lis 0x4330` + `stw`, which this source does
//    too, so the pool is dead weight rather than a routing problem.
//
// INLINE ASM: 0 instructions.  FLAGS: none needed (default -O2 -G0 -mcpu=750).
// family=m2c range=0x80079464-0x80079A50 size=1516B
// fn_80079464  Bilinear texel resample (0x80079464, size 0x5EC = 1516B)
// range=0x80079464-0x80079A50 size=1516B
// Hand-rebuilt from want (tools/ps_disasm.py) + the PROMOTED callee sources
// (src/fn_80006350.c, src/fn_80078948.c, src/fn_8000F2F8.c) and the family
// template in src/wip/fn_80078C5C.c (same fn_80078948-caller idiom).
// No inline asm.
#include "types.h"

extern f32 lbl_80295844;
extern f64 lbl_80295848;
extern f32 lbl_80295850;
extern f32 lbl_80295854;
extern f32 lbl_80295858;

typedef struct { s32 unk0x110; s32 unk0x114; s32 unk0x118; } Pool_t;
extern Pool_t *lbl_802FFE98;

extern void *fn_80006350(void *arg0, f32 angle);
extern void fn_80078948(s32 *out, s32 base, s16 a, s16 b, s32 w, s32 h);
extern void fn_8000F2F8(Pool_t *arg0, s32 arg1);
extern void fn_8000F320(Pool_t *arg0);
extern void *Mem_Alloc(u32 size);
extern void Mem_Free2(void *p);

struct frame {
    f32 v[4];                                  /* r1+0x08  fn_80006350 out  */
    u8 tex[16];                                /* r1+0x18  fn_80078948 out  */
    s32 wt[4];                                 /* r1+0x28  weights (dead)   */
    f32 t38, t3C, t40, t44, t48, t4C;
    f32 t50, t54, t58, t5C, t60, t64;          /* r1+0x38  float temps      */
    s32 base;                                  /* r1+0x68                   */
    s32 dimW, dimH;                            /* r1+0x6c / 0x70            */
    void *buf;                                 /* r1+0x74                   */
    union { s32 i; u16 h[2]; } q[2];           /* r1+0x78 / 0x7c            */
    s32 x, y;                                  /* r1+0x80 / 0x84            */
    s32 maxX, maxY;                            /* r1+0x88 / 0x8c            */
    s32 dX0, dX1, dY0, dY1;                    /* r1+0x90 .. 0x9c           */
    s32 n, n2, row;                            /* r1+0xa0 .. 0xa8           */
    s32 pad;                                   /* r1+0xac                   */
    s32 hold;                                  /* r1+0xb0                   */
    s32 pad2[20];                               /* frame filler              */
};

s32 fn_80079464(void *arg0, f32 farg0, f32 farg1, f32 farg2) {
    struct frame fr;
    volatile u16 *q0h = (volatile u16 *)&fr.q[0];
    volatile u16 *q1h = (volatile u16 *)&fr.q[1];
    Pool_t *pool;
    s32 *dim;
    s32 spin_outer, spin_next, spin_inner;
    s32 col, cx, cy, fx, fy;
    s32 xpos, ypos, a, b;
    s32 w0, w1, w2, w3;
    u8 *out;
    f32 *pb38 = &fr.t38;
    f32 *pb48 = &fr.t48;
    f32 *pb50 = &fr.t50;
    f32 *pb58 = &fr.t58;
    f32 f5, f7, f8, f29, f30, lim;

    pool = lbl_802FFE98;
    fr.base = (s32)((s32 (*)(void *))*(s32 *)((char *)pool + (s32)0x15C))(arg0 + *(s16 *)((char *)pool + (s32)0x158));
    lim = lbl_80295844;
    dim = *(s32 *)((char *)arg0 + (s32)0xC);
    fr.dimH = (s32)(u16)(1 << *(u8 *)((char *)dim + (s32)0x7));
    fr.dimW = (s32)(u16)(1 << *(u8 *)((char *)dim + (s32)0x6));
    if (farg1 < lim) {
        farg1 = ((f32)((f64)fr.dimW - lbl_80295848) - lbl_80295850) * lbl_80295854;
    }
    if (farg2 < lim) {
        farg2 = ((f32)((f64)fr.dimH - lbl_80295848) - lbl_80295850) * lbl_80295854;
    }
    fn_80006350(fr.v, farg0);
    fr.n = fr.dimW * fr.dimH;
    fn_8000F2F8(pool, pool->unk0x118);
    fr.buf = Mem_Alloc(fr.n << 2);
    fn_8000F320(pool);

    f29 = -farg1;
    f30 = -farg2;
    spin_outer = 1;
    do {
        spin_next = spin_outer - 1;
        spin_inner = 1;
        do { } while (--spin_inner != -1);
        spin_outer = spin_next;
    } while (spin_outer != -1);

    f5 = lbl_80295850;
    f7 = lbl_80295844;
    fr.maxX = (fr.dimW - 1) << 10;
    fr.t48 = f5;
    fr.t4C = f7;
    fr.maxY = (fr.dimH - 1) << 10;
    fr.t50 = fr.t48 * fr.v[0] + fr.t4C * fr.v[2];
    fr.t54 = fr.t48 * fr.v[1] + fr.t4C * fr.v[3];
    fr.t40 = *pb50;
    fr.t44 = *(pb50 + 1);
    *pb50 = f7;
    *(pb50 + 1) = f5;
    fr.t58 = fr.t50 * fr.v[0] + fr.t54 * fr.v[2];
    fr.t5C = fr.t50 * fr.v[1] + fr.t54 * fr.v[3];
    *pb50 = f29;
    *(pb50 + 1) = f30;
    fr.t60 = f29 * fr.v[0] + f30 * fr.v[2];
    fr.t64 = f29 * fr.v[1] + f30 * fr.v[3];
    *(pb58 + 1) = fr.t64;
    *pb58 = fr.t60;
    f8 = lbl_80295858;
    fr.row = 0;
    fr.dX0 = (s32)(fr.t40 * f8);
    *pb38 = fr.t60;
    *(pb38 + 1) = fr.t64;
    fr.dX1 = (s32)(fr.t44 * f8);
    fr.dY0 = (s32)(fr.t48 * f8);
    xpos = (s32)((fr.t38 + farg1) * f8);
    fr.dY1 = (s32)(fr.t4C * f8);
    ypos = (s32)((fr.t3C + farg2) * f8);
    out = (u8 *)fr.buf;
    if (fr.row < fr.dimH) {
        do {
            fr.n2 = xpos + fr.dY0;
            if (fr.dimW != 0) {
                col = fr.dimW;
                do {
                    cx = xpos;
                    if (cx >= 0) {
                        if (cx > fr.maxX) {
                            cx = fr.maxX;
                        }
                    } else {
                        cx = 0;
                    }
                    fr.x = cx;
                    if (ypos >= 0) {
                        if (ypos > fr.maxY) {
                            ypos = fr.maxY;
                        }
                    } else {
                        ypos = 0;
                    }
                    fr.y = ypos;
                    fr.q[0].i = fr.x >> 10;
                    fx = fr.x & 0x3FF;
                    fr.q[1].i = fr.y >> 10;
                    fy = fr.y & 0x3FF;
                    fr.hold = fr.maxX;
                    fn_80078948((s32 *)fr.tex, fr.base,
                                (s16)q0h[1], (s16)q1h[1], fr.dimW, fr.dimH);
                    col--;
                    a = 0x400 - fy;
                    b = 0x400 - fx;
                    xpos += fr.dX0;
                    ypos += fr.dX1;
                    w1 = (a * fx) >> 10;
                    w0 = (b * a) >> 10;
                    w2 = (b * fy) >> 10;
                    w3 = (fx * fy) >> 10;
                    fr.wt[0] = w0;
                    fr.wt[1] = w1;
                    fr.wt[2] = w2;
                    fr.wt[3] = w3;
                    out[0] = (u8)((w0 * fr.tex[0] + w1 * fr.tex[4]
                                  + w2 * fr.tex[8] + w3 * fr.tex[0xC]
                                  + 0x200) >> 10);
                    out[1] = (u8)((w0 * fr.tex[1] + w1 * fr.tex[5]
                                  + w2 * fr.tex[9] + w3 * fr.tex[0xD]
                                  + 0x200) >> 10);
                    out[2] = (u8)((w0 * fr.tex[2] + w1 * fr.tex[6]
                                  + w2 * fr.tex[0xA] + w3 * fr.tex[0xE]
                                  + 0x200) >> 10);
                    out[3] = (u8)((w0 * fr.tex[3] + w1 * fr.tex[7]
                                  + w2 * fr.tex[0xB] + w3 * fr.tex[0xF]
                                  + 0x200) >> 10);
                    out += 4;
                } while (col != 0);
            }
            fr.row = fr.row + 1;
            xpos = fr.n2;
            ypos += fr.dY1;
        } while (fr.row < fr.dimH);
    }
    memcpy((void *)fr.base, fr.buf, fr.n << 2);
    if (fr.buf != 0) {
        Mem_Free2(fr.buf);
    }
    return 1;
}
