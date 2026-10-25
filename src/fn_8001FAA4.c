// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001FAA4-0x8001FB2C (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80300270[];
extern char lbl_80300284[];
extern char lbl_8030028C[];
void fn_8001FAA4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 t = arg0;

    t |= arg1 << 6;
    t |= arg2 << 0xC;
    t |= arg3 << 0x12;
    t |= arg4 << 0x18;
    (*(void (**)(s32, s32))lbl_80300284)(0x30, t);
    (*(void (**)(s32, s32))lbl_8030028C)(0x1018, 1);
    (*(void (**)(s32))lbl_80300270)(t);
}
