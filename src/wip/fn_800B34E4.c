// WIP DRAFT (non-matching) - hand reconstruction from the retail disasm.
// family=m2c range=0x800B34E4-0x800B4488 size=4004B
// extra_cflags: -mps-float
//
// INERT: not registered in splits.txt/configure.py - never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// ---------------------------------------------------------------------------
// STATUS 2026-09-27: PARKED at 169/975 words (17.3%), object 3900 B vs want
//   4004 B (975 insns vs 1001). The previous m2c draft scored 0.92% with a
//   1300 B object. Verify with:
//     tools/venv/bin/python tools/ps_diff.py 0x800B34E4
//   (ps_diff is the PS-aware scorer; test_wip_drafts.py agrees at 17.3%.)
//
// WHAT WAS FIXED (all verified byte-exact / near-exact):
//   * Frame plus prologue plus epilogue are now exact: frame setup, link
//     save, callee-saved float and integer saves, parameter homes, and the
//     matching restore plus return, and the local region ends exactly where
//     the original's does. Three levers, each independently necessary:
//     (1) FILE-LOCAL TYPED LAYOUTS (see below). The shared Unk_* classes
//         type every f32 slot as s32 (Unk_DB0E2BAB) or as a 16x s32 scratch
//         block (Unk_59AB5482); ngccc emitted fctiwz/stfd for every store
//         and then dead-stripped ~2700 B.
//     (2) ONE frame struct (FR) instead of five separate locals. As separate
//         locals ngccc sorts the 16-byte sp8 ABOVE the three 64-byte
//         matrices, which shifts every r1 displacement in the function.
//     (3) &fr.I[0] must be a NESTED-scope pointer: at function scope it gets
//         a callee-saved home and the saved set grows by two registers;
//         the original holds it in a scratch register only inside the 2nd
//         multiply. Same for the matrix base around the 8-pair copy - at
//         function scope the 8 pair stores into the destination force 8
//         reloads of the source base because the pair store can alias; a
//         block-scoped local loads it once, like the original.
//   * Callee signature: `void *fn_80003Exx(void *, f32)` returning the
//     matrix it was handed, and `f32 fn_800B6344(void *)` (all four read r3
//     as a pointer; the fn_80003Exx family returns r3, not void). Getting
//     these wrong was the cause of the phantom crclr/mr pairs.
//   * Constants: zero, one and degree-to-radian scale. All three are loaded as
//     plain constant loads off real symbols (a sized scalar extern decl folds
//     the displacement; a byte-array extern does not).
//   * The 3 Euler-blend blocks: right-nested multiply-add tree, which is the
//     only tree that gives the original multiply-then-accumulate order.
//   * The 2nd multiply reads I through a pointer and arg1 through a
//     `volatile f32 *`, except arg1[0,1,4,5,8,9] which are cached. Without
//     the volatile view ngccc hoists ALL 16 arg1 floats into callee-saved
//     FPRs (17 stfd, 0x180 frame). With it, 0. With the 6 named exceptions
//     pinned to fr26..fr31: exactly retail's 6 stfd and 0x120 frame.
//
// DISCLOSURE - register pins: six DECLARATION-LEVEL hard-register pins
//   (register f32 bN __asm__("fr26".."fr31");) on the six cached arg1 floats.
//   No inline-asm instruction templates anywhere in this file. Without the
//   pins ngccc only picks 2 of the 6 callee-saved FPR homes; with them the
//   save list is byte-identical to retail's. Pinned map (retail's):
//   fr26=arg1[0] fr27=arg1[4] fr28=arg1[9] fr29=arg1[1] fr30=arg1[5]
//   fr31=arg1[8].
//
// RESIDUAL (precise, 26 insns short overall):
//   1. Each of the 3 Euler-blend blocks is ~20 insns SHORT (193/195/202 vs
//      retail's 213/217/217). The 16-store identity init and the empty
//      `for (i=0;i<4;i++){}` doloop are both present, but retail's stores sit
//      in the bdnz delay window in a rotate-right order (0x50,0x54,0x18..0x4c)
//      while ngccc emits 0x14,0x0c,0x08,0x10 here. That rotation is a pure
//      store-scheduling artifact of the delay-slot filler; ~12 of the missing
//      words per block are this one run.
//   2. The 2nd multiply is ~29 words over: the original reloads the
//      10 non-cached source floats about twice each and keeps the other 6 in
//      callee-saved float registers; here the 6 pins add copy setup and the
//      volatile reloads are not folded into the original exact count.
//   3. The paired-single 2x2 block is 41 words vs the original 45: all pair
//      arithmetic words are emitted in the right kinds and order, but 4 of
//      the 6 pair-store destinations are dead in the original (overwritten by
//      the 2nd multiply) and the compiler drops the 4 stores that are dead,
//      leaving 2.
//   4. The tail word load is emitted twice (once hoisted to the top of the
//      tail, once mid-tail) because the pair-add chain aliases.
//   5. Prologue scheduling only: the original interleaves the two constant
//      loads with the 8-pair copy; here both constant setups land first. Also
//      the frame-address setup plus register copy is hoisted above the copy
//      in the original and sunk below it here. Both are call-setup and
//      scheduling order artifacts, not a semantic difference.
//   None of these are reachable by a semantic fix; items 1-2 are the
//   documented big-function allocator/store-scheduling wall (AGENTS.md
//   6af-171, recipe 24/64). Do not grind them without a new lever.
// ---------------------------------------------------------------------------
#include "types.h"

