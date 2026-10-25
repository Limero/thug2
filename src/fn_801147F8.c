// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801147F8-0x80114A38 (576B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern s32 ContainsFlag(CStruct *, s32);
extern void fn_80130C4C(Unk_FFAD6788 *, s32);
extern void fn_80130C5C(Unk_FFAD6788 *, s32);
extern void fn_80130C6C(Unk_FFAD6788 *, u32);
extern void fn_80130CB8(Unk_FFAD6788 *, u32);
extern f32 lbl_8029D1AC;
extern f32 lbl_8029D1B0;
extern f32 lbl_8029D1B4;
extern f64 lbl_8029D1B8;

static __inline__ s32 wait_unsigned(f32 value) {
    f32 temp_f13;
    f64 threshold;
    s32 result;
    temp_f13 = value;
    threshold = lbl_8029D1B8;
    if (!((f64)temp_f13 >= threshold)) {
        result = (s32)temp_f13;
    } else {
        result = (s32)((f64)temp_f13 - threshold);
        result ^= 0x80000000;
    }
    return result;
}

bool ScriptWait(CStruct *arg0, Unk_FFAD6788 *arg1) {
    f32 sp8;
    f32 seconds_value;
    f32 frame_value;
    s32 temp_r29;
    s32 seconds_int;
    s32 frame_int;
    u32 wait_value;

    sp8 = lbl_8029D1AC;
    GetFloat(arg0, 0, &sp8, 0);
    temp_r29 = ContainsFlag(arg0, QB_INTERLEAVABLE);
    if ((ContainsFlag(arg0, QB_SECONDS) != 0) || (ContainsFlag(arg0, QB_SECOND) != 0)) {
        seconds_value = sp8 * lbl_8029D1B0;
        seconds_int = (s32)seconds_value;
        if (temp_r29 == 0) {
            fn_80130C6C(arg1, (u32)seconds_int);
        } else {
            fn_80130CB8(arg1, (u32)seconds_int);
        }
        return true;
    }
    if ((ContainsFlag(arg0, QB_GAMEFRAME) != 0) || (ContainsFlag(arg0, QB_GAMEFRAMES) != 0) || (ContainsFlag(arg0, QB_GAME) != 0)) {
        fn_80130C4C(arg1, (s32)sp8);
        return true;
    }
    if ((ContainsFlag(arg0, QB_FRAME) != 0) || (ContainsFlag(arg0, QB_FRAMES) != 0)) {
        frame_value = (sp8 * lbl_8029D1B0) / lbl_8029D1B4;
        frame_int = (s32)frame_value;
        if (temp_r29 == 0) {
            fn_80130C6C(arg1, frame_int);
        } else {
            fn_80130CB8(arg1, frame_int);
        }
        return true;
    }
    if (ContainsFlag(arg0, QB_ONE_PER_FRAME) != 0) {
        fn_80130C5C(arg1, (s32)sp8);
        return true;
    }
    if (temp_r29 == 0) {
        wait_value = wait_unsigned(sp8);
        fn_80130C6C(arg1, wait_value);
    } else {
        wait_value = wait_unsigned(sp8);
        fn_80130CB8(arg1, wait_value);
    }
    return true;
}
