// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80185E9C-0x80185EFC (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(s32, s32, s32, s32);
s32 fn_801918C4(s32, s32);
s32 GoalManager_GetGoal(s32, s32, s32);
void fn_80185E9C(s32 arg0, CStruct *arg1) {
    s32 sp8;

    GetChecksum_2(arg1, QB_NAME, &sp8, 1);
    fn_801918C4(*(s32 *)((char *)(GoalManager_GetGoal(arg0, sp8, 1)) + 0x18), arg1);
}