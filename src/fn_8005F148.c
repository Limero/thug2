// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005F148-0x8005F188 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

void fn_8005F148(void *o, s32 a1, s32 a2, s32 *a3, s32 a4, s32 a5) {
    void *t;
    s32 sp8;

    sp8 = *a3;
    t = *(void **)((char *)o + 0x14);
    ((void (*)(void *, s32, s32, s32 *, s32, s32))*(void **)((char *)t + 0x54))(
        (char *)o + *(s16 *)((char *)t + 0x50), a1, a2, &sp8, a4, a5);
}
