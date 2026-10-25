// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80160874-0x80160928 (180B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EFC;
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_801A54DC(void *, s32, CStruct *, s32);
s32 fn_801A5D88(Unk_C7387A53 *);
void fn_801A7EB4(Unk_C7387A53 *);

s32 ScriptSetSpecialTrickInfo(CStruct *pParams, CScript *pScript) {
    s32 sp8[4];
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 temp_r3;
    s32 var_r3;

    GetInteger(pParams, QB_SLOT, &sp18, (s32 *)1);
    GetChecksum_2(pParams, QB_TRICK_NAME, &sp1C, 1);
    GetChecksum_2(pParams, QB_KEY_COMBO, &sp20, 1);
    temp_r3 = fn_801A5D88(lbl_80305EFC);
    var_r3 = 0;
    if (temp_r3 != 0) {
        fn_801A7EB4((void *)sp8);
        sp8[1] = sp1C;
        sp8[2] = sp20;
        fn_801A54DC(temp_r3, sp18, (void *)sp8, 0);
        var_r3 = 1;
    }
    return var_r3;
}
