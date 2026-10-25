// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801893E0-0x8018941C (60B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 Game_GetGoalManager(s32);
void fn_80185CE8(s32, s32);
// ScriptGoalManager_CheckDistanceRecord @ 0x801893E0
void ScriptGoalManager_CheckDistanceRecord(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    fn_80185CE8(Game_GetGoalManager(GetChecksum_2(pParams, QB_NAME, &sp8, 1)), sp8);
}
