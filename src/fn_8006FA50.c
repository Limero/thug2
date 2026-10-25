// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006FA50-0x8006FA90 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern u8 lbl_80366DD8[];
void fn_8006FA50(s32 arg0, s32 arg1) {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;

    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        b0 = 0x60;
        b1 = 0x60;
        b2 = 0x80;
        b3 = 0x66;
        lbl_80366DD8[0] = b0;
        lbl_80366DD8[1] = b1;
        lbl_80366DD8[2] = b2;
        lbl_80366DD8[3] = b3;
    }
}
