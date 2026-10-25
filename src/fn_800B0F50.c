// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B0F50-0x800B1164 (532B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

s32 Mem_NewZero(s32);
void fn_800071D4(s32);
s32 fn_800F0F84(s32, s32);
s32 fn_800546A0(s32);
s32 fn_800A398C(s32, s32);
s32 fn_800B14C0(s32);
s32 fn_800B1550(s32);
void fn_800B15B0(s32, s32);
void fn_800B16FC(s32, s32);
void fn_800F078C(s32, s32);
s32 GetChecksum_2(s32, s32, s32 *, s32);
s32 GetFloat(s32, s32, f32 *, s32);
s32 ContainsFlag(s32, s32);

extern s32 lbl_80301A38;
extern s32 lbl_80301B0C;

// File-local layout: 0x74 (radius) and 0x78 (radius^2) are floats.
typedef struct Unk_B0F50 {
    s32 unk0x0;
    s32 unk0x4;
    char pad0x8[0x50];
    s32 unk0x58;
    s32 unk0x5C;
    s32 unk0x60;
    s32 unk0x64;
    s32 unk0x68;
    s32 unk0x6C;
    s32 unk0x70;
    f32 unk0x74;
    f32 unk0x78;
    s32 unk0x7C;
    char pad0x80[0x24];
    s32 unk0xA4;
    s32 unk0xA8;
} Unk_B0F50;

void fn_800B0F50(s32 arg0, s32 arg1) {
    s32 sp8;
    s32 spC;
    s32 zero;
    u32 ctr;
    s32 temp_r30;
    s32 var_r30;
    s32 temp_r3;
    void *temp_r11;
    Unk_B0F50 *temp_r31;
    s32 node;
    f32 rad;

    ctr = 4;
    temp_r31 = (Unk_B0F50 *)Mem_NewZero(0xB0);
    do {
        ctr -= 1;
    } while (ctr != 0);
    fn_800071D4((s32)temp_r31 + 0x80);
    zero = 0;
    temp_r11 = *(void **)&lbl_80301B0C;
    temp_r31->unk0xA8 = *(s32 *)((char *)temp_r11 + 4);
    *(s32 *)((char *)temp_r11 + 4) = (s32)temp_r31;
    temp_r31->unk0x4 = arg0;
    temp_r31->unk0x58 = arg1;
    temp_r31->unk0x7C = zero;
    temp_r31->unk0x70 = zero;
    temp_r30 = fn_800F0F84(arg0, 1);
    GetChecksum_2(temp_r30, QB_NAME, (s32 *)((char *)temp_r31 + 4), 0);
    if (GetChecksum_2(temp_r30, QB_SHAPE, &sp8, 0) != 0) {
        temp_r31->unk0x70 = fn_800B14C0(sp8);
    }
    fn_800B16FC((s32)temp_r31, fn_800546A0(temp_r31->unk0x4));
    fn_800F078C(temp_r30, (s32)temp_r31 + 8);
    temp_r31->unk0x6C = zero;
    if (GetChecksum_2(temp_r30, QB_TYPE, &spC, (spC = zero, 0)) != 0) {
        temp_r31->unk0x6C = fn_800B1550(spC);
    }
    GetFloat(temp_r30, QB_RADIUS, &temp_r31->unk0x74, 0);
    rad = temp_r31->unk0x74;
    temp_r31->unk0x78 = rad * rad;
    GetChecksum_2(temp_r30, QB_TRIGGERSCRIPT, (s32 *)((char *)temp_r31 + 0xA4), 0);
    temp_r31->unk0x5C = zero;
    temp_r31->unk0x60 = zero;
    temp_r31->unk0x64 = zero;
    temp_r3 = ContainsFlag(temp_r30, QB_PROXIMOBJECT);
    if (temp_r3 != 0) {
        temp_r31->unk0x68 = -1;
        GetChecksum_2(temp_r30, QB_NAME, (s32 *)((char *)temp_r31 + 0x5C), 0);
        return;
    }
    temp_r31->unk0x68 = temp_r3;
    temp_r31->unk0x58 = 1;
    var_r30 = 0;
    goto walk_test;
walk_body:
    if (*(s32 *)((char *)node + 0xC8) != 0) {
        temp_r31->unk0x64 |= 1 << var_r30;
    }
    var_r30 += 1;
walk_test:
    node = fn_800A398C(lbl_80301A38, var_r30);
    if ((node != 0) && (var_r30 <= 0x1F)) {
        goto walk_body;
    }
    fn_800B15B0((s32)temp_r31, 0);
    fn_800B15B0((s32)temp_r31, arg1);
}
