// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A9E0C-0x800A9E80 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_800A9CE8(s32 arg0, s32 *arg1, s32 arg2);
s32 fn_800A9E0C(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp8[256];
    s32 count;

    count = fn_800A9CE8(arg0, sp8, arg2);
    if (count == 0) {
        return 0;
    }
    if (count > 0) {
        if (arg1 >= count) {
            return sp8[arg1 % count];
        }
        return sp8[arg1];
    }
    return 0;
}
