// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80230BA4-0x80230BC4 (32B). Byte-identical.
#include "types.h"
void fn_80230BA4(s32 arg0) {
    s32 *var_r3;
    s32 var_ctr;

    var_r3 = arg0 + 0x364;
    var_ctr = 0x12;
    do {
        *((s32 *)var_r3) = 0;
        var_r3 = (s32 *)((char *)var_r3 - 0x28);
        var_ctr -= 1;
    } while (var_ctr != 0);
}
