// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009DC58-0x8009DC9C (68B). Byte-identical.
#include "types.h"
extern s32 lbl_80301A14;
s32 fn_8009DC58(void) {
    s32 var_r3;

    var_r3 = 1;
    if (lbl_80301A14 != 0) {
        var_r3 = fn_8009DEB8();
        lbl_80301A14 = 0;
    }
    return var_r3;
}
