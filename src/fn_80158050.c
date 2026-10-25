// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80158050-0x80158178 (296B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 fn_801259C8(s32, s32);
extern s32 fn_80129528(CStruct *, s32);
extern s32 fn_801A5DAC(s32);
extern void fn_801A46F8(s32, CStruct *, s32, s32);
extern void fn_801A4540(s32, CStruct *);
extern s32 lbl_80305EFC;
bool ScriptResetToDefaultProfile(CStruct *pParams, CScript *pScript) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    CStruct *temp_r28;
    s32 temp_r30;
    s32 temp_r31;
    u32 var_r29;
    register s32 v8 __asm__("r4");

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    var_r29 = 0U;
    temp_r28 = fn_801259C8(QB_MASTER_SKATER_LIST, 1);
    if (var_r29 < (u32) *((u32 *)&temp_r28->unk0x4)) {
        do {
            temp_r30 = fn_80129528(temp_r28, var_r29);
            GetChecksum_2(temp_r30, QB_NAME, &spC, 1);
            v8 = sp8;
            if (v8 == spC) {
                temp_r31 = fn_801A5DAC(lbl_80305EFC);
                if (GetChecksum_2(pParams, QB_PARTIAL, &sp10, 0) != 0) {
                    if (sp10 == -QB_UNKNOWN_0x3E9B50E0) {
                        fn_801A46F8(temp_r31, temp_r30, 0, 1);
                    } else {
                        fn_801A46F8(temp_r31, temp_r30, 1, 0);
                    }
                } else {
                    fn_801A4540(temp_r31, temp_r30);
                }
            }
            var_r29 += 1;
        } while (var_r29 < (u32) *((u32 *)&temp_r28->unk0x4));
    }
    return true;
}
