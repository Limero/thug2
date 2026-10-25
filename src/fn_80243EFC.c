// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80243EFC-0x80243F58 (92B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
void fn_80243EFC(s32 *arg0, s32 *arg1, s32 arg2) {
    s32 temp_r11 = *arg0;
    s32 temp_r9 = *arg1;

    switch (arg2) {
    case -QB_UNKNOWN_0x40000000:
        break;
    case 1:
        *(s32 *)arg0 = temp_r9;
        *(s32 *)arg1 = -temp_r11;
        return;
    case 2:
        *(s32 *)arg0 = -temp_r11;
        *(s32 *)arg1 = -temp_r9;
        return;
    case 3:
        *(s32 *)arg0 = -temp_r9;
        *(s32 *)arg1 = temp_r11;
        return;
    }
}
