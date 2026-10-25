// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80053D10-0x80053E40 (304B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_80292FD4;
extern f32 lbl_80292FD8;
extern f32 lbl_80292FE8;
void fn_80053D10(f32 *arg0, f32 *arg1, f32 *arg2, s32 arg5, f32 farg0, f32 farg1, f32 farg2) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f13;
    s32 temp_r9;

    if (farg1 == lbl_80292FD4) {
        *arg2 = farg2;
        *arg1 = farg2;
        *arg0 = farg2;
        return;
    }
    farg0 = farg0 / lbl_80292FD8;
    temp_f12 = lbl_80292FE8;
    temp_f10 = farg2 * (temp_f12 - farg1);
    temp_r9 = (s32) farg0;
    temp_f0 = farg0 - (f32) (f64) temp_r9;
    temp_f0_2 = farg2 * (temp_f12 - (farg1 * temp_f0));
    temp_f13 = farg2 * (temp_f12 - (farg1 * (temp_f12 - temp_f0)));
    switch (temp_r9) {
    case 0:
        *arg0 = farg2;
        *arg1 = temp_f13;
        *arg2 = temp_f10;
        return;
    case 1:
        *arg0 = temp_f0_2;
        *arg1 = farg2;
        *arg2 = temp_f10;
        return;
    case 2:
        *arg0 = temp_f10;
        *arg1 = farg2;
        *arg2 = temp_f13;
        return;
    case 3:
        *arg0 = temp_f10;
        *arg1 = temp_f0_2;
        *arg2 = farg2;
        return;
    case 4:
        *arg0 = temp_f13;
        *arg1 = temp_f10;
        *arg2 = farg2;
        return;
    default:
        *arg0 = farg2;
        *arg1 = temp_f10;
        *arg2 = temp_f0_2;
        return;
    }
}
