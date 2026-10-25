// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011C924-0x8011C97C (88B). Byte-identical.
#include "types.h"
extern s32 fn_8011BC60(void);
extern s32 fn_8011BD7C(s32 arg0, s32 arg1);
extern s32 fn_80121218(s32 arg0);
s32 fn_8011C924(s32 arg0) {
    s32 temp_r3;

    if (fn_8011BC60() != 0) {
        return 0;
    }
    temp_r3 = fn_8011BD7C(arg0, 1);
    return temp_r3 >= 0 ? fn_80121218(temp_r3) : 0;
}
