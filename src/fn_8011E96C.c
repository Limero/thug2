// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011E96C-0x8011E9A0 (52B). Byte-identical.
#include "types.h"
extern char lbl_8038EBB8[];
s32 fn_8011E96C(void) {
    s32 *var_r9;
    s32 temp_r0;
    s32 var_ctr;
    s32 var_r3;

    var_r3 = 0;
    var_ctr = 0x3B;
    var_r9 = (s32 *)lbl_8038EBB8;
loop_1:
    temp_r0 = *var_r9;
    var_r9 += 2;
    if (temp_r0 != 0) {
        var_r3 += 1;
        var_ctr -= 1;
        if (var_ctr == 0) {
            return -1;
        }
        goto loop_1;
    }
    return var_r3;
}
