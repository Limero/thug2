// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801895F4-0x80189634 (64B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 Game_GetGoalManager(s32);
void fn_80185F74(s32, s32);
// ScriptGoalManager_UnPauseCompetition @ 0x801895F4
bool ScriptGoalManager_UnPauseCompetition(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    fn_80185F74(Game_GetGoalManager(GetChecksum_2(pParams, QB_NAME, &sp8, 1)), sp8);
    return true;
}
