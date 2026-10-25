// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8026B550-0x8026B5B8 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-gcse
#include "types.h"

char *strstr(const char *searchee, const char *lookfor) {
    u32 i;

    if (*searchee == 0) {
        if (*lookfor)
            return NULL;
found:
        return (char *)searchee;
    }

    while (*searchee) {
        i = 0;
        while (1) {
            if (lookfor[i] == 0)
                goto found;
            if (lookfor[i] != searchee[i])
                break;
            i++;
        }
        searchee++;
    }
    return NULL;
}
