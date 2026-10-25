// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80184558-0x801845B8 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern s32 GoalManager_GetGoal(s32 arg0, s32 arg1, s32 arg2);
extern void fn_8018BE00(void *arg0, s32 arg1, s32 arg2);

void fn_80184558(Unk_C7387A53 *arg0, s32 arg1) {
    Unk_C7387A53 *node;
    s32 *p;

    node = (Unk_C7387A53 *)GoalManager_GetGoal((s32)arg0, arg1, 1);
    for (;;) {
        p = *(s32 **)((char *)node + 0x30);
        if (p == NULL) {
            break;
        }
        if (*p == 0) {
            break;
        }
        node = (Unk_C7387A53 *)GoalManager_GetGoal((s32)arg0, *p, 1);
    }
    fn_8018BE00(node, 1, 0);
}
