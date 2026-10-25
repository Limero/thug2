// Promoted from src/wip 2026-09-19 (sda route).
// extra_cflags: -msdata=eabi, -G4
// range 0x8024EA94-0x8024EAD4 (64B). Verified LINK-SIM EXACT (tools/sda_verify.py).
// ID: skeleton clear path: if (arg0) fn_80252C3C(arg0, 3);
//     then, if the sdata global lbl_803CA340 is live, fn_8024EE6C(lbl_803CA340, 3).
// The r13-relative global access needs the per-object -msdata=eabi -G4 override.
#include "types.h"

extern s32 lbl_803CA340;
void fn_80252C3C(s32, s32);
void fn_8024EE6C(s32, s32);

void fn_8024EA94(s32 arg0) {
    if (arg0 != 0) {
        fn_80252C3C(arg0, 3);
    }
    if (lbl_803CA340 != 0) {
        fn_8024EE6C(lbl_803CA340, 3);
    }
}
