// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801298EC-0x8012998C (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
u8 *fn_80129574(u8 *, s8, s32);
s32 fn_801298EC(s32 arg0, u8 *arg1, u8 *arg2, u32 arg3) {
    u32 len;
    u32 i;
    u8 *base;

    len = strlen(arg1);
    base = arg2;
    if (arg3 < (u32)(len + 6)) {
        return 0;
    }
    arg2 = fn_80129574(arg2, 3, arg0);
    for (i = 0; i < len; i++) {
        *arg2 = *arg1;
        arg1++;
        arg2++;
    }
    *arg2 = 0;
    arg2++;
    return arg2 - base;
}
