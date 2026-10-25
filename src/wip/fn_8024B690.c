// WIP DRAFT (non-matching) — hand-rebuilt from disasm 2026-08-25
// family=m2c range=0x8024B690-0x8024BA9C size=1036B
// PARKED: tail clear window frozen as asm (~12 insns of 259) — same ProDG
// doloop wall as fn_8024AEF0/B208 ([li size reg][mfctr save][srwi][addi -1]
// [mtctr][stw peel][stwu bdnz][mtctr restore]); semantics =
// memset(*(arg0+0x10C)+off, 0, 0x80). Allocator cascade otherwise (see
// fn_8024B208 header WALL 2 — same disease, divergence from the prologue).
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 16.2% ([5]rev->16.2%).
#include "types.h"
#include "structs.h"
// FLAG: -fno-rerun-cse-after-loop
extern void fn_80251490(s32 dst, s32 a, s32 w, s32 x, s32 y, CStruct * src, s32 e);
extern void fn_8024C144(Unk_C7387A53 * obj, Unk_5B449B03 * a, CStruct * entry, s32 x, s32 y, CStruct * src, s32 flag);
extern void fn_802511DC(s32 a, s32 b, s32 c);
extern void fn_80250900(void * a, void * b, s32 c);
extern void fn_80250A1C(void * a, void * b, s32 c, u8 * d);
extern void fn_8024EF18(s32 a);
extern void fn_8024F65C(void * a, s32 b, s32 c, void * d, s32 e);
extern void fn_802502C0(s32 a, s32 b, s32 c, s32 d, s32 e);
extern void fn_8024FD90(Unk_5B449B03 * a, s32 b, s32 c);
extern s32 lbl_802B13A8[];

void fn_8024B690(Unk_891D1D72 *arg0, Unk_12004030 *arg1, s32 arg2, s32 arg3, u32 arg4, u32 arg5, s32 arg6) {
    volatile s32 sp8;
    volatile s32 spC;
    u8 mode;
    s32 dimW;
    s32 dimH;
    s32 sum;
    s32 mag;
    s32 qq;
    s32 res;
    u32 entryOff;
    u8 *entryBase;
    Unk_1D9F1A68 *texP;
    s32 texW;
    s32 dstY;
    s32 entry;
    s32 uvW;
    u32 i;
    u32 bit;
    s32 off;
    s32 clrSize;

    if (!(arg1->unk0xDC & 8)) {
        mode = *(u8 *)arg1;
        if (mode <= 1U) {
            sp8 = arg1->unk0x8;
            spC = arg1->unk0xC;
            if (sp8 & 3) {
                sp8 = (sp8 >> 1) | 1;
            } else {
                sp8 = sp8 / 2;
            }
            dimW = spC;
            if (dimW & 3) {
                dimW = (dimW >> 1) | 1;
            } else {
                dimW = dimW / 2;
            }
            spC = dimW;
        } else {
            sum = arg1->unk0x8 + arg1->unk0x10 + arg1->unk0x18 + arg1->unk0x20;
            if (sum != 0) {
                mag = sum < 0 ? -sum : sum;
                qq = mag / 16;
                res = lbl_802B13A8[mag % 16] + qq * 2;
                if (sum <= 0) {
                    res = -res;
                }
                sum = res;
            }
            sp8 = sum;
            sum = arg1->unk0xC + arg1->unk0x14 + arg1->unk0x1C + arg1->unk0x24;
            if (sum != 0) {
                mag = sum < 0 ? -sum : sum;
                qq = mag / 16;
                res = lbl_802B13A8[mag % 16] + qq * 2;
                if (sum <= 0) {
                    res = -res;
                }
                sum = res;
            }
            spC = sum;
        }
        entryOff = arg5 * 4;
        entryBase = (u8 *)arg0 + 0x10;
        texP = *((u8 * *)&arg0->unk0xC);
        dstY = arg3 * 0x10;
        texW = texP->unk0x4;
        entry = *(s32 *)(*(s32 *)(entryBase + entryOff) + 8);
        fn_80251490(texP->unk0x8, entry, texW, arg2 * 0x10, dstY, (void *)&sp8, arg0->unk0x48);
        fn_80251490(texP->unk0x8, entry, texW, arg2 * 0x10 + 8, dstY, (char *)arg1 + 0x10, arg0->unk0x48);
        uvW = texW >> 1;
        fn_80251490(texP->unk0x8, entry, texW, arg2 * 0x10, dstY + 8, (char *)arg1 + 0x18, arg0->unk0x48);
        fn_80251490(texP->unk0x8, entry, texW, arg2 * 0x10 + 8, dstY + 8, (char *)arg1 + 0x20, arg0->unk0x48);
        fn_80251490(*(s32 *)(*((u8 * *)&arg0->unk0xC) + 0xC), *(s32 *)(*(char *)(entryBase + entryOff) + 0xC), uvW, arg2 * 8, arg3 * 8, (void *)&sp8, arg0->unk0x48);
        fn_80251490(*(s32 *)(*((u8 * *)&arg0->unk0xC) + 0x10), *(s32 *)(*(char *)(entryBase + entryOff) + 0x10), uvW, arg2 * 8, arg3 * 8, (void *)&sp8, arg0->unk0x48);
    } else {
        entry = *(s32 *)((u8 *)arg0 + 0x10 + entryOff);
        entryOff = arg5 * 4;
        fn_8024C144(arg0, arg0->unk0xC, entry, arg2, arg3, (char *)arg1 + 8, arg6);
    }
    if (arg4 != 0) {
        i = 0;
        bit = 5;
        off = 0;
        clrSize = 0x80;
        do {
            if (arg4 & (1 << bit)) {
                {
                    char *clrP = (char *)(off + arg0->unk0x10C);
                    __asm__ __volatile__("mfctr 11; srwi 10,%1,2; addi 10,10,-1; mtctr 10; mr 9,%0; li 10,0; stw 10,0(9); .Lw4: stwu 10,4(9); bdnz .Lw4; mtctr 11"
                                         :
                                         : "r"(clrP), "r"(clrSize)
                                         : "r9", "r10", "r11", "cc", "ctr", "memory");
                }
                fn_802511DC(arg0->unk0x90, (s32)arg0 + 0xB4, arg0->unk0x94);
                if (arg0->unk0x4C == 0) {
                    fn_80250900(arg0->unk0x110 + off, arg0->unk0x10C + off, *(u8 *)arg1);
                } else {
                    fn_80250A1C(arg0->unk0x110 + off, arg0->unk0x10C + off, *(u8 *)arg1, arg0->unk0x5C);
                }
                fn_8024EF18(arg0->unk0x110 + (i << 6) + (i << 6));
            }
            i += 1;
            off += 0x80;
            bit -= 1;
        } while (i <= 5U);
        if ((arg0->unk0x84 == 0) || ((arg1->unk0xDC & 4) == 0)) {
            fn_8024F65C(arg0->unk0xC, arg2, arg3, arg0->unk0x110, arg4);
        } else {
            fn_802502C0(arg0->unk0xC, arg2, arg3, arg0->unk0x110, arg4);
        }
    }
    fn_8024FD90(arg0->unk0xC, arg2, arg3);
}
