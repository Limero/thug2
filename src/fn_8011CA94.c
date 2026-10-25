// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011CA94-0x8011CAF0 (92B). Byte-identical.
#include "types.h"
extern f32 lbl_8029D5AC;
extern f32 lbl_80302CAC;
s32 fn_8011BC38(void);
s32 fn_8011C3D0(f32);
s32 fn_8011CA94(f32 farg0) {
    volatile double _dummy;
    f32 var_f31;

    var_f31 = farg0;
    if (fn_8011BC38() != 0) {
        return 0;
    }
    if (var_f31 < lbl_8029D5AC) {
        var_f31 = lbl_80302CAC;
    }
    return fn_8011C3D0(var_f31);
}
