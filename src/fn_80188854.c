// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80188854-0x801888FC (168B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
// ScriptGoalManager_SetGoalFlag @ 0x80188854
void ScriptGoalManager_SetGoalFlag(CStruct *, CScript *pScript);
s32 Game_GetGoalManager(s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_80184EB4(s32, s32, s32, s32, s32);
void ScriptGoalManager_SetGoalFlag(CStruct *pParams, CScript *pScript) {
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r29;

    temp_r29 = Game_GetGoalManager(pParams);
    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    GetChecksum_2(pParams, 0, &spC, 1);
    GetInteger(pParams, 0, &sp10, 1);
    sp14 = 0;
    GetChecksum_2(pParams, QB_SKATER, &sp14, 0);
    fn_80184EB4(temp_r29, sp8, spC, sp10, sp14);
}
