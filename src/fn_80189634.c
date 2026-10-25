// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80189634-0x8018965C (40B). Byte-identical.
#include "types.h"
#include "structs.h"
// ScriptGoalManager_UnBeatAllGoals @ 0x80189634
bool ScriptGoalManager_UnBeatAllGoals(CStruct *pParams, CScript *pScript) {
    Game_GetGoalManager();
    fn_80185F9C();
    return true;
}
