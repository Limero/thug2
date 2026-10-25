// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018A62C-0x8018A6D4 (168B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 Game_GetGoalManager(void);
void fn_80186EF0(void *, s32, s32);

// ScriptGoalManager_SetEndRunType @ 0x8018A62C
bool ScriptGoalManager_SetEndRunType(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 var_r30;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    var_r30 = 1;
    if (ContainsFlag(pParams, QB_GOAL_ENDOFRUN) != 0) {
        var_r30 = 0;
    } else if ((ContainsFlag(pParams, QB_ENDOFRUN) == 0) && (ContainsFlag(pParams, QB_NONE) != 0)) {
        var_r30 = 2;
    }
    fn_80186EF0((void *)Game_GetGoalManager(), sp8, var_r30);
    return true;
}
