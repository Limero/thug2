// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801883BC-0x801883E4 (40B). Byte-identical.
#include "types.h"
#include "structs.h"
// ScriptGoalManager_ClearLastGoal @ 0x801883BC
bool ScriptGoalManager_ClearLastGoal(CStruct *pParams, CScript *pScript) {
    Game_GetGoalManager();
    fn_80183D5C();
    return true;
}
