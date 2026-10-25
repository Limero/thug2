// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000ECDC-0x8000ED30 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8000ECDC(CStruct *arg0, s32 *arg1) {
    s32 temp_r3;
    s32 temp_r4;
    CStruct *var_r11;

    temp_r4 = *arg1;
    var_r11 = arg0->unk0x4 + ((temp_r4 & ((1 << arg0->unk0x0) - 1)) * 0xC);
    while (var_r11 != NULL) {
        if ((s32) var_r11->unk0x0 == temp_r4) {
            temp_r3 = var_r11->unk0x4;
            if (temp_r3 != 0) {
                return temp_r3;
            }
        }
        var_r11 = var_r11->unk0x8;
    }
    return 0;
}
