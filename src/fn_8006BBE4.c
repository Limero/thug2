// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006BBE4-0x8006BC44 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
u32 fn_8006BBE4(void *arg0, u32 arg1) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r11;
    s32 var_r9;
    u32 var_r10;
    u32 var_r8;
    void *var_r3;

    var_r3 = arg0;
    var_r10 = 0U;
    var_r8 = -1U;
    var_r9 = ((Unk_D0F3FE29 *)var_r3)->unk0x600 - ((Unk_D0F3FE29 *)var_r3)->unk0x0;
    while (var_r10 < arg1) {
        temp_r11 = ((Unk_D0F3FE29 *)var_r3)->unk0x600;
        if (temp_r11 != 0) {
            temp_r0 = ((Unk_D0F3FE29 *)var_r3)->unk0x0;
            if (temp_r0 != 0) {
                temp_r0_2 = temp_r11 - temp_r0;
                if (temp_r0_2 >= var_r9) {
                    var_r9 = temp_r0_2;
                    var_r8 = var_r10;
                }
            }
        }
        var_r10 += 1;
        var_r3 += 4;
    }
    return var_r8;
}
