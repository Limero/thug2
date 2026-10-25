// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018E8C8-0x8018EA28 (352B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
typedef struct { char pad0x0[0x18C]; f32 unk0x18C; } Unk_Sk8;
Unk_Sk8 *GetChecksum_3(s32, s32);
s32 fn_801745B4(s32);
void AddInteger(s32, s32, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 lbl_80305EAC;
bool fn_8018E8C8(Unk_C8FEE62D *arg0) {
    s32 spC;
    s32 sp8;
    s32 temp_r28;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r3;
    s32 var_r30;
    Unk_89391A04 *temp_r9;

    temp_r9 = (Unk_89391A04 *)arg0->unk0x14;
    temp_r3 = temp_r9->unk0x9C((char *)arg0 + temp_r9->unk0x98);
    if (temp_r3 == 0) {
        sp8 = temp_r3;
        GetInteger((CStruct *)arg0->unk0x20, QB_MINIGAME_RECORD, &sp8, 0);
        temp_r30 = fn_801745B4(lbl_80305EAC);
        spC = 0x2710;
        GetInteger((CStruct *)arg0->unk0x20, QB_START_HEIGHT, &spC, 0);
        var_r30 = (s32)GetChecksum_3(temp_r30, QB_SKATERSTATE)->unk0x18C - spC;
        if (var_r30 < 0) {
            var_r30 = 0;
        }
        temp_r29 = var_r30 / 12;
        temp_r28 = var_r30 % 12;
        AddInteger(arg0->unk0x20, QB_CURRENT_HEIGHT_FEET, temp_r29);
        AddInteger(arg0->unk0x20, QB_CURRENT_HEIGHT_INCHES, temp_r28);
        if (var_r30 > sp8) {
            AddInteger(arg0->unk0x20, QB_MINIGAME_RECORD, var_r30);
            AddInteger(arg0->unk0x20, QB_RECORD_FEET, temp_r29);
            AddInteger(arg0->unk0x20, QB_RECORD_INCHES, temp_r28);
            return true;
        }
        goto block_5;
    }
block_5:
    return false;
}
