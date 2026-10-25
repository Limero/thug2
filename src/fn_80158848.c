// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80158848-0x801588B0 (104B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 fn_801A7150(s32, s32, s32);

void ScriptSetClassicStat(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    s32 temp_r29;

    temp_r29 = *(s32 *)((char *)*(s32 *)&lbl_80305EAC + 0x24);
    GetChecksum_2(pParams, 0, &sp8, 0);
    GetInteger(pParams, 0, &spC, 0);
    fn_801A7150(temp_r29, sp8, spC);
}
