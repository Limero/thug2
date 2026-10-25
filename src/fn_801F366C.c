// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F366C-0x801F36B0 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
u8 *fn_801F366C(void *arg0, s32 arg1) {
    s32 var_r11;
    u8 temp_r0;
    s32 count;
    s32 var_r10;
    u8 *var_r9;

    count = ((Unk_7258DEBD *)arg0)->unk0x328;
    var_r11 = 0;
    if (var_r11 < count) {
        arg0 = (char *)arg0 + 0x300;
        var_r10 = count;
        __asm__ volatile("" : "+r"(var_r10));
        var_r9 = arg0;
        do {
            temp_r0 = *(u8 *)var_r9;
            var_r9 += 4;
            if (temp_r0 == arg1) {
                return arg0;
            }
            var_r11 += 1;
            arg0 = (char *)arg0 + 4;
        } while (var_r11 < var_r10);
    }
    return NULL;
}
