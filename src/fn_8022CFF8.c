// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022CFF8-0x8022D024 (44B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80305FCC[];
extern char lbl_80305FD4[];
extern char lbl_80305FDC[];
void fn_8022CFF8(s32 arg0) {
    s32 temp_r11;

    temp_r11 = *(s32 *)lbl_80305FDC * 4;
    *(s32 *)((char *)temp_r11 + (s32)(s32)lbl_80305FCC) = arg0;
    *(s32 *)((char *)temp_r11 + (s32)(s32)lbl_80305FD4) = 0;
}
