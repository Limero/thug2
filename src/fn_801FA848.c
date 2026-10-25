// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FA848-0x801FA924 (220B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_801FA74C(Unk_C7387A53 * arg0, Unk_C7387A53 * arg1, f32 farg0, s32 arg2, f32 farg1, f32 farg2, f32 farg3);
extern void fn_801FB2D4(Unk_C7387A53 * arg0);
void fn_801FA848(Unk_C7387A53 *arg0, s32 arg1, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
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
    s32 var_r29;
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
    do {
        var_r31 = arg0->unk0x24;
        var_r29 = 0;
        if (var_r31 != NULL) {
            do {
                if (fn_801FA74C(arg0, var_r31, var_f28, arg1, var_f30, var_f29, var_f31) != 0) {
                    var_r29 = 1;
                }
                var_r31 = var_r31->unk0x4;
            } while (var_r31 != NULL);
        }
    } while (var_r29 != 0);
    fn_801FB2D4(arg0);
}
