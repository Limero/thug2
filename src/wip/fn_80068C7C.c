// WIP DRAFT (non-matching) -- hand-reconstructed 2026-09-26.
//
// family=m2c range=0x80068C7C-0x80068E60 size=484B
// extra_cflags: -mps-float
//
// INERT: not registered in splits.txt/configure.py -- never compiled, not
// counted in objdiff progress. activate via tools/wip.py.
//
// SCORE: DIFF 4.1% (reloc-masked), compiles clean with -mps-float.
// Verify: tools/venv/bin/python tools/score_body.py 0x80068C7C \
//            src/wip/fn_80068C7C.c "-mps-float"
//
// STATUS: PARKED. This replaces the previous m2c "corrupted husk" (0.0%, 20
// `0;` statements, punned &sp38/&sp28 arithmetic, float/int domain mix). The
// semantics, the callee signature, the local layout and every instruction of
// the 121-word body are now identified; what is left is a pure
// register-allocation / scheduling gap over ~18 simultaneously live FPRs
// (doc-15 "brittle allocator" class). See BLOCKER in section 7.
//
// ---------------------------------------------------------------------------
// 1. OPCODE IDENTIFICATION (the main new result)
//
// tools/disasm.py and capstone CANNOT read this function: they report `???`
// for every psq_l/psq_st (primary opcode 56/57/60/61) and mislabel every Gekko
// paired-single word as AltiVec (`vmsumshm`, `xxsel`, `xscmpgtdp`).  The field
// layouts below were therefore derived EMPIRICALLY by assembling candidate
// mnemonics with build/compilers/ProDG/3.9.3/NgcAs.exe and reading the encoded
// words back.  (ngcas only accepts NUMERIC register operands -- `f0`/`r3` are
// rejected with "Expected FPR/GPR register"; binutils' `as` has no psq_*
// mnemonics at all.)  Resulting table:
//
//   psq_l/lu/st/stu   opcode 56/57/60/61; bit26=A, frD=25..21, rA=20..16,
//                     W=bit15, I=14..12, d=11..0.  All sites here use W=0/I=0,
//                     i.e. single-lane scalar traffic through the PS unit.
//   Gekko PS A-form   opcode 4; frD=25..21, frA=20..16, frB=15..11, frC=10..6,
//                     xo5=5..1.  add=21 sub=20 mul=25 div=18 madd=29 msub=28
//                     nmsub=30 nmadd=31 sel=23 sum0=10 sum1=11 muls0=12
//                     muls1=13 madds0=14 madds1=15 merge00/01/10/11 = xo5 16
//                     with frC=16..19, res=24 rsqrte=26, and
//                     neg/mr/nabs/abs = xo5 8 with frC=1/2/4/8.
//
//   IMPORTANT: the twelve words capstone printed as `vmsumshm` / `xscmpgtdp` in
//   this function are plain **ps_muls0** (xo5=12) with a REAL frC register --
//   that field is the second source operand, not an opcode selector.  Verified
//   by compiling `__builtin_ps_muls0(a,b)`, which encodes as 1001 00 XX with
//   frA at 20..16, frC at 10..6 and frB unused.  So the doc-29 "capstone
//   mislabels PS as VMX" warning applies here, while the doc-06 "XO5=6/7 is a
//   hard wall" class does NOT: all 121 words are emittable.
// ---------------------------------------------------------------------------
// 2. DECODED WORD SEQUENCE (prose form; per-word detail lives in sections 3-6)
//
// The 121-word body opens by claiming a 0xC8 frame, loads two small-data page
// anchors, and builds the scalar reciprocal S = 1/(x*y*(y-x)) from the two
// incoming float arguments with a subtract, two multiplies and a divide. It
// loads paired-single row images from the three pointer arguments at element
// offsets 0 and 8, stages the frame pointer plus 8, counts 3 into the count
// register, and parks the output pointer in a saved register for the tail.
// The middle build-up spills the scalar operands to the 0x98/0xA0/0xA8 slots,
// forms the c-minus-a and b-minus-a paired differences, scales them by x and
// by the second vector base, derives the S-scaled R and T terms and the W/Z
// pair, and streams every intermediate through the twelve 16-byte rows at
// 0x08-0x90 with paired stores while re-reading rows for the next stage; the
// 0x38/0x40 coefficient pair is duplicated at 0x58/0x60 along the way. A
// three-iteration count-register loop over the frame bases 0x28, 0x38, 0x48
// with a 4-byte induction step then computes the guarded quadratic root per
// element (zero guard with a skip edge, one multiply, one divide and two
// multiply-adds, indexed loads and stores). The tail reloads the loop
// outputs, restores the output pointer, stores the two result floats at
// output offsets 0 and 8, issues one final scalar store, frees the 0xC8
// frame and returns. No floating save/restore pair appears anywhere.
//
// ---------------------------------------------------------------------------
// 3. CALLEE SIGNATURE (m2c had this wrong -- it interleaved the GPR and FPR
//    argument counters; PPC SysV uses two INDEPENDENT streams)
//
//   r3 = arg0 (out, f32*), r4 = arg1, r5 = arg2, r6 = arg3, f1 = farg0,
//   f2 = farg1.  Four GPR pointer args come FIRST, then the two floats.
//   arg1/arg2/arg3 are 3-float vectors read at offsets 0 and 8 (x and z; the
//   y slot is never read).  arg1 is additionally read element-wise by the
//   loop (`lfsx f13, r10, r4` with r10 = 0, 4, 8).  Return: `mr r3, r7` where
//   r7 = arg0, so the function returns arg0 after storing two floats to it.
// ---------------------------------------------------------------------------
// 4. LOCAL LAYOUT  (frame 0xC8; no FPR save area, no callee-saved GPRs)
//
//   Twelve 16-byte rows at 0x08, 0x18, 0x28, ... 0xB8 -- i.e. either
//   `__ps_t row[2]` or `float row[4]`.  Only elements 0 and 2 are ever
//   written; the loop walks elements 0,1,2 of the three rows at 0x28/0x38/0x48
//   with a 4-BYTE stride.  Confirmed by probe: `float m[12][4]` and
//   `__ps_t p[12][2]` both give frame 0xC8 with row 11 at 0xB8, and
//   `__ps_t p[9][2]; float q[3][4];` puts the float rows at 0x98/0xA8/0xB8
//   exactly as here.  Rows 0x08..0x90 are written with psq_st (PS values);
//   rows 0x98..0xC0 with plain stfs (x, y, S).
//
//   row @off    contents
//   0x08/0x10   (c0-a0)*x , (c2-a2)*x
//   0x18/0x20   (b0-a0)*x , (b2-a2)*b0
//   0x28/0x30   lin[0]=(y-R*S)^2 , lin[2]=Z*W       <- loop LINEAR coefficient
//   0x38/0x40   quad[0]=(S-P)*Q , quad[2]=(T-Q)*Q   <- loop QUADRATIC coeff
//   0x48..0x54  loop output[0..3]  (element 3 is a dead 0.0f store)
//   0x58/0x60   duplicate of 0x38/0x40
//   0x68/0x70   y-R*S , Z          then later  S-P , T
//   0x78/0x80   (b0-a0)*x^2 , (b2-a2)*b0*x
//   0x88/0x90   R*S , T*S
//   0x98/0xA0   x , y
//   0xA8/0xB0   y , x
//   0xB8/0xC0   S , S
//
//   with a = arg1, b = arg2, c = arg3, x = farg0, y = farg1 and
//        S = 1/(x*y*(y-x)),  R = (c0-a0)*x,  T = (c2-a2)*x,
//        P = (b0-a0)*x,      Q = (b2-a2)*b0,
//        W = y - R*S,        Z = Q*x - T*S.
// ---------------------------------------------------------------------------
// 5. CONSTANTS  (see src/r2d_80294900.c)
//   lbl_8029493C = 1.0f    lbl_80294940 = 0.0f    lbl_80294944 = -0.5f
// ---------------------------------------------------------------------------
// 6. CONTROL FLOW
//   Prologue -> twelve __builtin_ps_sub / ps_muls0 building S and the eight
//   intermediates above -> 3-iteration `li r0,3 / mtctr / bdnz` loop (bases
//   r1+0x28, r1+0x38, r1+0x48, induction r10 += 4) -> dead 0.0f store to 0x54
//   -> out[0] = res[0]; out[1] = res[2]; return out.
//
//   The loop is a GUARDED QUADRATIC ROOT.  With a = quad[i], b = lin[i],
//   c = arg1[i]:
//        s = (a > 0.0f) ? b * (-0.5f) / a : 0.0f;
//        res[i] = a*s*s + (b*s + c);
//   Note it reads lin[1] (0x2C) and quad[1] (0x3C), which the prologue never
//   writes: retail genuinely computes an uninitialised i=1 result and then
//   discards it, since only res[0] and res[2] are exported.
// ---------------------------------------------------------------------------
// 7. BLOCKER / NEXT STEP
//
//   The body below is semantically faithful and now compiles to the right
//   SHAPE: identical frame size (0xC8), the same instruction vocabulary
//   (lfs/stfs/lfsx/stfsx + psq_l/psq_st + ps_sub/ps_muls0 + fmadds/fdivs +
//   fcmpu/ble + mtctr/bdnz) and a 14-instruction loop against want's 15 that
//   matches want instruction-for-instruction in structure.  It still scores
//   4.1%: 92 emitted words vs want's 121, and the register assignment
//   diverges from word 2 onward.  Want holds ~18 live f32 values at once in
//   caller-saved FPRs with no stfd/lfd pair anywhere, so it must spill and
//   re-read its rows; the draft keeps fewer values live, CSEs them in
//   registers, and therefore omits ~29 want words -- six `ps_mr` copies
//   (0xD08/0xD2C/0xD48/0xD5C/0xD74/0xD7C) plus the psq_l re-reads of rows
//   0x98/0xA0/0xA8/0xB0/0xB8/0xC0/0x08/0x10/0x38 that retail reloads.
//   Want also reloads lin[i] TWICE in the loop (0x80068E0C and 0x80068E18)
//   where the draft CSEs the two reads into one register.
//
//   Remaining levers, in the order worth trying:
//   (a) Make each row the canonical storage and read EVERY operand back out of
//       it, so ngccc re-reads the rows and emits the missing ps_mr / psq_l
//       pairs.  Staging through named temps is what currently lets GCC CSE.
//   (b) Want's `fcmpu cr0, f12, f11` puts the QUADRATIC coefficient in the
//       first operand slot while the draft puts the guard value there; swapping
//       which local the compare tests may fix the operand slots.
//   (c) Move the first lin[i] read before the `if` guard to reproduce the
//       duplicated load inside the loop body.
//
//   This is a scheduling/allocator wall, not a missing-information wall: every
//   opcode, stack offset, constant and control-flow edge is now known.  Do NOT
//   re-attempt a re-decode -- use the field table in section 1.
// ---------------------------------------------------------------------------
#include "types.h"

