// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F12D8-0x801F12F8 (32B). Byte-identical.
#include "types.h"
void fn_801F12D8(s32 arg0) {
    s32 *var_r3;
    s32 var_r0;
    s32 zero;
    zero = 0;
    var_r3 = (s32 *)(arg0 + 0x190);
    var_r0 = 0;
    do {
        *var_r3 = zero;
        var_r0 -= 1;
        var_r3 -= 1;
    } while (var_r0 >= 0);
}
