// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BB444-0x801BB474 (48B). Byte-identical.
#include "types.h"
extern f32 lbl_80305F30;
extern f32 lbl_803A2F30;
void fn_801BB444(s32 arg0, s32 arg1) {
    f32 temp_f0;

    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        temp_f0 = lbl_80305F30;
        lbl_803A2F30 = temp_f0 * temp_f0;
    }
}
