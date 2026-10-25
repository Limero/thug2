// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801899F8-0x80189D68 (880B). Byte-identical.
#include "types.h"
extern char lbl_80305EAC[];
extern char lbl_80305EFC[];
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 fn_80128978(s32, s32);
extern s32 fn_801A5DAC(s32, s32);
extern s32 fn_80174A58(void *, CStruct *);
extern s32 fn_801A568C(s32, s32);
extern s32 ContainsFlag(CStruct *, s32);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 GetStructure(s32, s32);
extern s32 GetStructure_2(CStruct *, s32, s32 *, s32);
extern s32 fn_801281BC(s32, s32, void *, s32);
extern void AddString(CStruct *, s32, void *);
extern s32 AddChecksum(CStruct *, s32, s32);
extern s32 GetArray(CStruct *, s32, s32 *, s32);
extern s32 GetChecksum(CStruct *, s32);
extern s32 fn_801259C8(s32, s32);
extern s32 fn_80129528(CStruct *, s32);
extern s32 GetString(CStruct *, s32 *, s32 *, s32);
extern s32 AddInteger(CStruct *, s32, s32);
extern s32 fn_801A5388(s32);
extern s32 s_find_trick_in_mapping(void *, void *, s32);

bool ScriptGoalManager_GetTrickFromKeyCombo(s32 arg0, CScript *arg1) {
    s32 sp8[16]; /* [&iter, spC, sp10, sp14, sp18, sp1C..sp44] */
    s32 var_r28;
    s32 var_r29;
    s32 temp_r30;
    s32 temp_r3;
    s32 temp_r3_2;

    GetChecksum_2(arg0, QB_KEY_COMBO, &sp8[4], 1);
    if (fn_80128978(arg0, QB_PROFILE) != 0) {
        GetChecksum_2(arg0, QB_PROFILE, &sp8[5], 1);
        var_r29 = fn_801A5DAC(*(s32 *)&lbl_80305EFC, sp8[5]);
    } else {
        var_r29 = fn_80174A58(*(s32 *)&lbl_80305EAC, 0);
    }
    temp_r30 = fn_801A568C(var_r29, QB_TRICK_MAPPING);
    if (ContainsFlag(arg0, QB_SPECIAL) == 0) {
        arg0 = GetInteger(temp_r30, sp8[4], &sp8[6], 0);
        if (arg0 != 0) {
            AddInteger(arg1->unk0x18, QB_CAT_NUM, sp8[6]);
            return true;
        }
        if (GetChecksum_2(temp_r30, sp8[4], &sp8[7], 0) == 0) {
            return false;
        }
        if (sp8[7] == -QB_UNKNOWN_0x09F36F70) {
            return false;
        }
        GetStructure_2(GetStructure(sp8[7], 1), QB_PARAMS, &sp8[8], 1);
        fn_801281BC(sp8[8], QB_NAME, &sp8[9], 1);
        AddString(arg1->unk0x18, QB_TRICK_STRING, sp8[9]);
        AddChecksum(arg1->unk0x18, QB_TRICK_CHECKSUM, sp8[7]);
        sp8[10] = arg0;
        if ((GetChecksum_2(sp8[8], QB_EXTRATRICKS, &sp8[10], 0) == 0) && (GetArray(sp8[8], QB_EXTRATRICKS, &sp8[11], 0) != 0)) {
            sp8[10] = GetChecksum(sp8[11], 0);
        }
        if (sp8[10] != 0) {
            GetStructure_2(fn_80129528(fn_801259C8(sp8[10], 1), 0), QB_PARAMS, &sp8[12], 1);
            GetString(sp8[12], QB_NAME, &sp8[13], 1);
            AddString(arg1->unk0x18, QB_EXTRA_TRICK_STRING, sp8[13]);
            AddChecksum(arg1->unk0x18, QB_EXTRA_TRICK_CHECKSUM, sp8[10]);
        }
        return true;
    }
    if (ContainsFlag(arg0, QB_SPECIAL) != 0) {
        var_r28 = 0;
        temp_r3_2 = fn_801A5388(var_r29);
        for (; var_r28 < temp_r3_2; var_r28++) {
            s_find_trick_in_mapping(&sp8[0], var_r29, var_r28);
            if (sp8[2] == sp8[4]) {
                if (sp8[1] == -QB_UNKNOWN_0x09F36F70) {
                    return false;
                }
                temp_r3 = GetStructure(sp8[1], 0);
                if (temp_r3 != 0) {
                    GetStructure_2(temp_r3, QB_PARAMS, &sp8[14], 1);
                    fn_801281BC(sp8[14], QB_NAME, &sp8[15], 1);
                    AddString(arg1->unk0x18, QB_TRICK_STRING, sp8[15]);
                }
                if (sp8[3] != 0) {
                    AddInteger(arg1->unk0x18, QB_TRICK_CHECKSUM, sp8[1]);
                } else {
                    AddChecksum(arg1->unk0x18, QB_TRICK_CHECKSUM, sp8[1]);
                }
                AddInteger(arg1->unk0x18, QB_CURRENT_INDEX, var_r28);
                return true;
            }
        }
    }
    return false;
}
