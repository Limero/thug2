// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A15DC-0x800A1680 (164B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8009EE2C(void *, s32, s32, s32);
s32 fn_800A15DC(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    register s32 r27 asm("r27") = (s32)arg0;
    register s32 r28 asm("r28") = arg1;
    register s32 r30 asm("r30") = arg2;
    register s32 r29 asm("r29") = arg3;
    s32 temp_r3;
    Unk_E71E4713 *temp_r9;
    void *var_r31;

    var_r31 = ((Unk_6A70655D *)r27)->unk0x110;
    if (var_r31 != NULL) {
loop_1:
        temp_r9 = ((Unk_C8FEE62D *)var_r31)->unk0x18;
        temp_r3 = ((s32 (*)(void *, void *, void *, void *))temp_r9->unk0x64)(var_r31 + temp_r9->unk0x60, r28, r30, r29);
        if (temp_r3 != 0) {
            if (temp_r3 == 1) {
                return 1;
            }
        } else {
            return 0;
        }
        var_r31 = ((Unk_C8FEE62D *)var_r31)->unk0x10;
        if (var_r31 == NULL) {
            goto block_6;
        }
        goto loop_1;
    }
block_6:
    return fn_8009EE2C((void *)r27, r28, r30, r29);
}
