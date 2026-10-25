// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011D224-0x8011D29C (120B). Byte-identical.
#include "types.h"
extern f32 lbl_8029D5CC;
extern f32 lbl_80302CAC;
extern s32 lbl_80302CD0;
s32 fn_8011BC38();
void fn_80120924(s32);
s32 fn_8011C11C(s32, f32);
// PlayMusicStream @ 0x8011D224
void PlayMusicStream(s32 arg0, f32 farg0) {
    volatile double _dummy;
    f32 var_f31;

    var_f31 = farg0;
    if (fn_8011BC38() == 0) {
        fn_80120924(0);
        if (var_f31 < lbl_8029D5CC) {
            var_f31 = lbl_80302CAC;
        }
        fn_8011C11C(arg0, var_f31);
        lbl_80302CD0 = 1;
    }
}
