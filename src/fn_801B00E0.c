// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B00E0-0x801B0144 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80305F24;
extern s32 lbl_80305F28;
void fn_801B0E6C(void *arg0, s32 arg1);
void fn_801B00E0(void) {
    s32 t;
    s32 f;
    t = lbl_80305F28;
    if ((u32)t > 1U) {
        lbl_80305F28 = t - 1;
        return;
    }
    f = lbl_80305F24;
    if (f != 0) {
        fn_801B0E6C((void *)f, 3);
    }
    lbl_80305F24 = 0;
    lbl_80305F28 = 0;
}
