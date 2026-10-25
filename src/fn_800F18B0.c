// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F18B0-0x800F18D8 (40B). Byte-identical.
#include "types.h"
void fn_800F18B0(s32 arg0, s32 arg1, u16 arg2) {
    s32 var_ctr;
    u16 *var_r3;

    var_r3 = (u16 *)(arg0 + 2);
    var_ctr = 0x4000;
    do {
        if ((s32) *var_r3 == arg1) {
            *var_r3 = arg2;
        }
        var_r3 += 2;
        var_ctr -= 1;
    } while (var_ctr != 0);
}
