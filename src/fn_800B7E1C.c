// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B7E1C-0x800B7E60 (68B). Byte-identical.
#include "types.h"
extern char lbl_803CA200[];
extern char lbl_8037E778[];
void fn_800B7E1C(s32 arg0, f32 farg0) {
    char *temp_r9;
    char *temp_r11;
    f32 *var_r9;
    s32 *var_r11;
    s32 var_ctr;

    var_ctr = 8;
    temp_r11 = lbl_8037E778;
    temp_r9 = lbl_803CA200;
    var_r9 = (f32 *)(temp_r9 + 0x1C);
    var_r11 = (s32 *)(temp_r11 + 0x54);
    for (; var_ctr != 0; var_ctr--) {
        if (*var_r11 == arg0) {
            *var_r9 = farg0;
            return;
        }
        var_r9--;
        var_r11 -= 3;
    }
}
