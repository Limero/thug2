// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801252F0-0x80125320 (48B). Byte-identical.
#include "types.h"
bool fn_801252F0(s32 *arg0) {
    s32 temp_r11;

    temp_r11 = *arg0 & 0x7F0000;
    if ((temp_r11 == 0x140000) || (temp_r11 == 0x150000)) {
        return true;
    }
    return false;
}
