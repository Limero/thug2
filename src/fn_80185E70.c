// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80185E70-0x80185E9C (44B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 GoalManager_GetGoal(s32, s32, s32);
void fn_80191C50(void * arg0);
void fn_80185E70(s32 arg0, s32 arg1) {
    fn_80191C50(*(s32 *)((char *)GoalManager_GetGoal(arg0, arg1, 1) + 0x18));
}
