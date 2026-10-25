// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015FCA4-0x8015FDF4 (336B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EFC;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetStructure(s32, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_801A5D88(Unk_C7387A53 *);
s32 fn_801A56F4(s32);
s32 fn_801A5C04(Unk_9994C3F5 *);
s32 fn_801A5C40(s32, s32);
s32 ScriptTrickIsLocked(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 var_r9;
    s32 var_r3;
    s32 obj;
    s32 node;
    s32 item;
    s32 temp;
    s32 i;
    s32 n;

    GetChecksum_2(pParams, QB_TRICK, &sp8, 1);
    node = GetStructure(sp8, 1);
    if (node == 0) {
        return 0;
    }
    GetStructure_2(node, QB_PARAMS, &spC, 1);
    if (spC == 0) {
        return 0;
    }
    if (GetChecksum_2(spC, QB_SKATER, &sp10, 0) == 0) {
        return 0;
    }
    obj = lbl_80305EFC;
    if (ContainsFlag(spC, QB_ONLYWITH) != 0) {
        s32 flag;
        temp = fn_801A56F4(fn_801A5D88(obj));
        flag = 1;
        __asm__("" : "+r"(flag));
        if (temp == sp10) {
            flag = 0;
        }
        return flag;
    } else {
        i = 0;
        n = fn_801A5C04(obj);
        while (i < n) {
            item = fn_801A5C40(obj, i);
            if (fn_801A56F4(item) == sp10) {
                sp14 = 0;
                GetInteger(item + 0x6C, QB_IS_HIDDEN, &sp14, 0);
                var_r3 = 1;
                if (sp14 == 0) {
                    var_r3 = 0;
                }
                return var_r3;
            }
            i += 1;
        }
    }
    return 0;
}