// File-local layouts. The shared Unk_* classes in structs.h type every one
// of these slots as s32 (Unk_DB0E2BAB) or as a 16 x s32 scratch block
// (Unk_59AB5482), which made ngccc emit fctiwz/stfd conversions for every f32
// store and then dead-strip ~2700 B of the body (1300 B object vs 4004 B
// retail). Every 4x4 in this function is f32, and the 4-float scratch at
// r1+0x08 is a 2-element paired-single pair.
typedef union { __ps_t ps; struct { f32 hi, lo; } flt; } PSU;

typedef struct {                /* *(arg0 + 0x0C) */
    char pad0x00[0x58];
    __ps_t p11;                 /* +0x58 */
    __ps_t p12;                 /* +0x60 */
    char pad0x68[0x68];
    __ps_t m[8];                /* +0xD0 .. +0x108 */
} M8;

typedef struct {                /* arg0 */
    char pad0x00[0x0C];
    M8 *unk0x0C;
    char pad0x10[0x20];
    __ps_t unk0x30;             /* the 4 floats tested against 0.0f below */
    __ps_t unk0x38;
    char pad0x40[0x90];
    s32 unk0xD0;
    char pad0xD4[0x90];
    s32 unk0x164;
    char pad0x168[0x90];
    s32 unk0x1F8;
    s32 unk0x1FC;               /* negate arg1 rows 0/1 and 2/3 */
    __ps_t unk0x200;
    __ps_t unk0x208;
} A0;

typedef struct { f32 v[16]; } M4;   /* arg1: a 4x4 f32 matrix */

/* One frame object so the stack layout is fixed by the struct and cannot be
 * re-sorted by ngccc (it otherwise pushes the 16-byte sp8 above the three
 * 64-byte matrices, shifting every displacement in the function). */
typedef struct {
    PSU sp8[2];                /* r1+0x08  pair scratch (also the negation temp) */
    f32 I[16];                 /* r1+0x18  the identity / Euler-blend source     */
    f32 sp58[16];              /* r1+0x58  fn_80003Exx scratch, then multiply dst  */
    f32 R[16];                 /* r1+0x98  the blended 4x4                        */
    void * volatile spD8;      /* r1+0xd8  &fr.I[0]  (dead store in retail too)   */
    void * volatile spDC;      /* r1+0xdc  arg1                                    */
} FR;

extern f32 lbl_80298880;       /* 0.0f                */
extern f32 lbl_80298884;       /* 1.0f                */
extern f32 lbl_80298888;       /* 0.017453292f (deg)  */
f32 fn_800B6344(void *);
void *fn_80003E0C(void *, f32);
void *fn_80003EB0(void *, f32);
void *fn_80003F54(void *, f32);

