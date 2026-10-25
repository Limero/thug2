// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011391C-0x801139B0 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 ContainsFlag(CStruct *, s32);
void fn_8011A888(s32, f32, s32, s32);

extern f32 lbl_8029D10C;
extern s32 lbl_80302C34;

bool ScriptSetGlobalPitchModulation(CStruct *arg0) {
    f32 sp8;
    f32 fv;

    sp8 = lbl_8029D10C;
    GetFloat(arg0, 0, &sp8, 0);
    fv = sp8;
    fn_8011A888(lbl_80302C34, fv, ContainsFlag(arg0, QB_ALL_SFX), ContainsFlag(arg0, QB_ALL_STREAMS));
    return true;
}
