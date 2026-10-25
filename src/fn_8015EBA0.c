// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015EBA0-0x8015EC30 (144B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EFC;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_801A5DAC(s32, s32);
void AddInteger(CStruct *, s32, s32);
bool ScriptUnlockSkater(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    s32 temp_r31;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    temp_r31 = fn_801A5DAC(lbl_80305EFC, sp8) + 0x6C;
    spC = 1;
    GetInteger(temp_r31, QB_IS_HIDDEN, &spC, 1);
    if (spC != 0) {
        AddInteger(temp_r31, QB_IS_HIDDEN, 0);
    }
    return true;
}
