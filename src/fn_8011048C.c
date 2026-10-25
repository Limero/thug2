// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011048C-0x80110538 (172B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8012772C(CStruct *, s32, f32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
bool ScriptClamp(CStruct *pParams, CScript *pScript) {
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 var_f13;
    f32 minv;

    GetFloat(pParams, 0, &sp8, 1);
    GetFloat(pParams, QB_MIN, &spC, 1);
    GetFloat(pParams, QB_MAX, &sp10, 1);
    minv = spC;
    fn_8012772C(pScript->unk0x18, QB_CLAMPED,
        (var_f13 = ((sp8 > sp10) ? sp10 : sp8), (var_f13 < minv) ? minv : var_f13));
    return true;
}
