// WIP DRAFT (non-matching) — HAND-REBUILT 2026-09-27 from the retail disasm.
// family=m2c range=0x800B16FC-0x800B24F4 size=3576B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled by the
// build, not counted in objdiff progress.
//
// fn_800B16FC(self, obj): inverts a 4x4 float matrix in place.
//   self->mode (+0x70) selects the path (1 / 2 / 4); the matrix is at self+0x18.
//   * 1     : p = fn_80057E2C(obj); copy 8 floats  p[0..7]   -> self+0x80
//   * 2 / 4 : the same 8-float copy, PLUS
//             q = fn_80057FBC(self->obj); copy 16 floats q[0..15]
//                       -> self+0x20   (4-iteration bdnz loop, 8 pairs)
//             cof[16] = adjugate(M),  M = self+0x18
//             det     = the 4x4 determinant from M[8], M[4], M[0xC] and the
//                       last-row / last-column minors
//             if (det != 1.0f && 1.0f/det != 1.0f) cof[i] *= 1.0f/det  (PS)
//             copy cof[0..15] back over M   (8 PS pair copies)
//   modes 0, 3 and anything else return immediately.
//
// lbl_80298818 == 1.0f (rodata2 float) — it is the pivot guard, not an epsilon.
// The 0xe0/0xf0-prefixed words are Gekko psq_l / psq_st (primary opcode
// 56 / 60); capstone cannot decode them and it mislabels the opcode-4
// A-form words (ps_muls0 = xo5 12, the splat/merge = xo5 0). Both confirmed by
// compiling ngccc probes, so the draft is genuinely paired-single.
//
// VERDICT 2026-09-27: DIFF. masked 11/868 = 1.3%; 21/868 = 2.5% once the
// 1-instruction prologue shift is factored out; opcode-shape 292/857 = 34.1%.
// got 3472 B vs retail 3576 B (894 insns). Full hand-rebuild: nothing is
// dead-stripped any more. The previous m2c body compiled to 896 B because it
// modelled the whole 4x4 matrix as never-read stack scalars and ngccc
// stripped the function (the classic m2c-statics-DCE husk, trap 7).
//
// WHAT IS NOW CORRECT (do not re-derive):
//   * the algebra of all 16 cofactors and of the 4x4 determinant — m2c's
//     expressions were right, only its types and offsets were wrong;
//   * every load displacement, 0x00..0x3C off self+0x18. m2c's unk0xNN are
//     BYTE offsets; indexing an 'f32 *' scaled them all by 4 (0x34 -> 0xd0).
//     The file-local Mat4_t layout is the fix (trap 1).
//   * the 5-compare switch tree. All five mode labels must be present and
//     every arm must end in 'goto epilogue'; that is what makes ngccc 2.95
//     emit cmp 2 / bgt / cmp 0 / cmp 1 / cmp 3 / cmp 4 instead of folding
//     modes 0 and 3 into one default. Probe-verified (form D).
//   * both PS pair-copy blocks and the ps_muls0 scale pass, under -mps-float.
//
// RESIDUAL — precisely why C does not reach it from here:
//   1. Prologue is 1 insn short, which shifts the whole body by 4 bytes, so
//      the fixed-offset masked compare reads ~1% however good the body is.
//        Retail grows the frame by 0xd0 and saves eight float registers,
//        f24 through f31, at frame offsets 0x90 through 0xc8, plus a single
//        integer register r31 at 0x8c and the link value at 0xd4, twelve
//        setups in all with one saved GPR. The build grows the frame by 0xc8
//        and saves only f25 through f31 at the same 0x90-to-0xc8 span, with
//        a two-register integer save from r30 at 0x88 and the link value at
//        0xcc, eleven setups with two saved GPRs.
//      The 8th callee-saved FPR is what buys the +8 frame: retail uses f24
//      for the 1.0f pivot guard and f25..f31 for M[0] plus the six det
//      minors. This build only reaches 7, and additionally homes arg0 in r30
//      (r31 then holds a second web), so the GPR save area becomes an stmw
//      span instead of a lone stw. Chicken-and-egg with item 2: det/scale
//      spill to 0x08/0x0C, pushing 'cof' from the retail 0x08(r1) to
//      0x10(r1) and leaving 8 fewer bytes of locals.
//   2. FPR colouring of the 16 cofactor blocks (~400 straight-line
//      fmuls/fmsubs/fmadds, and cases 2 and 4 are near-identical code).
//      Every arithmetic OPCODE and every operand pairing now matches, e.g.
//        At 0x800B183C for example retail multiplies f7 by f9 into f10
//        while the build multiplies f8 by f0 into f11.
//      but no source shape reproduces GCC 2.95's exact FPR numbering for a
//      block this size (tried: m2c staging, unique names per web, decl
// order, reg pins). Same wall as the big-function
//      allocator-order parks, at a much larger scale.
//   3. The 8-float psq scale array sits at 0x48 in case 2 and 0x68 in case 4
//      in retail (two block-scoped arrays sharing one locals area); here it
//      collapses to a single slot per arm.
// PARKING: not worth another session at this size. The two transferable
// findings are (a) 0xe0/0xf0 == psq_l/psq_st, primary opcode 56/60 — capstone
// simply cannot decode them, and (b) a 5-label switch with all arms ending in
// 'goto <epilogue>' is required to reproduce ngccc's 5-compare tree.
#include "structs.h"

