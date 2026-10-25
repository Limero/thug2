// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801129F0-0x80112A44 (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8005548C(s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
// ScriptAllowBoneLOD @ 0x801129F0
bool ScriptAllowBoneLOD(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 var_r3;

    sp8 = 1;
    GetInteger(pParams, QB_ALLOW, &sp8, 0);
    var_r3 = 1;
    if (sp8 <= 0) {
        var_r3 = 0;
    }
    fn_8005548C(var_r3);
    return true;
}