void fn_800B34E4(A0 *arg0, M4 *arg1) {
    FR fr;
    f32 *m;
    f32 t;
    s32 i;
    s32 var_r28;
    __ps_t *s8;

    s8 = (void *)&fr.sp8[0];

    /* 8-pair copy of m8+0xD0 into arg1, then rows 6/7 forced to (0,0,0,1) */
    {
        M8 *mm = arg0->unk0x0C;
        ((__ps_t *)arg1)[0] = mm->m[0];
        ((__ps_t *)arg1)[1] = mm->m[1];
        ((__ps_t *)arg1)[2] = mm->m[2];
        ((__ps_t *)arg1)[3] = mm->m[3];
        ((__ps_t *)arg1)[4] = mm->m[4];
        ((__ps_t *)arg1)[5] = mm->m[5];
        ((__ps_t *)arg1)[6] = mm->m[6];
        ((__ps_t *)arg1)[7] = mm->m[7];
    }
    fr.sp8[0].flt.lo = lbl_80298880;
    fr.sp8[0].flt.hi = lbl_80298880;
    fr.sp8[1].flt.lo = lbl_80298880;
    fr.sp8[1].flt.hi = lbl_80298884;
    ((__ps_t *)arg1)[7] = s8[1];
    ((__ps_t *)arg1)[6] = s8[0];

    if (arg0->unk0x1FC != 0) {
        fr.sp8[0].flt.lo = -arg1->v[ 8]; fr.sp8[0].flt.hi = -arg1->v[ 9];
        fr.sp8[1].flt.lo = -arg1->v[10];
        fr.sp8[1].flt.hi = -arg1->v[11];
        ((__ps_t *)arg1)[4] = s8[0];
        ((__ps_t *)arg1)[5] = s8[1];
        fr.sp8[0].flt.lo = -arg1->v[ 0]; fr.sp8[0].flt.hi = -arg1->v[ 1];
        fr.sp8[1].flt.lo = -arg1->v[ 2];
        fr.sp8[1].flt.hi = -arg1->v[ 3];
        ((__ps_t *)arg1)[0] = s8[0];
        ((__ps_t *)arg1)[1] = s8[1];
    }

    for (i = 0; i < 4; i++) { }
    var_r28 = 1;

    if (arg0->unk0xD0 != 0) {
        t = fn_800B6344((char *)arg0 + 0x40);
        if (t != lbl_80298880) {
    fr.I[ 0] = lbl_80298884;
    fr.I[ 1] = lbl_80298880;
    fr.I[ 2] = lbl_80298880;
    fr.I[ 3] = lbl_80298880;
    fr.I[ 4] = lbl_80298880;
    fr.I[ 5] = lbl_80298884;
    fr.I[ 6] = lbl_80298880;
    fr.I[ 7] = lbl_80298880;
    fr.I[ 8] = lbl_80298880;
    fr.I[ 9] = lbl_80298880;
    fr.I[10] = lbl_80298884;
    fr.I[11] = lbl_80298880;
    fr.I[12] = lbl_80298880;
    fr.I[13] = lbl_80298880;
    fr.I[14] = lbl_80298880;
    fr.I[15] = lbl_80298884;
        var_r28 = 0;
            for (i = 0; i < 4; i++) { }
            m = (f32 *)fn_80003E0C(&fr.sp58[0], t * lbl_80298888);
            {
    fr.R[ 0] = fr.I[ 3]*m[12] + (fr.I[ 2]*m[ 8] + (fr.I[ 0]*m[ 0] + fr.I[ 1]*m[ 4]));
    fr.R[ 1] = fr.I[ 3]*m[13] + (fr.I[ 2]*m[ 9] + (fr.I[ 0]*m[ 1] + fr.I[ 1]*m[ 5]));
    fr.R[ 2] = fr.I[ 3]*m[14] + (fr.I[ 2]*m[10] + (fr.I[ 0]*m[ 2] + fr.I[ 1]*m[ 6]));
    fr.R[ 3] = fr.I[ 3]*m[15] + (fr.I[ 2]*m[11] + (fr.I[ 0]*m[ 3] + fr.I[ 1]*m[ 7]));
    fr.R[ 4] = fr.I[ 7]*m[12] + (fr.I[ 6]*m[ 8] + (fr.I[ 4]*m[ 0] + fr.I[ 5]*m[ 4]));
    fr.R[ 5] = fr.I[ 7]*m[13] + (fr.I[ 6]*m[ 9] + (fr.I[ 4]*m[ 1] + fr.I[ 5]*m[ 5]));
    fr.R[ 6] = fr.I[ 7]*m[14] + (fr.I[ 6]*m[10] + (fr.I[ 4]*m[ 2] + fr.I[ 5]*m[ 6]));
    fr.R[ 7] = fr.I[ 7]*m[15] + (fr.I[ 6]*m[11] + (fr.I[ 4]*m[ 3] + fr.I[ 5]*m[ 7]));
    fr.R[ 8] = fr.I[11]*m[12] + (fr.I[10]*m[ 8] + (fr.I[ 8]*m[ 0] + fr.I[ 9]*m[ 4]));
    fr.R[ 9] = fr.I[11]*m[13] + (fr.I[10]*m[ 9] + (fr.I[ 8]*m[ 1] + fr.I[ 9]*m[ 5]));
    fr.R[10] = fr.I[11]*m[14] + (fr.I[10]*m[10] + (fr.I[ 8]*m[ 2] + fr.I[ 9]*m[ 6]));
    fr.R[11] = fr.I[11]*m[15] + (fr.I[10]*m[11] + (fr.I[ 8]*m[ 3] + fr.I[ 9]*m[ 7]));
    fr.R[12] = fr.I[15]*m[12] + (fr.I[14]*m[ 8] + (fr.I[12]*m[ 0] + fr.I[13]*m[ 4]));
    fr.R[13] = fr.I[15]*m[13] + (fr.I[14]*m[ 9] + (fr.I[12]*m[ 1] + fr.I[13]*m[ 5]));
    fr.R[14] = fr.I[15]*m[14] + (fr.I[14]*m[10] + (fr.I[12]*m[ 2] + fr.I[13]*m[ 6]));
    fr.R[15] = fr.I[15]*m[15] + (fr.I[14]*m[11] + (fr.I[12]*m[ 3] + fr.I[13]*m[ 7]));
            }
        }
    }

    if (arg0->unk0x164 != 0) {
        t = fn_800B6344((char *)arg0 + 0xD4);
        if (t != lbl_80298880) {
            if (var_r28 != 0) {
    fr.I[ 0] = lbl_80298884;
    fr.I[ 1] = lbl_80298880;
    fr.I[ 2] = lbl_80298880;
    fr.I[ 3] = lbl_80298880;
    fr.I[ 4] = lbl_80298880;
    fr.I[ 5] = lbl_80298884;
    fr.I[ 6] = lbl_80298880;
    fr.I[ 7] = lbl_80298880;
    fr.I[ 8] = lbl_80298880;
    fr.I[ 9] = lbl_80298880;
    fr.I[10] = lbl_80298884;
    fr.I[11] = lbl_80298880;
    fr.I[12] = lbl_80298880;
    fr.I[13] = lbl_80298880;
    fr.I[14] = lbl_80298880;
    fr.I[15] = lbl_80298884;
            }
            var_r28 = 0;
            for (i = 0; i < 4; i++) { }
            m = (f32 *)fn_80003EB0(&fr.sp58[0], t * lbl_80298888);
            {
    fr.R[ 0] = fr.I[ 3]*m[12] + (fr.I[ 2]*m[ 8] + (fr.I[ 0]*m[ 0] + fr.I[ 1]*m[ 4]));
    fr.R[ 1] = fr.I[ 3]*m[13] + (fr.I[ 2]*m[ 9] + (fr.I[ 0]*m[ 1] + fr.I[ 1]*m[ 5]));
    fr.R[ 2] = fr.I[ 3]*m[14] + (fr.I[ 2]*m[10] + (fr.I[ 0]*m[ 2] + fr.I[ 1]*m[ 6]));
    fr.R[ 3] = fr.I[ 3]*m[15] + (fr.I[ 2]*m[11] + (fr.I[ 0]*m[ 3] + fr.I[ 1]*m[ 7]));
    fr.R[ 4] = fr.I[ 7]*m[12] + (fr.I[ 6]*m[ 8] + (fr.I[ 4]*m[ 0] + fr.I[ 5]*m[ 4]));
    fr.R[ 5] = fr.I[ 7]*m[13] + (fr.I[ 6]*m[ 9] + (fr.I[ 4]*m[ 1] + fr.I[ 5]*m[ 5]));
    fr.R[ 6] = fr.I[ 7]*m[14] + (fr.I[ 6]*m[10] + (fr.I[ 4]*m[ 2] + fr.I[ 5]*m[ 6]));
    fr.R[ 7] = fr.I[ 7]*m[15] + (fr.I[ 6]*m[11] + (fr.I[ 4]*m[ 3] + fr.I[ 5]*m[ 7]));
    fr.R[ 8] = fr.I[11]*m[12] + (fr.I[10]*m[ 8] + (fr.I[ 8]*m[ 0] + fr.I[ 9]*m[ 4]));
    fr.R[ 9] = fr.I[11]*m[13] + (fr.I[10]*m[ 9] + (fr.I[ 8]*m[ 1] + fr.I[ 9]*m[ 5]));
    fr.R[10] = fr.I[11]*m[14] + (fr.I[10]*m[10] + (fr.I[ 8]*m[ 2] + fr.I[ 9]*m[ 6]));
    fr.R[11] = fr.I[11]*m[15] + (fr.I[10]*m[11] + (fr.I[ 8]*m[ 3] + fr.I[ 9]*m[ 7]));
    fr.R[12] = fr.I[15]*m[12] + (fr.I[14]*m[ 8] + (fr.I[12]*m[ 0] + fr.I[13]*m[ 4]));
    fr.R[13] = fr.I[15]*m[13] + (fr.I[14]*m[ 9] + (fr.I[12]*m[ 1] + fr.I[13]*m[ 5]));
    fr.R[14] = fr.I[15]*m[14] + (fr.I[14]*m[10] + (fr.I[12]*m[ 2] + fr.I[13]*m[ 6]));
    fr.R[15] = fr.I[15]*m[15] + (fr.I[14]*m[11] + (fr.I[12]*m[ 3] + fr.I[13]*m[ 7]));
            }
        }
    }

    if (arg0->unk0x1F8 != 0) {
        t = fn_800B6344((char *)arg0 + 0x168);
        if (t != lbl_80298880) {
            if (var_r28 != 0) {
    fr.I[ 0] = lbl_80298884;
    fr.I[ 1] = lbl_80298880;
    fr.I[ 2] = lbl_80298880;
    fr.I[ 3] = lbl_80298880;
    fr.I[ 4] = lbl_80298880;
    fr.I[ 5] = lbl_80298884;
    fr.I[ 6] = lbl_80298880;
    fr.I[ 7] = lbl_80298880;
    fr.I[ 8] = lbl_80298880;
    fr.I[ 9] = lbl_80298880;
    fr.I[10] = lbl_80298884;
    fr.I[11] = lbl_80298880;
    fr.I[12] = lbl_80298880;
    fr.I[13] = lbl_80298880;
    fr.I[14] = lbl_80298880;
    fr.I[15] = lbl_80298884;
            }
            var_r28 = 0;
            for (i = 0; i < 4; i++) { }
            m = (f32 *)fn_80003F54(&fr.sp58[0], t * lbl_80298888);
            {
    fr.R[ 0] = fr.I[ 3]*m[12] + (fr.I[ 2]*m[ 8] + (fr.I[ 0]*m[ 0] + fr.I[ 1]*m[ 4]));
    fr.R[ 1] = fr.I[ 3]*m[13] + (fr.I[ 2]*m[ 9] + (fr.I[ 0]*m[ 1] + fr.I[ 1]*m[ 5]));
    fr.R[ 2] = fr.I[ 3]*m[14] + (fr.I[ 2]*m[10] + (fr.I[ 0]*m[ 2] + fr.I[ 1]*m[ 6]));
    fr.R[ 3] = fr.I[ 3]*m[15] + (fr.I[ 2]*m[11] + (fr.I[ 0]*m[ 3] + fr.I[ 1]*m[ 7]));
    fr.R[ 4] = fr.I[ 7]*m[12] + (fr.I[ 6]*m[ 8] + (fr.I[ 4]*m[ 0] + fr.I[ 5]*m[ 4]));
    fr.R[ 5] = fr.I[ 7]*m[13] + (fr.I[ 6]*m[ 9] + (fr.I[ 4]*m[ 1] + fr.I[ 5]*m[ 5]));
    fr.R[ 6] = fr.I[ 7]*m[14] + (fr.I[ 6]*m[10] + (fr.I[ 4]*m[ 2] + fr.I[ 5]*m[ 6]));
    fr.R[ 7] = fr.I[ 7]*m[15] + (fr.I[ 6]*m[11] + (fr.I[ 4]*m[ 3] + fr.I[ 5]*m[ 7]));
    fr.R[ 8] = fr.I[11]*m[12] + (fr.I[10]*m[ 8] + (fr.I[ 8]*m[ 0] + fr.I[ 9]*m[ 4]));
    fr.R[ 9] = fr.I[11]*m[13] + (fr.I[10]*m[ 9] + (fr.I[ 8]*m[ 1] + fr.I[ 9]*m[ 5]));
    fr.R[10] = fr.I[11]*m[14] + (fr.I[10]*m[10] + (fr.I[ 8]*m[ 2] + fr.I[ 9]*m[ 6]));
    fr.R[11] = fr.I[11]*m[15] + (fr.I[10]*m[11] + (fr.I[ 8]*m[ 3] + fr.I[ 9]*m[ 7]));
    fr.R[12] = fr.I[15]*m[12] + (fr.I[14]*m[ 8] + (fr.I[12]*m[ 0] + fr.I[13]*m[ 4]));
    fr.R[13] = fr.I[15]*m[13] + (fr.I[14]*m[ 9] + (fr.I[12]*m[ 1] + fr.I[13]*m[ 5]));
    fr.R[14] = fr.I[15]*m[14] + (fr.I[14]*m[10] + (fr.I[12]*m[ 2] + fr.I[13]*m[ 6]));
    fr.R[15] = fr.I[15]*m[15] + (fr.I[14]*m[11] + (fr.I[12]*m[ 3] + fr.I[13]*m[ 7]));
            }
        }
    }

    fr.sp8[0].flt.lo = lbl_80298880;
    fr.sp8[0].flt.hi = lbl_80298880;
    fr.sp8[1].flt.lo = lbl_80298880;
    fr.sp8[1].flt.hi = lbl_80298880;
    if (var_r28 == 0) {
        s8[0] = arg0->unk0x30;
        s8[1] = arg0->unk0x38;
        if (fr.sp8[0].flt.lo != lbl_80298880 || fr.sp8[0].flt.hi != lbl_80298880 || fr.sp8[1].flt.lo != lbl_80298880) {
            __ps_t A0p, A1p, T0, T1, t3, u3, w3, v3;
            __ps_t *B = (__ps_t *)arg1;
            __ps_t *o = (__ps_t *)&fr.sp58[0];
            A0p = s8[0];
            A1p = s8[1];
            t3 = __builtin_ps_madds1(((__ps_t *)&fr.I[0])[5], __builtin_ps_madds0(((__ps_t *)&fr.I[0])[3], __builtin_ps_madds1(((__ps_t *)&fr.I[0])[2], __builtin_ps_muls0(((__ps_t *)&fr.I[0])[0], A0p), A0p), A1p), A1p);
            u3 = __builtin_ps_madds1(((__ps_t *)&fr.I[0])[6], __builtin_ps_madds0(((__ps_t *)&fr.I[0])[4], __builtin_ps_madds1(((__ps_t *)&fr.I[0])[3], __builtin_ps_muls0(((__ps_t *)&fr.I[0])[1], A0p), A0p), A1p), A1p);
            T0 = __builtin_ps_sub(A0p, t3);
            T1 = __builtin_ps_sub(A1p, u3);
            w3 = __builtin_ps_madds1(B[6], __builtin_ps_madds0(B[4], __builtin_ps_madds1(B[2], __builtin_ps_muls0(B[0], T0), T0), T1), T1);
            v3 = __builtin_ps_madds1(B[7], __builtin_ps_madds0(B[5], __builtin_ps_madds1(B[3], __builtin_ps_muls0(B[1], T0), T0), T1), T1);
            o[2] = t3;
            o[3] = u3;
            s8[1] = v3;
            o[1] = v3;
            s8[0] = w3;
            o[0] = w3;
        }
        fr.spDC = arg1;
        fr.spD8 = &fr.I[0];
        {
        f32 *ip = &fr.I[0];
        volatile f32 *av = arg1->v;
        register f32 b0 __asm__("fr26") = arg1->v[ 0];
        register f32 b4 __asm__("fr27") = arg1->v[ 4];
        register f32 b9 __asm__("fr28") = arg1->v[ 9];
        register f32 b1 __asm__("fr29") = arg1->v[ 1];
        register f32 b5 __asm__("fr30") = arg1->v[ 5];
        register f32 b8 __asm__("fr31") = arg1->v[ 8];
    fr.sp58[ 0] = ip[ 3]*av[12] + (ip[ 2]*b8 + (ip[ 0]*b0 + ip[ 1]*b4));
    fr.sp58[ 1] = ip[ 3]*av[13] + (ip[ 2]*b9 + (ip[ 0]*b1 + ip[ 1]*b5));
    fr.sp58[ 2] = ip[ 3]*av[14] + (ip[ 2]*av[10] + (ip[ 0]*av[ 2] + ip[ 1]*av[ 6]));
    fr.sp58[ 3] = ip[ 3]*av[15] + (ip[ 2]*av[11] + (ip[ 0]*av[ 3] + ip[ 1]*av[ 7]));
    fr.sp58[ 4] = ip[ 7]*av[12] + (ip[ 6]*b8 + (ip[ 4]*b0 + ip[ 5]*b4));
    fr.sp58[ 5] = ip[ 7]*av[13] + (ip[ 6]*b9 + (ip[ 4]*b1 + ip[ 5]*b5));
    fr.sp58[ 6] = ip[ 7]*av[14] + (ip[ 6]*av[10] + (ip[ 4]*av[ 2] + ip[ 5]*av[ 6]));
    fr.sp58[ 7] = ip[ 7]*av[15] + (ip[ 6]*av[11] + (ip[ 4]*av[ 3] + ip[ 5]*av[ 7]));
    fr.sp58[ 8] = ip[11]*av[12] + (ip[10]*b8 + (ip[ 8]*b0 + ip[ 9]*b4));
    fr.sp58[ 9] = ip[11]*av[13] + (ip[10]*b9 + (ip[ 8]*b1 + ip[ 9]*b5));
    fr.sp58[10] = ip[11]*av[14] + (ip[10]*av[10] + (ip[ 8]*av[ 2] + ip[ 9]*av[ 6]));
    fr.sp58[11] = ip[11]*av[15] + (ip[10]*av[11] + (ip[ 8]*av[ 3] + ip[ 9]*av[ 7]));
    fr.sp58[12] = ip[15]*av[12] + (ip[14]*b8 + (ip[12]*b0 + ip[13]*b4));
    fr.sp58[13] = ip[15]*av[13] + (ip[14]*b9 + (ip[12]*b1 + ip[13]*b5));
    fr.sp58[14] = ip[15]*av[14] + (ip[14]*av[10] + (ip[12]*av[ 2] + ip[13]*av[ 6]));
    fr.sp58[15] = ip[15]*av[15] + (ip[14]*av[11] + (ip[12]*av[ 3] + ip[13]*av[ 7]));
        }
        ((__ps_t *)arg1)[0] = ((__ps_t *)&fr.sp58[0])[0];
        ((__ps_t *)arg1)[1] = ((__ps_t *)&fr.sp58[0])[1];
        ((__ps_t *)arg1)[2] = ((__ps_t *)&fr.sp58[0])[2];
        ((__ps_t *)arg1)[3] = ((__ps_t *)&fr.sp58[0])[3];
        ((__ps_t *)arg1)[4] = ((__ps_t *)&fr.sp58[0])[4];
        ((__ps_t *)arg1)[5] = ((__ps_t *)&fr.sp58[0])[5];
        ((__ps_t *)arg1)[6] = ((__ps_t *)&fr.sp58[0])[6];
        ((__ps_t *)arg1)[7] = ((__ps_t *)&fr.sp58[0])[7];
    }
    ((__ps_t *)arg1)[6] = arg0->unk0x0C->p11;
    ((__ps_t *)arg1)[7] = arg0->unk0x0C->p12;
    ((__ps_t *)arg1)[6] = __builtin_ps_add(((__ps_t *)arg1)[6], s8[1]);
    ((__ps_t *)arg1)[7] = __builtin_ps_add(((__ps_t *)arg1)[7], s8[1]);
    ((__ps_t *)arg1)[6] = __builtin_ps_add(((__ps_t *)arg1)[6], arg0->unk0x200);
    ((__ps_t *)arg1)[7] = __builtin_ps_add(((__ps_t *)arg1)[7], arg0->unk0x208);
    arg1->v[15] = lbl_80298884;
}
