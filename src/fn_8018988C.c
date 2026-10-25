// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018988C-0x801898E4 (88B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GoalManager_GetGoal(s32, s32, s32);
s32 Game_GetGoalManager(s32);
void fn_8018EDB0(Unk_C7387A53 *, s32);
// ScriptGoalManager_ClearEndRun @ 0x8018988C
bool ScriptGoalManager_ClearEndRun(CStruct *arg0, s32 arg1) {
    s32 sp8;

    fn_8018EDB0(GoalManager_GetGoal(Game_GetGoalManager(GetChecksum_2(arg0, QB_NAME, &sp8, 1)), sp8, 1), arg1);
    return true;
}
