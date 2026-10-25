// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80110538-0x8011058C (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8000B0A0(s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
// ScriptSetProgressive @ 0x80110538
bool ScriptSetProgressive(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 var_r3;

    sp8 = 0;
    GetInteger(pParams, QB_ON, &sp8, 0);
    var_r3 = 1;
    if (sp8 <= 0) {
        var_r3 = 0;
    }
    fn_8000B0A0(var_r3);
    return true;
}
