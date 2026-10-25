// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FB15C-0x801FB1C4 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_801F9594(CStruct *, s32);
void fn_801FB50C(Unk_C7387A53 *);
void fn_801FB15C(Unk_C7387A53 *arg0) {
    void *temp_r31;
    CStruct *var_r3;

    var_r3 = arg0->unk0x24;
    if (var_r3 != NULL) {
        do {
            temp_r31 = var_r3->unk0x4;
            if (var_r3 != NULL) {
                fn_801F9594(var_r3, 3);
            }
            var_r3 = temp_r31;
        } while (var_r3 != NULL);
    }
    arg0->unk0x24 = NULL;
    arg0->unk0x28 = 0;
    arg0->unk0x2C = 0;
    fn_801FB50C(arg0);
}
