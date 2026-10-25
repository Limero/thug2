// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F3A6C-0x800F3AB4 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern s32 lbl_80301BB8;
extern u8 lbl_803CA080[];

void fn_800F3A6C(void *arg0) {
    s32 i = 0;
    u8 *p = lbl_803CA080;

    do {
        if (p == arg0) {
            lbl_80301BB8 &= ~(1 << i);
            return;
        }
        p += 0x60;
        i++;
    } while (i < 4);
}
