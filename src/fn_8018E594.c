// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018E594-0x8018E654 (192B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_8009CF2C(CStruct *);
extern s32 fn_80198F7C(s32);
extern s32 Game_GetGoalManager(s32);
extern s32 GoalManager_GetGoal(s32, s32, s32);
extern char lbl_80305EC0[];
extern char lbl_80305F9C[];
void fn_8018E594(Unk_C7387A53 *arg0) {
    register s32 chk __asm__("r3");
    s32 temp_r30;
    s32 var_r0;
    void *temp_r3;
    Unk_4AA2E777 *temp_r9;
    CStruct *var_r31;

    if ((fn_8009CF2C(*(s32 *)&lbl_80305F9C) != 0) && ((chk = fn_80198F7C(*(s32 *)&lbl_80305EC0)) == QB_NETGOALATTACK)) {
        var_r0 = arg0->unk0x70 | QB_UNKNOWN_0x10000000;
    } else {
        var_r0 = arg0->unk0x70 | QB_UNKNOWN_0x20000000;
    }
    arg0->unk0x70 = var_r0;
    temp_r30 = Game_GetGoalManager(chk);
    var_r31 = arg0->unk0x30;
    while ((var_r31 != NULL) && (*(s32 *)var_r31 != 0)) {
        temp_r3 = GoalManager_GetGoal(temp_r30, *(s32 *)var_r31, 1);
        temp_r9 = ((Unk_C8FEE62D *)temp_r3)->unk0x14;
        temp_r9->unk0xDC(temp_r3 + temp_r9->unk0xD8);
        var_r31 = var_r31->unk0x4;
    }
}
