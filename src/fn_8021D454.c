// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021D454-0x8021D4E8 (148B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8022989C(void);
s32 fn_8021D4E8(s32, CStruct *, s32);
s32 fn_8021D454(s32 arg0, CStruct *arg1, s32 arg2) {
    s32 var_r31;
    s32 var_r3;
    Unk_C7387A53 *temp_r9;
    register void *var_r11 asm("r11");

    temp_r9 = arg0 + 0x130;
    arg1->unk0x4 = temp_r9;
    var_r11 = temp_r9->unk0xC;
    if ((s32) ((CStruct *)var_r11)->unk0x4 == -1) {
        var_r11 = NULL;
    }
    arg1->unk0x4 = var_r11;
    if (var_r11 != NULL) {
        var_r3 = ((CStruct *)var_r11)->unk0x4;
    } else {
        var_r3 = 0;
    }
    var_r31 = var_r3;
    if ((arg2 == 0) && (var_r31 != 0) && (fn_8022989C() != 0)) {
        var_r31 = fn_8021D4E8(arg0, arg1, 0);
    }
    return var_r31;
}
