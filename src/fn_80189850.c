// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80189850-0x8018988C (60B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_801869BC(s32, s32);
s32 Game_GetGoalManager(void);
// ScriptGoalManager_EndRunCalled @ 0x80189850
void ScriptGoalManager_EndRunCalled(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    fn_801869BC(Game_GetGoalManager(), sp8);
}
