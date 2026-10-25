// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80188EB0-0x80188EE4 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
// ScriptGoalManager_GoalsAreSelected @ 0x80188EB0
bool ScriptGoalManager_GoalsAreSelected(CStruct *pParams, CScript *pScript) {
    s32 var_r3;

    Game_GetGoalManager();
    
    return ( !(fn_80184248() <= 0) );
}
