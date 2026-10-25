// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80185104-0x8018513C (56B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 GoalManager_GetGoal(void *, s32, s32);
void NextRaceWaypoint(Unk_8B98B2B7 *, s32);
void fn_80185104(void *arg0, s32 arg1) {
    NextRaceWaypoint(GoalManager_GetGoal(arg0, arg1, 1), arg1);
}
