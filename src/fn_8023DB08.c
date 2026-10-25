// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023DB08-0x8023DB80 (120B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_802448E4(Unk_5AA7B5D7 *, s32);
void fn_8023DB08(Unk_31DE137E *arg0) {
    void *var_r0;
    Unk_C8FEE62D *var_r31;
    Unk_C8FEE62D *var_r3;

    var_r31 = NULL;
    var_r0 = arg0->unk0x60;
    var_r3 = NULL;
    if (var_r0 != NULL) {
        do {
            var_r31 = var_r3;
            var_r3 = var_r0;
            var_r0 = var_r3->unk0x14;
        } while (var_r0 != NULL);
    }
    if (var_r3 != NULL) {
        fn_802448E4(var_r3, 3);
        if (var_r31 != NULL) {
            var_r31->unk0x14 = 0;
            return;
        }
        arg0->unk0x60 = var_r31;
    }
}
