// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80157E8C-0x80158050 (452B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EFC;
extern void *fn_801259C8(s32 arg0, s32 arg1);
extern s32 CStruct_new(s32 arg0);
extern s32 CStruct_ctor(s32 arg0);
extern void *fn_80129528(CStruct * arg0, u32 arg1);
extern s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern void AddInteger(CStruct * arg0, s32 arg1, s32 arg2);
extern s32 fn_801A5C04(Unk_9994C3F5 * arg0);
extern void *fn_801A5C40(void *arg0, u32 arg1);
extern s32 fn_80126FF4(Unk_80577C09 * arg0, CStruct * arg1);
extern s32 CStruct_delete(CStruct * arg0, s32 arg1);
bool ScriptResetAllToDefaultStats(CStruct *pParams, CScript *pScript) {
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    CStruct *temp_r26;
    s32 temp_r28;
    s32 temp_r29;
    s32 temp_r29_2;
    s32 temp_r27;
    CStruct *temp_r31_arr;
    s32 temp_r31_2;
    u32 var_r30;
    u32 var_r31;

    temp_r26 = fn_801259C8(QB_MASTER_SKATER_LIST, 1);
    var_r31 = 0U;
    while (var_r31 < (u32)*((u32 *)&temp_r26->unk0x4)) {
        temp_r28 = CStruct_ctor(CStruct_new(8));
        temp_r29 = (s32)fn_80129528(temp_r26, var_r31);
        GetChecksum_2(temp_r29, QB_NAME, &sp8, 1);
        temp_r31_arr = (s32)fn_801259C8(QB_STAT_NAMES, 0);
        var_r30 = 0U;
        while (var_r30 < (u32)*((u32 *)&temp_r31_arr->unk0x4)) {
            GetChecksum_2((s32)fn_80129528((void *)temp_r31_arr, var_r30++), QB_NAME, &spC, 1);
            GetInteger(temp_r29, spC, &sp10, 1);
            AddInteger(temp_r28, spC, sp10);
        }
        GetInteger(temp_r29, QB_POINTS_AVAILABLE, &sp14, 1);
        AddInteger(temp_r28, QB_POINTS_AVAILABLE, sp14);
        temp_r29_2 = lbl_80305EFC;
        temp_r27 = fn_801A5C04((void *)temp_r29_2);
        for (var_r30 = 0U; var_r30 < (u32)temp_r27; var_r30++) {
            temp_r31_2 = (s32)((char *)fn_801A5C40((void *)temp_r29_2, var_r30) + 0x6C);
            GetChecksum_2(temp_r31_2, QB_NAME, &sp18, 1);
            if (sp18 == sp8) {
                fn_80126FF4(temp_r31_2, temp_r28);
                break;
            }
        }
        if (temp_r28 != 0) {
            CStruct_delete(temp_r28, 3);
        }
        var_r31++;
    }
    return true;
}
