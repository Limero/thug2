// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80111894-0x801118C8 (52B). Byte-identical.
#include "types.h"
extern f32 lbl_8029D018;
extern f32 lbl_8029D01C;
f32 fn_80111894(f32 farg0, f32 farg1, f32 farg2) {
    f32 var_f1;

    var_f1 = ((farg0 - farg1) * farg2) + farg1;
    if (var_f1 < lbl_8029D018) {
        var_f1 = lbl_8029D018;
    }
    if (var_f1 > lbl_8029D01C) {
        var_f1 = lbl_8029D01C;
    }
    return var_f1;
}
