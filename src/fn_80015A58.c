// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80015A58-0x80015AA8 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
s32 fn_80015BDC(s32, s32, s32);
s32 fn_80015A58(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_r30;
    s32 temp_r4;
    s32 temp_r5;
    s32 var_r3;

    temp_r5 = arg2 << 5;
    temp_r4 = (arg1 << 5) + 4;
    temp_r30 = arg0 + temp_r4 + temp_r5;
    if (fn_80015BDC(temp_r30, temp_r4, temp_r5) != 6) {
        var_r3 = 0;
    } else {
        var_r3 = temp_r30;
    }
    return var_r3;
}
