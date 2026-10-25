// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015164C-0x80151690 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_802A7D54;
extern s32 GetFloat(CStruct * arg0, s32 arg1, f32 * arg2, s32 arg3);
void fn_8016CFFC(f32 arg0);
bool ScriptSetRotateVelocity(CStruct *pParams, CScript *pScript) {
    f32 sp8;

    sp8 = lbl_802A7D54;
    GetFloat(pParams, 0, &sp8, 0);
    fn_8016CFFC(sp8);
    return true;
}
