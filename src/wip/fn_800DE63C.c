// PARKED 2026-10-21: 68.75% (192B exact). Body is structurally right: one-shot
// vcall when unk0x1C==0, then a 2-iteration 0xC-stride do-while over the
// timer/unk0x38 slots. Residual clusters, all allocator/addressing ties:
//  (a) pre-header order: want lis(timer base),li r25,addi slot,li off vs got
//      addi slot,li off,lis,li (the lis/lo pair reads as 0 in the .o relocs);
//  (b) lwzx/stwx operand order: want (index,base), got (base,index) — the same
//      commutative sum, but the encoding's rA/rB roles are flipped;
//  (c) want cmpwi r27,0 vs got mr r0,r27;cmpwi r0,0 (exit test copies the
//      counter). Tried pointer-walk + off, (char*)arg0+0x20+off, int counter
//      and do/while(idx--!=0) forms; (b) and (c) survive all of them.
// family=m2c range=0x800DE63C-0x800DE6FC size=192B
// INERT: not registered in splits.txt/configure.py — never compiled.
#include "types.h"
typedef struct { char pad0x0[0x40]; s16 unk0x40; char pad0x42[0x2]; void *unk0x44; } V_DE63C;
typedef struct { char pad0x0[0x18]; V_DE63C *unk0x18; s32 unk0x1C; char pad0x20[0x18]; s32 unk0x38; } A_DE63C;
s32 Tmr_GetTime(void);
void fn_8000C5D8(s32, s32, s32);
extern s32 lbl_80303150;
void fn_800DE63C(A_DE63C *arg0) {
    s32 idx;
    char *base;
    char *slot;
    s32 off;

    if (arg0->unk0x1C == 0) {
        V_DE63C *vt = arg0->unk0x18;
        ((void (*)(void *, s32))vt->unk0x44)((char *)arg0 + vt->unk0x40, 1);
        return;
    }

    idx = 1;
    base = (char *)arg0 + 0x20;
    slot = (char *)arg0 + 0x34;
    off = 0xC;
    do {
        if (*(s32 *)(off + base) != 0) {
            s32 prev = *(s32 *)(slot - 4);
            if ((u32)((lbl_80303150 + Tmr_GetTime()) - prev) >= *(u32 *)slot) {
                fn_8000C5D8(arg0->unk0x38, idx, 0);
                *(s32 *)(off + base) = 0;
            }
        }
        slot -= 0xC;
        off -= 0xC;
    } while (idx-- != 0);
}
