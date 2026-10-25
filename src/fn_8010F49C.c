// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010F49C-0x8010F4F0 (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8012772C(CStruct *, s32, f32);
s32 GetFloat(CStruct *, void *, f32 *, void *);
f32 sqrtf(f32);
bool ScriptSqrt(CStruct *pParams, CScript *pScript) {
    f32 sp8;
    f32 var_f0;

    GetFloat(pParams, 0, &sp8, 1);
    var_f0 = sqrtf(sp8);
    fn_8012772C(pScript->unk0x18, QB_SQRT, var_f0);
    return true;
}
