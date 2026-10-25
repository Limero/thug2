// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005EE18-0x8005EE4C (52B). Byte-identical.
#include "types.h"
extern char lbl_80366548[];
extern bool lbl_80366588;
s32 fn_8005EE18(void) {
    s32 var_ctr;

    if (lbl_80366588 == 0) {
        var_ctr = 4;
        do {
            var_ctr -= 1;
        } while (var_ctr != 0);
        lbl_80366588 = 1;
    }
    return (s32)lbl_80366548;
}
