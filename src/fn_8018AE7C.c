// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018AE7C-0x8018AEE4 (104B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 Game_GetGoalManager(void);
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_80187C14(Unk_9994C3F5 *, CStruct *, s32);

bool ScriptGoalManager_GetViewGoalsInfo(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r29;

    temp_r29 = Game_GetGoalManager();
    sp8 = 0;
    GetChecksum_2(pParams, QB_SKATER, &sp8, 0);
    fn_80187C14(temp_r29, pScript->unk0x18, sp8);
    return true;
}
