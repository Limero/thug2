// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017161C-0x80171730 (276B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_80128850(CStruct *, void *, s32 *, s32);
s32 fn_801728BC(CStruct *, s32 *, s32);
s32 fn_80172910(CStruct *, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 *fn_800F03A0(s32, void *, s32);

void fn_8017161C(CStruct *arg0, CStruct *arg1) {
    s32 sp10;
    s32 spC;
    u16 sp8;
    s32 temp_r3;
    s32 *var_r30;
    s32 *temp_r3_2;
    s32 var_r29;

    temp_r3 = GetChecksum_2(arg1, QB_NAME, &spC, 0);
    if (temp_r3 != 0) {
        if (fn_801728BC(arg0->unk0x4, &spC, 1) == 0) {
            fn_80172910(arg0->unk0x4, &spC, arg0);
        }
    } else if (fn_80128850(arg1, QB_PREFIX, &sp10, 0) != 0) {
        sp8 = temp_r3;
        temp_r3_2 = fn_800F03A0(sp10, &sp8, ContainsFlag(arg1, QB_NOPREFIXWARNING) ^ 1);
        var_r29 = 0;
        if (var_r29 < (s32)sp8) {
            var_r30 = temp_r3_2;
            do {
                if (fn_801728BC(arg0->unk0x4, var_r30, 1) == 0) {
                    fn_80172910(arg0->unk0x4, var_r30, arg0);
                }
                var_r29 += 1;
                var_r30 += 1;
            } while (var_r29 < (s32)sp8);
        }
    }
}
