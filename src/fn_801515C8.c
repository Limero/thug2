// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801515C8-0x80151608 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8005DDBC(s32);
// ScriptResetCamera @ 0x801515C8
bool ScriptResetCamera(CStruct *pParams, CScript *pScript) {
    s32 var_r31;

    var_r31 = 0;
    do {
        fn_8005DDBC(var_r31);
        var_r31 += 1;
    } while (var_r31 <= 1);
    return true;
}
