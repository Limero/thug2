// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011BE68-0x8011BEAC (68B). Byte-identical.
#include "types.h"
extern bool lbl_80302CB8;
extern s32 lbl_80302CD0;
s32 fn_8011BC38(void);
void fn_80120924(s32);
// StopMusic @ 0x8011BE68
void StopMusic(void) {
    s32 temp_r3;

    temp_r3 = fn_8011BC38();
    if (temp_r3 == 0) {
        lbl_80302CB8 = 1;
        lbl_80302CD0 = temp_r3;
        fn_80120924(1);
    }
}
