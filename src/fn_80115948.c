// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80115948-0x801159C0 (120B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void SetScriptString(s32, s32);
s32 GetString(CStruct *, s32 *, s32 *, s32);
void GetInteger(CStruct *, s32, s32 *, s32);
extern char lbl_8029D1C4[];
bool ScriptSetScriptString(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;

    sp8 = 0;
    GetInteger(pParams, QB_INDEX, &sp8, 0);
    spC = (s32)lbl_8029D1C4;
    GetString(pParams, QB_STRING, &spC, 0);
    SetScriptString(sp8, spC);
    return true;
}
