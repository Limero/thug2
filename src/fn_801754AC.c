// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801754AC-0x80175504 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_8009CF2C(s32);
extern char lbl_80305EC0[];
extern char lbl_80305F9C[];
s32 fn_80198CD0(s32);
s32 fn_801754AC(s32 arg0) {
    s32 var_r31;

    var_r31 = 0;
    if ((fn_8009CF2C(*(s32 *)&lbl_80305F9C) != 0) || (fn_80198CD0(*(s32 *)&lbl_80305EC0) > 1U)) {
        var_r31 = 1;
    }
    return var_r31;
}