// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800ACA28-0x800ACA6C (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
u8 *fn_800ACA28(void *arg0, s32 arg1) {
    s32 var_r11;
    s32 temp_r0;
    s32 count;
    s32 var_r10;
    u8 *var_r9;

    count = *(s32 *)((char *)arg0 + 0x2054);
    var_r11 = 0;
    if (var_r11 < count) {
        arg0 = (char *)arg0 + 0x54;
        var_r10 = count;
        __asm__ volatile("" : "+r"(var_r10));
        var_r9 = arg0;
        do {
            temp_r0 = *(s32 *)var_r9;
            var_r9 += 0x20;
            if (temp_r0 == arg1) {
                return arg0;
            }
            var_r11 += 1;
            arg0 = (char *)arg0 + 0x20;
        } while (var_r11 < var_r10);
    }
    return NULL;
}
