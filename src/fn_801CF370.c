// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CF370-0x801CF4F0 (384B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 ContainsFlag(CStruct *, s32);
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern f32 fn_8014030C(s32, s32, Unk_FFAD6788 *);
extern f32 lbl_802AD338;
extern f32 lbl_802AD33C;
extern f32 lbl_802AD340;
extern f32 lbl_802AD344;
extern f32 lbl_802AD348;

bool fn_801CF370(Unk_FBF5ED10 *arg0, CStruct *arg1) {
    volatile double _dummy;
    s32 var_r29;
    f32 temp_f31;

    var_r29 = arg0->unk0xC;
    if (ContainsFlag(arg1, QB_LEVELEND) != 0) {
        goto store338;
    }
    temp_f31 = lbl_802AD33C;
    if (arg0->unk0x3B8 == temp_f31) {
        goto done;
    }
    if (ContainsFlag(arg1, QB_END) == 0) {
        goto body;
    }
store338:
    arg0->unk0x3B8 = lbl_802AD338;
    goto done;
body:
    GetFloat(arg1, QB_MAX, (char *)arg0 + 0x3BC, 1);
    arg0->unk0x3C0 = arg0->unk0x3BC;
    GetFloat(arg1, QB_MAX_MAX, (char *)arg0 + 0x3C0, 0);
    arg0->unk0x3B8 = lbl_802AD340;
    GetFloat(arg1, QB_TIME, (char *)arg0 + 0x3B8, 0);
    arg0->unk0x3C4 = lbl_802AD344;
    GetFloat(arg1, QB_FRICTION, (char *)arg0 + 0x3C4, 0);
    arg0->unk0x3C8 = fn_8014030C(QB_PHYSICS_GROUND_GRAVITY, 1, var_r29);
    GetFloat(arg1, QB_GRAVITY, (char *)arg0 + 0x3C8, 0);
    if (ContainsFlag(arg1, QB_NOTIMELIMIT) != 0) {
        arg0->unk0x3B8 = lbl_802AD348;
    }
    if (ContainsFlag(arg1, QB_CURRENTLEVEL) != 0) {
        arg0->unk0x3B8 = temp_f31;
    }
done:
    return true;
}
