// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FA01C-0x801FA068 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801F93F8(Unk_C7387A53 *, Unk_C8FEE62D *);
void fn_801FA01C(Unk_C7387A53 *arg0, Unk_C8FEE62D *arg1) {
    Unk_C7387A53 *var_r31;

    var_r31 = arg0->unk0xC;
    if (var_r31 != NULL) {
        do {
            fn_801F93F8(var_r31, arg1);
            var_r31 = var_r31->unk0x24;
        } while (var_r31 != NULL);
    }
}
