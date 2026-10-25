// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80126620-0x80126698 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_802FFE54;
extern char lbl_80303258[];
s32 fn_80126620(s32 arg0) {
    s32 temp_r10;
    s32 temp_r11;
    s32 var_ctr;
    s32 var_r3;
    char *var_r9;

    if (lbl_802FFE54 == 0) {
        return 0;
    }
    temp_r10 = (u16)arg0 * 0x50;
    temp_r11 = *(s32 *)&lbl_80303258;
    var_r9 = (char *)temp_r11 + temp_r10;
    var_r3 = *(s32 *)(var_r9 + 4);
    if (var_r3 != 0) {
        if (*(s32 *)(temp_r11 + temp_r10) != arg0) {
            for (var_ctr = 9; var_ctr != 0; var_ctr--) {
                var_r9 += 8;
                var_r3 = *(s32 *)(var_r9 + 4);
                if (var_r3 == 0) {
                    goto fail;
                }
                if (*(s32 *)var_r9 == arg0) {
                    return var_r3;
                }
            }
        } else {
            return var_r3;
        }
    }
fail:
    return 0;
}
