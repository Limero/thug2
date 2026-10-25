// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010F3DC-0x8010F43C (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8012772C(CStruct *, s32, f32);
s32 GetFloat(CStruct *, void *, f32 *, void *);
f32 acosf(f32);
extern f32 lbl_8029CEE4;
bool ScriptACos(CStruct *pParams, CScript *pScript) {
    f32 sp8;
    f32 var_f0;

    GetFloat(pParams, 0, &sp8, 1);
    var_f0 = acosf(sp8) * lbl_8029CEE4;
    fn_8012772C(pScript->unk0x18, QB_ACOS, var_f0);
    return true;
}
