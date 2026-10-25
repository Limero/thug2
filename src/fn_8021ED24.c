// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021ED24-0x8021ED4C (40B). Byte-identical.
#include "types.h"
void fn_8021ED24(s32 arg0, s32 arg1) {
    s32 *var_r3;
    s32 var_r9;

    var_r3 = (s32 *)((char *)arg0 + 0x54);
    var_r9 = 0;
    do {
        *(s32 *)((char *)var_r3) = *(s32 *)((char *)(var_r9 + arg1));
        var_r9 += 4;
        var_r3 += 1;
    } while (var_r9 != 0x20);
}
