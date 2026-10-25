// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FF554-0x801FF57C (40B). Byte-identical.
#include "types.h"
extern f32 lbl_802AEB0C;
extern f32 lbl_802AEB10;
f32 fn_801FF554(f32 farg0, f32 farg1) {
    f32 temp_f2;

    temp_f2 = farg1 * lbl_802AEB0C * farg0;
    return temp_f2 / ((lbl_802AEB10 - farg0) + temp_f2);
}
