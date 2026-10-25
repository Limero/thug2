// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F34F4-0x801F3534 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
bool fn_801F34F4(void *arg0, s32 arg1) {
    s32 var_r9;
    u8 temp_r0;
    s32 var_r11;

    temp_r0 = ((Unk_4D38C000 *)arg0)->unk0x336;
    var_r9 = 0;
    if (var_r9 < temp_r0) {
        arg0 = (char *)arg0 + 0x32C;
        var_r11 = temp_r0;
        __asm__ volatile("" : "+r"(var_r11));
        do {
            if (*(u8 *)((char *)arg0 + var_r9) == arg1) {
                return true;
            }
            var_r9 += 1;
        } while (var_r9 < var_r11);
    }
    return false;
}
