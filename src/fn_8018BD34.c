// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018BD34-0x8018BDB8 (132B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 Game_GetGoalManager(void *arg0);
extern s32 GoalManager_GetGoal(s32 arg0, s32 arg1, s32 arg2);
void fn_8018BD34(Unk_C7387A53 *arg0) {
    s32 *var_r30;
    s32 temp_r31;
    s32 var_r29;
    s32 var_r3;

    temp_r31 = Game_GetGoalManager(arg0);
    var_r30 = *((s32 * *)&arg0->unk0x2C);
    if ((var_r30 != NULL) && ((s32)*var_r30 != 0)) {
        var_r29 = 0;
        do {
            ((CStruct *)var_r30)->unk0x8 = var_r29;
            var_r3 = GoalManager_GetGoal(temp_r31, *var_r30, 1);
            if (var_r3 != 0) {
                fn_8018BD34((void *)var_r3);
            }
            var_r30 = *((s32 * *)&((CStruct *)var_r30)->unk0x4);
        } while ((var_r30 != NULL) && ((s32)*var_r30 != 0));
    }
}
