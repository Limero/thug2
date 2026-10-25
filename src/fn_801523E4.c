// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801523E4-0x80152510 (300B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 fn_80054EE8(void);
s32 fn_80055E74(Unk_FFAD6788 *, void *);
s32 fn_80058234(void *, void *);
s32 fn_800F0F84(void *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
s32 fn_80175450(void *, CStruct *);
s32 fn_8017DD4C(Unk_C7387A53 *);
bool fn_801523E4(s32 arg0) {
    s32 spC;
    s32 sp8;
    s32 temp_r30;
    s32 temp_r31;
    s32 temp_r3_2;
    s32 neg;
    CStruct *temp_r9;
    void *var_r30;
    void *var_r31;
    CStruct *var_r3;

    temp_r30 = lbl_80305EAC;
    if (fn_8017DD4C(temp_r30) != 0) {
        return true;
    }
    temp_r31 = fn_800F0F84(arg0, 1);
    temp_r3_2 = fn_80175450(temp_r30, temp_r31);
    if (temp_r3_2 != 0) {
        goto Lret1;
    }
    sp8 = temp_r3_2;
    GetChecksum_2(temp_r31, QB_CLASS, &sp8, 0);
    if ((sp8 != QB_LEVELOBJECT) && (sp8 != QB_LEVELGEOMETRY)) {
        goto Lret0;
    }
    {
        spC = temp_r3_2;
        if (GetChecksum_2(temp_r31, (void *)QB_NAME, &spC, 0) == 0) {
            goto Lret1;
        }
        {
            var_r30 = NULL;
            var_r3 = fn_80054EE8();
            if (var_r3 != NULL) {
loop_6:
                temp_r9 = var_r3->unk0xC;
                neg = temp_r9->unk0x4;
                var_r31 = temp_r9;
                if (neg == -1) {
                    var_r31 = NULL;
                }
                var_r30 = fn_80055E74(var_r3->unk0x4, spC);
                if (var_r30 == NULL) {
                    var_r3 = var_r31;
                    if (var_r3 != NULL) {
                        goto loop_6;
                    }
                }
            }
            fn_80058234(var_r30, 1);
        }
    }
    goto Lret1;
Lret0:
    return false;
Lret1:
    return true;
}
