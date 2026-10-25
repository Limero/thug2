// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023DA18-0x8023DA64 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8023DA18(Unk_9D3CA704 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4) {
    u8 temp_r12;
    u8 temp_r8;
    u8 var_r0;
    u8 var_r10;
    u8 var_r11;
    u8 var_r9;

    temp_r8 = arg0->unk0x4D;
    temp_r12 = arg0->unk0x4F;
    var_r11 = arg0->unk0x53;
    var_r10 = temp_r8;
    var_r9 = arg0->unk0x55;
    var_r0 = temp_r12;
    if (var_r11 < var_r10) {
        var_r10 = var_r11;
        var_r11 = temp_r8;
    }
    if (var_r9 < var_r0) {
        var_r0 = var_r9;
        var_r9 = temp_r12;
    }
    *arg1 = var_r10;
    *arg2 = var_r0;
    *arg3 = var_r11;
    *arg4 = var_r9;
}

