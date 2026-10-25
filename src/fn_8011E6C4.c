// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011E6C4-0x8011E710 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8011E610(CStruct *);
s32 fn_8011E6C4(s32 *arg0) {
    s32 var_r11;
    s32 var_r3;

    var_r11 = 1;
    if ((s32) *arg0 == 0) {
        var_r11 = 0;
    }
    var_r3 = 0;
    if (var_r11 != 0) {
        fn_8011E610(arg0);
        var_r3 = 1;
    }
    return var_r3;
}
