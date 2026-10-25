// WIP DRAFT (non-matching) — hand-rebuilt from disasm (G)
// PARKED (G, 2nd pass): 92.5% (was 84.9%). Big win this pass:
// copy-backs must be TYPED __ps_t pair reads —
//   ((__ps_t volatile *)base)[k] = ((__ps_t volatile *)&fr.out[0])[k];
// emits want's fused psq_l(out-stack)+psq_st pairs (scalar f32 RHS gave
// lfs-pair hybrids). Matrix-2 tail pair order is [0,1,2,3,4,7,5,6].
// Remaining 39 diffs, 4 clusters:
// (a) FRAME +8 + cvt slot: want frame 0x100 with cvt@r1+0xB0/0xB4; got 0x108
//     with cvt@0xA8 (pad[16]). pad[24] puts cvt@0xB0 correctly BUT frame goes
//     0x110 — GCC's post-locals gap shrinks only 4B per +8 locals (0x14->0x10),
//     want needs gap 0x04. Gap looks like spill slack, not arithmetic.
// (b) cvt store order: want stores the high word at offset B4, materialises
//     0x4330 into r10, then stores the low word at offset B0; got hoists the
//     constant materialisation ABOVE the high-word store. volatile-u32 cast
//     does NOT block const remat; comma self-assign folds away. Untried lever:
//     asm literal birth __asm__("lis %0,0x4330" : "=r"(hi)) with hi pinned r10,
//     placed between.
// (c) WINDOW-1 (rel 0x148-0x174): want loads immediate 4 into r0, loads the
//     m-base pointer from 0xc(r28) into r9, loads the float at 0x94(r28) into
//     f0, moves to the count register, then derives the t1 address into r29,
//     arg0+0x20 into r30, r9+0x78 into r31, and the t2 address into r27, then
//     multiplies f30 by f0 into f1 and takes the counted loop branch. Got
//     keeps the m-base load in r31 (web coalesced) and sinks only 3 of the
//     address derivations. Asm wedges for the loop boilerplate (immediate 4
//     load, count-register move, counted branch) reproduce the shape, BUT
//     every way tried to split the m-web (plain local, register-char pin on
//     r9, anonymous inline dereference) SHIFTS THE WHOLE SAVED-GPR MAP (arg0
//     home from r28 to r27/r26 with stmw narrowing to r26, cascading ~100
//     displacements) back down to 52-54%. The map and the window fight:
//     whoever cracks (c) must re-check arg0 home + stmw span after EACH edit.
// (d) WINDOW-2 (rel 0x50C): want loads the float at 0x94(r28) into f0,
//     multiplies f30 by f0 into f1 and takes the counted loop branch, then
//     derives r3 and calls. NOTE: want has only TWO immediate-load/count-move
//     pairs total — loop-2's counted branch at 0x1738 consumes the count move
//     emitted right AFTER call#1 (immediate 4 into r0, save of r31 to 4(r29),
//     count move from r0 at 0x13A0-0x13A8), NOT a second immediate load.
//     Matrix-2 first-row scratch-role flips (f11/f13 vs got f13/f0) likely heal
//     with (d).
// Callees: fn_80003E0C(void*,f32)->void* (result stored to fr.t1/fr.t2);
// guards/cvt-dance/lerp/dot-tree all match as written.
// family=m2c range=0x801E1224-0x801E1A3C size=2072B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
// RESTORED 2026-09-20 by tools/restore_best_body.py.  The working body
// scored 45.9% while git revision 3951297ac scores 92.5%;
// the pool's struct-ification sweep and/or tools/store_order_search.py had
// rewritten this body in place and kept the worse result while the notes
// above stayed put.  Winner picked from 16 distinct committed bodies.
// Re-verify with tools/score_addrs.py before editing again.
#include "types.h"

extern f32 lbl_802AD768;
extern f64 lbl_802AD770;
extern f32 fn_8012570C(s32 hash, s32 flag);
extern void *fn_80003E0C(void *arg0, f32 farg1);
extern f32 fn_801417B8(void *obj, s32 hash);
extern s32 fn_800AA02C(void *obj);

