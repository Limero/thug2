// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FB2A8-0x801FB2D4 (44B). Byte-identical.
#include "types.h"
#include "structs.h"
void *fn_801FB2A8(Unk_C7387A53 *arg0, s32 arg1) {
    CStruct *var_r3;

    var_r3 = arg0->unk0x24;
    while (var_r3 != NULL) {
        if ((s32) var_r3->unk0x10 == arg1) {
            return var_r3;
        }
        var_r3 = var_r3->unk0x4;
    }
    return NULL;
}
