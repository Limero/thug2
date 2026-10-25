// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80053E7C-0x80053FB0 (308B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
typedef struct { f32 x, y, z, w; } V4;
s32 fn_80128CE0(CStruct *, void *, void *, s32);
s32 fn_80128978(s32, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 GetVector(CStruct *, s32, CStruct *, s32);
extern f32 lbl_80293004;
s32 fn_80053E7C(s32 arg0, CStruct *arg1) {
    V4 sp8;
    f32 sp18;
    s32 temp_r30;
    s32 temp_r28;
    s32 temp_r3;
    s32 var_r0;

    if (fn_80128978((s32)arg1, QB_SCALE) != 0) {
        if (GetFloat(arg1, QB_SCALE, &sp18, 0) != 0) {
            V4 *pp = &sp8;
            f32 v = sp18;
            sp8.x = v;
            pp->w = lbl_80293004;
            pp->y = v;
            pp->z = v;
            ((__ps_t *)arg0)[1] = ((__ps_t *)pp)[1];
            ((__ps_t *)arg0)[0] = ((__ps_t *)pp)[0];
            return 1;
        }
        if (GetVector(arg1, QB_SCALE, (CStruct *)arg0, 0) != 0) {
            return 1;
        }
    }
    temp_r30 = fn_80128CE0(arg1, QB_X, (void *)arg0, 0);
    temp_r28 = fn_80128CE0(arg1, QB_Y, (void *)(arg0 + 4), 0);
    temp_r3 = fn_80128CE0(arg1, QB_Z, (void *)(arg0 + 8), 0);
    var_r0 = 0;
    if (temp_r30 != 0) {
        goto block_4;
    }
    if (temp_r28 != 0) {
        goto block_4;
    }
    if (temp_r3 != 0) {
    block_4:
        var_r0 = 1;
    }
    return var_r0;
}
