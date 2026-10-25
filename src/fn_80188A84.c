// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80188A84-0x80188AF0 (108B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 Game_GetGoalManager(s32);
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 fn_801850D4(s32, s32);
extern void fn_80126FF4(Unk_80577C09 *, CStruct *);
bool ScriptGoalManager_GetGoalParams(s32 arg0, void *arg1) {
    s32 sp8;
    register void *a1 __asm__("r28");
    register s32 a0 __asm__("r30");
    s32 temp_r29;

    a1 = arg1;
    a0 = arg0;
    temp_r29 = Game_GetGoalManager(a0);
    GetChecksum_2(a0, QB_NAME, &sp8, 1);
    a0 = ((CScript *)a1)->unk0x18;
    fn_80126FF4(a0, fn_801850D4(temp_r29, sp8));
    return true;
}