extern f32 lbl_80298818;
extern void *fn_80057E2C(void *);
extern void *fn_80057FBC(void *);

/* The 4x4 matrix, by TRUE byte layout. m2c named these unk0xNN byte offsets;
   going through an f32 pointer would scale every displacement by 4. */
typedef struct {
    f32 c00, c04, c08, c0C, c10, c14, c18, c1C, c20, c24, c28, c2C, c30, c34, c38, c3C;
} Mat4_t;

/* self: 4x4 float matrix at +0x18, mode at +0x70, object at +0x7C,
   8-float destination at +0x80. */
typedef struct {
    char pad0x0[0x18];
    Mat4_t mtx;         /* 0x18..0x54 */
    char pad0x58[0x18];
    s32 mode;           /* 0x70 */
    s32 unk0x74;
    s32 unk0x78;
    void *obj;          /* 0x7C */
    f32 dst[8];         /* 0x80 */
} Self_B16FC;

void fn_800B16FC(Self_B16FC *arg0, void *arg1) {
    f32 cof[16];                 /* 0x08(r1)..0x44(r1) in retail */
    Mat4_t *mt;
    f32 det;
    f32 scale;
    __ps_t *P;
    __ps_t *Q;
    int n;

    arg0->obj = arg1;
    if (arg1 == 0) {
        goto epilogue;
    }
    /* All five mode labels are present: that is what makes ngccc 2.95 build
       the retail 5-compare tree (cmp 2 / bgt / cmp 0 / cmp 1 / cmp 3 / cmp 4)
       instead of folding modes 0 and 3 into one default. Probe-verified. */
    switch (arg0->mode) {
    case 0:
        goto epilogue;
    case 1:
        P = (__ps_t *)arg0->dst;
        Q = (__ps_t *)fn_80057E2C(arg1);
        P[0] = Q[0];
        P[1] = Q[1];
        P[2] = Q[2];
        P[3] = Q[3];
        goto epilogue;
    case 2: {
        f32 temp_f12_4;
        f32 temp_f1;
        f32 temp_f26;
        f32 temp_f27;
        f32 temp_f13;
        f32 temp_f3;
        f32 temp_f0_9;
        f32 temp_f31;
        f32 temp_f30;
        f32 temp_f10_10;
        f32 temp_f29;
        f32 temp_f6_17;
        f32 temp_f13_2;
        f32 temp_f9_17;
        f32 temp_f8_17;
        f32 temp_f11_6;
        f32 temp_f0_10;
        f32 temp_f3_2;
        f32 temp_f7;
        f32 temp_f9;
        f32 temp_f5;
        f32 temp_f6;
        f32 temp_f8;
        f32 temp_f11;
        f32 temp_f7_2;
        f32 temp_f9_2;
        f32 temp_f5_2;
        f32 temp_f6_2;
        f32 temp_f8_2;
        f32 temp_f11_2;
        f32 temp_f7_3;
        f32 temp_f9_3;
        f32 temp_f5_3;
        f32 temp_f6_3;
        f32 temp_f8_3;
        f32 temp_f11_3;
        f32 temp_f7_4;
        f32 temp_f9_4;
        f32 temp_f5_4;
        f32 temp_f6_4;
        f32 temp_f8_4;
        f32 temp_f11_4;
        f32 temp_f7_5;
        f32 temp_f9_5;
        f32 temp_f5_5;
        f32 temp_f6_5;
        f32 temp_f8_5;
        f32 temp_f12;
        f32 temp_f4;
        f32 temp_f9_6;
        f32 temp_f10;
        f32 temp_f6_6;
        f32 temp_f7_6;
        f32 temp_f8_6;
        f32 temp_f0;
        f32 temp_f9_7;
        f32 temp_f10_2;
        f32 temp_f6_7;
        f32 temp_f7_7;
        f32 temp_f8_7;
        f32 temp_f0_2;
        f32 temp_f9_8;
        f32 temp_f10_3;
        f32 temp_f6_8;
        f32 temp_f7_8;
        f32 temp_f8_8;
        f32 temp_f0_3;
        f32 temp_f7_9;
        f32 temp_f9_9;
        f32 temp_f5_6;
        f32 temp_f6_9;
        f32 temp_f8_9;
        f32 temp_f11_5;
        f32 temp_f9_10;
        f32 temp_f10_4;
        f32 temp_f6_10;
        f32 temp_f7_10;
        f32 temp_f8_10;
        f32 temp_f0_4;
        f32 temp_f9_11;
        f32 temp_f10_5;
        f32 temp_f6_11;
        f32 temp_f7_11;
        f32 temp_f8_11;
        f32 temp_f0_5;
        f32 temp_f8_12;
        f32 temp_f10_6;
        f32 temp_f6_12;
        f32 temp_f7_12;
        f32 temp_f9_12;
        f32 temp_f12_2;
        f32 temp_f7_13;
        f32 temp_f9_13;
        f32 temp_f5_7;
        f32 temp_f6_13;
        f32 temp_f8_13;
        f32 temp_f12_3;
        f32 temp_f25;
        f32 temp_f9_14;
        f32 temp_f10_7;
        f32 temp_f6_14;
        f32 temp_f7_14;
        f32 temp_f8_14;
        f32 temp_f0_6;
        f32 temp_f9_15;
        f32 temp_f10_8;
        f32 temp_f6_15;
        f32 temp_f7_15;
        f32 temp_f8_15;
        f32 temp_f0_7;
        f32 temp_f9_16;
        f32 temp_f10_9;
        f32 temp_f6_16;
        f32 temp_f7_16;
        f32 temp_f8_16;
        f32 temp_f0_8;
        f32 det;
        f32 scale;
    P = (__ps_t *)arg0->dst;
    Q = (__ps_t *)fn_80057E2C(arg1);
    P[0] = Q[0];
    P[1] = Q[1];
    P[2] = Q[2];
    P[3] = Q[3];
    P = (__ps_t *)((char *)arg0 + 0x20);
    Q = (__ps_t *)fn_80057FBC(arg0->obj);
    n = 4;
    do {
        P[0] = Q[0];
        P[1] = Q[1];
        P[2] = Q[2];
        P[3] = Q[3];
        P[4] = Q[4];
        P[5] = Q[5];
        P[6] = Q[6];
        P[7] = Q[7];
    } while (--n != 0);
    mt = &arg0->mtx;
    P = (__ps_t *)cof;
    Q = (__ps_t *)mt;
        temp_f7 = mt->c34;
        temp_f9 = mt->c2C;
        temp_f5 = mt->c38;
        temp_f6 = mt->c3C;
        temp_f8 = mt->c24;
        temp_f11 = mt->c28;
        cof[2] = (mt->c1C * ((temp_f8 * temp_f5) - (temp_f7 * temp_f11))) + ((mt->c14 * ((temp_f11 * temp_f6) - (temp_f5 * temp_f9))) - (mt->c18 * ((temp_f8 * temp_f6) - (temp_f7 * temp_f9))));
        temp_f7_2 = mt->c30;
        temp_f9_2 = mt->c2C;
        temp_f5_2 = mt->c38;
        temp_f6_2 = mt->c3C;
        temp_f8_2 = mt->c20;
        temp_f11_2 = mt->c28;
        cof[6] = -((mt->c1C * ((temp_f8_2 * temp_f5_2) - (temp_f7_2 * temp_f11_2))) + ((mt->c10 * ((temp_f11_2 * temp_f6_2) - (temp_f5_2 * temp_f9_2))) - (mt->c18 * ((temp_f8_2 * temp_f6_2) - (temp_f7_2 * temp_f9_2)))));
        temp_f7_3 = mt->c30;
        temp_f9_3 = mt->c2C;
        temp_f5_3 = mt->c34;
        temp_f6_3 = mt->c3C;
        temp_f8_3 = mt->c20;
        temp_f11_3 = mt->c24;
        cof[10] = (mt->c1C * ((temp_f8_3 * temp_f5_3) - (temp_f7_3 * temp_f11_3))) + ((mt->c10 * ((temp_f11_3 * temp_f6_3) - (temp_f5_3 * temp_f9_3))) - (mt->c14 * ((temp_f8_3 * temp_f6_3) - (temp_f7_3 * temp_f9_3))));
        temp_f7_4 = mt->c30;
        temp_f9_4 = mt->c28;
        temp_f5_4 = mt->c34;
        temp_f6_4 = mt->c38;
        temp_f8_4 = mt->c20;
        temp_f11_4 = mt->c24;
        cof[14] = -((mt->c18 * ((temp_f8_4 * temp_f5_4) - (temp_f7_4 * temp_f11_4))) + ((mt->c10 * ((temp_f11_4 * temp_f6_4) - (temp_f5_4 * temp_f9_4))) - (mt->c14 * ((temp_f8_4 * temp_f6_4) - (temp_f7_4 * temp_f9_4)))));
        temp_f7_5 = mt->c34;
        temp_f9_5 = mt->c2C;
        temp_f5_5 = mt->c38;
        temp_f6_5 = mt->c3C;
        temp_f8_5 = mt->c24;
        temp_f12 = mt->c28;
        temp_f4 = mt->c00;
        cof[3] = -((mt->c0C * ((temp_f8_5 * temp_f5_5) - (temp_f7_5 * temp_f12))) + ((mt->c04 * ((temp_f12 * temp_f6_5) - (temp_f5_5 * temp_f9_5))) - (mt->c08 * ((temp_f8_5 * temp_f6_5) - (temp_f7_5 * temp_f9_5)))));
        temp_f9_6 = mt->c30;
        temp_f10 = mt->c2C;
        temp_f6_6 = mt->c38;
        temp_f7_6 = mt->c3C;
        temp_f8_6 = mt->c20;
        temp_f0 = mt->c28;
        cof[7] = (mt->c0C * ((temp_f8_6 * temp_f6_6) - (temp_f9_6 * temp_f0))) + ((temp_f4 * ((temp_f0 * temp_f7_6) - (temp_f6_6 * temp_f10))) - (mt->c08 * ((temp_f8_6 * temp_f7_6) - (temp_f9_6 * temp_f10))));
        temp_f9_7 = mt->c30;
        temp_f10_2 = mt->c2C;
        temp_f6_7 = mt->c34;
        temp_f7_7 = mt->c3C;
        temp_f8_7 = mt->c20;
        temp_f0_2 = mt->c24;
        cof[11] = -((mt->c0C * ((temp_f8_7 * temp_f6_7) - (temp_f9_7 * temp_f0_2))) + ((temp_f4 * ((temp_f0_2 * temp_f7_7) - (temp_f6_7 * temp_f10_2))) - (mt->c04 * ((temp_f8_7 * temp_f7_7) - (temp_f9_7 * temp_f10_2)))));
        temp_f9_8 = mt->c30;
        temp_f10_3 = mt->c28;
        temp_f6_8 = mt->c34;
        temp_f7_8 = mt->c38;
        temp_f8_8 = mt->c20;
        temp_f0_3 = mt->c24;
        cof[15] = (mt->c08 * ((temp_f8_8 * temp_f6_8) - (temp_f9_8 * temp_f0_3))) + ((temp_f4 * ((temp_f0_3 * temp_f7_8) - (temp_f6_8 * temp_f10_3))) - (mt->c04 * ((temp_f8_8 * temp_f7_8) - (temp_f9_8 * temp_f10_3))));
        temp_f7_9 = mt->c34;
        temp_f9_9 = mt->c1C;
        temp_f5_6 = mt->c38;
        temp_f6_9 = mt->c3C;
        temp_f8_9 = mt->c14;
        temp_f11_5 = mt->c18;
        cof[2] = ((mt->c0C * ((temp_f8_9 * temp_f5_6) - (temp_f7_9 * temp_f11_5))) + ((mt->c04 * ((temp_f11_5 * temp_f6_9) - (temp_f5_6 * temp_f9_9))) - (mt->c08 * ((temp_f8_9 * temp_f6_9) - (temp_f7_9 * temp_f9_9)))));
        temp_f9_10 = mt->c30;
        temp_f10_4 = mt->c1C;
        temp_f6_10 = mt->c38;
        temp_f7_10 = mt->c3C;
        temp_f8_10 = mt->c10;
        temp_f0_4 = mt->c18;
        cof[8] = -((mt->c0C * ((temp_f8_10 * temp_f6_10) - (temp_f9_10 * temp_f0_4))) + ((temp_f4 * ((temp_f0_4 * temp_f7_10) - (temp_f6_10 * temp_f10_4))) - (mt->c08 * ((temp_f8_10 * temp_f7_10) - (temp_f9_10 * temp_f10_4)))));
        temp_f9_11 = mt->c30;
        temp_f10_5 = mt->c1C;
        temp_f6_11 = mt->c34;
        temp_f7_11 = mt->c3C;
        temp_f8_11 = mt->c10;
        temp_f0_5 = mt->c14;
        cof[12] = (mt->c0C * ((temp_f8_11 * temp_f6_11) - (temp_f9_11 * temp_f0_5))) + ((temp_f4 * ((temp_f0_5 * temp_f7_11) - (temp_f6_11 * temp_f10_5))) - (mt->c04 * ((temp_f8_11 * temp_f7_11) - (temp_f9_11 * temp_f10_5))));
        temp_f8_12 = mt->c30;
        temp_f10_6 = mt->c18;
        temp_f6_12 = mt->c34;
        temp_f7_12 = mt->c38;
        temp_f9_12 = mt->c10;
        temp_f12_2 = mt->c14;
        cof[16] = -((mt->c08 * ((temp_f9_12 * temp_f6_12) - (temp_f8_12 * temp_f12_2))) + ((temp_f4 * ((temp_f12_2 * temp_f7_12) - (temp_f6_12 * temp_f10_6))) - (mt->c04 * ((temp_f9_12 * temp_f7_12) - (temp_f8_12 * temp_f10_6)))));
        temp_f7_13 = mt->c24;
        temp_f9_13 = mt->c1C;
        temp_f5_7 = mt->c28;
        temp_f6_13 = mt->c2C;
        temp_f8_13 = mt->c14;
        temp_f12_3 = mt->c18;
        temp_f25 = mt->c00;
        cof[5] = -((mt->c0C * ((temp_f8_13 * temp_f5_7) - (temp_f7_13 * temp_f12_3))) + ((mt->c04 * ((temp_f12_3 * temp_f6_13) - (temp_f5_7 * temp_f9_13))) - (mt->c08 * ((temp_f8_13 * temp_f6_13) - (temp_f7_13 * temp_f9_13)))));
        temp_f9_14 = mt->c20;
        temp_f10_7 = mt->c1C;
        temp_f6_14 = mt->c28;
        temp_f7_14 = mt->c2C;
        temp_f8_14 = mt->c10;
        temp_f0_6 = mt->c18;
        cof[9] = (mt->c0C * ((temp_f8_14 * temp_f6_14) - (temp_f9_14 * temp_f0_6))) + ((temp_f25 * ((temp_f0_6 * temp_f7_14) - (temp_f6_14 * temp_f10_7))) - (mt->c08 * ((temp_f8_14 * temp_f7_14) - (temp_f9_14 * temp_f10_7))));
        temp_f9_15 = mt->c20;
        temp_f10_8 = mt->c1C;
        temp_f6_15 = mt->c24;
        temp_f7_15 = mt->c2C;
        temp_f8_15 = mt->c10;
        temp_f0_7 = mt->c14;
        cof[11] = -((mt->c0C * ((temp_f8_15 * temp_f6_15) - (temp_f9_15 * temp_f0_7))) + ((temp_f25 * ((temp_f0_7 * temp_f7_15) - (temp_f6_15 * temp_f10_8))) - (mt->c04 * ((temp_f8_15 * temp_f7_15) - (temp_f9_15 * temp_f10_8)))));
        temp_f9_16 = mt->c20;
        temp_f10_9 = mt->c18;
        temp_f6_16 = mt->c24;
        temp_f7_16 = mt->c28;
        temp_f8_16 = mt->c10;
        temp_f0_8 = mt->c14;
        cof[15] = ((mt->c08 * ((temp_f8_16 * temp_f6_16) - (temp_f9_16 * temp_f0_8))) + ((temp_f25 * ((temp_f0_8 * temp_f7_16) - (temp_f6_16 * temp_f10_9))) - (mt->c04 * ((temp_f8_16 * temp_f7_16) - (temp_f9_16 * temp_f10_9)))));
        temp_f12_4 = mt->c2C;
        temp_f1 = mt->c30;
        temp_f26 = mt->c34;
        temp_f27 = mt->c38;
        temp_f13 = mt->c3C;
        temp_f3 = mt->c20;
        temp_f0_9 = mt->c24;
        temp_f31 = mt->c18;
        temp_f30 = (temp_f3 * temp_f13) - (temp_f1 * temp_f12_4);
        temp_f10_10 = mt->c28;
        temp_f29 = (temp_f0_9 * temp_f13) - (temp_f26 * temp_f12_4);
        temp_f6_17 = mt->c10;
        temp_f13_2 = (temp_f10_10 * temp_f13) - (temp_f27 * temp_f12_4);
        temp_f9_17 = mt->c14;
        temp_f8_17 = mt->c1C;
        temp_f11_6 = (temp_f3 * temp_f27) - (temp_f1 * temp_f10_10);
        temp_f0_10 = (temp_f0_9 * temp_f27) - (temp_f26 * temp_f10_10);
        temp_f3_2 = (temp_f3 * temp_f26) - (temp_f1 * temp_f0_9);
        det = ((mt->c08 * ((temp_f8_17 * temp_f3_2) + ((temp_f6_17 * temp_f29) - (temp_f9_17 * temp_f30)))) + ((temp_f25 * ((temp_f8_17 * temp_f0_10) + ((temp_f9_17 * temp_f13_2) - (temp_f31 * temp_f29)))) - (mt->c04 * ((temp_f8_17 * temp_f11_6) + ((temp_f6_17 * temp_f13_2) - (temp_f31 * temp_f30)))))) - (mt->c0C * ((temp_f31 * temp_f3_2) + ((temp_f6_17 * temp_f0_10) - (temp_f9_17 * temp_f11_6))));
        if (det != lbl_80298818) {
            scale = lbl_80298818 / det;
            if (scale != lbl_80298818) {
                __ps_t scl[4];
                scl[0] = scale;
                scl[1] = scale;
                scl[2] = scale;
                scl[3] = scale;
                P[0] = __builtin_ps_muls0(P[0], scl[0]);
                P[1] = __builtin_ps_muls0(P[1], scl[0]);
                P[2] = __builtin_ps_muls0(P[2], scl[1]);
                P[3] = __builtin_ps_muls0(P[3], scl[1]);
                P[4] = __builtin_ps_muls0(P[4], scl[2]);
                P[5] = __builtin_ps_muls0(P[5], scl[2]);
                P[6] = __builtin_ps_muls0(P[6], scl[3]);
                P[7] = __builtin_ps_muls0(P[7], scl[3]);
            }
        }
        Q[0] = P[0];
        Q[1] = P[1];
        Q[2] = P[2];
        Q[3] = P[3];
        Q[4] = P[4];
        Q[5] = P[5];
        Q[6] = P[6];
        Q[7] = P[7];
        goto epilogue;
    }
    case 4: {
        f32 temp_f12_8;
        f32 temp_f1_2;
        f32 temp_f26_2;
        f32 temp_f27_2;
        f32 temp_f13_3;
        f32 temp_f3_3;
        f32 temp_f0_19;
        f32 temp_f31_2;
        f32 temp_f30_2;
        f32 temp_f10_20;
        f32 temp_f29_2;
        f32 temp_f6_34;
        f32 temp_f13_4;
        f32 temp_f9_34;
        f32 temp_f8_34;
        f32 temp_f11_12;
        f32 temp_f0_20;
        f32 temp_f3_4;
        f32 temp_f7_17;
        f32 temp_f9_18;
        f32 temp_f5_8;
        f32 temp_f6_18;
        f32 temp_f8_18;
        f32 temp_f11_7;
        f32 temp_f7_18;
        f32 temp_f9_19;
        f32 temp_f5_9;
        f32 temp_f6_19;
        f32 temp_f8_19;
        f32 temp_f11_8;
        f32 temp_f7_19;
        f32 temp_f9_20;
        f32 temp_f5_10;
        f32 temp_f6_20;
        f32 temp_f8_20;
        f32 temp_f11_9;
        f32 temp_f7_20;
        f32 temp_f9_21;
        f32 temp_f5_11;
        f32 temp_f6_21;
        f32 temp_f8_21;
        f32 temp_f11_10;
        f32 temp_f7_21;
        f32 temp_f9_22;
        f32 temp_f5_12;
        f32 temp_f6_22;
        f32 temp_f8_22;
        f32 temp_f12_5;
        f32 temp_f4_2;
        f32 temp_f9_23;
        f32 temp_f10_11;
        f32 temp_f6_23;
        f32 temp_f7_22;
        f32 temp_f8_23;
        f32 temp_f0_11;
        f32 temp_f9_24;
        f32 temp_f10_12;
        f32 temp_f6_24;
        f32 temp_f7_23;
        f32 temp_f8_24;
        f32 temp_f0_12;
        f32 temp_f9_25;
        f32 temp_f10_13;
        f32 temp_f6_25;
        f32 temp_f7_24;
        f32 temp_f8_25;
        f32 temp_f0_13;
        f32 temp_f7_25;
        f32 temp_f9_26;
        f32 temp_f5_13;
        f32 temp_f6_26;
        f32 temp_f8_26;
        f32 temp_f11_11;
        f32 temp_f9_27;
        f32 temp_f10_14;
        f32 temp_f6_27;
        f32 temp_f7_26;
        f32 temp_f8_27;
        f32 temp_f0_14;
        f32 temp_f9_28;
        f32 temp_f10_15;
        f32 temp_f6_28;
        f32 temp_f7_27;
        f32 temp_f8_28;
        f32 temp_f0_15;
        f32 temp_f8_29;
        f32 temp_f10_16;
        f32 temp_f6_29;
        f32 temp_f7_28;
        f32 temp_f9_29;
        f32 temp_f12_6;
        f32 temp_f7_29;
        f32 temp_f9_30;
        f32 temp_f5_14;
        f32 temp_f6_30;
        f32 temp_f8_30;
        f32 temp_f12_7;
        f32 temp_f25_2;
        f32 temp_f9_31;
        f32 temp_f10_17;
        f32 temp_f6_31;
        f32 temp_f7_30;
        f32 temp_f8_31;
        f32 temp_f0_16;
        f32 temp_f9_32;
        f32 temp_f10_18;
        f32 temp_f6_32;
        f32 temp_f7_31;
        f32 temp_f8_32;
        f32 temp_f0_17;
        f32 temp_f9_33;
        f32 temp_f10_19;
        f32 temp_f6_33;
        f32 temp_f7_32;
        f32 temp_f8_33;
        f32 temp_f0_18;
        f32 det;
        f32 scale;
    P = (__ps_t *)arg0->dst;
    Q = (__ps_t *)fn_80057E2C(arg1);
    P[0] = Q[0];
    P[1] = Q[1];
    P[2] = Q[2];
    P[3] = Q[3];
    P = (__ps_t *)((char *)arg0 + 0x20);
    Q = (__ps_t *)fn_80057FBC(arg0->obj);
    n = 4;
    do {
        P[0] = Q[0];
        P[1] = Q[1];
        P[2] = Q[2];
        P[3] = Q[3];
        P[4] = Q[4];
        P[5] = Q[5];
        P[6] = Q[6];
        P[7] = Q[7];
    } while (--n != 0);
    mt = &arg0->mtx;
    P = (__ps_t *)cof;
    Q = (__ps_t *)mt;
        temp_f7_17 = mt->c34;
        temp_f9_18 = mt->c2C;
        temp_f5_8 = mt->c38;
        temp_f6_18 = mt->c3C;
        temp_f8_18 = mt->c24;
        temp_f11_7 = mt->c28;
        cof[2] = (mt->c1C * ((temp_f8_18 * temp_f5_8) - (temp_f7_17 * temp_f11_7))) + ((mt->c14 * ((temp_f11_7 * temp_f6_18) - (temp_f5_8 * temp_f9_18))) - (mt->c18 * ((temp_f8_18 * temp_f6_18) - (temp_f7_17 * temp_f9_18))));
        temp_f7_18 = mt->c30;
        temp_f9_19 = mt->c2C;
        temp_f5_9 = mt->c38;
        temp_f6_19 = mt->c3C;
        temp_f8_19 = mt->c20;
        temp_f11_8 = mt->c28;
        cof[6] = -((mt->c1C * ((temp_f8_19 * temp_f5_9) - (temp_f7_18 * temp_f11_8))) + ((mt->c10 * ((temp_f11_8 * temp_f6_19) - (temp_f5_9 * temp_f9_19))) - (mt->c18 * ((temp_f8_19 * temp_f6_19) - (temp_f7_18 * temp_f9_19)))));
        temp_f7_19 = mt->c30;
        temp_f9_20 = mt->c2C;
        temp_f5_10 = mt->c34;
        temp_f6_20 = mt->c3C;
        temp_f8_20 = mt->c20;
        temp_f11_9 = mt->c24;
        cof[10] = (mt->c1C * ((temp_f8_20 * temp_f5_10) - (temp_f7_19 * temp_f11_9))) + ((mt->c10 * ((temp_f11_9 * temp_f6_20) - (temp_f5_10 * temp_f9_20))) - (mt->c14 * ((temp_f8_20 * temp_f6_20) - (temp_f7_19 * temp_f9_20))));
        temp_f7_20 = mt->c30;
        temp_f9_21 = mt->c28;
        temp_f5_11 = mt->c34;
        temp_f6_21 = mt->c38;
        temp_f8_21 = mt->c20;
        temp_f11_10 = mt->c24;
        cof[14] = -((mt->c18 * ((temp_f8_21 * temp_f5_11) - (temp_f7_20 * temp_f11_10))) + ((mt->c10 * ((temp_f11_10 * temp_f6_21) - (temp_f5_11 * temp_f9_21))) - (mt->c14 * ((temp_f8_21 * temp_f6_21) - (temp_f7_20 * temp_f9_21)))));
        temp_f7_21 = mt->c34;
        temp_f9_22 = mt->c2C;
        temp_f5_12 = mt->c38;
        temp_f6_22 = mt->c3C;
        temp_f8_22 = mt->c24;
        temp_f12_5 = mt->c28;
        temp_f4_2 = mt->c00;
        cof[3] = -((mt->c0C * ((temp_f8_22 * temp_f5_12) - (temp_f7_21 * temp_f12_5))) + ((mt->c04 * ((temp_f12_5 * temp_f6_22) - (temp_f5_12 * temp_f9_22))) - (mt->c08 * ((temp_f8_22 * temp_f6_22) - (temp_f7_21 * temp_f9_22)))));
        temp_f9_23 = mt->c30;
        temp_f10_11 = mt->c2C;
        temp_f6_23 = mt->c38;
        temp_f7_22 = mt->c3C;
        temp_f8_23 = mt->c20;
        temp_f0_11 = mt->c28;
        cof[7] = (mt->c0C * ((temp_f8_23 * temp_f6_23) - (temp_f9_23 * temp_f0_11))) + ((temp_f4_2 * ((temp_f0_11 * temp_f7_22) - (temp_f6_23 * temp_f10_11))) - (mt->c08 * ((temp_f8_23 * temp_f7_22) - (temp_f9_23 * temp_f10_11))));
        temp_f9_24 = mt->c30;
        temp_f10_12 = mt->c2C;
        temp_f6_24 = mt->c34;
        temp_f7_23 = mt->c3C;
        temp_f8_24 = mt->c20;
        temp_f0_12 = mt->c24;
        cof[11] = -((mt->c0C * ((temp_f8_24 * temp_f6_24) - (temp_f9_24 * temp_f0_12))) + ((temp_f4_2 * ((temp_f0_12 * temp_f7_23) - (temp_f6_24 * temp_f10_12))) - (mt->c04 * ((temp_f8_24 * temp_f7_23) - (temp_f9_24 * temp_f10_12)))));
        temp_f9_25 = mt->c30;
        temp_f10_13 = mt->c28;
        temp_f6_25 = mt->c34;
        temp_f7_24 = mt->c38;
        temp_f8_25 = mt->c20;
        temp_f0_13 = mt->c24;
        cof[15] = (mt->c08 * ((temp_f8_25 * temp_f6_25) - (temp_f9_25 * temp_f0_13))) + ((temp_f4_2 * ((temp_f0_13 * temp_f7_24) - (temp_f6_25 * temp_f10_13))) - (mt->c04 * ((temp_f8_25 * temp_f7_24) - (temp_f9_25 * temp_f10_13))));
        temp_f7_25 = mt->c34;
        temp_f9_26 = mt->c1C;
        temp_f5_13 = mt->c38;
        temp_f6_26 = mt->c3C;
        temp_f8_26 = mt->c14;
        temp_f11_11 = mt->c18;
        cof[2] = ((mt->c0C * ((temp_f8_26 * temp_f5_13) - (temp_f7_25 * temp_f11_11))) + ((mt->c04 * ((temp_f11_11 * temp_f6_26) - (temp_f5_13 * temp_f9_26))) - (mt->c08 * ((temp_f8_26 * temp_f6_26) - (temp_f7_25 * temp_f9_26)))));
        temp_f9_27 = mt->c30;
        temp_f10_14 = mt->c1C;
        temp_f6_27 = mt->c38;
        temp_f7_26 = mt->c3C;
        temp_f8_27 = mt->c10;
        temp_f0_14 = mt->c18;
        cof[8] = -((mt->c0C * ((temp_f8_27 * temp_f6_27) - (temp_f9_27 * temp_f0_14))) + ((temp_f4_2 * ((temp_f0_14 * temp_f7_26) - (temp_f6_27 * temp_f10_14))) - (mt->c08 * ((temp_f8_27 * temp_f7_26) - (temp_f9_27 * temp_f10_14)))));
        temp_f9_28 = mt->c30;
        temp_f10_15 = mt->c1C;
        temp_f6_28 = mt->c34;
        temp_f7_27 = mt->c3C;
        temp_f8_28 = mt->c10;
        temp_f0_15 = mt->c14;
        cof[12] = (mt->c0C * ((temp_f8_28 * temp_f6_28) - (temp_f9_28 * temp_f0_15))) + ((temp_f4_2 * ((temp_f0_15 * temp_f7_27) - (temp_f6_28 * temp_f10_15))) - (mt->c04 * ((temp_f8_28 * temp_f7_27) - (temp_f9_28 * temp_f10_15))));
        temp_f8_29 = mt->c30;
        temp_f10_16 = mt->c18;
        temp_f6_29 = mt->c34;
        temp_f7_28 = mt->c38;
        temp_f9_29 = mt->c10;
        temp_f12_6 = mt->c14;
        cof[16] = -((mt->c08 * ((temp_f9_29 * temp_f6_29) - (temp_f8_29 * temp_f12_6))) + ((temp_f4_2 * ((temp_f12_6 * temp_f7_28) - (temp_f6_29 * temp_f10_16))) - (mt->c04 * ((temp_f9_29 * temp_f7_28) - (temp_f8_29 * temp_f10_16)))));
        temp_f7_29 = mt->c24;
        temp_f9_30 = mt->c1C;
        temp_f5_14 = mt->c28;
        temp_f6_30 = mt->c2C;
        temp_f8_30 = mt->c14;
        temp_f12_7 = mt->c18;
        temp_f25_2 = mt->c00;
        cof[5] = -((mt->c0C * ((temp_f8_30 * temp_f5_14) - (temp_f7_29 * temp_f12_7))) + ((mt->c04 * ((temp_f12_7 * temp_f6_30) - (temp_f5_14 * temp_f9_30))) - (mt->c08 * ((temp_f8_30 * temp_f6_30) - (temp_f7_29 * temp_f9_30)))));
        temp_f9_31 = mt->c20;
        temp_f10_17 = mt->c1C;
        temp_f6_31 = mt->c28;
        temp_f7_30 = mt->c2C;
        temp_f8_31 = mt->c10;
        temp_f0_16 = mt->c18;
        cof[9] = (mt->c0C * ((temp_f8_31 * temp_f6_31) - (temp_f9_31 * temp_f0_16))) + ((temp_f25_2 * ((temp_f0_16 * temp_f7_30) - (temp_f6_31 * temp_f10_17))) - (mt->c08 * ((temp_f8_31 * temp_f7_30) - (temp_f9_31 * temp_f10_17))));
        temp_f9_32 = mt->c20;
        temp_f10_18 = mt->c1C;
        temp_f6_32 = mt->c24;
        temp_f7_31 = mt->c2C;
        temp_f8_32 = mt->c10;
        temp_f0_17 = mt->c14;
        cof[11] = -((mt->c0C * ((temp_f8_32 * temp_f6_32) - (temp_f9_32 * temp_f0_17))) + ((temp_f25_2 * ((temp_f0_17 * temp_f7_31) - (temp_f6_32 * temp_f10_18))) - (mt->c04 * ((temp_f8_32 * temp_f7_31) - (temp_f9_32 * temp_f10_18)))));
        temp_f9_33 = mt->c20;
        temp_f10_19 = mt->c18;
        temp_f6_33 = mt->c24;
        temp_f7_32 = mt->c28;
        temp_f8_33 = mt->c10;
        temp_f0_18 = mt->c14;
        cof[15] = ((mt->c08 * ((temp_f8_33 * temp_f6_33) - (temp_f9_33 * temp_f0_18))) + ((temp_f25_2 * ((temp_f0_18 * temp_f7_32) - (temp_f6_33 * temp_f10_19))) - (mt->c04 * ((temp_f8_33 * temp_f7_32) - (temp_f9_33 * temp_f10_19)))));
        temp_f12_8 = mt->c2C;
        temp_f1_2 = mt->c30;
        temp_f26_2 = mt->c34;
        temp_f27_2 = mt->c38;
        temp_f13_3 = mt->c3C;
        temp_f3_3 = mt->c20;
        temp_f0_19 = mt->c24;
        temp_f31_2 = mt->c18;
        temp_f30_2 = (temp_f3_3 * temp_f13_3) - (temp_f1_2 * temp_f12_8);
        temp_f10_20 = mt->c28;
        temp_f29_2 = (temp_f0_19 * temp_f13_3) - (temp_f26_2 * temp_f12_8);
        temp_f6_34 = mt->c10;
        temp_f13_4 = (temp_f10_20 * temp_f13_3) - (temp_f27_2 * temp_f12_8);
        temp_f9_34 = mt->c14;
        temp_f8_34 = mt->c1C;
        temp_f11_12 = (temp_f3_3 * temp_f27_2) - (temp_f1_2 * temp_f10_20);
        temp_f0_20 = (temp_f0_19 * temp_f27_2) - (temp_f26_2 * temp_f10_20);
        temp_f3_4 = (temp_f3_3 * temp_f26_2) - (temp_f1_2 * temp_f0_19);
        det = ((mt->c08 * ((temp_f8_34 * temp_f3_4) + ((temp_f6_34 * temp_f29_2) - (temp_f9_34 * temp_f30_2)))) + ((temp_f25_2 * ((temp_f8_34 * temp_f0_20) + ((temp_f9_34 * temp_f13_4) - (temp_f31_2 * temp_f29_2)))) - (mt->c04 * ((temp_f8_34 * temp_f11_12) + ((temp_f6_34 * temp_f13_4) - (temp_f31_2 * temp_f30_2)))))) - (mt->c0C * ((temp_f31_2 * temp_f3_4) + ((temp_f6_34 * temp_f0_20) - (temp_f9_34 * temp_f11_12))));
        if (det != lbl_80298818) {
            scale = lbl_80298818 / det;
            if (scale != lbl_80298818) {
                __ps_t scl[4];
                scl[0] = scale;
                scl[1] = scale;
                scl[2] = scale;
                scl[3] = scale;
                P[0] = __builtin_ps_muls0(P[0], scl[0]);
                P[1] = __builtin_ps_muls0(P[1], scl[0]);
                P[2] = __builtin_ps_muls0(P[2], scl[1]);
                P[3] = __builtin_ps_muls0(P[3], scl[1]);
                P[4] = __builtin_ps_muls0(P[4], scl[2]);
                P[5] = __builtin_ps_muls0(P[5], scl[2]);
                P[6] = __builtin_ps_muls0(P[6], scl[3]);
                P[7] = __builtin_ps_muls0(P[7], scl[3]);
            }
        }
        Q[0] = P[0];
        Q[1] = P[1];
        Q[2] = P[2];
        Q[3] = P[3];
        Q[4] = P[4];
        Q[5] = P[5];
        Q[6] = P[6];
        Q[7] = P[7];
        goto epilogue;
    }
    case 3:
        goto epilogue;
    }
epilogue:
    return;
}
