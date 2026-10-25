// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801884B4-0x80188514 (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
s32 Game_GetGoalManager(s32);
s32 fn_80128978(s32, s32);
void fn_801843AC(s32, s32);
// ScriptGoalManager_DeactivateAllGoals @ 0x801884B4
bool ScriptGoalManager_DeactivateAllGoals(s32 arg0) {
    s32 var_r29;
    s32 temp_r31;

    var_r29 = 0;
    temp_r31 = Game_GetGoalManager(arg0);
    if (fn_80128978(arg0, QB_FORCE_ALL) != 0) {
        var_r29 = 1;
    }
    fn_801843AC(temp_r31, var_r29);
    return true;
}
