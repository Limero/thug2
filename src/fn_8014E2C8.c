// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8014E2C8-0x8014E30C (68B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 GetText(CStruct *, void *, void *, s32);
void fn_80124C00(s32);
s32 ScriptPlayMovie(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 var_r3;

    if (GetText(pParams, 0, &sp8, 1) == 0) {
        var_r3 = 0;
    } else {
        fn_80124C00(sp8);
        var_r3 = 1;
    }
    return var_r3;
}
