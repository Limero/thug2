// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80036194-0x800361EC (88B). Byte-identical.
// extra_cflags: -fno-sched-spec -fno-sched-interblock
#include "types.h"
void fn_800360B0(s32, s32);
void fn_80036194(s32 arg0) {
    char *var_r31;
    s32 temp_r0;
    u32 var_r30;

    var_r30 = 0U;
    var_r31 = (char *)arg0 + 0x1C;
    do {
        temp_r0 = *(s32 *)var_r31;
        var_r31 += 0x78;
        if (temp_r0 != -1) {
            fn_800360B0(arg0, var_r30);
        }
        var_r30 += 1;
    } while (var_r30 <= 3U);
}
