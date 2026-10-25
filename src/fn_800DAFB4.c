// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DAFB4-0x800DAFE4 (48B). Byte-identical.
#include "types.h"
extern u32 lbl_80301B24;
extern u32 lbl_80301B28;
extern s32 lbl_80301B2C;
void fn_800DAFB4(void) {
    u32 temp_r9;
    u32 temp_r9_2;

    temp_r9 = lbl_80301B24;
    temp_r9_2 = temp_r9 + 1;
    lbl_80301B24 = temp_r9_2;
    lbl_80301B28 = temp_r9_2;
    lbl_80301B2C = temp_r9_2 ^ (((temp_r9 >> 1U) & 1) + 1);
}
