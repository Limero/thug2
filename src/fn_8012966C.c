// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012966C-0x801297E4 (376B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
u8 *fn_80129574(u8 *buf, s32 tag, s32 key);
u8 *fn_8012CB7C(u8 *p, u32 v);
u8 *fn_8012CBD4(u8 *p, u32 v);
s32 fn_8012966C(s32 arg0, u32 arg1, u8 *arg2, u32 arg3) {
    u8 sp8[20];
    s32 var_r11;
    u8 *var_r3;
    u8 *var_r11_2;
    u8 *start;
    u32 temp_r3_2;
    u32 var_r9;
    u8 temp_r0;
    start = arg2;
    var_r11 = 1;
    if (arg1 == 0) {
        var_r11 = 0x12;
    } else if (arg1 <= 0xFF) {
        var_r11 = 0x10;
    } else if (arg1 <= 0xFFFF) {
        var_r11 = 0x11;
    } else if ((u32)(arg1 + 0x80) <= 0xFF) {
        var_r11 = 0xE;
    } else if ((u32)(arg1 + 0x8000) <= 0xFFFF) {
        var_r11 = 0xF;
    }
    var_r3 = sp8;
    switch (var_r11) {
    case 1:
        var_r3 = fn_8012CB7C(fn_80129574(var_r3, 1, arg0), arg1);
        break;
    case 0xE:
    case 0x10:
        var_r3 = fn_80129574(sp8, var_r11, arg0);
        *var_r3++ = arg1;
        break;
    case 0xF:
    case 0x11:
        var_r3 = fn_8012CBD4(fn_80129574(sp8, var_r11, arg0), arg1 & 0xFFFF);
        break;
    case 0x12:
        var_r3 = fn_80129574(var_r3, 0x12, arg0);
        break;
    }
    temp_r3_2 = var_r3 - sp8;
    if (arg3 < temp_r3_2) {
        return 0;
    }
    var_r9 = 0;
    var_r11_2 = sp8;
    while (var_r9 < temp_r3_2) {
        temp_r0 = *var_r11_2;
        var_r9++;
        var_r11_2++;
        *arg2++ = temp_r0;
    }
    return arg2 - start;
}
