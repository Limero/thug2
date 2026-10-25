// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022DC74-0x8022DCD8 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 *fn_80240C7C(void *);                           

s32 *fn_8022DC74(Unk_C7387A53 *arg0, s32 arg1) {
    Unk_9994C3F5 *var_r31;

    var_r31 = arg0->unk0xC;
    if (var_r31 != NULL) {
loop_1:
        if ((s32) *fn_80240C7C(var_r31) == arg1) {
            return fn_80240C7C(var_r31);
        }
        var_r31 = var_r31->unk0x8;
        if (var_r31 == NULL) {
            goto block_4;
        }
        goto loop_1;
    }
block_4:
    return NULL;
}
