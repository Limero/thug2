// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80188804-0x8018882C (40B). Byte-identical.
#include "types.h"
#include "structs.h"
// ScriptGoalManager_PauseAllGoals @ 0x80188804
bool ScriptGoalManager_PauseAllGoals(CStruct *pParams, CScript *pScript) {
    Game_GetGoalManager();
    fn_80184BE8();
    return true;
}
