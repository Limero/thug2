// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80106134-0x80106184 (80B). Byte-identical.
#include "types.h"
extern s32 lbl_80302BD0;
extern s32 lbl_803CA220[];
void fn_80106134(s32 arg0) {
    s32 *var_r9;
    s32 temp_r0;
    s32 temp_r11;
    s32 var_r10;

    var_r9 = lbl_803CA220;
    for (var_r10 = 0; var_r10 < 8; var_r10++) {
        temp_r0 = 1 << var_r10;
        temp_r11 = lbl_80302BD0;
        if (!(temp_r11 & temp_r0)) {
            *var_r9 = arg0;
            lbl_80302BD0 = temp_r11 | temp_r0;
            return;
        }
        var_r9 += 1;
    }
}
