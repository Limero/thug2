// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80189294-0x801892BC (40B). Byte-identical.
#include "types.h"
#include "structs.h"
// ScriptGoalManager_UnlockAllGoals @ 0x80189294
bool ScriptGoalManager_UnlockAllGoals(CStruct *pParams, CScript *pScript) {
    Game_GetGoalManager();
    fn_80185B4C();
    return true;
}
