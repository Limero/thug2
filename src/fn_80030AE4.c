// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80030AE4-0x80030B1C (56B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80030AE4(Unk_C7387A53 *arg0, s32 arg1) {
    Unk_C7387A53 *var_r11;
    CStruct *var_r9;

    var_r9 = arg0->unk0x24;
    if ((s32) var_r9->unk0x4 == -1) {
        var_r9 = NULL;
    }
    var_r11 = (var_r9 != NULL) ? (char *)var_r9 - 4 : NULL;
    if (var_r11 != NULL) {
        arg0->unk0x58 = arg1;
        var_r11->unk0x74 = arg1;
    }
}
