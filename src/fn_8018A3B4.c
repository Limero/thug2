// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018A3B4-0x8018A3F0 (60B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_80186CE0(s32, s32);
s32 Game_GetGoalManager(void);
// ScriptGoalManager_GoalExists @ 0x8018A3B4
void ScriptGoalManager_GoalExists(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    fn_80186CE0(Game_GetGoalManager(), sp8);
}
