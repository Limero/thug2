// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80092EA4-0x80092F00 (92B). Byte-identical.
#include "types.h"
void fn_80092EA4(s32 arg0, s32 arg1) {
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_r9;
    s32 var_r9_2;

    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        var_r9 = 0x3F;
        do {
            var_ctr = 4;
loop_4:
            var_ctr -= 1;
            if (var_ctr != 0) {
                goto loop_4;
            }
            var_r9 -= 1;
        } while (var_r9 != -1);
        var_r9_2 = 7;
        do {
            var_ctr_2 = 5;
loop_8:
            var_ctr_2 -= 1;
            if (var_ctr_2 != 0) {
                goto loop_8;
            }
            var_r9_2 -= 1;
        } while (var_r9_2 != -1);
    }
}
