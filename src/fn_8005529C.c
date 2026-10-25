// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005529C-0x80055334 (152B). Byte-identical.
#include "types.h"
extern char lbl_80293154[];
extern char lbl_8029315C[];
s32 strstr(s32, s32);
void strcpy(s32, s32);
s32 fn_8005529C(s32 arg0, s32 arg1) {
    s32 var_r0;
    s32 var_r30;
    s8 *temp_r3;
    s8 *temp_r3_2;

    var_r30 = 1;
    strcpy(arg1, arg0);
    temp_r3 = strstr(arg1, (s32)lbl_80293154);
    if (temp_r3 == NULL) {
        var_r30 = 0;
    }
    if (var_r30 != 0) {
        *((u8 *)temp_r3) = 0;
    }
    temp_r3_2 = strstr(arg1, (s32)lbl_8029315C);
    var_r0 = 1;
    __asm__("" : "+r"(var_r0));
    if (temp_r3_2 == NULL) {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        *((u8 *)temp_r3_2) = 0;
    }
    return var_r30;
}
