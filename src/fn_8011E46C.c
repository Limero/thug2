// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011E46C-0x8011E4B8 (76B). Byte-identical.
#include "types.h"
extern s32 lbl_80302CA4;
void fn_8011E46C(s32 arg0) {
    if (fn_8011BC38() == 0) {
        if (lbl_80302CA4 != arg0) {
            StopMusic();
        }
        lbl_80302CA4 = arg0;
    }
}
