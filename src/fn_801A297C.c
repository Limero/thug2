// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A297C-0x801A29F0 (116B). Byte-identical.
#include "types.h"
#include "structs.h"
void *fn_801A26E0(Unk_31DE137E *, s32);
void *fn_801A297C(Unk_C7387A53 *arg0) {
    void *temp_r3;
    Unk_DB0E2BAB *temp_r9;
    void *var_r3;

    temp_r3 = fn_801A26E0(arg0, 0);
    if (temp_r3 != NULL) {
        temp_r9 = ((Unk_C8FEE62D *)temp_r3)->unk0x14;
        if (((s32 (*)(void *))temp_r9->unk0x44)(temp_r3 + temp_r9->unk0x40) != 0) {
            var_r3 = ((Unk_C8FEE62D *)temp_r3)->unk0x18;
            return var_r3;
        }
    }
    if (arg0->unk0x144 != 0) {
        var_r3 = (void *)((char *)arg0 + 0x70);
        return var_r3;
    }
    var_r3 = NULL;
    return var_r3;
}
