// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A6820-0x801A6848 (40B). Byte-identical.
#include "types.h"
s32 fn_801A6820(u32 arg0, s32 arg1) {
    s32 var_ctr;
    s32 var_r9;
    u32 var_r3;

    var_r3 = arg0;
    var_r9 = 0;
    var_ctr = 0x20;
    do {
        if (var_r3 & 1) {
            var_r9 += 1;
        }
        var_r3 = var_r3 >> 1U;
        var_ctr -= 1;
    } while (var_ctr != 0);
    return var_r9;
}
