// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80189364-0x801893A4 (64B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 Game_GetGoalManager(s32);
void fn_80185C98(s32, s32);
// ScriptGoalManager_SetStartHeight @ 0x80189364
bool ScriptGoalManager_SetStartHeight(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    fn_80185C98(Game_GetGoalManager(GetChecksum_2(pParams, QB_NAME, &sp8, 1)), sp8);
    return true;
}
