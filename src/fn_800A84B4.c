// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A84B4-0x800A856C (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_802981EC;
extern char lbl_802981F0[];
extern char lbl_80298240[];

typedef struct {
    char pad0x0[0x18];
    s32 unk0x18;
    char pad0x1C[0x4];
    f32 unk0x20;
    f32 unk0x24;
    f32 unk0x28;
    f32 unk0x2C;
    f32 unk0x30;
    f32 unk0x34;
    f32 unk0x38;
    f32 unk0x3C;
    char pad0x40[0x10];
    f32 unk0x50;
    f32 unk0x54;
    f32 unk0x58;
    f32 unk0x5C;
    char pad0x60[0x10];
    f32 unk0x70;
    char pad0x74[0xC];
    f32 unk0x80;
    char pad0x84[0xC];
    f32 unk0x90;
    char pad0x94[0x60];
    s32 unk0xF4;
} A84B4Obj;

typedef struct {
    char pad0x0[0x20];
    f32 unk0x20;
    f32 unk0x24;
    f32 unk0x28;
    f32 unk0x2C;
} A84B4SubA;

typedef struct {
    char pad0x0[0x4];
    f32 unk0x4;
    f32 unk0x8;
    f32 unk0xC;
} A84B4SubB;

void *fn_800A84B4(A84B4Obj *arg0, s32 arg1) {
    f32 temp_f0;
    f32 temp_f13;
    s32 var_ctr;
    A84B4SubA *temp_r11;
    A84B4SubB *temp_r10;
    A84B4SubB *temp_r9;
    A84B4SubB *temp_r8;

    arg0->unk0xF4 = (s32)lbl_80298240;
    for (var_ctr = 0; var_ctr < 4; var_ctr++) { __asm__ volatile("" ::: "memory"); }
    *(volatile s32 *)&arg0->unk0x18 = arg1;
    temp_r11 = (A84B4SubA *)((char *)arg0 + 0x20);
    temp_f13 = lbl_802981EC;
    temp_r10 = (A84B4SubB *)((char *)arg0 + 0x70);
    temp_r9 = (A84B4SubB *)((char *)arg0 + 0x90);
    temp_r8 = (A84B4SubB *)((char *)arg0 + 0x80);
    arg0->unk0x20 = temp_f13;
    temp_f0 = *(f32 *)lbl_802981F0;
    arg0->unk0x34 = temp_f13;
    arg0->unk0x24 = temp_f0;
    arg0->unk0x28 = temp_f0;
    arg0->unk0x2C = temp_f0;
    arg0->unk0x30 = temp_f0;
    arg0->unk0x38 = temp_f0;
    arg0->unk0x3C = temp_f0;
    temp_r11->unk0x20 = temp_f0;
    temp_r11->unk0x24 = temp_f0;
    temp_r11->unk0x28 = temp_f13;
    temp_r11->unk0x2C = temp_f0;
    arg0->unk0x50 = temp_f0;
    arg0->unk0x54 = temp_f0;
    arg0->unk0x58 = temp_f0;
    arg0->unk0x5C = temp_f13;
    arg0->unk0x70 = temp_f0;
    temp_r10->unk0x4 = temp_f0;
    temp_r10->unk0x8 = temp_f0;
    temp_r10->unk0xC = temp_f13;
    arg0->unk0x90 = temp_f0;
    temp_r9->unk0x4 = temp_f0;
    temp_r9->unk0x8 = temp_f0;
    temp_r9->unk0xC = temp_f13;
    arg0->unk0x80 = temp_f0;
    temp_r8->unk0x4 = temp_f0;
    temp_r8->unk0x8 = temp_f0;
    temp_r8->unk0xC = temp_f13;
    return arg0;
}
