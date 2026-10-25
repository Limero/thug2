// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FA9E4-0x801FAA9C (184B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_801F9988(Unk_C7387A53 * arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
s32 fn_801FA9E4(Unk_C7387A53 *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    volatile double _dummy0;
    volatile double _dummy1;
    volatile double _dummy2;
    volatile double _dummy3;
    register f32 temp_f0 __asm__("fr0");
    register f32 temp_f0_2 __asm__("fr0");
    f32 var_f28;
    f32 var_f29;
    f32 var_f30;
    f32 var_f31;
    s32 temp_r3;
    s32 var_r30;
    CStruct *var_r31;

    var_f28 = farg0;
    var_f29 = farg2;
    var_f30 = farg1;
    var_f31 = farg3;
    if (var_f28 > var_f29) {
        temp_f0 = var_f28;
        var_f28 = var_f29;
        var_f29 = temp_f0;
    }
    if (var_f30 > var_f31) {
        temp_f0_2 = var_f30;
        var_f30 = var_f31;
        var_f31 = temp_f0_2;
    }
    var_r31 = arg0->unk0x24;
    var_r30 = 0;
    if (var_r31 != NULL) {
        do {
            temp_r3 = fn_801F9988(var_r31, var_f28, var_f30, var_f29, var_f31);
            var_r31 = var_r31->unk0x4;
            var_r30 += temp_r3;
        } while (var_r31 != NULL);
    }
    return var_r30;
}
