// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015D3E0-0x8015D438 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EC0;
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_8019893C(s32, s32);
bool ScriptSetTrickScoreTracking(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 1;
    GetInteger(pParams, 0, &sp8, 0);
    fn_8019893C(lbl_80305EC0, sp8 != 0);
    return true;
}
