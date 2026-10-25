// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801ED20C-0x801ED2DC (208B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80303150[];
extern f32 lbl_802AD910;
extern f64 lbl_802AD918;
extern s32 Tmr_GetTime(void);
extern f32 fn_8012570C(s32 hash, s32 flag);
void fn_801ED20C(Unk_C5855798 *arg0) {
    s32 temp_r30;
    s32 var_r9;
    s32 var_lim;
    f32 temp_f1;

    if (arg0->unk0x37C == 0) {
        return;
    }
    temp_r30 = arg0->unk0x380;
    temp_r30 = (*(s32 *)&lbl_80303150 + Tmr_GetTime()) - temp_r30;
    temp_f1 = fn_8012570C(QB_PHYSICS_TIME_BEFORE_FREE_REVERT, 0) * lbl_802AD910;
    if (!(temp_f1 >= lbl_802AD918)) {
        var_lim = (s32)temp_f1;
    } else {
        var_lim = (s32)(temp_f1 - lbl_802AD918);
        var_lim ^= (s32)0x80000000;
    }
    if ((u32)temp_r30 <= (u32)var_lim) {
        return;
    }
    var_r9 = arg0->unk0x37C;
    var_r9 = var_r9 - 1;
    arg0->unk0x37C = var_r9;
    if (var_r9 != 0) {
        arg0->unk0x380 = *(s32 *)&lbl_80303150 + Tmr_GetTime();
    }
}
