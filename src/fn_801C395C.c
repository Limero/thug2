// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C395C-0x801C397C (32B). Byte-identical.
#include "types.h"
void fn_801C395C(s32 arg0) {
    s32 *var_r3;
    s32 var_ctr;

    var_r3 = arg0 + 0x54;
    var_ctr = 3;
    do {
        *((s32 *)var_r3) = 0;
        var_r3 = (s32 *)((char *)var_r3 - 0x14);
        var_ctr -= 1;
    } while (var_ctr != 0);
}
