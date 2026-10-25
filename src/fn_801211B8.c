// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801211B8-0x80121218 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8039B8C0[];
extern f32 lbl_8029D86C;
extern f32 lbl_8029D870;
s32 fn_80120D14(s32, s32, s32, f32, f32, f32, s32);
s32 fn_801211B8(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_r3;

    temp_r3 = fn_80120D14(arg0, arg1, arg2, lbl_8029D86C, lbl_8029D86C, lbl_8029D870, 1);
    if (temp_r3 != 0) {
        *(s32 *)((char *)(arg1 * 4) + (s32)lbl_8039B8C0) = arg0;
    }
    return temp_r3;
}
