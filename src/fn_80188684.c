// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80188684-0x801886E0 (92B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 Game_GetGoalManager(s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_80184170(Unk_C7387A53 *, s32);
// ScriptGoalManager_HasActiveGoals @ 0x80188684
s32 ScriptGoalManager_HasActiveGoals(CStruct *pParams, CScript *pScript) {
    s32 temp_r29;
    s32 temp_r3;

    temp_r29 = Game_GetGoalManager(pParams);
    temp_r3 = fn_80184170(temp_r29, ContainsFlag(pParams, QB_COUNT_ALL));
    return (temp_r3 > 0) ? 1 : 0;
}
