// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020ACB0-0x8020ADE4 (308B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AF378[];
extern char lbl_802AF380[];
extern s32 GetChecksum_3(Unk_6A70655D *, s32);
extern s32 fn_800CC358(Unk_C7387A53 *);
extern f32 fn_8020ADE4(void *);
extern void Script_RunScript(s32, s32, s32, s32, s32);
extern void fn_800CC038(s32, s32, s32, s32, f32);
void fn_8020ACB0(Unk_CEAF6E85 *arg0) {
    f32 var_f1;
    s32 temp_r30;
    s32 var_r11;

    if (arg0->unk0x1378 != 0) {
        temp_r30 = GetChecksum_3(arg0->unk0xC, QB_ANIMBLENDER);
        if ((fn_800CC358(temp_r30) == QB_RUNOUT) || (fn_800CC358(temp_r30) == QB_RUNOUTQUICK)) {
            var_f1 = fn_8020ADE4(arg0);
            fn_800CC038(temp_r30, 1, 0, 0, var_f1);
        } else if (fn_8020ADE4(arg0) > *(f64 *)lbl_802AF378) {
            var_r11 = 1;
            if (*(s32 *)(arg0->unk0x34 + 0x20) == 0) {
                var_r11 = 0;
            }
            if (var_r11 == 1) {
                var_f1 = *(f32 *)lbl_802AF380;
                fn_800CC038(temp_r30, 1, 0, 0, var_f1);
            } else {
                Script_RunScript(QB_TANTRUMOFF, 0, arg0->unk0xC, 0, 0);
                if ((arg0->unk0x1C10 == 0)
                    || (arg0->unk0x1C0C != 0)) {
                    var_f1 = fn_8020ADE4(arg0);
                    fn_800CC038(temp_r30, 1, 0, 0, var_f1);
                } else {
                    arg0->unk0x1C0C = 1;
                    Script_RunScript(QB_BAIL_QUICK_GETUP, 0, arg0->unk0xC, 0, 0);
                }
            }
        }
    }
}