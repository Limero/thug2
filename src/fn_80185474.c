// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80185474-0x801854C4 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "types.h"
void fn_8018E6C4(void *);
void fn_8018E6D4(void *);
s32 GoalManager_GetGoal(s32, s32, s32);
void fn_80185474(s32 a0, s32 a1) {
    s32 temp_r31;

    temp_r31 = GoalManager_GetGoal((s32)a0, (s32)a1, 1);
    if (fn_8018E3B8() != 0) {
        fn_8018E6D4(temp_r31);
        return;
    }
    fn_8018E6C4(temp_r31);
}