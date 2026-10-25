// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80097478-0x80097500 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern u8 lbl_803018C8[];
s32 fn_8001EFBC(s32, u32 *);
void fn_80097478(u32 *arg0) {
    u32 temp;
    u32 spC;
    volatile u32 sp8;

    temp = *arg0;
    spC = temp;
    if (((s32) (temp >> 0x18) != (s32) lbl_803018C8[0]) ||
        ((s32) (u8) (temp >> 0x10) != (s32) lbl_803018C8[1]) ||
        ((s32) (u8) (temp >> 8) != (s32) lbl_803018C8[2]) ||
        ((s32) ((u8 *) &spC)[3] != (s32) lbl_803018C8[3])) {
        *(s32 *) &lbl_803018C8 = spC;
        sp8 = spC;
        fn_8001EFBC(4, &sp8);
    }
}
