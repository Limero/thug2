// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018A6D4-0x8018A748 (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_80186F28(void *, s32, s32);
s32 Game_GetGoalManager(s32);
// ScriptGoalManager_SetShouldDeactivateOnExpire @ 0x8018A6D4
bool ScriptGoalManager_SetShouldDeactivateOnExpire(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    fn_80186F28(Game_GetGoalManager(GetInteger(pParams, 0, &spC, 1)), sp8, (spC != 0));
    return true;
}
