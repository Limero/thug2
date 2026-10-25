// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009DBF8-0x8009DC58 (96B). Byte-identical.
#include "types.h"
extern s32 lbl_80301A14;
s32 fn_8009DEB0(void);
s32 fn_8009DBF8(void) {
    s32 var_r0;
    s32 var_r3;
    s32 var_r3_2;

    var_r3_2 = 0;
    if (lbl_80301A14 == 0) {
        var_r3_2 = fn_8009DEB0();
        var_r0 = 1;
        if (var_r3_2 == 0) {
            var_r0 = 0;
        }
        lbl_80301A14 = var_r0;
    }
    var_r3 = 1;
    if (var_r3_2 == 0) {
        var_r3 = 0;
    }
    return var_r3;
}
