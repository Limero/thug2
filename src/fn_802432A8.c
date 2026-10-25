// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802432A8-0x802432E8 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8023F7C8(void *);
void fn_802432A8(void *arg0) {
    void *temp_r30;
    Unk_C7387A53 *var_r30;

    var_r30 = arg0;
    if (var_r30 != NULL) {
        do {
            temp_r30 = var_r30->unk0xC;
            fn_8023F7C8(var_r30);
            var_r30 = temp_r30;
        } while (var_r30 != NULL);
    }
}
