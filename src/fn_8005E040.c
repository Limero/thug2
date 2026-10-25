// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005E040-0x8005E08C (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_803C9E18[];
void fn_800242B8(void);
void fn_8005E040(void) {
    s32 *var_r31;
    register s32 temp_r3 __asm__("r3");
    s32 *temp_r30;

    var_r31 = lbl_803C9E18;
    temp_r30 = lbl_803C9E18 + 9;
    do {
        temp_r3 = *var_r31;
        var_r31++;
        if (temp_r3 != 0) {
            fn_800242B8();
        }
    } while (var_r31 <= temp_r30);
}
