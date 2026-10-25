// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001ECB0-0x8001EDE0 (304B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern s32 lbl_80300258;
extern void (*lbl_80300280)(u32);
extern u8 lbl_803002D0[8];
extern s32 lbl_803002E0[20];

void fn_8001ECB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    lbl_80300280(((u32)lbl_803002E0[lbl_80300258] + 0xFFF80000U) >> 9 |
                 (arg1 << 10) | (lbl_803002D0[arg3] << 24));
    lbl_80300280(0xFEFFFF00);
    lbl_80300280(0x0F000000);
    lbl_80300280(((u32)arg0 + 0x80000000U) >> 5 | 0x64000000U);
    lbl_80300280(((u32)lbl_803002E0[lbl_80300258] + 0xFFF80000U) >> 9 |
                 (arg2 << 10) | 0x65000000U);
    lbl_80300280(0xFEFFFF00);
    lbl_80300280(0x0F000000);
    lbl_80300258 = (lbl_80300258 + 1) % 20;
}
