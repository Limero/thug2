// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F1F2C-0x800F1F74 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
bool fn_800F1F2C(Unk_A231C4C2 *arg0, s32 arg1) {
    register u32 nh __asm__("r0");
    u32 n;
    s32 *p;
    u32 i = 0;

    nh = *(u32 *)((char *)arg0 + 0x10008);
    if (i < nh) {
        n = nh;
        p = (s32 *)((char *)arg0 + 0x1000C);
        do {
            s32 e = *p;
            p += 3;
            if (arg1 == e) {
                return true;
            }
            i += 1;
        } while (i < n);
    }
    return false;
}
