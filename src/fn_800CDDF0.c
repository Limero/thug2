// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CDDF0-0x800CDE90 (160B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80301B48;
s32 GetChecksum_3(Unk_6A70655D *, s32);
s32 fn_800F2AD8(s32, s32, s32);
s32 fn_800FC374(s32, s32, s32, s32);
void fn_800CDDF0(Unk_31DE137E *arg0, s32 arg1, s32 arg2) {
    s32 var_r4;
    s32 var_r5;
    Unk_FFAD6788 *temp_r3;
    Unk_C7387A53 *temp_r11;

    var_r4 = arg2;
    if (var_r4 != 0) {
        var_r5 = 1;
        arg0->unk0x1C = fn_800FC374(arg1, var_r4, var_r5, arg0->unk0xC);
        return;
    }
    temp_r11 = *(s32 *)(GetChecksum_3(arg0->unk0xC, QB_MODEL) + (s32)0x210);
    temp_r3 = fn_800F2AD8(lbl_80301B48, temp_r11->unk0x34, 0);
    if (temp_r3 != 0) {
        var_r5 = temp_r3->unk0x88;
        var_r4 = temp_r3->unk0x8C;
        arg0->unk0x1C = fn_800FC374(arg1, var_r4, var_r5, arg0->unk0xC);
        return;
    }
    arg0->unk0x1C = fn_800FC374(arg1, 0, 0, arg0->unk0xC);
}
