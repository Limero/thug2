// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019B634-0x8019B728 (244B). Byte-identical.
#include "types.h"
f32 fn_8019B48C(s32 arg0, s32 arg1);
bool fn_8019B634(void *arg0, s32 arg1) {
    s32 sp8[7];
    s32 *arr;
    s32 *var_r9;
    s32 var_ctr;
    s32 var_r11;
    s32 var_r25;
    f32 temp_f31;
    s32 temp_r9;
    s32 temp_x;
    s32 i;
    s32 off_i;
    s32 off_j;
    register s32 cnt __asm__("r29");
    register s32 *p __asm__("r28");

    arr = sp8;
    var_ctr = 5;
    var_r11 = 4;
    var_r9 = &sp8[4];
    do {
        *var_r9 = var_r11;
        var_r9 -= 1;
        var_r11 -= 1;
        var_ctr -= 1;
    } while (var_ctr != 0);
    i = 0;
    do {
        if (i <= 4) {
            off_i = i << 2;
            p = arr;
            cnt = 5 - i;
            off_j = off_i;
            do {
                temp_f31 = fn_8019B48C(arg0, *(s32 *)((char *)p + off_i));
                if (temp_f31 < fn_8019B48C(arg0, *(s32 *)(off_j + (s32)p))) {
                    temp_r9 = *(s32 *)(off_j + (s32)arr);
                    temp_x = *(s32 *)((char *)arr + off_i);
                    *(s32 *)((char *)arr + off_i) = temp_r9;
                    *(s32 *)(off_j + (s32)arr) = temp_x;
                }
                off_j += 4;
            } while (--cnt != 0);
        }
        var_r25 = i + 1;
        i = var_r25;
    } while (var_r25 <= 3);
    if ((sp8[0] == arg1) || (sp8[1] == arg1) || (sp8[2] == arg1)) {
        return true;
    }
    return false;
}
