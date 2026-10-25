// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80110EB4-0x80110F7C (200B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_8029CF84;
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_80059380(f32, f32);
void fn_80059394(s32, f32, f32);
bool ScriptSetDynamicLightModulationFactor(CStruct *pParams, CScript *pScript) {
    f32 sp8;
    f32 spC;
    s32 sp10;

    sp8 = lbl_8029CF84;
    spC = lbl_8029CF84;
    sp10 = 0;
    if (GetFloat(pParams, QB_VALUE, &sp8, 0) != 0) {
        GetFloat(pParams, QB_VALUE2, &spC, 0);
        if (ContainsFlag(pParams, QB_AMBIENT) != 0) {
            fn_80059380(sp8, spC);
        } else {
            GetInteger(pParams, QB_DIRECTIONAL, &sp10, 0);
            fn_80059394(sp10, sp8, spC);
        }
    }
    return true;
}
