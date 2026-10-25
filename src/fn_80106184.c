// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80106184-0x801061DC (88B). Byte-identical.
#include "types.h"
extern s32 lbl_80302BD0;
extern s32 lbl_803CA220[];
void fn_80106184(s32 arg0) {
    s32 *var_r9;
    s32 temp_r0;
    s32 temp_r10;
    s32 temp_r11;
    s32 var_r8;

    var_r9 = lbl_803CA220;
    for (var_r8 = 0; var_r8 < 8; var_r8++) {
        temp_r11 = 1 << var_r8;
        temp_r10 = lbl_80302BD0;
        if ((temp_r10 & temp_r11) && (*var_r9 == arg0)) {
            lbl_80302BD0 = temp_r10 & ~temp_r11;
            return;
        }
        var_r9 += 1;
    }
}
