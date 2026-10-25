// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018A4E8-0x8018A548 (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 Game_GetGoalManager(s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GoalManager_GetGoal(s32, s32, s32);
void fn_80195098(void);
// ScriptGoalManager_ClearTetrisTricks @ 0x8018A4E8
bool ScriptGoalManager_ClearTetrisTricks(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r29;

    temp_r29 = Game_GetGoalManager(pParams);
    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    GoalManager_GetGoal(temp_r29, sp8, 1);
    fn_80195098();
    return true;
}
