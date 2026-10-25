// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800057F4-0x80005854 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

void fn_800057F4(f32 *arg0, s32 arg1)
{
    f32 T, U;

    if (arg1 == 1) {
        goto c1;
    }
    if (arg1 <= 1) {
        return;
    }
    if (arg1 == 2) {
        goto c2;
    }
    if (arg1 == 3) {
        goto c3;
    }
    return;

c1:
    T = arg0[0];
    U = arg0[2];
store:
    T = -T;
    __asm__("" : "+f"(T));
    *(volatile f32 *)&arg0[0] = U;
    *(volatile f32 *)&arg0[2] = T;
    return;

c2:
    U = arg0[0];
    U = -U;
    T = arg0[2];
    goto store;

c3:
    U = arg0[2];
    T = arg0[0];
    U = -U;
    *(volatile f32 *)&arg0[0] = U;
    *(volatile f32 *)&arg0[2] = T;
    return;
}