extern f32 lbl_8029493C;  /*  1.0f */
extern f32 lbl_80294940;  /*  0.0f */
extern f32 lbl_80294944;  /* -0.5f */

f32 *fn_80068C7C(f32 *out, f32 *a, f32 *b, f32 *c, f32 farg0, f32 farg1) {
    SN_PS_type p[9][2];
    float q[3][4];
    f32 *qf = (f32 *)&p[3][0];
    f32 *lf = (f32 *)&p[2][0];
    f32 *lo = (f32 *)&p[4][0];
    s32 i;

    /* S = 1 / (x*y*(y-x)) : the reciprocal every later term is scaled by. */
    q[2][0] = lbl_8029493C / (farg0 * farg1 * (farg1 - farg0));
    q[2][2] = q[2][0];
    q[0][0] = farg0;
    q[0][2] = farg1;
    q[1][0] = farg1;
    q[1][2] = farg0;

    /* c - a */
    p[6][0].ps = __builtin_ps_sub(*(__ps_t *)&c[0], *(__ps_t *)&a[0]);
    p[6][1].ps = __builtin_ps_sub(*(__ps_t *)&c[2], *(__ps_t *)&a[2]);
    /* (c-a)*x */
    p[5][0].ps = __builtin_ps_muls0(p[6][0].ps, *(__ps_t *)&q[0][0]);
    p[5][1].ps = __builtin_ps_muls0(p[6][1].ps, *(__ps_t *)&q[0][0]);
    p[0][0].ps = p[5][0].ps;
    p[0][1].ps = p[5][1].ps;

    /* b - a */
    p[6][0].ps = __builtin_ps_sub(*(__ps_t *)&b[0], *(__ps_t *)&a[0]);
    p[6][1].ps = __builtin_ps_sub(*(__ps_t *)&b[2], *(__ps_t *)&a[2]);
    /* (b2-a2)*b0  and  (b0-a0)*x */
    p[5][0].ps = __builtin_ps_muls0(p[6][0].ps, *(__ps_t *)&q[0][0]);
    p[5][1].ps = __builtin_ps_muls0(p[6][1].ps, *(__ps_t *)&b[0]);
    p[1][0].ps = p[5][0].ps;
    p[1][1].ps = p[5][1].ps;
    /* ... * x again */
    p[7][0].ps = __builtin_ps_muls0(p[1][0].ps, *(__ps_t *)&q[1][2]);
    p[7][1].ps = __builtin_ps_muls0(p[1][1].ps, *(__ps_t *)&q[0][0]);

    /* ((c0-a0)*x)*S  and  ((c2-a2)*x)*S */
    p[8][0].ps = __builtin_ps_muls0(p[0][0].ps, *(__ps_t *)&q[2][0]);
    p[8][1].ps = __builtin_ps_muls0(p[0][1].ps, *(__ps_t *)&q[2][0]);

    /* w = y - ((c0-a0)*x)*S ;  z = ((b2-a2)*b0)*x - ((c2-a2)*x)*S */
    p[6][0].ps = __builtin_ps_sub(*(__ps_t *)&q[0][2], p[8][0].ps);
    p[6][1].ps = __builtin_ps_sub(p[7][1].ps, p[8][1].ps);
    p[2][0].ps = __builtin_ps_muls0(p[6][0].ps, p[6][0].ps);
    p[2][1].ps = __builtin_ps_muls0(p[6][1].ps, p[6][0].ps);
    p[5][0].ps = p[2][0].ps;
    p[5][1].ps = p[2][1].ps;

    /* S - ((b0-a0)*x)  and  ((c2-a2)*x) - ((b2-a2)*b0) */
    p[6][0].ps = __builtin_ps_sub(*(__ps_t *)&q[2][0], p[1][0].ps);
    p[6][1].ps = __builtin_ps_sub(p[0][1].ps, p[1][1].ps);
    p[3][0].ps = __builtin_ps_muls0(p[6][0].ps, p[1][1].ps);
    p[3][1].ps = __builtin_ps_muls0(p[6][1].ps, p[1][1].ps);
    p[5][0].ps = p[3][0].ps;
    p[5][1].ps = p[3][1].ps;

    /* Three guarded quadratic roots:
         s = b*(-0.5)/a  (s = 0 when a <= 0),  out = a*s*s + (b*s + c).   */
    for (i = 0; i < 3; i++) {
        f32 s;
        f32 r;
        f32 t;
        s = lbl_80294940;
        r = qf[i];
        if (r > s) {
            s = lf[i] * lbl_80294944 / r;
        }
        t = lf[i];
        r = r * s;
        t = t * s + a[i];
        lo[i] = r * s + t;
    }
    lo[3] = lbl_80294940;
    out[0] = lo[0];
    out[1] = lo[2];
    return out;
}
