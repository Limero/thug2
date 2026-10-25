// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001E17C-0x8001E1D4 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80300330;
void VISetBlack(s32);
s32 fn_8001E17C(s32 arg0) {
    s32 temp_r31;
    temp_r31 = lbl_80300330;
    lbl_80300330 = arg0;
    if (arg0 != 0) {
        VISetBlack(arg0);
    } else {
        VISetBlack(0);
    }
    return temp_r31 != 0;
}
