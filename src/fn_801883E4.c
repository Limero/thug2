// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801883E4-0x80188438 (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 Game_GetGoalManager(s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_80183D68(Unk_C7387A53 *, s32);
// ScriptGoalManager_WinGoal @ 0x801883E4
void ScriptGoalManager_WinGoal(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r29;

    temp_r29 = Game_GetGoalManager(pParams);
    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    fn_80183D68(temp_r29, sp8);
}
