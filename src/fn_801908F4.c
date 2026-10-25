// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801908F4-0x8019094C (88B). Byte-identical.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetChecksum_2(CStruct *, s32, s32 *, s32);
void *fn_801908F4(CStruct *arg0, CStruct *arg1) {
    GetChecksum_2(arg1, QB_GOAL_ID, arg0, 1);
    arg0->unk0x10 = 0;
    arg0->unk0x4 = 0;
    arg0->unk0x8 = 0;
    arg0->unk0xC = 0;
    return arg0;
}
