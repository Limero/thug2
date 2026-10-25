// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018A3F0-0x8018A43C (76B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void Game_GetGoalManager(void *);
void fn_80127CD4(CStruct *, s32, void *);
void *fn_80186D14(void);
// ScriptGoalManager_GetGoalAttemptInfo @ 0x8018A3F0
bool ScriptGoalManager_GetGoalAttemptInfo(void *arg0, CScript *arg1) {
    s32 temp_r29;

    Game_GetGoalManager(arg0);
    temp_r29 = arg1->unk0x18;
    fn_80127CD4((void *)temp_r29, QB_GOAL_ATTEMPT_INFO, fn_80186D14());
    return true;
}
