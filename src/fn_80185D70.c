// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80185D70-0x80185D9C (44B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_80191884(void *);
s32 GoalManager_GetGoal(s32, s32, s32);
void fn_80185D70(s32 a, s32 b) {
    fn_80191884(*(s32 *)(GoalManager_GetGoal(a, b, 1) + 0x18));
}
