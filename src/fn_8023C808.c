// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023C808-0x8023C84C (68B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80245500(CStruct *);
void fn_8023C808(Unk_31DE137E *arg0) {
    Unk_C8FEE62D *var_r31;

    var_r31 = arg0->unk0x60;
    if (var_r31 != NULL) {
        do {
            fn_80245500(var_r31);
            var_r31 = var_r31->unk0x14;
        } while (var_r31 != NULL);
    }
}
