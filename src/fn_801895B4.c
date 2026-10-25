// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801895B4-0x801895F4 (64B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 Game_GetGoalManager(s32);
void fn_80185F4C(s32, s32);
// ScriptGoalManager_PauseCompetition @ 0x801895B4
bool ScriptGoalManager_PauseCompetition(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    fn_80185F4C(Game_GetGoalManager(GetChecksum_2(pParams, QB_NAME, &sp8, 1)), sp8);
    return true;
}
