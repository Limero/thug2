// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CD6C8-0x800CD71C (84B). Byte-identical.
#include "types.h"
extern void fn_8011BEFC(s32);
bool fn_800CD6C8(s32 arg0) {
    s32 *var_r31;
    s32 var_r30;
    s32 zero = 0;

    var_r31 = (s32 *)(arg0 + 0x1C);
    var_r30 = 3;
    do {
        if (*var_r31 != 0) {
            fn_8011BEFC(*var_r31);
            *var_r31 = zero;
        }
        var_r31 += 1;
        var_r30 -= 1;
    } while (var_r30 != 0);
    return true;
}
