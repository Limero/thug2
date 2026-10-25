// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80183A1C-0x80183A64 (72B). Byte-identical.
#include "types.h"
s32 fn_801877F8(void);
s32 GoalManager_GetGoal(s32, s32, s32);
s32 fn_80183A1C(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_r3;
    s32 ret;

    ret = fn_801877F8();
    var_r3 = 0;
    if (ret != 0) {
        var_r3 = GoalManager_GetGoal(arg0, ret, arg2);
    }
    return var_r3;
}

