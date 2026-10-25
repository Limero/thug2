// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018A038-0x8018A0A4 (108B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GoalManager_GetGoal(s32, s32, s32);
s32 Game_GetGoalManager(s32);
void fn_8018C068(Unk_C7387A53 *, s32);
// ScriptGoalManager_AddTime @ 0x8018A038
bool ScriptGoalManager_AddTime(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    fn_8018C068(GoalManager_GetGoal(Game_GetGoalManager(GetInteger(pParams, 0, &spC, 1)), sp8, 1), spC);
    return true;
}
