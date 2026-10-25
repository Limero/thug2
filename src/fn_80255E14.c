// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80255E14-0x80255E34 (32B). Byte-identical.
#include "types.h"
s32 fn_80255E14(u32 arg0) {
    s32 var_r9;
    u32 var_r3;

    var_r9 = 0;
    var_r3 = arg0;
    if (var_r3 != 0) {
        do {
            var_r9 += 1;
            var_r3 = var_r3 >> 1U;
        } while (var_r3 != 0);
    }
    return var_r9;
}
