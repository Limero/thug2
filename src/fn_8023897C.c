// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023897C-0x802389D0 (84B). Byte-identical.
#include "types.h"
void *fn_8023897C(void *arg0, s32 arg1, s32 *arg2) {
    s32 count = 0;
    u8 *p;
    s32 ctr;
    if (count < arg1) {
        p = (u8 *)arg0 + 0x108C0;
        ctr = arg1;
        do {
            u8 v = *p;
            p += 0x154;
            if (v != 0) {
                count++;
            }
            ctr -= 1;
        } while (ctr != 0);
    }
    if (arg2 != NULL) {
        *arg2 = count;
    }
    return (u8 *)arg0 + 0x10770 + arg1 * 0x154;
}
