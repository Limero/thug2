// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801882F0-0x80188368 (120B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
// ScriptGoalManager_ActivateGoal @ 0x801882F0
void ScriptGoalManager_ActivateGoal(CStruct *, CScript *pScript);
s32 Game_GetGoalManager(s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
void fn_80183BC0(Unk_C7387A53 *, s32, s32);
void ScriptGoalManager_ActivateGoal(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 var_r29;
    s32 temp_r31;

    var_r29 = 0;
    temp_r31 = Game_GetGoalManager(pParams);
    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    if (ContainsFlag(pParams, QB_DONTASSERT) != 0) {
        var_r29 = 1;
    }
    fn_80183BC0(temp_r31, sp8, var_r29);
}
