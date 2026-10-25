// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80054894-0x80054904 (112B). Byte-identical.
#include "types.h"
extern char lbl_802930F8[];
extern char lbl_80293110[];
extern char lbl_80293118[];
void fn_80054894(void *arg0, s32 arg1, s32 arg2) {
    s32 var_r30;

    if (arg2 != 0) {
        var_r30 = (s32)lbl_80293110;
    } else {
        var_r30 = (s32)lbl_80293118;
    }
    sprintf(arg0, (s32)lbl_802930F8, arg1, arg1, var_r30, fn_8005570C());
}
