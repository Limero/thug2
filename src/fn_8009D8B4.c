// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009D8B4-0x8009D91C (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8009D8B4(void *arg0, s32 arg1) {
    u8 *p = (u8 *)arg0 + 1;
    u32 mask = 1;
    s32 idx = 0;
    s32 ctr = 0x19;
    do {
        if ((arg1 & mask) != 0) {
            if ((u32)idx <= 3 || idx == 0x12 || idx == 0x13 || idx == 0x14 || idx == 0x15) {
                p[idx] = 0x80;
            } else {
                p[idx] = 0;
            }
        }
        mask <<= 1;
        idx += 1;
        ctr -= 1;
    } while (ctr != 0);
}
