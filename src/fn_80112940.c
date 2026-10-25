// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80112940-0x801129F0 (176B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_8005E1B8(f32);
void fn_8005E1E8(f32);
void fn_80055960(s32);

bool ScriptSetScreen(CStruct *pParams, CScript *pScript) {
    f32 sp8;
    f32 spC;
    s32 sp10;
    s32 enabled;

    if (GetFloat(pParams, QB_ASPECT, &sp8, 0) != 0)
        fn_8005E1B8(sp8);
    if (GetFloat(pParams, QB_ANGLE, &spC, 0) != 0)
        fn_8005E1E8(spC);
    if (GetInteger(pParams, QB_LETTERBOX, &sp10, 0) != 0) {
        enabled = 1;
        if (sp10 == 0)
            enabled = 0;
        fn_80055960(enabled);
    }
    return true;
}
