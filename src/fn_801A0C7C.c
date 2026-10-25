// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A0C7C-0x801A0CC0 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_803A2E40[];
extern f32 lbl_802AB0D0;
extern f32 lbl_802AB0D4;
void fn_801A0C7C(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF && arg0 != 0) {
        f32 v = lbl_802AB0D0;
        lbl_803A2E40[0] = v;
        lbl_803A2E40[1] = v;
        lbl_803A2E40[2] = v;
        lbl_803A2E40[3] = lbl_802AB0D4;
    }
}
