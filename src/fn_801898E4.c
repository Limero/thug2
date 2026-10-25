// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801898E4-0x80189928 (68B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetChecksum_2(CStruct *, s32, s32 *, s32);
void GoalManager_GetGoal(s32, s32, s32);
s32 Game_GetGoalManager(void);
s32 fn_8018EE80(void);
s32 ScriptGoalManager_FinishedEndOfRun(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    GoalManager_GetGoal(Game_GetGoalManager(), sp8, 1);
    return fn_8018EE80();
}
