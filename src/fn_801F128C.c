// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F128C-0x801F12D8 (76B). Byte-identical.
#include "types.h"
s32 fn_801F125C(s32 arg0);
s32 fn_801F128C(s32 arg0, s32 arg1) {
    s32 temp_r3 = fn_801F125C(arg1);
    s32 idx;
    s32 *arr;
    if (temp_r3 == -1) {
        return 0;
    }
    idx = temp_r3 * 4;
    arr = (s32 *)((char *)arg0 + 0x190);
    return *((s32 *)((char *)arr + idx));
}
