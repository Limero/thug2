// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800158D8-0x8001593C (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_80015A30(void *, s32);
void fn_800158D8(void) {
    extern s32 lbl_802FFF6C;
    extern s32 lbl_802FFF70;
    u32 temp_r9;

    temp_r9 = (u32)lbl_802FFF70;
    if (temp_r9 > 1U) {
        *(volatile s32 *)&lbl_802FFF70 = temp_r9 - 1;
        return;
    }
    if (lbl_802FFF6C != 0) {
        fn_80015A30(lbl_802FFF6C, 3);
    }
    *(volatile s32 *)&lbl_802FFF70 = 0;
    *(volatile s32 *)&lbl_802FFF6C = 0;
}