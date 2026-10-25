// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80221B14-0x80221B7C (104B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_8009CF2C(CStruct * arg0);
extern s32 fn_80219698(CStruct * arg0);
extern s32 fn_80219638(Unk_C7387A53 * arg0);
extern s32 lbl_80305F9C;
bool ScriptIsAutoServing(CStruct *pParams, CScript *pScript) {
    s32 temp_r31;

    temp_r31 = lbl_80305F9C;
    if (fn_8009CF2C(temp_r31) == 0) {
        return false;
    }
    if (fn_80219698(temp_r31) == 0) {
        return false;
    }
    return (fn_80219638(temp_r31) ^ 1) == 0;
}
