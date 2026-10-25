// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018AE18-0x8018AE7C (100B). Byte-identical.
#include "types.h"
#include "structs.h"

s32 Game_GetGoalManager(void);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_80187A98(s32, s32);

bool ScriptGoalManager_HideAllGoalPeds(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 var_r4;
    s32 temp_r31;

    temp_r31 = Game_GetGoalManager();
    GetInteger(pParams, 0, &sp8, 1);
    var_r4 = 1;
    if (sp8 == 0) {
        var_r4 = 0;
    }
    fn_80187A98(temp_r31, var_r4);
    return true;
}
