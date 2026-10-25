// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009A6C0-0x8009A710 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_803018F0[];
void fn_8009A6C0(s32 **arg0) {
    s32 *temp_r0;
    s32 *temp_r0_2;
    s32 *var_r9;

    temp_r0 = *(s32 * *)&lbl_803018F0;
    if (temp_r0 == arg0) {
        *(s32 * *)&lbl_803018F0 = *arg0;
        return;
    }
    if (temp_r0 != NULL) {
        var_r9 = temp_r0;
loop_4:
        temp_r0_2 = *((s32 *)var_r9);
        if (temp_r0_2 != NULL) {
            if (temp_r0_2 == arg0) {
                *((s32 *)var_r9) = *arg0;
                return;
            }
            var_r9 = *((s32 * volatile *)var_r9);
            goto loop_4;
        }
    }
}
