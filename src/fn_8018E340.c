// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018E340-0x8018E3B8 (120B). Byte-identical.
#include "types.h"
#include "structs.h"
bool fn_8018E340(Unk_C8FEE62D *arg0) {
    Unk_5BE2D2B7 *temp_r9;
    CStruct *var_r3;

    temp_r9 = arg0->unk0x14;
    if (temp_r9->unk0xAC((char *)arg0 + temp_r9->unk0xA8) != 0) {
block_1:
        return true;
    }
    var_r3 = arg0->unk0x2C;
    if (var_r3 != NULL) {
loop_3:
        if (var_r3->unk0x8 == 0) {
            var_r3 = var_r3->unk0x4;
            if (var_r3 == NULL) {
                goto block_5;
            }
            goto loop_3;
        }
        goto block_1;
    }
block_5:
    return false;
}
