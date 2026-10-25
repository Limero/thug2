// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8028DF98-0x8028DFE8 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

s32 fn_8028DF3C(s32, s32);
s32 lbl_8025C558(u32, s32, s32);

s32 fn_8028DF98(u32 arg0, s32 arg1, s32 arg2) {
    if ((u32)(arg0 - 1) <= 1u) {
        return fn_8028DF3C(arg1, arg2);
    }
    if (arg0 == 0) {
        return -1;
    }
    return lbl_8025C558(arg0, arg1, arg2);
}
