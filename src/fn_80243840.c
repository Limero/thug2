// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80243840-0x802438A4 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80243840(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_r9;
    s32 var_ctr;
    void *temp_r0;
    Unk_9994C3F5 *temp_r11;
    CStruct *var_r10;
    void **base;

    base = (void **)((char *)arg0 + 4);
    temp_r11 = base[arg3];
    var_r10 = (char *)arg0 + 0x84;
    var_ctr = 0x20;
loop_1:
    temp_r0 = *(s32 *)((char *)var_r10 - 0x80);
    if (temp_r0 == NULL) {
        *(s32 *)((char *)var_r10 - 0x80) = temp_r11;
        temp_r9 = *arg0;
        temp_r11->unk0x8 = temp_r9;
        *arg0 = temp_r9 + 1;
        *(s32 *)(*(s32 *)((char *)((char *)var_r10) - 0x80) + 0x10) = arg1;
        *(s32 *)(*(s32 *)((char *)((char *)var_r10) - 0x80) + 0x18) = arg2;
        *(s32 *)(*(s32 *)((char *)((char *)var_r10) - 0x80) + 0xE8) = arg3;
        var_r10->unk0x0 = temp_r0;
        return;
    }
    var_r10 = (char *)var_r10 + 4;
    var_ctr -= 1;
    if (var_ctr == 0) {
        return;
    }
    goto loop_1;
}
