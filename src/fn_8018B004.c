// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018B004-0x8018B04C (72B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetChecksum_2(CStruct *, s32, s32 *, s32);
void GoalManager_GetGoal(s32, s32, s32);
s32 Game_GetGoalManager(void);
void fn_80197FA8(void);
// ScriptGoalManager_ResetTrickBeatTimer @ 0x8018B004
bool ScriptGoalManager_ResetTrickBeatTimer(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    GoalManager_GetGoal(Game_GetGoalManager(), sp8, 1);
    fn_80197FA8();
    return true;
}
