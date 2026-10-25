// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018A960-0x8018A9D0 (112B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 Game_GetGoalManager(s32);
s32 GetChecksum_2(CStruct *, u32, s32 *, s32);
s32 ContainsFlag(CStruct *, u32);
void fn_801879E4(s32, s32, s32);
void ScriptGoalManager_AdvanceStage(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 ctx;

    ctx = Game_GetGoalManager(pParams);
    GetChecksum_2(pParams, QB_JUST_WON_GOAL_ID, &sp8, (sp8 = 0, 0));
    fn_801879E4(ctx, ContainsFlag(pParams, QB_FORCE), sp8);
}
