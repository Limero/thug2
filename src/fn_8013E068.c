// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013E068-0x8013E098 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8013E068(void *arg0, CStruct *arg1) {
    Unk_C7387A53 *temp_r9;
    CStruct *var_r11;

    temp_r9 = *((void * *)&arg1->unk0x4);
    var_r11 = *((void * *)&temp_r9->unk0xC);
    __asm__ volatile("" : : "r"(temp_r9));
    if (var_r11->unk0x4 == -1) {
        var_r11 = NULL;
    }
    *((void * *)&arg1->unk0x4) = var_r11;
    if (var_r11 == NULL) {
        return 0;
    }
    return var_r11->unk0x4;
}
