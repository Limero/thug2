// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023B15C-0x8023B17C (32B). Byte-identical.
#include "types.h"
void fn_8023B15C(s32 arg0, s32 arg1, s32 arg2) {
    if ((u32)(arg1 - 1) <= 7U) {
        s32 *base = (s32 *)((char *)arg0 + 0x177A4);
        base[arg1] = arg2;
    }
}
