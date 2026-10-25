// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80188950-0x80188978 (40B). Byte-identical.
#include "types.h"
#include "structs.h"
// ScriptGoalManager_RestartLastGoal @ 0x80188950
bool ScriptGoalManager_RestartLastGoal(CStruct *pParams, CScript *pScript) {
    Game_GetGoalManager();
    fn_80184D74();
    return true;
}
