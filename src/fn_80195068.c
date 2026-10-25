// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80195068-0x80195098 (48B). Byte-identical.
#include "types.h"
bool fn_80195068(s32 arg0) {
    char *var_r3;
    s32 var_ctr;
    s32 temp_r0;

    var_r3 = (char *)arg0 + 0x84;
    for (var_ctr = 0x1E; var_ctr != 0; var_ctr--) {
        temp_r0 = *(s32 *)var_r3;
        var_r3 += 0x24;
        if (temp_r0 == 0) {
            return false;
        }
    }
    return true;
}
