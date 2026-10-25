// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80184BB0-0x80184BE8 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 GoalManager_GetGoal(s32, s32, s32);
s32 fn_8018D0EC(void *);

s32 fn_80184BB0(s32 arg0, s32 arg1) {
    s32 temp_r3;

    temp_r3 = GoalManager_GetGoal(arg0, arg1, 1);
    if (temp_r3 == 0) {
        return 0;
    }
    return fn_8018D0EC(temp_r3);
}
