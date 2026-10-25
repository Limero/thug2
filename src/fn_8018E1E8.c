// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018E1E8-0x8018E24C (100B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 Game_GetGoalManager(void);
s32 GoalManager_GetGoal(s32, s32, s32);
s32 fn_8018E24C(Unk_C7387A53 *);

void fn_8018E1E8(void *arg0) {
    s32 *node;
    s32 temp_r31;
    Unk_5F525A3F *p;

    temp_r31 = Game_GetGoalManager();
    p = (char *)arg0;
    while ((node = p->unk0x30) != NULL && (node[0]) != 0) {
        p = (char *)GoalManager_GetGoal(temp_r31, node[0], 1);
    }
    fn_8018E24C(p);
}
