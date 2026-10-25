// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8014E33C-0x8014E41C (224B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80128850(CStruct *, void *, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_8005AC44(s32, CStruct *);
s32 fn_800F03A0(s32, void *, s32);
void fn_80059A30(s32, u16, s32, Unk_80577C09 *);
// ScriptFakeLights @ 0x8014E33C
s32 ScriptFakeLights(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp10;
    s32 sp14;
    u16 sp8;
    s32 temp_r3;
    s32 var_r3;
    register s32 var_r30 __asm__("r30");

    spC = 0;
    var_r30 = GetChecksum_2(pParams, QB_ID, &spC, 0);
    if (var_r30 != 0) {
        fn_8005AC44(spC, pParams);
        goto block_9;
    }
    __asm__("" : "+r"(var_r30));
    sp10 = var_r30;
    GetInteger(pParams, QB_TIME, &sp10, 0);
    sp14 = var_r30;
    if (fn_80128850(pParams, QB_PREFIX, &sp14, 0) == 0) {
        return 0;
    }
    sp8 = (u16)var_r30;
    var_r30 = sp14;
    temp_r3 = ContainsFlag(pParams, QB_NOPREFIXWARNING) ^ 1;
    fn_80059A30(fn_800F03A0(var_r30, &sp8, temp_r3), sp8, sp10, pParams);
block_9:
    var_r3 = 1;
    return var_r3;
}
