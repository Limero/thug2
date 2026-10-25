// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018ADCC-0x8018AE18 (76B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 Game_GetGoalManager(void);
extern s32 GoalManager_GetGoal(s32, s32, s32);
void fn_801917FC(CStruct *);

bool ScriptGoalManager_StopLastStream(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    fn_801917FC(*(s32 *)((char *)GoalManager_GetGoal(Game_GetGoalManager(), sp8, 1) + 0x18));
    return true;
}
