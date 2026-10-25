// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FB358-0x801FB394 (60B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801FB358(Unk_C7387A53 *arg0) {
    s32 var_r3;
    CStruct *var_r11;
    Unk_C7387A53 *var_r9;
    void *temp_r0;

    var_r11 = arg0->unk0x24;
    var_r3 = 0;
    if (var_r11 == NULL) {
        return var_r3;
    }
    do {
        var_r9 = var_r11->unk0xC;
        temp_r0 = var_r11->unk0x4;
        if (var_r9 != NULL) {
            do {
                var_r9 = var_r9->unk0x24;
                var_r3 += 1;
            } while (var_r9 != NULL);
        }
        var_r11 = temp_r0;
    } while (var_r11 != NULL);
    return var_r3;
}
