// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021A784-0x8021A850 (204B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80303448;
extern char lbl_802AFDE8[];
s32 fn_801370C4(Unk_F386DC9F * arg0, s32 arg1, char * arg2, s32 arg3, s32 arg4, s32 arg5);
void fn_80222C2C(Unk_C7387A53 * arg0, s32 arg1);
s32 fn_8021A784(Unk_1DD1B27C *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_r0;
    s32 temp_r3;
    s32 temp_r9;
    s32 var_r8;
    s32 glob;
    s32 ret;

    glob = lbl_80303448;
    var_r8 = 0;
    if (arg1 != 0) {
        var_r8 = 1;
    }
    if (arg2 != 0) {
        var_r8 |= 8;
    } else {
        var_r8 |= 0x14;
    }
    if (arg3 != 0) {
        var_r8 |= 0x20;
    }
    temp_r3 = fn_801370C4(glob, arg4, (s32)lbl_802AFDE8, 0x141F, 0, var_r8);
    {
        s32 b9;
        s32 b0;
        register s32 t0 __asm__("r0");

        t0 = arg4 * 4;
        temp_r9 = (s32)((char *)arg0 + 0xC);
        __asm__("mr %0,%1" : "=&r"(b9) : "r"(temp_r9));
        __asm__("mr %0,%1" : "=&r"(b0) : "r"(t0));
        *(s32 *)(temp_r9 + t0) = temp_r3;
        if ((arg4 == 0) && (temp_r3 != 0)) {
            arg0->unk0x1B0 = arg4;
            arg0->unk0x1BC = arg4;
            arg0->unk0x1F8 = arg4;
            fn_80222C2C(arg0, 0);
        }
        arg0->unk0x108 = 0;
        arg0->unk0x34 = 0;
        arg0->unk0x1DC = 0;
        ret = *(s32 *)(b9 + b0);
    }
    return ret;
}
