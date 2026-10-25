// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800095B8-0x800095F0 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

// LowerCase @ 0x800095B8
void LowerCase(u8 *arg0) {
    u8 c = *arg0;
    if (c == 0) return;
    do {
        s8 d = (s8)c;
        if ((u32)(d - 0x41) <= 0x19U) d += 0x20;
        *arg0 = (u8)d;
        c = *(++arg0);
    } while (c != 0);
}
