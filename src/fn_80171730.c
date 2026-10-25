// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80171730-0x80171844 (276B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8015010C(s32 arg0);
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_800F03A0(s32, void *, s32);
s32 fn_801728BC(CStruct *arg0, s32 *arg1, s32 arg2);
s32 fn_80128850(CStruct *arg0, void *arg1, s32 *arg2, s32 arg3);
s32 ContainsFlag(CStruct *, s32);
void fn_80171730(CStruct *arg0, CStruct *arg1) {
    s32 sp10;
    s32 spC;
    u16 sp8;
    s32 *temp_r28;
    char *var_r30;
    s32 var_r29;
    s32 var_r31;
    sp8 = 0;
    if (GetChecksum_2(arg1, QB_NAME, &spC, 0) != 0) {
        if (fn_801728BC(arg0->unk0x4, &spC, 1) == 0) {
            fn_8015010C(spC);
        }
    } else if (fn_80128850(arg1, QB_PREFIX, &sp10, 0) != 0) {
        var_r31 = 0;
        temp_r28 = fn_800F03A0(sp10, &sp8, ContainsFlag(arg1, QB_NOPREFIXWARNING) ^ 1);
        if (var_r31 >= (s32)sp8) {
            return;
        }
        var_r30 = (char *)temp_r28;
        var_r29 = 0;
        do {
            if (fn_801728BC(arg0->unk0x4, (s32 *)var_r30, 1) == 0) {
                fn_8015010C(*(s32 *)((char *)(var_r29 + (s32)temp_r28)));
            }
            var_r31 += 1;
            var_r30 += 4;
            var_r29 += 4;
        } while (var_r31 < (s32) sp8);
    }
}
