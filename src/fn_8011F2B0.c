// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011F2B0-0x8011F308 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_8029D6BC;
s32 fn_8011ED40(s32);
s32 fn_8011ED64(s32, s32, f32);
void fn_8011F2B0(void) {
    s32 var_r31;

    var_r31 = 0;
    do {
        if (fn_8011ED40(var_r31) != 0) {
            fn_8011ED64(var_r31, 0, lbl_8029D6BC);
        }
        var_r31 += 1;
    } while (var_r31 <= 0x3A);
}
