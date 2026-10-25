// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018AD80-0x8018ADCC (76B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 Game_GetGoalManager(void);
extern s32 GoalManager_GetGoal(s32, s32, s32);
extern void fn_801916B4(CStruct *);
bool ScriptGoalManager_UnloadLastFam(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    fn_801916B4(*(s32 *)((char *)GoalManager_GetGoal(Game_GetGoalManager(), sp8, 1) + 0x18));
    return true;
}
