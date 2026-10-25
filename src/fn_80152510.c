// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80152510-0x80152610 (256B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80054EE8(void);
s32 fn_80055E74(Unk_FFAD6788 *, void *);
s32 fn_800F0F84(void *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
bool fn_80152510(s32 arg0, CStruct *arg1) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    register s32 temp_r31 __asm__("r31");
    register s32 zero __asm__("r29");
    s32 neg;
    CStruct *temp_r9;
    void *var_r30;
    Unk_9994C3F5 *var_r31;
    CStruct *var_r3;

    GetChecksum_2(arg1, (s32 *)QB_LIGHT_GROUP, &sp8, 1);
    temp_r31 = fn_800F0F84(arg0, 1);
    zero = 0;
    spC = zero;
    GetChecksum_2(temp_r31, QB_CLASS, &spC, 0);
    if (spC != QB_LEVELGEOMETRY) {
        goto Lret0;
    }
    {
        s32 hn = QB_NAME & 0xFFFF0000;
        __asm__("" : "+r"(hn));
        sp10 = zero;
        if (GetChecksum_2(temp_r31, hn | (QB_NAME & 0xFFFF), &sp10, 0) != 0) {
            var_r31 = NULL;
            var_r3 = fn_80054EE8();
            if (var_r3 != NULL) {
loop_3:
                temp_r9 = var_r3->unk0xC;
                neg = temp_r9->unk0x4;
                var_r30 = temp_r9;
                if (neg == -1) {
                    var_r30 = NULL;
                }
                var_r31 = fn_80055E74(var_r3->unk0x4, sp10);
                if (var_r31 == NULL) {
                    var_r3 = var_r30;
                    if (var_r3 != NULL) {
                        goto loop_3;
                    }
                }
            }
            var_r31->unk0x8 = sp8;
        }
    }
    goto Lret1;
Lret0:
    __asm__("" :: "r"(zero));
    return false;
Lret1:
    __asm__("" :: "r"(zero));
    return true;
}
