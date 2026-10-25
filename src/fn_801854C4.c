// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801854C4-0x8018551C (88B). Byte-identical.
#include "types.h"
#include "structs.h"

extern void *GoalManager_GetGoal(void *arg0, void *arg1, s32 arg2);
extern void fn_8018E400(Unk_C7387A53 * arg0);

void fn_801854C4(void *arg0, void *arg1) {
    Unk_C8FEE62D *temp_r3;
    Unk_89391A04 *temp_r9;

    temp_r3 = GoalManager_GetGoal(arg0, arg1, 1);
    temp_r9 = *((void * *)&temp_r3->unk0x14);
    if (((s32 (*)(void *))(*((void * *)&temp_r9->unk0x24)))(
            (char *)temp_r3 + temp_r9->unk0x20) != 0) {
        fn_8018E400(temp_r3);
    }
}
