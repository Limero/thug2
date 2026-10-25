// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801893A4-0x801893E0 (60B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 Game_GetGoalManager(s32);
void fn_80185CC0(s32, s32);
// ScriptGoalManager_CheckHeightRecord @ 0x801893A4
void ScriptGoalManager_CheckHeightRecord(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    fn_80185CC0(Game_GetGoalManager(GetChecksum_2(pParams, QB_NAME, &sp8, 1)), sp8);
}
