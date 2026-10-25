// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003A390-0x8003A3D4 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8003A390(CStruct *arg0, s32 arg1) {
    register s32 n __asm__("r11");
    s32 *p;
    s32 cnt = arg0->unk0x4;
    s32 i = 0;

    if (i < cnt) {
        __asm__ volatile("mr %0, %1" : "=r"(n) : "r"(cnt));
        p = (s32 *)((char *)arg0 + 8);
        do {
            s32 v = *p++;

            if (arg1 == v) {
                return i;
            }
            i += 1;
        } while (i < n);
    }
    return 0;
}
