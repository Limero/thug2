// WIP DRAFT (non-matching) — hand-rebuilt from disasm 2026-08-25
// family=m2c range=0x8024AEF0-0x8024B208 size=792B
// PARKED 61% (masked; test_wip counts the two link-time bdnz addend words as
// diffs). Two walls + one allocator tie-break:
//
// WALL 1 — inline-expanded memset doloops (asm-frozen here, ~12% of insns).
// Retail clears arg1+8/0x20 bytes and *(arg0+0x10C)/0x300 bytes via the
// ProDG template [ptr birth][li SIZE][mfctr rS][srwi rT,rC,2][addi -1]
// [mtctr][mr copy][li 0][stw peel][stwu loop][bdnz][mtctr restore]. No plain-C
// shape reproduces it on ANY in-tree cc1 (3.5/3.5b140/3.7/3.8.1/3.9.3):
// constant-count loops always fold to [li N/4; mtctr] without wrapper;
// opaque-barrier/pinned counts kill the bct conversion instead (addic./bne).
// Retail's loop.c computed the CTR init from the size REGISTER w/o folding.
// 27 DOL sites share this template (0x80249xxx-0x80252xxx zone), none matched.
//
// WALL 2 — var_r31 recompute-vs-copy allocator tie-break (doc-15 class).
// Want recomputes `var_r31 = var_r24*2` after the plane block (add r31,r24,r24
// x2, no copies); every C shape tried yields a save/restore COPY pair
// (mr rN,r31 / mr r31,rN) instead, stealing one callee-saved reg and cascading
// ~10 home swaps (byteP/arg2/arg3/var_r20/arg4). -fno-gcse (kills the PRE
// merge) collapses the whole function (59%->0.5%); sched flags no-op.
// Tried: split flagBase web (want has TWO arg0+0x48 webs: pre-loop r18 for
// F2C lookup + block-inline), volatile &sp8 (fixed &sp8-homing cascade!),
// u8* byteP (extsb fix), var_r5->r5 pin (arg-reg remat), expression
// differentiation, planeP r18 pin (conflicts with arg4 home).
//
// FIXED along the way: subfic/adde bool = `(idx <= 3)` materialized (u32 idx);
// cr4 long-range arg4 test + mtcrf 8 epilogue fall out naturally; lhz@0x4C /
// lwz@0x24 / lbz loads / sthx store widths; slwi (t<<1 not t*2); frame 0x60
// via one volatile s32 out-param + three "m"-pinned pads (volatile scalars
// cost 8B slots each!). Semantics of frozen windows:
// memset(arg1+8, 0, 0x20); memset(*(arg0+0x10C), 0, 0x300).
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"
extern s32 fn_80250EAC(CStruct * arg, s32 val);
extern void fn_80250E6C(CStruct * arg, s32 val);
extern s32 fn_80250AC4(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s16 * h);
extern s32 fn_8024C88C(Unk_C7387A53 * a, s32 b);
extern s32 fn_8024D480(Unk_C7387A53 * a, s32 b);
extern void fn_80250F2C(s32 a, void * b, s32 c, void *d, void * e);
extern void fn_8024DB0C(Unk_5B449B03 * a, void *b, Unk_5B449B03 * c, s32 d, s32 e);
extern void fn_8025085C(void * a, void * b, s32 c, s32 d);
extern void fn_8025097C(void * a, void * b, s32 c, s32 d, u8 * e);
extern void fn_8024EF18(s32 a);
extern void fn_8024F2AC(s32 a, s32 b, s32 c, s32 d);
extern void fn_8024FE30(s32 a, s32 b, s32 c, s32 d);

