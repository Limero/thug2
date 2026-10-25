// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004C414-0x8004C458 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
bool fn_8004C414(Unk_9E4B1D7B *arg0, s32 arg1) {
    register s32 n __asm__("r11");
    s32 *p;
    s32 cnt = arg0->unk0x778;
    s32 i = 0;

    if (i < cnt) {
        __asm__ volatile("mr %0, %1" : "=r"(n) : "r"(cnt));
        p = (s32 *)((char *)arg0 + 0x6B8);
        do {
            s32 v = *p++;

            if (arg1 == v) {
                return true;
            }
            i += 1;
        } while (i < n);
    }
    return false;
}
