// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80111824-0x80111894 (112B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_800557A4(s32, s32);
bool ScriptDebugRenderIgnore(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;

    spC = 0;
    sp8 = 0;
    GetInteger(pParams, QB_IGNORE_1, &sp8, 0);
    GetInteger(pParams, QB_IGNORE_0, &spC, 0);
    fn_800557A4(sp8, spC);
    return true;
}
