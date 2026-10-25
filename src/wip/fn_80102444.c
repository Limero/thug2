// WIP DRAFT — hand-rebuilt from want disasm 2026-10-11.
// family=m2c range=0x80102444-0x80102548 size=260B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// WANT decode (65 words, ProDG stwu-first leaf, no calls, no frame):
//   arg0->0xC = lbl_8029C868, then scalar copies (word@0, u16@4, u8@6,
//   word@8), arg0->0xC = lbl_8029C548 (yes, twice — both stores present),
//   ps-pair copies at +0x10/+0x18 (as +16/+24 byte offsets), empty ctr loop,
//   8x ps-pair block arg1+0x20 -> arg0+0x20, empty ctr loop, 8x ps-pair
//   block arg1+0x60 -> arg0+0x60, word@0xA0, return arg0 (mr r3,r7 at end).
// Block pointers: r8=arg0+0x20 / r10=arg1+0x20 computed EARLY (assigned
// right after the first store), r11=arg0+0x60 / r9=arg1+0x60 MID (assigned
// after loop 2). Delay loops are empty `for (i=0;i<4;i++){}`.
// PARKED 23.81% (was 7.7% m2c; size 252B vs 260B, -2 words). Gains this
// round: typed struct (u16@4/u8@6 already right in shared header), staged
// t8 temp reproduces the C548-store split between the 8-load/store, decl
// order reproduces the early/mid block-pointer windows.
// WALLS (all measured, plain C only — no asm per policy):
//  (a) HOME ROTATION: want arg0=r7/d20=r8/s20=r10, got arg0=r10/d20=r7/
//      s20=r8 (every access word shifts). Moving the d20/s20 assignments
//      after the first store did NOT move the home; the r7-vs-r10 pick for
//      the long-lived arg0 is not source-reachable. (~40 words)
//  (b) LOOP WINDOWS (recipe 92 class): want bdnz-to-self at +0x5C/+0xB0
//      with li/mtctr hoisted far above; got sinks block code into the
//      window and re-points bdnz forward (+0x5C/+0xA8 disp). The recipe-131
//      fix needs volatile-asm + register pins — not used here.
//  (c) -2 words: one loop's setup merged (suspected empty-loop deletion +
//      re-point; both li/mtctr pairs still present, so likely the missing
//      words are elsewhere — needs an alignment diff).
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

extern char lbl_8029C548[];
extern char lbl_8029C868[];

void *fn_80102444(Unk_FFCFB14C *arg0, Unk_FFCFB14C *arg1) {
    __ps_t *d20;
    __ps_t *s20;
    __ps_t *d60;
    __ps_t *s60;
    s32 t8;
    s32 i;

    arg0->unk0xC = (s32)lbl_8029C868;
    d20 = (__ps_t *)((char *)arg0 + 0x20);
    arg0->unk0x0 = arg1->unk0x0;
    s20 = (__ps_t *)((char *)arg1 + 0x20);
    arg0->unk0x4 = arg1->unk0x4;
    arg0->unk0x6 = arg1->unk0x6;
    t8 = arg1->unk0x8;
    arg0->unk0xC = (s32)lbl_8029C548;
    arg0->unk0x8 = t8;
    ((__ps_t *)arg0)[2] = ((__ps_t *)arg1)[2];
    ((__ps_t *)arg0)[3] = ((__ps_t *)arg1)[3];
    for (i = 0; i < 4; i++) {
    }
    d20[0] = s20[0];
    d20[1] = s20[1];
    d20[2] = s20[2];
    d20[3] = s20[3];
    d20[4] = s20[4];
    d20[5] = s20[5];
    d20[6] = s20[6];
    d20[7] = s20[7];
    for (i = 0; i < 4; i++) {
    }
    d60 = (__ps_t *)((char *)arg0 + 0x60);
    s60 = (__ps_t *)((char *)arg1 + 0x60);
    d60[0] = s60[0];
    d60[1] = s60[1];
    d60[2] = s60[2];
    d60[3] = s60[3];
    d60[4] = s60[4];
    d60[5] = s60[5];
    d60[6] = s60[6];
    d60[7] = s60[7];
    arg0->unk0xA0 = arg1->unk0xA0;
    return arg0;
}
