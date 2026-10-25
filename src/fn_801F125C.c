// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F125C-0x801F128C (48B). Byte-identical.
#include "types.h"
extern char lbl_80305F48[];
s32 fn_801F125C(s32 arg0) {
    char *var_r9;
    s32 temp_r0;
    s32 var_r3;

    var_r9 = lbl_80305F48;
    var_r3 = 0;
loop_1:
    temp_r0 = *((s32 *)var_r9);
    var_r9 += 4;
    if (temp_r0 != arg0) {
        var_r3 += 1;
        if (var_r3 > 0) {
            return -1;
        }
        goto loop_1;
    }
    return var_r3;
}
