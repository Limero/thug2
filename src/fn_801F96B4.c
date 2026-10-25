// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F96B4-0x801F9734 (128B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801F8430(Unk_C7387A53 *, s32, s32, f32);
void fn_801F96B4(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, f32 farg0) {
    volatile double _dummy;
    void *var_r0;
    Unk_C7387A53 *var_r31;

    var_r31 = arg0->unk0xC;
    var_r0 = NULL;
    if (var_r31 != NULL) {
        do {
            var_r0 = var_r31;
            var_r31 = var_r31->unk0x24;
        } while (var_r31 != NULL);
    }
    var_r31 = var_r0;
    if (var_r31 != NULL) {
        do {
            fn_801F8430(var_r31, arg1, arg2, farg0);
            var_r31 = var_r31->unk0x28;
        } while (var_r31 != NULL);
    }
}
