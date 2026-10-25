// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802025AC-0x802025DC (48B). Byte-identical.
#include "types.h"
bool fn_802025AC(s32 arg0) {
    s32 *var_r3;
    s32 var_ctr;

    var_r3 = arg0 + 0x30;
    var_ctr = 0x46;
    do {
        if ((s32) *((s32 *)var_r3) == 2) {
            *((s32 *)var_r3) = 0;
        }
        var_r3 = (s32 *)((char *)var_r3 + 0x24);
        var_ctr -= 1;
    } while (var_ctr != 0);
    return true;
}
