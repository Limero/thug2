// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80188978-0x801889CC (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 Game_GetGoalManager(s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_80184F20(s32, s32);
// ScriptGoalManager_AllFlagsSet @ 0x80188978
void ScriptGoalManager_AllFlagsSet(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r29;

    temp_r29 = Game_GetGoalManager(pParams);
    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    fn_80184F20(temp_r29, sp8);
}
