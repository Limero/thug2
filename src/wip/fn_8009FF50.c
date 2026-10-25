// PARKED 2026-10-06: paired-single wall — the want is a PS function (128 psq_l/psq_st
// words + 58 opcode-4 PS merges).  Block B and block C below are decoded exactly; the
// block-A rotation build is compiler *pairing* output (ps_mr/ps_merge00/ps_mul/ps_sum0
// chains) whose source-level pairing is not recoverable from the instruction stream,
// so the three align sub-blocks are not reconstructed.  No whole-body asm is used.
//
// family=ps range=0x8009FF50-0x800A0564 size=1556B
// FLAG: -mps-float
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Recovered shape (0x8009FF50):
//   arg0 is the script object (u8*, the two 4x4 matrices live at +0x78 and +0xD0),
//   arg1 is the QB context handed to GetVector/GetFloat.
//   1. v = {0,0,1,1}; GetVector(arg1, 0x455485EF, v, 0)
//         -> empty counted spin loop, m = identity, then build a rotation from
//            v with three "normalise + align" sub-blocks (PS merges), and copy
//            the finished 16-float matrix into arg0+0x78 and arg0+0xD0.
//   2. else GetVector(arg1, 0x748CA262, v, 0)
//         -> quaternion-style rotation from v with sqrtf(1 - v[2]).
//   3. else GetFloat x3 (hashes 0x7323E97C / 0x0424D9EA / 0x9D2D8850), scale by
//         lbl_80297B70, fn_80003830(m, x, y, z).
//   Every path ends by copying m into arg0+0x78 and arg0+0xD0.
//   Float-pool constants: lbl_80297B60 == 0.0f, lbl_80297B64 == 1.0f.
#include "types.h"

extern char lbl_80297B28[]; /* PS pair table (merge operand in the align blocks) */
extern char lbl_80297B68[]; /* alignment epsilon */
extern char lbl_80297B6C[]; /* quaternion scale */
extern char lbl_80297B70[]; /* euler-angle scale */

s32 GetVector(s32 arg1, s32 hash, f32 *out, s32 arg3);
void GetFloat(s32 arg1, s32 hash, f32 *out, s32 arg3);
void fn_80003830(f32 *mat, f32 x, f32 y, f32 z);
f32 sqrtf(f32);
f32 fabsf(f32);

s32 fn_8009FF50(u8 *arg0, s32 arg1) {
    f32 v[4];      /* sp0x08: script vector (x, y, z, w) */
    f32 m[16];     /* sp0x18: rotation matrix under construction */
    f32 axis[4];   /* sp0x38: axis rotated into the matrix rows */
    f32 up[4];     /* sp0x58: {1,0,0,1} reference axis */
    f32 angles[3]; /* sp0x68: XYZ euler angles from GetFloat */
    f32 t;
    f32 s;
    f32 a;
    f32 b;
    f32 c;
    f32 r0;
    f32 r1;
    f32 r2;
    f32 r4;
    f32 r5;
    f32 r6;
    f32 r8;
    f32 r9;
    f32 r10;
    f32 *dst;
    s32 i;

    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 1.0f;
    v[3] = 1.0f;

    if (GetVector(arg1, 0x455485EF, v, 0)) {
        /* empty counted delay loop emitted by the original */
        i = 4;
        do {
            i--;
        } while (i != 0);

        m[0] = 0.0f;
        m[1] = 0.0f;
        m[2] = 0.0f;
        m[3] = 0.0f;
        m[4] = 0.0f;
        m[5] = 0.0f;
        m[6] = 0.0f;
        m[7] = 0.0f;
        m[8] = 0.0f;
        m[9] = 0.0f;
        m[10] = 0.0f;
        m[11] = 0.0f;
        m[12] = 0.0f;
        m[13] = 0.0f;
        m[14] = 0.0f;
        m[15] = 0.0f;
        m[0] = 1.0f;
        m[5] = 1.0f;
        m[10] = 1.0f;
        m[15] = 1.0f;

        if (fabsf(v[1]) > *(f32 *)lbl_80297B68) {
            up[0] = 1.0f;
            up[1] = 0.0f;
            up[2] = 0.0f;
            up[3] = 1.0f;
        }

        axis[0] = v[0];
        axis[1] = v[1];
        axis[2] = v[2];
        axis[3] = 0.0f;

        /* Three align sub-blocks each normalise a vector with ps_rsqrte and
           then fill one matrix row from it against `up`.  Only the
           normalisation is representable from the decode; the row fill uses
           the ps_merge00/ps_madd/ps_sum0 chains tabulated in the PARKED note
           and is deliberately NOT guessed here. */
        t = (axis[0] * axis[0] + axis[1] * axis[1]) + axis[2] * axis[2];
        if (t > 0.0f) {
            t = 1.0f / sqrtf(t);
        } else {
            t = 0.0f;
        }
        axis[0] *= t;
        axis[1] *= t;
        axis[2] *= t;

        t = (up[0] * up[0] + up[1] * up[1]) + up[2] * up[2];
        if (t > 0.0f) {
            t = 1.0f / sqrtf(t);
        } else {
            t = 0.0f;
        }
        up[0] *= t;
        up[1] *= t;
        up[2] *= t;

        dst = (f32 *)(arg0 + 0x78);
        for (i = 0; i < 16; i++) {
            dst[i] = m[i];
        }
        dst = (f32 *)(arg0 + 0xD0);
        for (i = 0; i < 16; i++) {
            dst[i] = m[i];
        }
    } else if (GetVector(arg1, 0x748CA262, v, 0)) {
        /* v becomes the quaternion (x, y, z, sqrt(1 - z)); scalar singles are
           fully decoded (the fmuls/fmadds/fsubs/fadds run at 0x800A0318..). */
        m[0] = 0.0f;
        m[1] = 0.0f;
        m[2] = 0.0f;
        m[3] = 1.0f;
        m[0] = v[0];
        m[1] = v[1];
        m[2] = v[2];

        t = sqrtf(1.0f - m[2]);
        s = (m[0] * m[0] + m[1] * m[1] + m[2] * m[2]) + t * t;
        if (s > 0.0f) {
            s = *(f32 *)lbl_80297B6C / s;
        } else {
            s = 0.0f;
        }

        a = m[0] * s;
        b = m[1] * s;
        c = m[2] * s;

        r0 = 1.0f - (m[1] * b + m[2] * c);
        r1 = m[0] * b - t * c;
        r2 = m[0] * c + t * b;
        r4 = m[0] * b + t * c;
        r5 = 1.0f - (m[0] * a + m[2] * c);
        r6 = m[1] * c - t * a;
        r8 = m[0] * c - t * b;
        r9 = m[1] * c + t * a;
        r10 = 1.0f - (m[0] * a + m[1] * b);

        m[0] = r0;
        m[1] = r1;
        m[2] = r2;
        m[4] = r4;
        m[5] = r5;
        m[6] = r6;
        m[8] = r8;
        m[9] = r9;
        m[10] = r10;

        dst = (f32 *)(arg0 + 0x78);
        for (i = 0; i < 16; i++) {
            dst[i] = m[i];
        }
        dst = (f32 *)(arg0 + 0xD0);
        for (i = 0; i < 16; i++) {
            dst[i] = m[i];
        }
    } else {
        angles[0] = 0.0f;
        angles[1] = 0.0f;
        angles[2] = 0.0f;
        GetFloat(arg1, 0x7323E97C, &angles[0], 0);
        GetFloat(arg1, 0x0424D9EA, &angles[1], 0);
        GetFloat(arg1, 0x9D2D8850, &angles[2], 0);
        angles[0] *= *(f32 *)lbl_80297B70;
        angles[1] *= *(f32 *)lbl_80297B70;
        angles[2] *= *(f32 *)lbl_80297B70;
        fn_80003830(m, angles[0], angles[1], angles[2]);

        dst = (f32 *)(arg0 + 0x78);
        for (i = 0; i < 16; i++) {
            dst[i] = m[i];
        }
        dst = (f32 *)(arg0 + 0xD0);
        for (i = 0; i < 16; i++) {
            dst[i] = m[i];
        }
    }

    return 1;
}

