// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800176B8-0x80017700 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern char lbl_80300160[];
extern char lbl_80312434[];

s32 fn_800176B8(void)
{
    char *dst = lbl_80300160;
    char *src = lbl_80312434;
    s32 result = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        u16 v = *(u16 *)(src + (i * 0xC));
        u16 old = *(u16 *)(dst + (i * 2));
        u16 diff;

        *(u16 *)(dst + (i * 2)) = v;
        diff = old ^ v;
        __asm__("" : "+r"(diff));
        result |= v & diff;
    }
    return result;
}
