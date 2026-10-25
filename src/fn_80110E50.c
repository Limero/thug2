// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80110E50-0x80110EA4 (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80055980(s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
// ScriptSetColorBufferClear @ 0x80110E50
bool ScriptSetColorBufferClear(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 var_r3;

    sp8 = 0;
    GetInteger(pParams, QB_CLEAR, &sp8, 0);
    var_r3 = 1;
    if (sp8 <= 0) {
        var_r3 = 0;
    }
    fn_80055980(var_r3);
    return true;
}
