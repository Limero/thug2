// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80109C40-0x80109CF8 (184B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_8029CD2C;
extern f32 lbl_8029CD30;
extern f32 lbl_8029CD34;
extern f32 lbl_8029CD38;
extern s32 GetVector(CStruct *, s32, CStruct *, s32);
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern void fn_8010B920(void *, void *, f32);
void fn_80109C40(CStruct *arg0) {
    f32 temp_f12;
    f32 temp_f0;
    f32 temp_f11;
    f32 temp_f13;
    f32 vec[4];
    char out[16];
    f32 fval;
    f32 *vp;

    vp = &vec[0];
    temp_f12 = lbl_8029CD2C;
    temp_f0 = lbl_8029CD30;
    temp_f11 = lbl_8029CD34;
    temp_f13 = lbl_8029CD38;
    vp[0] = temp_f12;
    vp[1] = temp_f0;
    vp[3] = temp_f13;
    vp[2] = temp_f11;
    fval = temp_f11;
    GetVector(arg0, QB_CENTER, &vec[0], 0);
    GetFloat(arg0, QB_MORPH_TIME, &fval, 0);
    GetVector(arg0, QB_SUN_POS, &out[0], 1);
    fn_8010B920(&out[0], &vec[0], *(f32 *)&fval);
}
