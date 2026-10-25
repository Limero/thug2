// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80010D94-0x80010E78 (228B). Byte-identical.
#include "types.h"
extern s32 lbl_802FFEE0;
extern s32 lbl_802FFEA0[];
void fn_80010D94(s32 arg0, s32 arg1) {
    s32 temp_r0;

    temp_r0 = lbl_802FFEE0 + 1;
    lbl_802FFEE0 = temp_r0;
    switch (arg1) {                                 
    case 0x4:
        lbl_802FFEA0[temp_r0] = 2;
        return;
    case 0x8:
        lbl_802FFEA0[temp_r0] = 3;
        return;
    case 0x10:
        lbl_802FFEA0[temp_r0] = 4;
        return;
    case 0x20:
        lbl_802FFEA0[temp_r0] = 5;
        return;
    case 0x40:
        lbl_802FFEA0[temp_r0] = 6;
        return;
    case 0x80:
        lbl_802FFEA0[temp_r0] = 7;
        return;
    }
}
