// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CEA54-0x801CEAE0 (140B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern s32 ContainsFlag(CStruct *, s32);
extern f32 fn_8014030C(s32, s32, Unk_FFAD6788 *);
extern f32 lbl_802AD320;
bool fn_801CEA54(Unk_17FD7108 *arg0, CStruct *arg1) {
    s32 var_r29;

    var_r29 = *((s32 *)&arg0->unk0xC);
    GetFloat(arg1, 0, (char *)arg0 + 0x378, 0);
    if ((ContainsFlag(arg1, QB_DEFAULT) != 0) && (arg0->unk0x384 == lbl_802AD320)) {
        arg0->unk0x378 = fn_8014030C(QB_PHYSICS_ROLLING_FRICTION, 1, var_r29);
    }
    return true;
}
