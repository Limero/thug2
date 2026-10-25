// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80183C7C-0x80183CF0 (116B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80183C7C(s32 arg0, CStruct *arg1) {
    s32 temp_r0;
    CStruct *temp_r9;
    CStruct *var_r3;
    CStruct *var_r11;
    s32 key;

    var_r3 = arg0 + 0x20;
    key = arg1->unk0x8;
    var_r11 = var_r3;
    while (1) {
        temp_r9 = var_r11->unk0xC;
        temp_r0 = temp_r9->unk0x4;
        var_r11 = temp_r9;
        if (temp_r0 == -1) {
            var_r11 = 0;
        }
        if (var_r11 == 0) {
            break;
        }
        if (var_r11->unk0x8 <= key) {
            arg1->unk0x10 = var_r11->unk0x10;
            arg1->unk0xC = var_r11;
            *(s32 *)(var_r11->unk0x10 + 0xC) = arg1;
            var_r11->unk0x10 = arg1;
            return;
        }
    }
    arg1->unk0x10 = var_r3->unk0x10;
    arg1->unk0xC = var_r3;
    *(s32 *)(var_r3->unk0x10 + 0xC) = arg1;
    var_r3->unk0x10 = arg1;
}
