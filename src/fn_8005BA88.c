// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005BA88-0x8005BAEC (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_8005B954(s32, s32);
bool ScriptSetLoadingBarPos(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;

    GetInteger((void *)pParams, QB_X, &sp8, 0);
    GetInteger((void *)pParams, QB_Y, &spC, 0);
    fn_8005B954(sp8, spC);
    return true;
}