void fn_8024AEF0(Unk_804E7039 *arg0, Unk_12004030 *arg1, s32 arg2, s32 arg3, s8 arg4, u32 arg5, u32 arg6) {
    volatile s32 sp8;
    s32 spPadA;
    s32 spPadB;
    s32 spPadC;

    u8 *byteP;
    u32 t;
    s32 big;
    s32 w;
    u16 width;
    register s32 var_r5 __asm__("r5");
    s32 temp_r3;
    s32 var_r28;
    s32 var_r31;
    u8 *flagBase;
    u32 var_r25;
    s32 var_r20;
    s32 var_r24;

    __asm__("" : : "m"(sp8), "m"(spPadA), "m"(spPadB), "m"(spPadC));
    if (arg0->unk0x84 != 0) {
        if (fn_80250EAC((char *)arg0 + 0x30, 1) != 0) {
            arg1->unk0xDC |= 4;
        }
    }
    {
        register s32 p11 __asm__("r11");
        p11 = (s32)((char *)arg1 + 8);
        __asm__ __volatile__("li 9,0x20; mfctr 7; srwi 6,9,2; addi 6,6,-1; mtctr 6; mr 8,%0; li 6,0; stw 6,0(8);.Lw1: stwu 6,4(8); bdnz .Lw1; mtctr 7"
                             :
                             : "r"(p11)
                             : "r9", "r6", "r8", "cc", "ctr", "memory");
    }
    {
        register s32 t10 __asm__("r10");
        t10 = arg0->unk0x10C;
        __asm__ __volatile__("li 9,0x300; mfctr 8; srwi 7,9,2; addi 7,7,-1; mtctr 7; mr 11,%0; li 7,0; stw 7,0(11);.Lw2: stwu 7,4(11); bdnz .Lw2; mtctr 8"
                             :
                             : "r"(t10)
                             : "r9", "r7", "r11", "cc", "ctr", "memory");
    }
    byteP = (char *)arg1 + 2;
    var_r25 = 0U;
    var_r20 = 0;
    var_r24 = 0;
    do {
        t = arg1->unk0x1;
        big = (var_r25 <= 3);
        if (t - 1 <= 3) {
            w = 8;
        } else if ((t <= 0x18U) && (big == 0)) {
            w = (t + 0xD) >> 1;
        } else if (t <= 8U) {
            w = t << 1;
        } else if (t <= 0x18U) {
            w = t + 8;
        } else if (big != 0) {
            w = (u16)((t * 2) - 0x10);
        } else {
            w = (u16)(t - 6);
        }
        width = (u16)w;
        fn_80250AC4(arg0->unk0x24, arg2, arg3, arg0->unk0x4, var_r25, arg1->unk0x1, width, &sp8);
        if (arg4 != 0) {
            byteP[var_r25] = arg4;
        }
        var_r5 = 0;
        var_r31 = var_r24 * 2;
        if (arg6 < arg0->unk0x54) {
            void *planeP = (char *)arg0 + 0x48;
            temp_r3 = fn_8024C88C(planeP, var_r25 <= 3);
            if (temp_r3 != 0) {
                var_r28 = fn_8024D480(planeP, temp_r3);
            } else {
                var_r28 = 0;
            }
            if (temp_r3 > 8) {
                fn_80250E6C((char *)arg0 + 0x30, 1);
            }
            var_r5 = 1;
            var_r31 = var_r24 + var_r24;
            *(u16 *)(var_r20 + arg0->unk0x10C) = var_r28;
        }
        if (arg5 & (1 << (5 - var_r25))) {
            fn_80250F2C(((Unk_1D62F22E_2 *)flagBase)->unk0x44, var_r31 + arg0->unk0x10C, var_r5, (char *)arg0 + 0xA0, *(s32 *)((char *)arg0 + (s32)0x94 + (byteP[var_r25] << 2)));
        }
        fn_8024DB0C(&sp8, arg1, arg0->unk0x10C + var_r31, var_r25, width);
        if (arg0->unk0x4C == 0) {
            fn_8025085C(arg0->unk0x110 + var_r31, arg0->unk0x10C + var_r31, arg1->unk0x1, width);
        } else {
            fn_8025097C(arg0->unk0x110 + var_r31, arg0->unk0x10C + var_r31, arg1->unk0x1, width, arg0->unk0x58);
        }
        var_r25 += 1;
        var_r20 += 0x80;
        var_r24 += 0x40;
        fn_8024EF18(arg0->unk0x110 + var_r31);
    } while (var_r25 <= 5U);
    if ((arg0->unk0x84 == 0) || ((arg1->unk0xDC & 4) == 0)) {
        fn_8024F2AC(arg0->unk0xC, arg2, arg3, arg0->unk0x110);
    } else {
        fn_8024FE30(arg0->unk0xC, arg2, arg3, arg0->unk0x110);
    }
}
