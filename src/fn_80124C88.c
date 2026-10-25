// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80124C88-0x80124CEC (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern volatile char lbl_80303148[];
extern volatile char lbl_8030314C[];
void fn_80124D40(s32, s32);
void fn_80124C88(void) {
    u32 temp_r9;
    s32 temp_r3;

    temp_r9 = *(volatile u32 *)&lbl_8030314C;
    if (temp_r9 > 1U) {
        *(volatile u32 *)&lbl_8030314C = temp_r9 - 1;
        return;
    }
    temp_r3 = *(volatile s32 *)&lbl_80303148;
    if (temp_r3 != 0) {
        fn_80124D40(temp_r3, 3);
    }
    *(volatile u32 *)&lbl_8030314C = 0U;
    *(volatile s32 *)&lbl_80303148 = 0;
}
