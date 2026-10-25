// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80150590-0x801506D8 (328B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ContainsFlag(CStruct *, s32);
s32 fn_80128850(CStruct *, void *, s32 *, s32);
s32 fn_800F03A0(s32, s32, s32);
s32 fn_801503F4(s32, s32, Unk_FFAD6788 *, CStruct *);

s32 fn_80150590(CStruct *arg0, Unk_FFAD6788 *arg1, s32 arg2) {
    s32 sp18;
    s32 spC;
    s16 sp8;
    s32 temp_r3;
    s32 temp_r3_2;
    register s32 *var_r30 __asm__("r30");
    s32 var_r31;

    if (ContainsFlag(arg0, QB_LINKS) != 0) {
        goto L_ret1;
    }
    temp_r3 = ContainsFlag(arg0, QB_UNKNOWN_0xBCEB479A);
    if (temp_r3 != 0) {
        goto L_ret1;
    }
    if (fn_80128850(arg0, QB_PREFIX, &spC, 0) != 0) {
        sp8 = (s16)temp_r3;
        var_r30 = (s32 *)spC;
        var_r31 = 0;
        temp_r3_2 = fn_800F03A0(var_r30, &sp8, ContainsFlag(arg0, QB_NOPREFIXWARNING) ^ 1);
        if (var_r31 < *(u16 *)&sp8) {
            var_r30 = (s32 *)temp_r3_2;
            do {
                temp_r3 = fn_801503F4(*(s32 *)var_r30, arg2, arg1, arg0);
                var_r30 += 1;
                if ((temp_r3 != 0) && (arg2 == 5)) {
                    break;
                }
                var_r31 += 1;
            } while (var_r31 < *(u16 *)&sp8);
        }
        goto L_ret1;
    }
    if (fn_80128850(arg0, QB_NAME, &sp18, 0) != 0) {
        goto L_rec;
    }
    return 0;
L_ret1:
    return 1;
L_rec:
    return fn_801503F4(sp18, arg2, arg1, arg0);
}
