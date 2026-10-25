// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80188FEC-0x8018903C (80B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 Game_GetGoalManager(s32);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern void fn_801855A8(Unk_C7387A53 *, s32);
void ScriptGoalManager_HasGoalPoints(s32 arg0) {
    s32 sp8;
    register s32 a0 __asm__("r29");
    s32 temp_r30;

    a0 = arg0;
    temp_r30 = Game_GetGoalManager(a0);
    GetInteger(a0, 0, &sp8, 1);
    fn_801855A8(temp_r30, sp8);
}
