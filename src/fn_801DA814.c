// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801DA814-0x801DA88C (120B). Byte-identical.
#include "types.h"
#include "structs.h"
f32 fn_801DA6D0(Unk_71062261 * arg0);
extern f32 sqrtf(f32);
extern f32 lbl_802AD5D8;
extern f32 lbl_802AD5DC;

f32 fn_801DA814(Unk_71062261 *arg0, f32 farg0, f32 farg1, f32 farg2) {
    volatile double _dummy1;
    volatile double _dummy2;
    volatile double _dummy3;
    f32 var_f31;
    f32 var_f29;
    f32 var_f30;
    f32 temp_f1;

    var_f31 = farg1 - farg0;
    var_f29 = farg2;
    var_f30 = -fn_801DA6D0(arg0);
    temp_f1 = (var_f29 * var_f29) + ((var_f30 + var_f30) * var_f31);
    if (temp_f1 < lbl_802AD5D8) {
        return lbl_802AD5DC;
    }
    return (var_f29 + sqrtf(temp_f1)) / var_f30;
}
