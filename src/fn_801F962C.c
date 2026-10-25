// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F962C-0x801F9670 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801F8D2C(Unk_C8FEE62D *);
void fn_801F962C(Unk_C7387A53 *arg0) {
    Unk_C7387A53 *var_r31;

    var_r31 = arg0->unk0xC;
    if (var_r31 != NULL) {
        do {
            fn_801F8D2C(var_r31);
            var_r31 = var_r31->unk0x24;
        } while (var_r31 != NULL);
    }
}
