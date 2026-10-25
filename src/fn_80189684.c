// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80189684-0x80189704 (128B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 Game_GetGoalManager(s32);
extern s32 ContainsFlag(CStruct *, s32);
extern void fn_80186624(s32, s32, s32, s32);

bool ScriptGoalManager_AddGoalChoices(CStruct *pParams, CScript *pScript) {
    s32 temp_r27;
    s32 temp_r28;
    s32 temp_r29;

    temp_r27 = Game_GetGoalManager(pParams);
    temp_r28 = ContainsFlag(pParams, QB_SELECTED_ONLY);
    temp_r29 = ContainsFlag(pParams, QB_CLASSIC_ONLY);
    fn_80186624(temp_r27, temp_r28, temp_r29, ContainsFlag(pParams, QB_CREATED_ONLY));
    return true;
}
