// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D1204-0x800D1230 (44B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_800D12DC(void *);
void fn_800D1204(Unk_C7387A53 *arg0) {
    s32 temp_r9;

    temp_r9 = arg0->unk0x90 & QB_UNKNOWN_0x20000000;
    if (temp_r9 != 0) {
        fn_800D12DC(arg0);
    }
}
