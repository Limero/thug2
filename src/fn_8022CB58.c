// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022CB58-0x8022CBBC (100B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8022C83C(Unk_C8FEE62D *);
void fn_8022CE48(Unk_C8FEE62D *, void *);
void fn_8022CB58(Unk_950BD505 *arg0) {
    void *temp_r30;
    Unk_31DE137E *var_r31;

    var_r31 = arg0->unk0x4;
    if (var_r31 != NULL) {
        do {
            temp_r30 = var_r31->unk0x1C;
            fn_8022C83C(var_r31);
            fn_8022CE48(arg0, var_r31);
            var_r31 = temp_r30;
        } while (var_r31 != NULL);
    }
    arg0->unk0x4 = NULL;
    arg0->unk0x8 = 0;
    arg0->unk0xC = 0;
}
