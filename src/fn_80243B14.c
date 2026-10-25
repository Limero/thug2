// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80243B14-0x80243B70 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_80243A48(s32, s32, s32);
void fn_80243B14(s32 arg0) {
    s32 i;
    s32 *p;
    i = 0;
    p = (s32 *)(arg0 + 4);
    do {
        if (*p != 0) {
            fn_80243A48(arg0, i, 0);
        }
        i += 1;
        p += 1;
    } while (i <= 0x1F);
}
