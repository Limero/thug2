// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022C898-0x8022C8E0 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8022C898(Unk_D269F0B0 *arg0) {
    s32 var_r9;
    Unk_C7387A53 *var_r3;

    if ((s32) arg0->unk0x8 < 0) {
        return arg0->unk0x18;
    }
    var_r3 = arg0->unk0x10;
    var_r9 = 0;
    if (var_r3 != NULL) {
        do {
            var_r3 = var_r3->unk0x34;
            var_r9 += 1;
        } while (var_r3 != NULL);
    }
    if (var_r9 > 1) {
        return var_r9 - 1;
    }
    return 0;
}
