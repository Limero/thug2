// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80045870-0x800458E4 (116B). Byte-identical.
#include "types.h"
extern f32 lbl_802927BC;
extern f32 lbl_802927C0;
extern f32 lbl_802927C4;
extern f32 lbl_802927C8;
extern f32 lbl_802927CC;
f32 fn_80045870(f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;

    temp_f12 = lbl_802927C0;
    temp_f0 = -(((farg0 * farg2) / (((farg0 / lbl_802927BC) + temp_f12) * lbl_802927C4)) / farg3);
    temp_f2 = -(((farg1 * farg2) / (((farg0 / lbl_802927C8) + temp_f12) * lbl_802927CC)) / farg4);
    return (temp_f0 < temp_f2) ? temp_f0 : temp_f2;
}
