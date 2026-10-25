// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020773C-0x80207990 (596B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "qb_constants.h"

s32 fn_800145AC();
void fn_80207080(Unk_90685748 *, s32);
void fn_8020740C(void *, s32 *);

bool fn_8020773C(Unk_90685748 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp8;
    s32 mask;
    s32 i;
    s32 state;
    s32 found;
    s32 num;
    s32 off;
    s32 qq;
    char *p;
    char *bp;
    s32 t;
    u32 lim;
    void *base2;
    s32 id;
    s32 typ;

    lim = 0x3E8U;
    sp8 = arg1;
    i = 0;
    mask = -1;
    state = 0;
    num = arg0->unk0x99E;
    found = 0;
    if (i < arg0->unk0x99C) {
        qq = num * 0x18 + 0x4C;
        off = num * 0x18;
        p = (char *)qq + (s32)arg0;
        do {
            __asm__ volatile("addi %0,%1,0x3c" : "=r"(bp) : "r"(arg0));
            t = *(s32 *)((char *)bp + off);
            if ((u32)(fn_800145AC() - t) >= lim) {
                goto ret0;
            }
            if (arg2 == 0) {
                switch (state) {
                case 0:
                    if (!(((CStruct *)p)->unk0x4 & mask) && (*(s32 *)((char *)p + -0xC) == 2) && (*(s32 *)((char *)p + -8) == sp8)) {
                        ((CStruct *)p)->unk0x0 = 1;
                        state = 1;
                    }
                    break;
                case 1:
                    if (!(((CStruct *)p)->unk0x4 & mask) && (*(s32 *)((char *)p + -0xC) == 1) && (*(s32 *)((char *)p + -8) == sp8)) {
                        ((CStruct *)p)->unk0x0 = state;
                        if (arg3 != 0) {
                            fn_80207080(arg0, -1);
                            fn_8020740C(arg0, &sp8);
                        }
                        return true;
                    }
                    break;
                }
            } else {
                switch (state) {
                case 0:
                    id = *(s32 *)((char *)p + -8);
                    base2 = (char *)arg0 + 0x44;
                    if (((id == QB_TRIANGLE) || (id == QB_CIRCLE) || (id == QB_SQUARE))
                        && !(((CStruct *)p)->unk0x4 & mask)
                        && (*(s32 *)((char *)p + -0xC) == 2)
                        && (*(s32 *)((char *)base2 + off) == sp8)) {
                        ((CStruct *)p)->unk0x0 = 1;
                        state = 1;
                        found = *(s32 *)((char *)base2 + off);
                    }
                    break;
                case 1:
                    if (!(((CStruct *)p)->unk0x4 & mask) && (*(s32 *)((char *)p + -0xC) == 1) && (*(s32 *)((char *)p + -8) == found)) {
                        ((CStruct *)p)->unk0x0 = state;
                        state = 2;
                    }
                    break;
                case 2:
                    if (!(((CStruct *)p)->unk0x4 & mask) && ((typ = *(s32 *)((char *)p + -0xC)) == 1) && (*(s32 *)((char *)p + -8) == sp8)) {
                        ((CStruct *)p)->unk0x0 = typ;
                        if (arg3 != 0) {
                            fn_80207080(arg0, -1);
                            fn_8020740C(arg0, &sp8);
                        }
                        return true;
                    }
                    break;
                }
            }
            p -= 0x18;
            off -= 0x18;
            num -= 1;
            if (num < 0) {
                p += 0x960;
                off += 0x960;
                num += 100;
            }
            i += 1;
        } while (i < arg0->unk0x99C);
    }
ret0:
    return false;
}
