// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F3708-0x800F3740 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

bool fn_800F3708(void *arg0) {
    void **t = *(void ***) ((char *) arg0 + 0x50);
    void (*fp)(void *) = (void (*)(void *)) t[0xAC / 4];

    fp((char *) arg0 + (signed short) ((s16 *) t)[0xA8 / 2]);
    return false;
}
