// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009D020-0x8009D084 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern volatile char lbl_8030191C[];
extern volatile char lbl_80301920[];
void fn_8009D174(s32, s32);
void fn_8009D020(void) {
    u32 temp_r9;
    s32 temp_r3;

    temp_r9 = *(volatile u32 *)&lbl_80301920;
    if (temp_r9 > 1U) {
        *(volatile u32 *)&lbl_80301920 = temp_r9 - 1;
        return;
    }
    temp_r3 = *(volatile s32 *)&lbl_8030191C;
    if (temp_r3 != 0) {
        fn_8009D174(temp_r3, 3);
    }
    *(volatile u32 *)&lbl_80301920 = 0U;
    *(volatile s32 *)&lbl_8030191C = 0;
}
