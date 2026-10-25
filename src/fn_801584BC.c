// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801584BC-0x80158594 (216B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 GetStructure_2(CStruct *, s32, s32 *, s32);
extern s32 fn_801A5C04(Unk_9994C3F5 *);
extern s32 fn_801A5C40(s32, s32);
extern s32 fn_80126FF4(Unk_80577C09 *, CStruct *);
extern s32 lbl_80305EFC;
bool ScriptSetSkaterProfileInfoByName(CStruct *pParams, CScript *pScript) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r28;
    s32 temp_r29;
    s32 temp_r30;
    s32 var_r31;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    spC = 0;
    var_r31 = 0;
    GetStructure_2(pParams, QB_PARAMS, &spC, 1);
    temp_r28 = lbl_80305EFC;
    temp_r29 = fn_801A5C04(temp_r28);
    if (var_r31 < temp_r29) {
        do {
            temp_r30 = fn_801A5C40(temp_r28, var_r31) + 0x6C;
            GetChecksum_2(temp_r30, QB_NAME, &sp10, 1);
            if (sp10 == sp8) {
                fn_80126FF4(temp_r30, spC);
                return true;
            }
            var_r31 += 1;
        } while (var_r31 < temp_r29);
    }
    return false;
}
