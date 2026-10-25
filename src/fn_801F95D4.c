// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F95D4-0x801F962C (88B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801F83E8(Unk_C7387A53 *, s32);
void fn_801F95D4(Unk_C7387A53 *arg0) {
    void *temp_r31;
    Unk_C7387A53 *var_r3;

    var_r3 = arg0->unk0xC;
    if (var_r3 != NULL) {
        do {
            temp_r31 = var_r3->unk0x24;
            if (var_r3 != NULL) {
                fn_801F83E8(var_r3, 3);
            }
            var_r3 = temp_r31;
        } while (var_r3 != NULL);
    }
    arg0->unk0xC = NULL;
}