void fn_801E1224(void *arg0) {
    struct fr_s {
        char mat[0x40];
        volatile f32 out[16];
        void *t1;
        void *dst;
        void *t2;
        void *dst2;
        char pad[8];
        union { u32 w[2]; f64 d; } cvt;
    } fr;
    s32 *ctl9;
    s32 *m;
    char *a;
    s32 ivar;
    s32 i;
    f32 f30v;
    f32 t1v;
    f32 t2v;
    f32 fv;
    void **p1;
    void **p2;
    f32 f94v;
    char *tp;
    register f32 v00 __asm__("fr26");
    register f32 v01 __asm__("fr29");
    register f32 v10 __asm__("fr27");
    register f32 v11 __asm__("fr30");
    register f32 v20 __asm__("fr31");
    register f32 v21 __asm__("fr28");
    f32 v30;
    f32 v31;
    f32 v02;
    f32 v03;
    f32 v12;
    f32 v13;
    f32 v22;
    f32 v23;
    f32 v32;
    f32 v33;

    ctl9 = *(s32 **)((char *)arg0 + 0x15BC);
    if (*(s32 *)((char *)ctl9 + 0xAC) != 0) {
        return;
    }
    if (*(s32 *)((char *)ctl9 + 0x118) != 0) {
        return;
    }
    if (*(s32 *)((char *)ctl9 + 0x40) != 0) {
        return;
    }
    m = *(s32 **)((char *)arg0 + 0x15A0);
    if (*(s32 *)((char *)m + 0x194) != 0) {
        return;
    }
    if (*(s32 *)((char *)m + 0x1B8) != 0) {
        return;
    }

    a = (char *)m + 0x28;
    f30v = lbl_802AD768;
    ivar = 0;
    if (*(s32 *)(a + 4) != 0) {
        f30v = fn_801417B8(*(void **)((char *)arg0 + 0xC), 0xCBFDD841);
        ivar = fn_800AA02C(a);
    }
    m = (s32 *)((char *)m + 0x4C);
    if (*(s32 *)((char *)m + 4) != 0) {
        f30v = -fn_801417B8(*(void **)((char *)arg0 + 0xC), 0xCBFDD841);
        ivar = fn_800AA02C((char *)m);
    }
    t1v = fn_8012570C(0x5F70EF46, 1);
    t2v = fn_8012570C(0x12CD2D14, 1);

    fr.cvt.w[1] = (u32)ivar ^ 0x80000000;
    fr.cvt.w[0] = 0x43300000;
    fv = (f32)(fr.cvt.d - lbl_802AD770);

    if (fv <= t1v) {
        return;
    }
    if (fv < t2v) {
        f30v = (f30v * (fv - t1v)) / (t2v - t1v);
    }

    m = (s32 *)*(char **)((char *)arg0 + 0xC);
    f94v = *(f32 *)((char *)arg0 + 0x94);
    for (i = 0; i < 4; i++) {
    }
    p1 = (void **)&fr.t1;
    a = (char *)arg0 + 0x20;
    m = (s32 *)((char *)m + 0x78);
    p2 = (void **)&fr.t2;
    fr.t1 = fn_80003E0C(&fr.mat[0], f30v * f94v);
    p1[1] = (char *)m;
    tp = fr.t1;
    fr.out[0] = *(f32 *)((char *)tp + 0) * *(f32 *)((char *)m + 0x00) +
                *(f32 *)((char *)tp + 4) * *(f32 *)((char *)m + 0x10) +
                *(f32 *)((char *)tp + 8) * *(f32 *)((char *)m + 0x20) +
                *(f32 *)((char *)tp + 0xC) * *(f32 *)((char *)m + 0x30);
    fr.out[1] = *(f32 *)((char *)tp + 0) * *(f32 *)((char *)m + 0x04) +
                *(f32 *)((char *)tp + 4) * *(f32 *)((char *)m + 0x14) +
                *(f32 *)((char *)tp + 8) * *(f32 *)((char *)m + 0x24) +
                *(f32 *)((char *)tp + 0xC) * *(f32 *)((char *)m + 0x34);
    fr.out[2] = *(f32 *)((char *)tp + 0) * *(f32 *)((char *)m + 0x08) +
                *(f32 *)((char *)tp + 4) * *(f32 *)((char *)m + 0x18) +
                *(f32 *)((char *)tp + 8) * *(f32 *)((char *)m + 0x28) +
                *(f32 *)((char *)tp + 0xC) * *(f32 *)((char *)m + 0x38);
    fr.out[3] = *(f32 *)((char *)tp + 0) * *(f32 *)((char *)m + 0x0C) +
                *(f32 *)((char *)tp + 4) * *(f32 *)((char *)m + 0x1C) +
                *(f32 *)((char *)tp + 8) * *(f32 *)((char *)m + 0x2C) +
                *(f32 *)((char *)tp + 0xC) * *(f32 *)((char *)m + 0x3C);
    fr.out[4] = *(f32 *)((char *)tp + 0x10) * *(f32 *)((char *)m + 0x00) +
                *(f32 *)((char *)tp + 0x14) * *(f32 *)((char *)m + 0x10) +
                *(f32 *)((char *)tp + 0x18) * *(f32 *)((char *)m + 0x20) +
                *(f32 *)((char *)tp + 0x1C) * *(f32 *)((char *)m + 0x30);
    fr.out[5] = *(f32 *)((char *)tp + 0x10) * *(f32 *)((char *)m + 0x04) +
                *(f32 *)((char *)tp + 0x14) * *(f32 *)((char *)m + 0x14) +
                *(f32 *)((char *)tp + 0x18) * *(f32 *)((char *)m + 0x24) +
                *(f32 *)((char *)tp + 0x1C) * *(f32 *)((char *)m + 0x34);
    fr.out[6] = *(f32 *)((char *)tp + 0x10) * *(f32 *)((char *)m + 0x08) +
                *(f32 *)((char *)tp + 0x14) * *(f32 *)((char *)m + 0x18) +
                *(f32 *)((char *)tp + 0x18) * *(f32 *)((char *)m + 0x28) +
                *(f32 *)((char *)tp + 0x1C) * *(f32 *)((char *)m + 0x38);
    fr.out[7] = *(f32 *)((char *)tp + 0x10) * *(f32 *)((char *)m + 0x0C) +
                *(f32 *)((char *)tp + 0x14) * *(f32 *)((char *)m + 0x1C) +
                *(f32 *)((char *)tp + 0x18) * *(f32 *)((char *)m + 0x2C) +
                *(f32 *)((char *)tp + 0x1C) * *(f32 *)((char *)m + 0x3C);
    fr.out[8] = *(f32 *)((char *)tp + 0x20) * *(f32 *)((char *)m + 0x00) +
                *(f32 *)((char *)tp + 0x24) * *(f32 *)((char *)m + 0x10) +
                *(f32 *)((char *)tp + 0x28) * *(f32 *)((char *)m + 0x20) +
                *(f32 *)((char *)tp + 0x2C) * *(f32 *)((char *)m + 0x30);
    fr.out[9] = *(f32 *)((char *)tp + 0x20) * *(f32 *)((char *)m + 0x04) +
                *(f32 *)((char *)tp + 0x24) * *(f32 *)((char *)m + 0x14) +
                *(f32 *)((char *)tp + 0x28) * *(f32 *)((char *)m + 0x24) +
                *(f32 *)((char *)tp + 0x2C) * *(f32 *)((char *)m + 0x34);
    fr.out[10] = *(f32 *)((char *)tp + 0x20) * *(f32 *)((char *)m + 0x08) +
                 *(f32 *)((char *)tp + 0x24) * *(f32 *)((char *)m + 0x18) +
                 *(f32 *)((char *)tp + 0x28) * *(f32 *)((char *)m + 0x28) +
                 *(f32 *)((char *)tp + 0x2C) * *(f32 *)((char *)m + 0x38);
    fr.out[11] = *(f32 *)((char *)tp + 0x20) * *(f32 *)((char *)m + 0x0C) +
                 *(f32 *)((char *)tp + 0x24) * *(f32 *)((char *)m + 0x1C) +
                 *(f32 *)((char *)tp + 0x28) * *(f32 *)((char *)m + 0x2C) +
                 *(f32 *)((char *)tp + 0x2C) * *(f32 *)((char *)m + 0x3C);
    fr.out[12] = *(f32 *)((char *)tp + 0x30) * *(f32 *)((char *)m + 0x00) +
                 *(f32 *)((char *)tp + 0x34) * *(f32 *)((char *)m + 0x10) +
                 *(f32 *)((char *)tp + 0x38) * *(f32 *)((char *)m + 0x20) +
                 *(f32 *)((char *)tp + 0x3C) * *(f32 *)((char *)m + 0x30);
    fr.out[13] = *(f32 *)((char *)tp + 0x30) * *(f32 *)((char *)m + 0x04) +
                 *(f32 *)((char *)tp + 0x34) * *(f32 *)((char *)m + 0x14) +
                 *(f32 *)((char *)tp + 0x38) * *(f32 *)((char *)m + 0x24) +
                 *(f32 *)((char *)tp + 0x3C) * *(f32 *)((char *)m + 0x34);
    fr.out[14] = *(f32 *)((char *)tp + 0x30) * *(f32 *)((char *)m + 0x08) +
                 *(f32 *)((char *)tp + 0x34) * *(f32 *)((char *)m + 0x18) +
                 *(f32 *)((char *)tp + 0x38) * *(f32 *)((char *)m + 0x28) +
                 *(f32 *)((char *)tp + 0x3C) * *(f32 *)((char *)m + 0x38);
    fr.out[15] = *(f32 *)((char *)tp + 0x30) * *(f32 *)((char *)m + 0x0C) +
                 *(f32 *)((char *)tp + 0x34) * *(f32 *)((char *)m + 0x1C) +
                 *(f32 *)((char *)tp + 0x38) * *(f32 *)((char *)m + 0x2C) +
                 *(f32 *)((char *)tp + 0x3C) * *(f32 *)((char *)m + 0x3C);

    ((__ps_t volatile *)m)[0] = ((__ps_t volatile *)&fr.out[0])[0];
    ((__ps_t volatile *)m)[1] = ((__ps_t volatile *)&fr.out[0])[1];
    ((__ps_t volatile *)m)[2] = ((__ps_t volatile *)&fr.out[0])[2];
    ((__ps_t volatile *)m)[3] = ((__ps_t volatile *)&fr.out[0])[3];
    ((__ps_t volatile *)m)[4] = ((__ps_t volatile *)&fr.out[0])[4];
    ((__ps_t volatile *)m)[5] = ((__ps_t volatile *)&fr.out[0])[5];
    ((__ps_t volatile *)m)[6] = ((__ps_t volatile *)&fr.out[0])[6];
    ((__ps_t volatile *)m)[7] = ((__ps_t volatile *)&fr.out[0])[7];

    for (i = 0; i < 4; i++) {
    }
    fr.t2 = fn_80003E0C(&fr.mat[0], f30v * *(f32 *)((char *)arg0 + 0x94));
    p2[1] = a;
    tp = fr.t2;
    v10 = *(f32 *)((char *)a + 0x10);
    v00 = *(f32 *)((char *)a + 0x00);
    v20 = *(f32 *)((char *)a + 0x20);
    v30 = *(f32 *)((char *)a + 0x30);
    v11 = *(f32 *)((char *)a + 0x14);
    v01 = *(f32 *)((char *)a + 0x04);
    fr.out[0] = *(f32 *)((char *)tp + 0) * v00 +
                *(f32 *)((char *)tp + 4) * v10 +
                *(f32 *)((char *)tp + 8) * v20 +
                *(f32 *)((char *)tp + 0xC) * v30;
    v21 = *(f32 *)((char *)a + 0x24);
    v31 = *(f32 *)((char *)a + 0x34);
    v12 = *(f32 *)((char *)a + 0x18);
    v02 = *(f32 *)((char *)a + 0x08);
    fr.out[1] = *(f32 *)((char *)tp + 0) * v01 +
                *(f32 *)((char *)tp + 4) * v11 +
                *(f32 *)((char *)tp + 8) * v21 +
                *(f32 *)((char *)tp + 0xC) * v31;
    v22 = *(f32 *)((char *)a + 0x28);
    v32 = *(f32 *)((char *)a + 0x38);
    v13 = *(f32 *)((char *)a + 0x1C);
    v03 = *(f32 *)((char *)a + 0x0C);
    fr.out[2] = *(f32 *)((char *)tp + 0) * v02 +
                *(f32 *)((char *)tp + 4) * v12 +
                *(f32 *)((char *)tp + 8) * v22 +
                *(f32 *)((char *)tp + 0xC) * v32;
    v23 = *(f32 *)((char *)a + 0x2C);
    v33 = *(f32 *)((char *)a + 0x3C);
    fr.out[3] = *(f32 *)((char *)tp + 0) * v03 +
                *(f32 *)((char *)tp + 4) * v13 +
                *(f32 *)((char *)tp + 8) * v23 +
                *(f32 *)((char *)tp + 0xC) * v33;
    fr.out[4] = *(f32 *)((char *)tp + 0x10) * v00 +
                *(f32 *)((char *)tp + 0x14) * v10 +
                *(f32 *)((char *)tp + 0x18) * v20 +
                *(f32 *)((char *)tp + 0x1C) * v30;
    fr.out[5] = *(f32 *)((char *)tp + 0x10) * v01 +
                *(f32 *)((char *)tp + 0x14) * v11 +
                *(f32 *)((char *)tp + 0x18) * v21 +
                *(f32 *)((char *)tp + 0x1C) * v31;
    fr.out[6] = *(f32 *)((char *)tp + 0x10) * v02 +
                *(f32 *)((char *)tp + 0x14) * v12 +
                *(f32 *)((char *)tp + 0x18) * v22 +
                *(f32 *)((char *)tp + 0x1C) * v32;
    fr.out[7] = *(f32 *)((char *)tp + 0x10) * v03 +
                *(f32 *)((char *)tp + 0x14) * v13 +
                *(f32 *)((char *)tp + 0x18) * v23 +
                *(f32 *)((char *)tp + 0x1C) * v33;
    fr.out[8] = *(f32 *)((char *)tp + 0x20) * v00 +
                *(f32 *)((char *)tp + 0x24) * v10 +
                *(f32 *)((char *)tp + 0x28) * v20 +
                *(f32 *)((char *)tp + 0x2C) * v30;
    fr.out[9] = *(f32 *)((char *)tp + 0x20) * v01 +
                *(f32 *)((char *)tp + 0x24) * v11 +
                *(f32 *)((char *)tp + 0x28) * v21 +
                *(f32 *)((char *)tp + 0x2C) * v31;
    fr.out[10] = *(f32 *)((char *)tp + 0x20) * v02 +
                 *(f32 *)((char *)tp + 0x24) * v12 +
                 *(f32 *)((char *)tp + 0x28) * v22 +
                 *(f32 *)((char *)tp + 0x2C) * v32;
    fr.out[11] = *(f32 *)((char *)tp + 0x20) * v03 +
                 *(f32 *)((char *)tp + 0x24) * v13 +
                 *(f32 *)((char *)tp + 0x28) * v23 +
                 *(f32 *)((char *)tp + 0x2C) * v33;
    fr.out[12] = *(f32 *)((char *)tp + 0x30) * v00 +
                 *(f32 *)((char *)tp + 0x34) * v10 +
                 *(f32 *)((char *)tp + 0x38) * v20 +
                 *(f32 *)((char *)tp + 0x3C) * v30;
    fr.out[13] = *(f32 *)((char *)tp + 0x30) * v01 +
                 *(f32 *)((char *)tp + 0x34) * v11 +
                 *(f32 *)((char *)tp + 0x38) * v21 +
                 *(f32 *)((char *)tp + 0x3C) * v31;
    fr.out[14] = *(f32 *)((char *)tp + 0x30) * v02 +
                 *(f32 *)((char *)tp + 0x34) * v12 +
                 *(f32 *)((char *)tp + 0x38) * v22 +
                 *(f32 *)((char *)tp + 0x3C) * v32;
    fr.out[15] = *(f32 *)((char *)tp + 0x30) * v03 +
                 *(f32 *)((char *)tp + 0x34) * v13 +
                 *(f32 *)((char *)tp + 0x38) * v23 +
                 *(f32 *)((char *)tp + 0x3C) * v33;

    ((__ps_t volatile *)a)[0] = ((__ps_t volatile *)&fr.out[0])[0];
    ((__ps_t volatile *)a)[1] = ((__ps_t volatile *)&fr.out[0])[1];
    ((__ps_t volatile *)a)[2] = ((__ps_t volatile *)&fr.out[0])[2];
    ((__ps_t volatile *)a)[3] = ((__ps_t volatile *)&fr.out[0])[3];
    ((__ps_t volatile *)a)[4] = ((__ps_t volatile *)&fr.out[0])[4];
    ((__ps_t volatile *)a)[7] = ((__ps_t volatile *)&fr.out[0])[7];
    ((__ps_t volatile *)a)[5] = ((__ps_t volatile *)&fr.out[0])[5];
    ((__ps_t volatile *)a)[6] = ((__ps_t volatile *)&fr.out[0])[6];
}
