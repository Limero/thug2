// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80106560-0x801065AC (76B). Byte-identical.
#include "types.h"
#include "structs.h"
bool fn_80106560(Unk_C7387A53 *arg0, s32 arg1, s32 arg2) {
    s32 *temp_r9;
    s32 var_r10;
    s32 var_r11;

    var_r10 = 0;
    if (var_r10 < arg0->unk0x24) {
        var_r11 = 0;
loop_2:
        __asm__ volatile("" ::: "memory");
        temp_r9 = *((s32 * *)&arg0->unk0x2C);
        if (*(s32 *)((char *)(var_r11 + (s32)temp_r9)) == arg1) {
            *(s32 *)((char *)(var_r11 + (s32)temp_r9)) = arg2;
            return true;
        }
        var_r10 += 1;
        var_r11 += 4;
        if (var_r10 >= arg0->unk0x24) {
            goto end_4;
        }
        goto loop_2;
    }
end_4:
    return false;
}
