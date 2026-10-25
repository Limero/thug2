// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023C64C-0x8023C6A4 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_802448E4(Unk_5AA7B5D7 *, s32);
void fn_8023C64C(Unk_31DE137E *arg0) {
    void *temp_r31;
    Unk_C8FEE62D *var_r3;

    var_r3 = arg0->unk0x60;
    if (var_r3 != NULL) {
        do {
            temp_r31 = var_r3->unk0x14;
            if (var_r3 != NULL) {
                fn_802448E4(var_r3, 3);
            }
            var_r3 = temp_r31;
        } while (var_r3 != NULL);
    }
    arg0->unk0x64 = 0;
}
