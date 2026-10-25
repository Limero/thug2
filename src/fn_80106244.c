// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80106244-0x801062AC (104B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80302BD0[];
extern s32 lbl_803CA220[];
extern void fn_801060F8(Unk_5CB48605 *, s32);
void fn_80106244(s32 arg0) {
    s32 *var_r30;
    s32 var_r31;
    s32 temp_r11;

    var_r30 = lbl_803CA220;
    var_r31 = 0;
    do {
        temp_r11 = *(u32 *)lbl_80302BD0 & (1U << var_r31);
        if (temp_r11) {
            fn_801060F8(*var_r30, arg0);
        }
        var_r30 += 1;
        var_r31 += 1;
    } while (var_r31 <= 7);
}
