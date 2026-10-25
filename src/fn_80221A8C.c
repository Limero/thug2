// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80221A8C-0x80221B14 (136B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_8009CF2C(CStruct * arg0);
extern s32 fn_80219698(CStruct * arg0);
extern s32 fn_80219638(Unk_C7387A53 * arg0);
extern void *NextItem(s32 arg0);
extern s32 fn_80229884(CScript * arg0);
extern s32 lbl_80305F9C;
s32 ScriptIsHost(CStruct *pParams, CScript *pScript) {
    s32 temp_r31;
    s32 temp_r0;
    register s32 var_r3 __asm__("r3");

    temp_r31 = lbl_80305F9C;
    if (fn_8009CF2C(temp_r31) == 0) {
        return 0;
    }
    if (fn_80219698(temp_r31) != 0) {
        return fn_80219638(temp_r31) == 0;
    }
    var_r3 = (s32)NextItem(temp_r31);
    if (var_r3 == 0) {
        goto zeropath;
    }
    temp_r0 = fn_80229884(var_r3);
    var_r3 = 1;
    if (temp_r0 == 0) {
zeropath:
        var_r3 = 0;
    }
    return var_r3;
}
