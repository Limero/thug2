// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FA5E4-0x801FA628 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801F9798(Unk_C7387A53 *);
void fn_801FA5E4(Unk_C7387A53 *arg0) {
    CStruct *var_r31;

    var_r31 = arg0->unk0x24;
    if (var_r31 != NULL) {
        do {
            fn_801F9798(var_r31);
            var_r31 = var_r31->unk0x4;
        } while (var_r31 != NULL);
    }
}
