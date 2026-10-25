// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005761C-0x8005768C (112B). Byte-identical.
#include "types.h"
extern char lbl_80293220[];
extern char lbl_80293238[];
extern char lbl_80293240[];
void fn_8005761C(void *arg0, s32 arg1, s32 arg2) {
    s32 var_r30;

    if (arg2 != 0) {
        var_r30 = (s32)lbl_80293238;
    } else {
        var_r30 = (s32)lbl_80293240;
    }
    sprintf(arg0, (s32)lbl_80293220, arg1, arg1, var_r30, fn_8005570C());
}
