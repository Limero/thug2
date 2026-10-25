// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019E250-0x8019E340 (240B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EE4;
extern f32 lbl_802AAE68;
extern f64 lbl_802AAE70;
void fn_80125000(Unk_C71E6DE1 *);
s32 GetPair(s32, s32, s32 *, s32);
typedef struct out_t {
    s32 unk0;
    f32 unk4;
    f32 unk8;
} out_t;
bool ScriptSetMenuAutoRepeatTimes(CStruct *pParams, CScript *pScript) {
    out_t out;
    f32 temp_f13;
    f32 temp_f14;
    s32 var_r10;
    s32 var_r0;
    Unk_C7387A53 *temp_r8;
    register f32 fv __asm__("fr0");

    fn_80125000(&out);
    GetPair(pParams, 0, &out, 1);
    temp_r8 = (void *)lbl_80305EE4;
    fv = out.unk4;
    temp_f13 = fv * lbl_802AAE68;
    if (!(temp_f13 >= lbl_802AAE70)) {
        var_r10 = (s32)temp_f13;
    } else {
        var_r10 = (s32)(temp_f13 - lbl_802AAE70);
        var_r10 ^= (s32)0x80000000;
    }
    fv = out.unk8;
    temp_f14 = fv * lbl_802AAE68;
    if (!(temp_f14 >= lbl_802AAE70)) {
        var_r0 = (s32)temp_f14;
    } else {
        var_r0 = (s32)(temp_f14 - lbl_802AAE70);
        var_r0 ^= (s32)0x80000000;
    }
    temp_r8->unk0x50 = var_r10;
    temp_r8->unk0x54 = var_r0;
    return true;
}
