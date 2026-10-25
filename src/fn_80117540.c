// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80117540-0x80117588 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80128C80(CStruct *, void *, void *, s32);
// ScriptIsTrue @ 0x80117540
s32 ScriptIsTrue(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 var_r3;

    sp8 = 0;
    fn_80128C80(pParams, 0, &sp8, 0);
    var_r3 = 1;
    if (sp8 == 0) {
        var_r3 = 0;
    }
    return var_r3;
}
