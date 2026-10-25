// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80198434-0x8019849C (104B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 Game_GetGoalManager(void);
extern s32 fn_80198F7C(s32 arg0);
extern s32 fn_8019903C(s32 arg0, s32 arg1);
extern s32 GoalManager_GetGoal(s32 arg0, s32 arg1, s32 arg2);
extern s32 fn_8018C054(Unk_C7387A53 * arg0, s32 arg1);

s32 fn_80198434(s32 arg0, s32 arg1) {
    s32 temp_r29;
    s32 var_r3;

    temp_r29 = Game_GetGoalManager();
    var_r3 = GoalManager_GetGoal(temp_r29, fn_8019903C(arg0, fn_80198F7C(arg0)), 0);
    if (var_r3 != 0) {
        var_r3 = fn_8018C054(var_r3, arg1);
    }
    return var_r3;
}
