// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003C8E0-0x8003CC38 (856B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern s32 lbl_803003E8;
extern s32 lbl_803003F0;
s32 fn_8003AB44(s32);
s32 GetText(s32, s32, void *, s32);
s32 GetChecksum_2(s32, s32, s32 *, s32);
s32 fn_80060FA8(s32, s32, s32, s32);
s32 fn_8003C8E0(s32 arg0, s32 arg1) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 var_r30;
    s32 temp_r3;

    var_r30 = 0;
    temp_r3 = fn_8003AB44(lbl_803003F0);
    if (temp_r3 != 0) {
        register s32 *p8 __asm__("r28") = &sp8;
        if (GetText(temp_r3, QB_REPLACE, p8, 0) != 0) {
            GetText(temp_r3, QB_WITH, &spC, 1);
            sp10 = arg1;
            GetChecksum_2(temp_r3, QB_IN, &sp10, 0);
            var_r30 = fn_80060FA8(lbl_803003E8, sp10, sp8, spC);
        }
        if (GetText(temp_r3, QB_REPLACE1, p8, 0) != 0) {
            GetText(temp_r3, QB_WITH1, &spC, 1);
            sp14 = arg1;
            GetChecksum_2(temp_r3, QB_IN1, &sp14, 0);
            var_r30 = fn_80060FA8(lbl_803003E8, sp14, sp8, spC);
        }
        if (GetText(temp_r3, QB_REPLACE2, p8, 0) != 0) {
            GetText(temp_r3, QB_WITH2, &spC, 1);
            sp18 = arg1;
            GetChecksum_2(temp_r3, QB_IN2, &sp18, 0);
            var_r30 = fn_80060FA8(lbl_803003E8, sp18, sp8, spC);
        }
        if (GetText(temp_r3, QB_REPLACE3, p8, 0) != 0) {
            GetText(temp_r3, QB_WITH3, &spC, 1);
            sp1C = arg1;
            GetChecksum_2(temp_r3, QB_IN3, &sp1C, 0);
            var_r30 = fn_80060FA8(lbl_803003E8, sp1C, sp8, spC);
        }
        if (GetText(temp_r3, QB_REPLACE4, p8, 0) != 0) {
            GetText(temp_r3, QB_WITH4, &spC, 1);
            sp20 = arg1;
            GetChecksum_2(temp_r3, QB_IN4, &sp20, 0);
            var_r30 = fn_80060FA8(lbl_803003E8, sp20, sp8, spC);
        }
        if (GetText(temp_r3, QB_REPLACE5, p8, 0) != 0) {
            GetText(temp_r3, QB_WITH5, &spC, 1);
            sp24 = arg1;
            GetChecksum_2(temp_r3, QB_IN5, &sp24, 0);
            var_r30 = fn_80060FA8(lbl_803003E8, sp24, sp8, spC);
        }
        if (GetText(temp_r3, QB_REPLACE6, p8, 0) != 0) {
            GetText(temp_r3, QB_WITH6, &spC, 1);
            sp28 = arg1;
            GetChecksum_2(temp_r3, QB_IN6, &sp28, 0);
            var_r30 = fn_80060FA8(lbl_803003E8, sp28, sp8, spC);
        }
    }
    return var_r30;
}
