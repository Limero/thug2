// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CDA44-0x801CDB68 (292B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern s32 ContainsFlag(CStruct *, s32);
extern f32 lbl_802AD2C4;
extern f32 lbl_802AD2C8;
extern f64 lbl_802AD2D0;
extern f32 lbl_802AD2D8;

static __inline__ s32 wait_unsigned(f32 value) {
    f32 temp_f13;
    f64 threshold;
    s32 result;
    temp_f13 = value;
    threshold = lbl_802AD2D0;
    if (!((f64)temp_f13 >= threshold)) {
        result = (s32)temp_f13;
    } else {
        result = (s32)((f64)temp_f13 - threshold);
        result ^= 0x80000000;
    }
    return result;
}

s32 fn_801CDA44(CStruct *arg0, CStruct *arg1) {
    f32 sp8;
    sp8 = lbl_802AD2C4;
    GetFloat(arg1, 0, &sp8, 0);
    if ((ContainsFlag(arg1, QB_SECONDS) != 0) || (ContainsFlag(arg1, QB_SECOND) != 0)) {
        return wait_unsigned(sp8 * lbl_802AD2C8);
    }
    if ((ContainsFlag(arg1, QB_FRAMES) != 0) || (ContainsFlag(arg1, QB_FRAME) != 0)) {
        return wait_unsigned(sp8 * lbl_802AD2D8);
    }
    return wait_unsigned(sp8);
}