// NOTE (2026-10-06) — decoded opcode-4 sequence of the first block-A align
// sub-block (0x800A0068..0x800A008C).  The same pattern recurs for the second
// and third sub-blocks (0x800A00CC..0x800A00E4 / 0x800A0100..0x800A0134 /
// 0x800A0178..0x800A01DC), with the row operands rotated:
//   0x11800090 ps_mr     f12, f0
//   0x100B02F2 ps_mul    f0, f11, f11
//   0x10006C20 ps_merge00 f0, f0, f13
//   0x100C033A ps_madd   f0, f12, f12, f0
//   0x10000014 ps_sum0   f0, f0, f0, f0
//   0x11A00090 ps_mr     f13, f0        <- dot(axis, axis), compared to 0.0f
//   0x10000034 ps_rsqrte f0, f0         <- 1/sqrt(dot)
//   0x100C0018 ps_muls0  f0, f12, f0
//   0x11AB0332 ps_mul    f13, f11, f12
//   0x11AD5420 ps_merge00 f13, f13, f10
//   0x100A6CA0 ps_merge10 f0, f10, f13
//   0x118B4CA0 ps_merge10 f12, f11, f9
//   0x100002F2 ps_mul    f0, f0, f11
//   0x118A0332 ps_mul    f12, f10, f12
//   0x118C0028 ps_sub    f12, f12, f0
//   0x100C6420 ps_merge00 f0, f12, f12
//   0x11AD02F2 ps_mul    f13, f13, f11
//   0x11400090 ps_mr     f10, f0
//   0x116D6CA0 ps_merge10 f11, f13, f13
//   0x100A02B2 ps_mul    f0, f10, f10
//   0x11AD5828 ps_sub    f13, f13, f11
//   0x11AC6CA0 ps_merge10 f13, f12, f13
//   0x10004420 ps_merge00 f0, f4, f8
//   0x100D037A ps_muls1  f0, f13, f13
//   0x10000034 ps_rsqrte f0, f0
//   0x10004034 ps_rsqrte f0, f4
//   0x10000014 ps_sum0   f0, f0, f0, f0
//   0x11800090 ps_mr     f12, f0
//   0x100D0018 ps_muls0  f0, f13, f0
//   0x11AA0332 ps_mul    f13, f10, f12
// Block-B's paired-single tail (0x800A02F4..0x800A0304) decodes as
// ps_mul f0,f0,f0 / ps_merge00 f0,f0,f11 / ps_muls1 f13,f13,f13 /
// ps_sum0 f13,f13,f21,f13 and the operand staging is psq_l/psq_st of v and of
// the lbl_80297B28 pair.
// Residual blockers: (a) the source-level pairing choice of these PS chains,
// and (b) the psq_l/psq_st idiom for the two 4x4 copies.  -mps-float is set
// above but plain scalar C does not reach this pairing; the block-B/C math
// above is the part a future pass should verify first.
