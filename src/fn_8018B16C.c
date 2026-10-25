// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018B16C-0x8018B204 (152B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 Game_GetGoalManager(s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GoalManager_GetGoal(s32, s32, s32);
s32 fn_80190840(Unk_C7387A53 *);
void AddInteger(CStruct *, s32, s32);
// ScriptGoalManager_GetGoalRewardPoints @ 0x8018B16C
bool ScriptGoalManager_GetGoalRewardPoints(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r29;
    s32 temp_r29_2;
    s32 temp_r30;

    temp_r29 = Game_GetGoalManager(pParams);
    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    temp_r29_2 = GoalManager_GetGoal(temp_r29, sp8, 1);
    if (fn_80190840(temp_r29_2) != 0) {
        temp_r30 = pScript->unk0x18;
        AddInteger(temp_r30, QB_REWARD_POINTS, fn_80190840(temp_r29_2));
        return true;
    }
    return false;
}
