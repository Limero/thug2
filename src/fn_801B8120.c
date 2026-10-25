// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B8120-0x801B8168 (72B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern void fn_801B3220(Unk_C7387A53 * arg0, s32 * arg1, s32 * arg2, Unk_C8FEE62D * arg3);

void fn_801B8120(Unk_C7387A53 *arg0) {
    s32 temp_r0;
    s32 temp_r9;

    temp_r0 = arg0->unk0x24;
    temp_r9 = temp_r0 & 4;
    if (temp_r9 != 0) {
        arg0->unk0x24 = (s32)(temp_r0 & ~4);
        fn_801B3220(arg0, QB_STATE_GRINDOFF, QB_SKATERPED_STATETABLE, 0);
    }
}
