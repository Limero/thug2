// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009FE78-0x8009FEB4 (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

bool fn_8009FE78(void *arg0, s32 arg1) {
    void **t = *(void ***) ((char *) arg0 + 0x8);
    void (*fp)(void *, s32, s32) = (void (*)(void *, s32, s32)) t[0x54 / 4];

    fp((char *) arg0 + (signed short) ((s16 *) t)[0x50 / 2], arg1, 0);
    return true;
}
