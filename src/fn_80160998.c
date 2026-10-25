// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80160998-0x801609DC (68B). Byte-identical.
#include "types.h"

extern f32 lbl_802A82B8;
extern f32 lbl_802A82BC;

f32 fn_80160998(f32 farg0) {
    f32 var_f1;

    var_f1 = farg0;
    while (var_f1 < lbl_802A82B8) {
        var_f1 += lbl_802A82BC;
    }
    while (var_f1 > lbl_802A82BC) {
        var_f1 -= lbl_802A82BC;
    }
    return var_f1;
}
