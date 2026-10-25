// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018882C-0x80188854 (40B). Byte-identical.
#include "types.h"
#include "structs.h"
// ScriptGoalManager_UnPauseAllGoals @ 0x8018882C
bool ScriptGoalManager_UnPauseAllGoals(CStruct *pParams, CScript *pScript) {
    Game_GetGoalManager();
    fn_80184C50();
    return true;
}
