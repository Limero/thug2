// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AA95C-0x800AA9DC (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void sqrtf(f32);
extern char lbl_80298374[];
extern char lbl_80298378[];
extern char lbl_8029837C[];
void fn_800AA95C(f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    f32 var_f13;
    f32 var_f1;

    if (farg0 > *(f32 *)&lbl_80298374) {
        var_f13 = farg0 / *(f32 *)&lbl_80298378;
    } else {
        var_f13 = farg0 * *(f32 *)&lbl_8029837C;
    }
    if (farg1 > *(f32 *)&lbl_80298374) {
        var_f1 = farg1 / *(f32 *)&lbl_80298378;
    } else {
        var_f1 = farg1 * *(f32 *)&lbl_8029837C;
    }
    sqrtf((var_f13 * var_f13) + (var_f1 * var_f1));
}
