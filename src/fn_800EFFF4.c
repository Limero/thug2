// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EFFF4-0x800F0074 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800EFE0C(void *, s32);
void fn_800EFFF4(CStruct *arg0, s32 arg1) {
    void *temp_r31;
    Unk_C7387A53 *var_r29;
    CStruct *var_r3;

    var_r3 = arg0->unk0x4;
    var_r29 = NULL;
    if (var_r3 != NULL) {
        do {
            temp_r31 = var_r3->unk0xC;
            if ((s32) var_r3->unk0x8 == arg1) {
                if (var_r29 != NULL) {
                    var_r29->unk0xC = temp_r31;
                } else {
                    arg0->unk0x4 = temp_r31;
                }
                if (var_r3 != NULL) {
                    fn_800EFE0C(var_r3, 3);
                }
            } else {
                var_r29 = var_r3;
            }
            var_r3 = temp_r31;
        } while (var_r3 != NULL);
    }
}
