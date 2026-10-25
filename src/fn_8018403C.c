// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018403C-0x801840A4 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "types.h"
void fn_8018C054(void *, void *);
void fn_8018BFB4(void *);
s32 GoalManager_GetGoal(s32, s32, s32);
s32 fn_8018403C(void *arg0, void *arg1, s32 arg2) {
    s32 temp_r3;
    s32 var_r3;

    temp_r3 = GoalManager_GetGoal((s32)arg0, (s32)arg1, 1);
    if (temp_r3 != 0) {
        if (arg2 == -1) {
            fn_8018BFB4(temp_r3);
        } else {
            fn_8018C054(temp_r3, arg2);
        }
    }
    var_r3 = 1;
    if (temp_r3 == 0) {
        var_r3 = 0;
    }
    return var_r3;
}