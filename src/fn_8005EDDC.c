// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005EDDC-0x8005EE10 (52B). Byte-identical.
#include "types.h"
extern char lbl_80366500[];
extern bool lbl_80366540;
s32 fn_8005EDDC(void) {
    s32 var_ctr;

    if (lbl_80366540 == 0) {
        var_ctr = 4;
        do {
            var_ctr -= 1;
        } while (var_ctr != 0);
        lbl_80366540 = 1;
    }
    return (s32)lbl_80366500;
}
