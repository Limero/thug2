// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A0FF0-0x801A1130 (320B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Identification: virtual-camera setup handler — QB_VIRTUAL_CAM gate,
// allocates the camera resource via fn_800F2AD8 and hands it to fn_801A1150
// with the 0x5EA0E211 / 0xF8CFD515 property flags.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f64 lbl_802AB170;
extern f32 lbl_802AB178;
extern s32 lbl_80301B48;
void fn_800AB224(CScript *, CStruct *);
s32 ContainsFlag(CStruct *, s32);
f32 *fn_800F2AD8(s32, s32, s32);
s32 fn_800AB3FC(Unk_C7387A53 *);
void fn_801A1150(Unk_C7387A53 *, f32 *, s32, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_801A11D0(void *, f32);
s32 fn_800AB3E4(Unk_C7387A53 *, s32);
s32 fn_801A0FF0(Unk_C8FEE62D *arg0, CStruct *arg1) {
    s32 sp8;
    s32 mgr;
    s32 flag;
    f32 *res;
    s32 var_r3;

    fn_800AB224(arg0, arg1);
    if (ContainsFlag(arg1, QB_VIRTUAL_CAM) == 0) {
        mgr = lbl_80301B48;
        res = fn_800F2AD8(mgr, fn_800AB3FC(arg0), 0);
        var_r3 = 0;
        if (res == 0) {
            goto done;
        }
        flag = 0;
        if (ContainsFlag(arg1, QB_LOOP) != 0) {
            flag = 1;
        }
        fn_801A1150(arg0, res, flag, ContainsFlag(arg1, QB_BACKWARDS));
    } else {
        sp8 = 0;
        GetInteger(arg1, QB_FRAMES, &sp8, 1);
        fn_801A11D0(arg0, (f32)sp8 / lbl_802AB178);
    }
    fn_800AB3E4(arg0, 1);
    ((void (*)(void *))(*(s32 *)(arg0->unk0x14 + 0x24)))((char *)arg0 + *(s16 *)(arg0->unk0x14 + 0x20));
    var_r3 = 1;
done:
    return var_r3;
}
