// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801117DC-0x80111824 (72B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 lbl_803CAF44;
bool ScriptSetWireframeMode(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 0;
    GetInteger(pParams, QB_MODE, &sp8, 0);
    lbl_803CAF44 = sp8;
    return true;
}
