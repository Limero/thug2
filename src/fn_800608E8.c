// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800608E8-0x80060934 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800608E8(Unk_C8FEE62D *arg0, s32 arg1) {
    void ** volatile sp8;
    void **var_r9;
    CStruct *temp_r3;
    Unk_C8FEE62D *temp_r9;

    if ((s32) arg0->unk0x14 != 0) {
        temp_r3 = (CStruct *)arg0->unk0x10;
        var_r9 = NULL;
        if (temp_r3 != NULL) {
            var_r9 = (void **)temp_r3->unk0x4;
        }
        sp8 = var_r9;
        temp_r9 = (Unk_C8FEE62D *)*((s32 *)var_r9);
        if (temp_r9 != NULL) {
            if (temp_r9->unk0x14 == 0) {
                temp_r9->unk0x14 = arg1;
            }
        }
    }
}
