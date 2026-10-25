// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003CF18-0x8003D318 (1024B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_803003F0[];
#include "qb_constants.h"
#include "structs.h"
void AddInteger(s32, s32, s32);
s32 GetInteger(CStruct *, void *, s32 *, void *);
s32 fn_8003ABA0(void *, void *);
s32 ContainsFlag(s32, s32);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
s32 fn_8003AB44(s32, s32);
bool fn_8003CF18(void) {
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 var_r27;
    s32 var_r28;
    s32 var_r30;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_3;
    s32 temp_r3_4;
    s32 temp_r3_6;
    s32 temp_r3_7;
    s32 var_r26;
    s32 var_r31;

    var_r26 = 1;
    var_r30 = QB_SKATER_M_HEAD;
    var_r28 = QB_SKATER_M_HANDS;
    var_r27 = QB_SKATER_M_LOWER_LEGS;
    var_r31 = fn_8003ABA0(*(s32 *)&lbl_803003F0, QB_SKATER_M_HEAD);
    if (var_r31 == 0) {
        var_r26 = 0;
        var_r30 = QB_SKATER_F_HEAD;
        var_r28 = QB_SKATER_F_HANDS;
        var_r27 = QB_SKATER_F_LOWER_LEGS;
        var_r31 = fn_8003ABA0(*(s32 *)&lbl_803003F0, QB_SKATER_F_HEAD);
        if (var_r31 == 0) {
            return false;
        }
    }
    if (GetInteger(var_r31, QB_H, &sp8, 0) != 0) {
        GetInteger(var_r31, QB_S, &spC, 0);
        GetInteger(var_r31, QB_V, &sp10, 0);
    } else {
        temp_r3 = fn_8003AB44(*(s32 *)&lbl_803003F0, var_r30);
        if (temp_r3 != 0) {
            GetInteger(temp_r3, QB_DEFAULT_H, &sp8, 1);
            GetInteger(temp_r3, QB_DEFAULT_S, &spC, 1);
            GetInteger(temp_r3, QB_DEFAULT_V, &sp10, 1);
        }
    }
    var_r31 = 0;
    sp14 = var_r31;
    if (var_r26 != 0) {
        temp_r3_2 = fn_8003ABA0(*(s32 *)&lbl_803003F0, QB_BARE_TORSO);
        if (temp_r3_2 != 0) {
            GetChecksum_2(temp_r3_2, QB_DESC_ID, &sp14, 1);
            if (sp14 != QB_NONE) {
                AddInteger(temp_r3_2, QB_H, sp8);
                AddInteger(temp_r3_2, QB_S, spC);
                AddInteger(temp_r3_2, QB_V, sp10);
                AddInteger(temp_r3_2, QB_USE_DEFAULT_HSV, 0);
            }
        }
    }
    temp_r3_3 = fn_8003ABA0(*(s32 *)&lbl_803003F0, var_r28);
    if (temp_r3_3 != 0) {
        GetChecksum_2(temp_r3_3, QB_DESC_ID, &sp14, 1);
        if (sp14 == QB_HANDS) {
            AddInteger(temp_r3_3, QB_H, sp8);
            AddInteger(temp_r3_3, QB_S, spC);
            AddInteger(temp_r3_3, QB_V, sp10);
            AddInteger(temp_r3_3, QB_USE_DEFAULT_HSV, 0);
        }
    }
    temp_r3_4 = fn_8003ABA0(*(s32 *)&lbl_803003F0, var_r27);
    if (temp_r3_4 != 0) {
        AddInteger(temp_r3_4, QB_H, sp8);
        AddInteger(temp_r3_4, QB_S, spC);
        AddInteger(temp_r3_4, QB_V, sp10);
        AddInteger(temp_r3_4, QB_USE_DEFAULT_HSV, 0);
    }
    var_r31 = fn_8003AB44(*(s32 *)&lbl_803003F0, QB_SHOES);
    if ((var_r31 != 0) && (ContainsFlag(var_r31, QB_BARE_FEET) != 0)) {
        temp_r3_6 = fn_8003ABA0(*(s32 *)&lbl_803003F0, QB_SHOES);
        if (temp_r3_6 != 0) {
            AddInteger(temp_r3_6, QB_H, sp8);
            AddInteger(temp_r3_6, QB_S, spC);
            AddInteger(temp_r3_6, QB_V, sp10);
            AddInteger(temp_r3_6, QB_USE_DEFAULT_HSV, 0);
        }
    }
    temp_r3_7 = fn_8003ABA0(*(s32 *)&lbl_803003F0, QB_BODY);
    if (temp_r3_7 != 0) {
        AddInteger(temp_r3_7, QB_H, sp8);
        AddInteger(temp_r3_7, QB_S, spC);
        AddInteger(temp_r3_7, QB_V, sp10);
        AddInteger(temp_r3_7, QB_USE_DEFAULT_HSV, 0);
    }
    return true;
}

