// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80024060-0x80024090 (48B). Byte-identical.
#include "types.h"
extern bool lbl_80300374;
extern s32 lbl_80300378;
extern s32 lbl_8030037C;
void fn_80024060(void) {
    s32 temp_r11;
    s32 temp_r0;

    temp_r0 = lbl_8030037C;
    temp_r11 = lbl_80300374;
    if (temp_r0 < temp_r11) {
        lbl_8030037C = temp_r11;
    }
    lbl_80300378 = temp_r11;
    lbl_80300374 = 0;
}
