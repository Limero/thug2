// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80025DF8-0x80025E2C (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_803C9E40[];
void fn_80025DF8(s32 arg0) {
    s32 var_ctr;
    void *var_r11;
    char *base;

    base = (char *)lbl_803C9E40;
    var_ctr = 0x10;
    var_r11 = NULL;
loop_1:
    if ((s32) *(s32 *)((char *)var_r11 + (s32)base) == 0) {
        *(s32 *)((char *)var_r11 + (s32)base) = arg0;
        return;
    }
    var_r11 += 4;
    var_ctr -= 1;
    if (var_ctr == 0) {
        return;
    }
    goto loop_1;
}
