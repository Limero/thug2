// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F9734-0x801F9798 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801F8768(void *, s32, s32, f32);
void fn_801F9734(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, f32 farg0) {
    volatile double _dummy;
    Unk_C7387A53 *var_r31;

    var_r31 = arg0->unk0xC;
    if (var_r31 != NULL) {
        do {
            fn_801F8768(var_r31, arg1, arg2, farg0);
            var_r31 = var_r31->unk0x24;
        } while (var_r31 != NULL);
    }
}
