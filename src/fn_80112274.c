// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80112274-0x801122E4 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_80059048(s32, s32);

bool ScriptInitLightManager(CStruct *pParams, CScript *pScript) {
    s32 sp8 = 0;
    s32 spC = 0;

    GetInteger(pParams, 0x50228D9E, &sp8, 1);
    GetInteger(pParams, 0x701C70AC, &spC, 1);
    fn_80059048(sp8, spC);
    return true;
}
