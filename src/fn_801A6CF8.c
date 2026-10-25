// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A6CF8-0x801A6D34 (60B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801A6CF8(Unk_93C2DF4D *arg0, s32 arg1, s32 arg2) {
    s32 temp_r11;
    s32 var_r5;
    void *temp_r8;

    var_r5 = arg2;
    if (var_r5 == -1) {
        var_r5 = arg0->unk0x630;
    }
    temp_r8 = (char *)arg0 + 4;
    temp_r11 = ((arg1 >> 5) * 4) + (var_r5 << 5);
    *(s32 *)((char *)temp_r8 + temp_r11) = *(s32 *)((char *)temp_r8 + temp_r11) | (1 << (arg1 & 0x1F));
}
