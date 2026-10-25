// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800ACA6C-0x800ACAB0 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
u8 *fn_800ACA6C(void *arg0, s32 arg1) {
    s32 var_r11;
    s32 temp_r0;
    s32 count;
    s32 var_r10;
    u8 *var_r9;

    count = *(s32 *)((char *)arg0 + 0x2C58);
    var_r11 = 0;
    if (var_r11 < count) {
        arg0 = (char *)arg0 + 0x2058;
        var_r10 = count;
        __asm__ volatile("" : "+r"(var_r10));
        var_r9 = arg0;
        do {
            temp_r0 = *(s32 *)var_r9;
            var_r9 += 0xC;
            if (temp_r0 == arg1) {
                return arg0;
            }
            var_r11 += 1;
            arg0 = (char *)arg0 + 0xC;
        } while (var_r11 < var_r10);
    }
    return NULL;
}
