// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016F668-0x8016F69C (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_8016F668(s32 arg0) {
    s32 n = 0;
    char *p = (char *)arg0 + 0x198;
    if (*(s32 *)(p + n) != 0) {
        while (1) {
            n += 1;
            if (n > 1) break;
            p += 0x190;
            if (*(s32 *)p == 0) break;
        }
    }
    return n;
}
