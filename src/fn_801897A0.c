// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801897A0-0x80189818 (120B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetString(CStruct *, s32 *, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_8018694C(s32, s32, s32, s32);
s32 Game_GetGoalManager(s32);
// ScriptGoalManager_GetGoalAnimations @ 0x801897A0
bool ScriptGoalManager_GetGoalAnimations(CStruct *arg0, s32 arg1) {
    s32 spC;
    s32 sp8;

    GetChecksum_2(arg0, QB_NAME, &sp8, 1);
    spC = 0;
    fn_8018694C(Game_GetGoalManager(GetString(arg0, QB_TYPE, &spC, 0)), sp8, spC, arg1);
    return true;
}
