// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A17C8-0x801A1964 (412B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Identification: camera/object property handler — reads the 0x17E7321E f32
// property into +0x3C, forwards to fn_800244BC, then allocates the camera
// resource when 0xEE721991 is not set.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void fn_800AB224(CScript *, CStruct *);
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern void fn_800244BC(Unk_FFAD6788 *, f32);
extern s32 ContainsFlag(CStruct *, s32);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 fn_800F2AD8(s32, s32, s32);
extern s32 fn_800AB3FC(Unk_C7387A53 *);
extern s32 fn_800AB3E4(Unk_C7387A53 *, s32);
extern s32 fn_801A1AAC(Unk_C7387A53 *, f32 *, s32, s32);
extern s32 fn_801A1B2C(void *, f32);
extern void fn_801A1998(Unk_C8FEE62D *, CStruct *);
extern void fn_801A1C7C(Unk_C8FEE62D *);
extern void fn_801A1BE4(void *, s32, f32, f32);
extern f32 lbl_802AB1A8;
extern s32 lbl_80301B48;
s32 fn_801A17C8(Unk_DB0E2BAB *arg0, CStruct *arg1) {
    s32 sp8;
    s32 spC;
    s32 var_r3;
    s32 var_r30;
    s32 temp_r28;
    s32 temp_r30;
    s32 temp_r3;
    Unk_89391A04 *temp_r9;

    fn_800AB224(arg0, arg1);
    if (GetFloat(arg1, QB_FOV, &sp8, 0) != 0) {
        *(f32 *)&sp8 = *(f32 *)&sp8;
        *((f32 *)&arg0->unk0x3C) = *(f32 *)&sp8;
        fn_800244BC(arg0->unk0x18, *(f32 *)&sp8);
    }
    var_r3 = 0;
    if (ContainsFlag(arg1, QB_VIRTUAL_CAM) == 0) {
        temp_r30 = lbl_80301B48;
        temp_r28 = fn_800F2AD8(temp_r30, fn_800AB3FC(arg0), 0);
        if (temp_r28 == 0) {
            return var_r3;
        }
        temp_r3 = ContainsFlag(arg1, QB_LOOP);
        var_r30 = 0;
        if (temp_r3 != 0) {
            var_r30 = 1;
        }
        fn_801A1AAC(arg0, (f32 *)temp_r28, var_r30,
                    ContainsFlag(arg1, QB_BACKWARDS));
    } else {
        spC = 0;
        GetInteger(arg1, QB_FRAMES, &spC, 1);
        fn_801A1B2C(arg0, (f32)(f64)spC / lbl_802AB1A8);
    }
    fn_800AB3E4(arg0, 1);
    fn_801A1998(arg0, arg1);
    temp_r9 = *((void * *)&arg0->unk0x14);
    ((void (*)(void *)) *((void * *)&temp_r9->unk0x24))(
        (char *)arg0 + (int) temp_r9->unk0x20);
    fn_801A1C7C(arg0);
    fn_801A1BE4(arg0, 1, arg0->unk0x90,
                arg0->unk0x90);
    return 1;
}
