// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80035B24-0x80035E14 (752B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_800360B0(s32 arg0, s32 arg1);
void fn_80036194(s32 arg0);
void fn_800360C4(s32 arg0, s32 arg1);
void fn_80035E14(void *, void *, void *, void *);
s32 fn_800360D8(s32 arg0, s32 arg1);
s32 fn_80036128(s32 arg0);
void fn_800361EC(s32 arg0);
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(s32, s32, s32, s32);
s32 fn_80036078(s32, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80128978(s32, s32);
s32 fn_80035B24(s32 arg0, s32 arg1, CStruct *arg2) {
    u32 swv1;
    s32 spC;
    s32 sp8;
    s32 temp_r3;
    s32 var_r29;

    var_r29 = 0;
    switch (swv1 = arg1) {
    case 0x27B2B1C:
        if (GetInteger(arg2, QB_INDEX, &sp8, 0) == 0) {
            sp8 = 0;
            if (GetChecksum_2(arg2, QB_ID, &spC, 0) != 0) {
                sp8 = fn_80036078(arg0, spC);
            } else if (fn_80128978(arg2, QB_ALL) != 0) {
                var_r29 = 1;
            }
        }
        if (var_r29 != 0) {
            temp_r3 = fn_80036128(arg0);
        result_check:
            __asm__("" : "+r"(temp_r3));
            if (temp_r3 != 0) {
                temp_r3 = 1;
            } else {
                temp_r3 = 0;
            }
            return temp_r3;
        } else {
            temp_r3 = fn_800360D8(arg0, sp8);
            goto result_check;
        }
    case QB_UNKNOWN_0x20D24E9A:
        if (GetInteger(arg2, QB_INDEX, &sp8, 0) == 0) {
            sp8 = 0;
            if (GetChecksum_2(arg2, QB_ID, &spC, 0) != 0) {
                sp8 = fn_80036078(arg0, spC);
            } else if (fn_80128978(arg2, QB_ALL) != 0) {
                var_r29 = 1;
            }
        }
        if (var_r29 != 0) {
            fn_80036194(arg0);
        } else {
            fn_800360B0(arg0, sp8);
        }
        break;
    case QB_UNKNOWN_0x4599FB80:
        if (GetInteger(arg2, QB_INDEX, &sp8, 0) == 0) {
            sp8 = 0;
            if (GetChecksum_2(arg2, QB_ID, &spC, 0) != 0) {
                sp8 = fn_80036078(arg0, spC);
            } else if (fn_80128978(arg2, QB_ALL) != 0) {
                var_r29 = 1;
            }
        }
        if (var_r29 != 0) {
            fn_800361EC(arg0);
        } else {
            fn_800360C4(arg0, sp8);
        }
        break;
    case QB_UNKNOWN_0xB040E943:
        if (GetInteger(arg2, QB_INDEX, &sp8, 0) == 0) {
            sp8 = 0;
            if (GetChecksum_2(arg2, QB_ID, &spC, 0) != 0) {
                sp8 = fn_80036078(arg0, spC);
            } else if (fn_80128978(arg2, QB_ALL) != 0) {
                var_r29 = 1;
            }
        }
        fn_80035E14((void *)arg0, (void *)var_r29, (void *)sp8, arg2);
        break;
    default:
        return 2;
    }
    return 1;
}
