// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003BF90-0x8003C280 (752B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

s32 fn_8003BF90(s32 arg0, s32 arg1);
s32 GetInteger(s32 arg0, s32 arg1, s32 *arg2, s32 arg3);
s32 GetChecksum_2(s32 arg0, s32 arg1, s32 *arg2, s32 arg3);
s32 fn_80128978(s32, s32);
s32 fn_80128C80(s32, s32, s32 *, s32);
s32 fn_8003ABA0(s32, s32);
s32 fn_8003AB44(s32, s32);
s32 fn_80061720(s32, s32, f32, f32, f32);
s32 fn_80061AD4(s32, s32);

extern s32 lbl_803003E8;
extern s32 lbl_803003F0;
extern char lbl_80292048[];

#define HSV_SET(spH, spS, spV) \
    fn_80061720(lbl_803003E8, arg1, (f32)(f64)spH, \
        (f32)(f64)spS / *(f32 *)lbl_80292048, \
        (f32)(f64)spV / *(f32 *)lbl_80292048)

bool fn_8003BF90(s32 arg0, s32 arg1) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 t3;

    GetChecksum_2(arg1, QB_PART, &sp8, 1);
    t3 = fn_8003ABA0(lbl_803003F0, sp8);
    if (t3 == 0) {
        return true;
    }
    spC = 0;
    GetChecksum_2(t3, QB_DESC_ID, &spC, 0);
    if ((spC == QB_PAPERBAG) || (spC == QB_BIGFOOT)) {
        return false;
    }
    sp10 = 0;
    if (fn_80128978(t3, QB_USE_DEFAULT_HSV) == 0) {
        sp10 = 1;
    } else {
        GetInteger(t3, QB_USE_DEFAULT_HSV, &sp10, 0);
    }
    if (sp10 != 0) {
        t3 = fn_8003AB44(lbl_803003F0, sp8);
        if ((t3 != 0) && GetInteger(t3, QB_DEFAULT_H, &sp14, 0) &&
            GetInteger(t3, QB_DEFAULT_S, &sp18, 0) &&
            GetInteger(t3, QB_DEFAULT_V, &sp1C, 0)) {
            HSV_SET(sp14, sp18, sp1C);
        } else {
            fn_80061AD4(lbl_803003E8, arg1);
        }
        return false;
    }
    if (fn_80128C80(t3, QB_H, &sp20, 0) &&
        fn_80128C80(t3, QB_S, &sp24, 0) &&
        fn_80128C80(t3, QB_V, &sp28, 0)) {
        HSV_SET(sp20, sp24, sp28);
    }
    return true;
}
