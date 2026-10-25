// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800095F0-0x80009628 (56B). Byte-identical.
#include "types.h"
// UpperCase @ 0x800095F0
void UpperCase(u8 *arg0) {
    while (*arg0 != 0) {
        s8 c = (s8)*arg0;
        if ((u32)(c - 'a') <= 0x19U) {
            c -= 0x20;
        }
        *arg0 = c;
        arg0++;
    }
}
