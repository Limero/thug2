// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018A2C4-0x8018A354 (144B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 ContainsFlag(CStruct *, s32);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 Game_GetGoalManager();
extern void fn_80186C78(s32, s32, Unk_C8FEE62D *, s32);

bool ScriptGoalManager_ColorTrickObjects(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    s32 temp_r29;
    s32 temp_r30;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    temp_r29 = ContainsFlag(pParams, QB_CLEAR);
    spC = 0;
    GetInteger(pParams, QB_SKATER, &spC, 0);
    temp_r30 = spC + 1;
    fn_80186C78(Game_GetGoalManager(), sp8, temp_r30, temp_r29);
    return true;
}
