// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018A7D4-0x8018A854 (128B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 Game_GetGoalManager(s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80183A1C(s32, s32, s32);
void fn_80191E30(CStruct *, s32);
bool ScriptGoalManager_SuspendGoalPedLogic(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 var_r4;
    s32 temp_r29;
    s32 temp_r3;

    temp_r29 = Game_GetGoalManager(pParams);
    sp8 = 1;
    GetInteger(pParams, QB_SUSPEND, &sp8, 0);
    temp_r3 = *(s32 *)((char *)fn_80183A1C(temp_r29, pParams, 1) + 0x18);
    var_r4 = 1;
    if (sp8 == 0) {
        var_r4 = 0;
    }
    fn_80191E30((void *)temp_r3, var_r4);
    return true;
}
