// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801889CC-0x80188A60 (148B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
// ScriptGoalManager_GoalFlagSet @ 0x801889CC
void ScriptGoalManager_GoalFlagSet(CStruct *, CScript *pScript);
s32 Game_GetGoalManager(s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_80184F48(s32, s32, Unk_C7387A53 *, s32);
void ScriptGoalManager_GoalFlagSet(CStruct *pParams, CScript *pScript) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r29;

    temp_r29 = Game_GetGoalManager(pParams);
    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    GetChecksum_2(pParams, QB_FLAG, &spC, 1);
    sp10 = 0;
    GetChecksum_2(pParams, QB_SKATER, &sp10, 0);
    fn_80184F48(temp_r29, sp8, spC, sp10);
}
