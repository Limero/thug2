// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8028D328-0x8028D340 (24B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns -fno-schedule-insns2
#include "types.h"
void fn_8028D328(s32 *arg0, s32 arg1, s32 arg2) {
    s32 sum;
    arg0[0] = arg1;
    sum = arg1 + arg2;
    arg0[2] = arg1;
    arg0[3] = sum;
    arg0[1] = arg2;
}
