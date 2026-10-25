// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801137A0-0x8011385C (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_8029D0F4;
extern f32 lbl_8029D0F8;
extern s32 lbl_80302C34;

s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
void fn_8011A908(s32, f32, s32, s32);

bool ScriptSetSfxReverb(CStruct *arg0) {
    f32 reverb = 0.0f;
    s32 mode = 0;
    f32 vol;

    GetFloat(arg0, 0, &reverb, 0);
    if (reverb > lbl_8029D0F8) {
        reverb = lbl_8029D0F8;
    }

    GetInteger(arg0, QB_MODE, &mode, 0);
    vol = reverb;
    fn_8011A908(lbl_80302C34, vol, mode, ContainsFlag(arg0, QB_INSTANT));

    return true;
}
