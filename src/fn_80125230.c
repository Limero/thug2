// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80125230-0x80125274 (68B). Byte-identical.
#include "types.h"
extern char lbl_80303188[];
extern s32 lbl_80303190;
// DeleteString @ 0x80125230
void DeleteString(u32 arg0) {
    u32 temp_r11;

    temp_r11 = *(u32 *)&lbl_80303188;
    if ((arg0 < temp_r11) || (arg0 >= (u32) (temp_r11 + lbl_80303190))) {
        Mem_Free_3();
    }
}
