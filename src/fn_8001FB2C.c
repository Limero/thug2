// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001FB2C-0x8001FBAC (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80300270[];
extern char lbl_80300284[];
extern char lbl_8030028C[];

void fn_8001FB2C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_r30;
    s32 temp_r5;
    s32 temp_r6;

    temp_r5 = arg2 << 0xC;
    temp_r6 = arg3 << 0x12;
    temp_r30 = arg0 | (arg1 << 6) | temp_r5 | temp_r6;
    (*(void (**)(s32, s32))lbl_80300284)(0x40, temp_r30);
    (*(void (**)(s32, s32))lbl_8030028C)(0x1019, 1);
    (*(void (**)(s32))lbl_80300270)(temp_r30);
}
