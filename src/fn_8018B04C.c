// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018B04C-0x8018B098 (76B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void Game_GetGoalManager(void *);
void fn_80127C14(CStruct *, s32, CStruct *);
void *fn_801869E4(void);
// ScriptGoalManager_GetGoalManagerParams @ 0x8018B04C
bool ScriptGoalManager_GetGoalManagerParams(void *arg0, CScript *arg1) {
    s32 temp_r29;

    Game_GetGoalManager(arg0);
    temp_r29 = arg1->unk0x18;
    fn_80127C14((void *)temp_r29, QB_GOALMANAGERPARAMS, fn_801869E4());
    return true;
}
