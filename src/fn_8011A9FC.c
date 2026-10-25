// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011A9FC-0x8011AA4C (80B). Byte-identical.
#include "types.h"
s32 fn_8011ED40(s32);                               

s32 fn_8011A9FC(void) {
    s32 var_r30;
    s32 var_r31;

    var_r30 = 0;
    var_r31 = 0;
    do {
        if (fn_8011ED40(var_r31) != 0) {
            var_r30 += 1;
        }
        var_r31 += 1;
    } while (var_r31 <= 0x3A);
    return var_r30;
}
