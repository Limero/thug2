// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020740C-0x80207430 (36B). Byte-identical.
#include "types.h"
void fn_8020740C(void *arg0, s32 *arg1) {
    char *var_r3;
    s32 *var_r4;
    s32 temp_r0;
    s32 var_ctr;

    var_r4 = arg1;
    var_r3 = (char *)arg0 + 0x9A0;
    var_ctr = 3;
    do {
        temp_r0 = *var_r4;
        var_r4 += 1;
        *(s32 *)var_r3 = temp_r0;
        var_r3 += 4;
        var_ctr -= 1;
    } while (var_ctr != 0);
}
