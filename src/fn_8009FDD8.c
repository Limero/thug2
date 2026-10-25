// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009FDD8-0x8009FE04 (44B). Byte-identical.
#include "types.h"
#include "structs.h"
// GetChecksum_3 @ 0x8009FDD8
void *GetChecksum_3(Unk_6A70655D *arg0, s32 arg1) {
    CStruct *var_r3;

    var_r3 = arg0->unk0x110;
    while (var_r3 != NULL) {
        if ((s32) var_r3->unk0x4 == arg1) {
            return var_r3;
        }
        var_r3 = var_r3->unk0x10;
    }
    return NULL;
}
