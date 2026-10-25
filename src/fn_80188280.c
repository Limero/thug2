// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80188280-0x801882F0 (112B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
// ScriptGoalManager_EditGoal @ 0x80188280
void ScriptGoalManager_EditGoal(CStruct *, CScript *pScript);
s32 Game_GetGoalManager(s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
void fn_80183FDC(s32, s32, s32);
void ScriptGoalManager_EditGoal(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    s32 temp_r29;

    temp_r29 = Game_GetGoalManager(pParams);
    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    GetStructure_2(pParams, QB_PARAMS, &spC, 1);
    fn_80183FDC(temp_r29, sp8, spC);
}
