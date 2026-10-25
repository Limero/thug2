// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B62A4-0x800B62EC (72B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800B63C8(Unk_C8FEE62D *);
void fn_800B62A4(Unk_C7387A53 *arg0) {
    s32 var_r30;
    void *var_r31;

    var_r30 = 6;
    var_r31 = arg0;
    do {
        fn_800B63C8(var_r31);
        var_r31 += 0x18;
        var_r30 -= 1;
    } while (var_r30 != 0);
    arg0->unk0x90 = var_r30;
}
