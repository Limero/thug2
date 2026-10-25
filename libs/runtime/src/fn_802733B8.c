// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802733B8-0x80273448 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern s32 lbl_8028E040;

typedef void (*fp_t)(void);

void fn_802733B8(void) {
    s32 var_r11;
    s32 *temp_r10;
    s32 *var_r9;
    s32 temp_r0;
    s32 *p9;
    s32 *endp;
    s32 *curp;

    var_r11 = lbl_8028E040;
    temp_r10 = (s32 *)&lbl_8028E040;
    if (var_r11 == -1) {
        var_r11 = 0;
        if (temp_r10[1] != 0) {
            var_r9 = temp_r10 + 1;
            do {
                temp_r0 = var_r9[1];
                var_r9++;
                var_r11++;
            } while (temp_r0 != 0);
        }
    }
    temp_r0 = var_r11;
    if (temp_r0 != 0) {
        p9 = (s32 *)&lbl_8028E040;
        temp_r0 = temp_r0 * 4;
        endp = p9;
        __asm__("" : "+r"(endp));
        curp = (s32 *)((char *)p9 + (s32)temp_r0);
        do {
            ((fp_t)(s32)*curp)();
        } while (--curp != endp);
    }
}
