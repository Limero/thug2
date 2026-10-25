// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801899B0-0x801899F8 (72B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetChecksum_2(CStruct *, s32, s32 *, s32);
void GoalManager_GetGoal(s32, s32, s32);
s32 Game_GetGoalManager(void);
void fn_8018F2EC(void);
// ScriptGoalManager_RemoveTempSpecialTrick @ 0x801899B0
bool ScriptGoalManager_RemoveTempSpecialTrick(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    GoalManager_GetGoal(Game_GetGoalManager(), sp8, 1);
    fn_8018F2EC();
    return true;
}
