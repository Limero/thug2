// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F1940-0x801F19C8 (136B). Byte-identical.
#include "types.h"
extern char lbl_802AE24C[];
extern char lbl_802AE264[];
extern char lbl_802AE280[];
extern void Script_GenerateCRC(void *);
void fn_801F1940(s32 arg0, s32 arg1) {
    char sp8[0x64];
    register s32 var_r6 __asm__("r6");

    sp8[0] = 0;
    var_r6 = arg1;
    switch (var_r6) {
    case 0:
        sprintf(sp8, (s32)lbl_802AE24C, arg0, var_r6);
        break;
    case 1:
        sprintf(sp8, (s32)lbl_802AE264, arg0, var_r6);
        break;
    default:
        var_r6 = var_r6 - 2;
        sprintf(sp8, (s32)lbl_802AE280, arg0, var_r6);
        break;
    }
    Script_GenerateCRC(sp8);
}
