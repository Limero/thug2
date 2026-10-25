// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018694C-0x801869BC (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "types.h"
#include "types.h"
void AddChecksum(void *, void *, void *);
void fn_801270B4(void *, void *);
#include "qb_constants.h"
#include "structs.h"
s32 GoalManager_GetGoal(s32, s32, s32);
s32 fn_80191CC0(void *arg0, s32 arg1);
void fn_8018694C(s32 a0, s32 a1, s32 arg2, CScript *arg3) {
    s32 temp_r30;

    temp_r30 = fn_80191CC0(*(s32 *)(GoalManager_GetGoal((s32)a0, (s32)a1, 1) + 0x18), arg2);
    fn_801270B4(arg3->unk0x18, QB_PRO_STUFF);
    if (temp_r30 != 0) {
        AddChecksum(arg3->unk0x18, QB_PRO_STUFF, temp_r30);
    }
}