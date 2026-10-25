// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802150E4-0x802151B0 (204B). Byte-identical.
#include "types.h"
extern f32 lbl_802AF720;
extern char lbl_80303150[];
#include "qb_constants.h"
#include "structs.h"
s32 Tmr_GetTime();
void fn_802150E4(Unk_28EF92FB *arg0, s32 arg1) {
    f32 temp_f0;
    f32 temp_f13;
    f32 var_f12;
    s32 temp_r30;

    if ((s32) arg0->unk0x1C == 0) {
        temp_r30 = arg0->unk0x20;
        if ((u32) ((*(s32 *)&lbl_80303150 + Tmr_GetTime()) - temp_r30) <= 0x63U) {
            arg0->unk0x7C0 = (f32) arg0->unk0x7BC;
            return;
        }
        temp_f0 = arg0->unk0x7C0;
        temp_f13 = arg0->unk0x7BC;
        var_f12 = temp_f0;
        __asm__("" : "+f"(var_f12));
        if (temp_f13 < temp_f0) {
            var_f12 = temp_f13;
        }
        arg0->unk0x7C0 = temp_f13;
        arg0->unk0x7BC = var_f12;
        if ((arg0->unk0x80 == QB_RUN) && (var_f12 == lbl_802AF720)) {
            if (arg1 == QB_SKID) {
                arg0->unk0x80 = arg1;
                return;
            }
            arg0->unk0x80 = QB_STAND;
        }
    }
}
