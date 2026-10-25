// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80189454-0x80189494 (64B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 Game_GetGoalManager(s32);
void fn_80185D70(s32, s32);
// ScriptGoalManager_PlayGoalWaitStream @ 0x80189454
bool ScriptGoalManager_PlayGoalWaitStream(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    fn_80185D70(Game_GetGoalManager(GetChecksum_2(pParams, QB_NAME, &sp8, 1)), sp8);
    return true;
}
