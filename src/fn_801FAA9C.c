// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FAA9C-0x801FAB28 (140B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_801F9A24(Unk_C7387A53 * arg0, void * arg1, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void fn_801FAA9C(Unk_C7387A53 *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    volatile double _dummy0;
    volatile double _dummy1;
    volatile double _dummy2;
    volatile double _dummy3;
    f32 var_f28;
    f32 var_f29;
    f32 var_f30;
    f32 var_f31;
    s32 var_r3;
    CStruct *var_r31;

    var_r31 = arg0->unk0x24;
    var_f28 = farg0;
    var_f29 = farg1;
    var_f30 = farg2;
    var_f31 = farg3;
    var_r3 = 0;
    if (var_r31 != NULL) {
        do {
            var_r3 = fn_801F9A24(var_r31, var_r3, var_f28, var_f29, var_f30, var_f31);
            var_r31 = var_r31->unk0x4;
        } while (var_r31 != NULL);
    }
}
