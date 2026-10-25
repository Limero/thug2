// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80091C88-0x80091CF8 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_803792D8[];
extern char lbl_803017F4[];
extern void memset(void *, s32, s32);
void fn_80091C88(s32 *arg0) {
    char *p;
    s32 temp_r11_2;
    u32 temp_r11;

    temp_r11 = *(u32 *)&lbl_803017F4;
    if (temp_r11 <= 7U) {
        temp_r11_2 = temp_r11 * 0x60;
        p = (char *)lbl_803792D8;
        *(s32 *)(p + temp_r11_2) = arg0;
        *arg0 = 1;
        memset((char *)lbl_803792D8 + (s32)0x58 + temp_r11_2, 0, 8);
        *(u32 *)&lbl_803017F4 += 1;
    }
}
