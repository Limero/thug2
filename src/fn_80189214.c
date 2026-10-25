// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80189214-0x80189294 (128B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 Game_GetGoalManager(s32);
extern s32 ContainsFlag(CStruct *, s32);
extern s32 fn_80185A88(s32, s32, s32);
extern void AddInteger(CStruct *, s32, void *);

bool ScriptGoalManager_NumGoalsBeatenInLevel(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r28;
    s32 temp_r5;

    temp_r28 = Game_GetGoalManager(GetInteger(pParams, 0, &sp8, 1));
    temp_r5 = fn_80185A88(temp_r28, sp8, ContainsFlag(pParams, QB_COUNT_PRO_SPECIFIC_CHALLENGES));
    AddInteger(pScript->unk0x18, QB_NUM_BEATEN, temp_r5);
    return true;
}
