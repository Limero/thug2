// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011058C-0x80110644 (184B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8003EF4C(void *, void *, s32, s32, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetVector(CStruct *, s32, CStruct *, s32);
bool ScriptDebugLine(CStruct *pParams, CScript *pScript) {
    f32 sp8[4];
    f32 sp18[4];
    s32 sp28;
    s32 sp2C;

    sp28 = QB_UNKNOWN_0xFF0000FF;
    sp2C = 0;
    GetVector((s32)pParams, QB_START, sp8, 1);
    GetVector((s32)pParams, QB_END, sp18, 1);
    GetInteger((s32)pParams, QB_COLOR, &sp28, 0);
    GetInteger((s32)pParams, QB_FRAMES, &sp2C, 0);
    fn_8003EF4C(sp8, sp18, sp28, 0, sp2C);
    return true;
}
