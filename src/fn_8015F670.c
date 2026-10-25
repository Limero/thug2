// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015F670-0x8015F884 (532B). Byte-identical.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern s32 lbl_80305EFC;
extern char lbl_802A8294[];
extern char lbl_802A82A8[];
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80128978(s32, s32);
s32 fn_801A5DAC(s32, s32);
s32 fn_80174A58(void *, CStruct *);
s32 ContainsFlag(CStruct *, s32);
s32 fn_801A568C(s32, s32);
s32 fn_8015F510(s32, s32, s32);
s32 fn_801A5388(s32);
void s_find_trick_in_mapping(void *, void *, s32);
s32 fn_8015F5F4(CStruct *, s32);
void fn_80127848(CStruct *, void *, s32);
void fn_801276E8(CStruct *, void *, s32);
bool ScriptGetKeyComboBoundToTrick(s32 arg0, void *arg1) {
    s32 sp8[3];
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    register s32 var_r28 __asm__("r28");
    register s32 temp_r29 __asm__("r29");
    register s32 var_r26 __asm__("r26");
    register s32 var_r27 __asm__("r27");
    register s32 var_r3 __asm__("r31");
    register s32 a1 __asm__("r25");
    register s32 ctx __asm__("r30");

    a1 = (s32)arg1;
    ctx = arg0;
    sp18 = 0;
    if (GetChecksum_2(arg0, QB_TRICK, &sp18, 0) == 0) {
        GetInteger(arg0, QB_CAT_NUM, &sp1C, 1);
    }
    if (fn_80128978(ctx, QB_PROFILE) != 0) {
        GetChecksum_2(ctx, QB_PROFILE, &sp20, 1);
        var_r3 = fn_801A5DAC(lbl_80305EFC, sp20);
    } else {
        var_r3 = fn_80174A58(lbl_80305EAC, 0);
    }
    var_r28 = 0;
    var_r26 = 0;
    var_r27 = 0;
    if (sp18 != 0) {
        if (ContainsFlag(ctx, QB_SPECIAL) == 0) {
            arg0 = fn_801A568C(var_r3, QB_TRICK_MAPPING);
            var_r3 = fn_8015F510(arg0, sp18, 0);
            __asm__("" : "+r"(var_r27));
            sp24 = var_r27;
            if (GetChecksum_2(arg0, var_r3, &sp24, 0) != 0 && sp24 == sp18) {
                var_r28 = var_r3;
            }
        } else if (ContainsFlag(ctx, QB_SPECIAL) != 0) {
            arg0 = 0;
            temp_r29 = fn_801A5388(var_r3);
            while (arg0 < temp_r29) {
                s_find_trick_in_mapping(sp8, var_r3, arg0);
                if (sp8[1] == sp18) {
                    var_r28 = sp8[2];
                    var_r27 = arg0;
                    var_r26 = 1;
                    break;
                }
                arg0 += 1;
            }
        }
    } else {
        var_r28 = fn_8015F5F4(fn_801A568C(var_r3, QB_TRICK_MAPPING), sp1C);
    }
    if (var_r28 != 0) {
        fn_80127848(((CScript *)a1)->unk0x18, (s32)lbl_802A8294, var_r28);
        if (var_r26 != 0) {
            fn_801276E8(((CScript *)a1)->unk0x18, (s32)lbl_802A82A8, var_r27);
        }
        return true;
    }
    __asm__("" : "+r"(var_r28));
    return false;
}
