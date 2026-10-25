// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010F2BC-0x8010F31C (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8012772C(void *, void *);
s32 GetFloat(CStruct *, void *, f32 *, void *);
extern f32 lbl_8029CED8;
bool ScriptCos(CStruct *pParams, CScript *pScript) {
    f32 sp8;

    GetFloat(pParams, 0, &sp8, 1);
    cosf(sp8 * lbl_8029CED8);
    fn_8012772C(pScript->unk0x18, QB_COS);
    return true;
}
