// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802156FC-0x802157D0 (212B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 *lbl_80305EAC;
extern s32 lbl_80305F04;
extern f32 lbl_802AF73C;
extern s32 fn_801A6F44(s32, s32);
extern void fn_801A6F8C(s32, s32);
extern s32 Script_GetInteger(s32, s32);
extern s32 GetStructure(s32, s32);
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
f32 fn_802156FC(s32 arg0) {
    f32 spC;
    f32 sp8;
    s32 temp_r30;

    if (fn_801A6F44(((Unk_C7387A53 *)lbl_80305EAC)->unk0x24, QB_CHEAT_MOON) == 0) {
        GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_GRAVITY, &spC, 1);
        return spC;
    }
    temp_r30 = ((Unk_C7387A53 *)lbl_80305EAC)->unk0x24;
    fn_801A6F8C(temp_r30, Script_GetInteger(QB_CHEAT_MOON, 0));
    lbl_80305F04 = 1;
    GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_GRAVITY, &sp8, 1);
    return sp8 * lbl_802AF73C;
}
