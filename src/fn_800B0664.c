// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B0664-0x800B0780 (284B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
s32 GetChecksum_2(s32, s32, void *, s32);
s32 GetFloat(s32, s32, f32 *, s32);
void fn_800F078C(void *, void *);
s32 fn_800B08A4(s32, s32);
s32 fn_800F0F84(s32, s32);
void fn_800071D4(s32);
s32 Mem_NewZero(s32);
void *fn_800546A0(s32);
s32 fn_800B0844(s32);
void fn_800B0DB0(s32, void *, void *);
extern s32 lbl_80301B08;
typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    char pad0x8[0x20];
    s32 unk0x28;
    s32 unk0x2C;
    f32 unk0x30;
    f32 unk0x34;
    s32 unk0x38;
    char pad0x3C[0x2C];
} B0664Struct;
void fn_800B0664(s32 arg0, s32 arg1) {
    s32 sp8;
    f32 temp_f0;
    s32 temp_r28;
    s32 temp_r30;
    void *temp_r3;
    temp_r3 = Mem_NewZero(0x68);
    temp_r28 = temp_r3 + 4;
    fn_800071D4(temp_r3 + 0x40);
    ((B0664Struct *)temp_r3)->unk0x28 = arg1;
    ((B0664Struct *)temp_r3)->unk0x4 = arg0;
    ((B0664Struct *)temp_r3)->unk0x38 = 0;
    ((B0664Struct *)temp_r3)->unk0x2C = 2;
    GetChecksum_2(temp_r30 = fn_800F0F84(arg0, 1), QB_NAME, temp_r28, 0);
    fn_800B0DB0(lbl_80301B08, temp_r28, temp_r3);
    if (GetChecksum_2(temp_r30, QB_TYPE, &sp8, 0) != 0) {
        ((B0664Struct *)temp_r3)->unk0x2C = fn_800B0844(sp8);
    }
    fn_800B08A4(temp_r3, fn_800546A0(((B0664Struct *)temp_r3)->unk0x4));
    fn_800F078C(temp_r30, temp_r3 + 8);
    GetFloat(temp_r30, QB_RADIUS, temp_r3 + 0x30, 0);
    temp_f0 = ((B0664Struct *)temp_r3)->unk0x30;
    ((B0664Struct *)temp_r3)->unk0x34 = temp_f0 * temp_f0;
    GetChecksum_2(temp_r30, QB_TRIGGERSCRIPT, temp_r3 + 0x64, 0);
}
