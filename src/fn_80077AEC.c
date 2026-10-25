// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80077AEC-0x80077B30 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_80295764;
extern f32 lbl_80377648[4];
extern bool lbl_80377658;
f32 *fn_80077AEC(void) {
    f32 temp_f0;

    if (lbl_80377658 == 0) {
        temp_f0 = lbl_80295764;
        lbl_80377658 = 1;
        lbl_80377648[0] = temp_f0;
        lbl_80377648[1] = temp_f0;
        lbl_80377648[2] = temp_f0;
        lbl_80377648[3] = temp_f0;
    }
    return lbl_80377648;
}
