// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80078FFC-0x80079028 (44B). Byte-identical.
#include "types.h"
void fn_80078FFC(s32 *arg0, s32 arg1, s32 *arg2, s32 arg3, s32 arg4) {
    s32 *var_r3;
    s32 *var_r5;
    s32 temp_r0;
    s32 var_ctr;

    var_r3 = arg0;
    var_r5 = arg2;
    var_ctr = arg4;
    if (arg4 > 0) {
        do {
            temp_r0 = *((s32 *)var_r5);
            var_r5 += arg3;
            *((s32 *)var_r3) = temp_r0;
            var_r3 += arg1;
            var_ctr -= 1;
        } while (var_ctr != 0);
    }
}
