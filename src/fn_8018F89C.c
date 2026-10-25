// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018F89C-0x8018FAE8 (588B). Byte-identical.
#include "types.h"
extern char lbl_80305EAC[];
#include "qb_constants.h"
#include "structs.h"

extern s32 GetStructure(s32 arg0, s32 arg1);
extern s32 fn_80174A58(void * arg0, CStruct * arg1);
extern s32 fn_801A568C(s32 arg0, s32 arg1);
extern s32 GetChecksum(CStruct * arg0, s32 arg1);
extern s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 fn_801A5388(s32 arg0);
extern void s_find_trick_in_mapping(void *arg0, void * arg1, s32 arg2);
extern s32 GetString(CStruct * arg0, s32 * arg1, s32 * arg2, s32 arg3);
extern s32 fn_801745B4(s32 arg0);
extern s32 fn_801259C8(s32 arg0, s32 arg1);
extern s32 fn_80129528(CStruct * arg0, s32 arg1);
extern s32 CreateString(char * arg0);
extern void fn_80129218(CStruct * arg0, s32 arg1, s32 arg2);
extern s32 GetStructure_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 fn_801281BC(s32 arg0, s32 arg1, void *arg2, s32 arg3);

bool fn_8018F89C(CStruct *arg0, CStruct *arg1, CStruct *arg2, s32 arg3) {
    s32 sp8[3];
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 temp_r19;
    s32 temp_r21;
    s32 temp_r22;
    s32 temp_r24;
    s32 temp_r25;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r3;
    s32 var_r26;
    s32 var_r27;
    s32 var_r28;
    s32 var_r31;

    var_r27 = 0;
    temp_r19 = GetStructure(QB_GOAL_TETRIS_TRICK_TEXT, 1);
    temp_r21 = *(s32 *)&lbl_80305EAC;
    temp_r24 = fn_801A568C((void *)(temp_r25 = fn_80174A58(temp_r21, 0)), QB_TRICK_MAPPING);
    temp_r22 = arg0->unk0x4;
    while (var_r27 < temp_r22) {
        temp_r29 = GetChecksum(arg0, var_r27);
        var_r28 = 0;
        {
            register s32 z1c __asm__("r0");
            __asm__("li %0, 0" : "=r"(z1c));
            sp1C = z1c;
        }
        sp18 = 0;
        var_r26 = 0;
        if (GetInteger(temp_r24, temp_r29, &sp18, 0) != 0) {
            var_r26 = 1;
            var_r28 = 1;
        } else if (GetChecksum_2(temp_r24, temp_r29, &sp1C, 0) != 0) {
            var_r28 = 1;
        } else {
            temp_r30 = fn_801A5388(temp_r25);
            for (var_r31 = 0; var_r31 < temp_r30; var_r31++) {
                s_find_trick_in_mapping(sp8, temp_r25, var_r31);
                if (sp8[2] == temp_r29) {
                    var_r28 = 1;
                    sp1C = sp8[1];
                    break;
                }
            }
        }
        if (var_r28 == 0) {
            return false;
        }
        GetString(temp_r19, temp_r29, &sp20, 1);
        if (var_r26 != 0) {
            temp_r3 = fn_801745B4(temp_r21);
            if (temp_r3 != 0) {
                char *base = (char *)temp_r3 + (s32)0x194;
                GetString(**(s32 **)(base + (sp18 << 2)), QB_NAME, &sp24, 1);
            }
        } else if (arg3 > -1) {
            GetString(fn_80129528(fn_801259C8(QB_PREMADE_CATS, 1), arg3), QB_NAME, &sp24, 1);
        } else {
            GetStructure_2(GetStructure(sp1C, 1), QB_PARAMS, &sp28, 1);
            fn_801281BC(sp28, QB_NAME, &sp24, 1);
        }
        fn_80129218(arg1, var_r27, CreateString(sp20));
        fn_80129218(arg2, var_r27, CreateString(sp24));
        var_r27 += 1;
    }
    return true;
}
