// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80123584-0x80123668 (228B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8029DEB4[];
extern char lbl_8029E2F4[];
int OSPanic();
void fn_80123584(u16 *dst, s32 mode, u32 *src, s32 offset, u32 count) {
    u32 i;
    u16 *s0;
    u16 *s1;

    if (mode == 1) {
        u16 *s = (u16 *)(src[0] + offset * 2);
        for (i = 0; i < count; i++) {
            *dst++ = s[i];
            *dst++ = s[i];
        }
        return;
    }
    s0 = (u16 *)(src[0] + offset * 2);
    s1 = (u16 *)(src[1] + offset * 2);
    if (mode != 2) {
        OSPanic(lbl_8029DEB4, 0x6C5, lbl_8029E2F4);
    }
    for (i = 0; i < count; i++) {
        *dst++ = *s0++;
        *dst++ = *s1++;
    }
}
