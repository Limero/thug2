// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003B9E0-0x8003BA48 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_80292018;
extern s32 lbl_803003E8;
extern void *lbl_803003EC;
void fn_80062528(s32 arg0, f32 *arg1);
void fn_80037B7C(void *arg0);
bool fn_8003B9E0(void) {
    f32 sp8[4];
    f32 *var_r9;
    f32 temp_f0;

    var_r9 = sp8;
    temp_f0 = lbl_80292018;
    var_r9[0] = temp_f0;
    var_r9[1] = temp_f0;
    var_r9[2] = temp_f0;
    var_r9[3] = temp_f0;
    fn_80062528(lbl_803003E8, var_r9);
    if (lbl_803003EC != 0) {
        fn_80037B7C(lbl_803003EC);
        return true;
    }
    return false;
}
