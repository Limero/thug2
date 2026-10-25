// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011BE24-0x8011BE68 (68B). Byte-identical.
#include "types.h"
extern s32 fn_8011BD0C(s32);
s32 fn_8011BE24(s32 arg0) {
    s32 var_r31;

    var_r31 = arg0;
    while (fn_8011BD0C(var_r31) == 0) {
        var_r31 += 1;
    }
    return var_r31;
}
