// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80188564-0x801885E4 (128B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 Game_GetGoalManager(s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
void fn_80184558(s32, s32);
void fn_80184528(s32, s32);
// ScriptGoalManager_UninitializeGoal @ 0x80188564
bool ScriptGoalManager_UninitializeGoal(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r31;

    temp_r31 = Game_GetGoalManager(pParams);
    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    if (ContainsFlag(pParams, QB_AFFECT_TREE) != 0) {
        fn_80184558(temp_r31, sp8);
    } else {
        fn_80184528(temp_r31, sp8);
    }
    return true;
}
