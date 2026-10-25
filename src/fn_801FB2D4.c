// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FB2D4-0x801FB334 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801FB1C4(Unk_C7387A53 * arg0, CStruct * arg1);

void fn_801FB2D4(Unk_C7387A53 *arg0) {
    void *temp_r31;
    Unk_C7387A53 *temp_r9;
    CStruct *var_r4;

    var_r4 = arg0->unk0x24;
    while (var_r4 != NULL) {
        temp_r9 = var_r4->unk0xC;
        temp_r31 = var_r4->unk0x4;
        if ((temp_r9 == NULL) || (temp_r9->unk0x24 == 0)) {
            fn_801FB1C4(arg0, var_r4);
        }
        var_r4 = temp_r31;
    }
}
