// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000A7F8-0x8000A868 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern u32 lbl_802FFA3C[];
u32 fn_8000A7F8(u32 arg0, s8 *arg1) {
    u32 hash;
    s8 c;

    hash = arg0;
    if (arg1 == NULL) {
        return hash;
    }
    c = *arg1;
    arg1++;
    if (c == 0) {
        return hash;
    }
    do {
        if ((u32)(c - 0x41) <= 0x19) {
            c += 0x20;
        }
        if (c == 0x2F) {
            c = 0x5C;
        }
        hash = lbl_802FFA3C[(hash ^ c) & 0xFF] ^ (hash >> 8);
        c = *arg1;
        arg1++;
    } while (c != 0);
    return hash;
}
