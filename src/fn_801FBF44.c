// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FBF44-0x801FBF90 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801FA01C(Unk_C7387A53 *, Unk_C8FEE62D *);
void fn_801FBF44(Unk_C7387A53 *arg0, Unk_C8FEE62D *arg1) {
    CStruct *var_r31;

    var_r31 = arg0->unk0x24;
    if (var_r31 != NULL) {
        do {
            fn_801FA01C(var_r31, arg1);
            var_r31 = var_r31->unk0x4;
        } while (var_r31 != NULL);
    }
}
