// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000901C-0x800090F0 (212B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-expensive-optimizations
#include "types.h"
u32 fn_8000901C(u32 *arg0, s32 arg1) {
    s32 temp_r5;
    u32 *temp_r8;
    u32 temp_r0;
    u32 var_r6;

    arg0[5] = arg0[5] + arg1;
    if (arg0[3] == 0) {
        u32 *p = (u32 *)arg0[0];
        register u32 v __asm__("r0");
        v = *p;
        arg0[3] = 0x20;
        arg0[0] = (u32)(p + 1);
        arg0[2] = v;
    }
    temp_r5 = arg0[3];
    if (temp_r5 >= arg1) {
        arg0[3] = temp_r5 - arg1;
        if (arg1 == 0x20) {
            var_r6 = arg0[2];
        } else {
            var_r6 = arg0[2] & ((1 << arg1) - 1);
        }
        arg0[2] = arg0[2] >> arg1;
    } else {
        temp_r8 = (u32 *)arg0[0];
        arg1 = arg1 - temp_r5;
        temp_r0 = *temp_r8;
        var_r6 = (arg0[2] & ((1 << temp_r5) - 1)) | ((temp_r0 & ((1 << arg1) - 1)) << temp_r5);
        arg0[0] = (u32)(temp_r8 + 1);
        arg0[2] = temp_r0 >> arg1;
        arg0[3] = 0x20 - arg1;
    }
    return var_r6;
}
