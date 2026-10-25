// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80036128-0x80036194 (108B). Byte-identical.
#include "types.h"
s32 fn_800360D8(s32, s32);
bool fn_80036128(s32 arg0) {
    s32 *var_r31;
    s32 temp_r0;
    u32 var_r30;

    var_r30 = 0U;
    var_r31 = arg0 + 0x1C;
loop_1:
    temp_r0 = *((s32 *)var_r31);
    var_r31 = (s32 *)((char *)var_r31 + 0x78);
    if ((temp_r0 != -1) && (fn_800360D8(arg0, var_r30) == 0)) {
        return false;
    }
    var_r30 += 1;
    if (var_r30 > 3U) {
        return true;
    }
    goto loop_1;
}
