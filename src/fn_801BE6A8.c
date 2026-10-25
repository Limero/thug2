// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BE6A8-0x801BE7F0 (328B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AC400[];
extern char lbl_802AC40C[];
extern char lbl_802AC418[];
extern char lbl_802AC424[];
extern char lbl_802AC430[];
extern f32 lbl_802AC43C;
extern f32 lbl_802AC440;
extern s32 fn_8012834C(CStruct *, void *, void *, s32);
extern s32 fn_80128C80(CStruct *, void *, void *, s32);
extern void fn_801BECA0(Unk_31DE137E *, f32, f32, f32, f32, f32);
extern void CSkaterCameraComponent_SetMode(Unk_2C96AD5A *, s32, f32);
s32 fn_801BE6A8(Unk_31DE137E *arg0, u32 arg1, CStruct *arg2) {
    s32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 temp_f0;

    switch (arg1) {
    case QB_SC_SHAKECAMERA:
        temp_f0 = lbl_802AC43C;
        sp8 = temp_f0;
        spC = temp_f0;
        sp10 = temp_f0;
        sp14 = temp_f0;
        sp18 = temp_f0;
        fn_8012834C(arg2, (s32)lbl_802AC400, &sp8, 0);
        fn_8012834C(arg2, (s32)lbl_802AC40C, &spC, 0);
        fn_8012834C(arg2, (s32)lbl_802AC418, &sp10, 0);
        fn_8012834C(arg2, (s32)lbl_802AC424, &sp14, 0);
        fn_8012834C(arg2, (s32)lbl_802AC430, &sp18, 0);
        fn_801BECA0(arg0, sp8, spC, sp10, sp14, sp18);
        break;
    case QB_SC_SETMODE:
        sp1C = 0;
        fn_80128C80(arg2, QB_MODE, &sp1C, 1);
        CSkaterCameraComponent_SetMode(arg0, sp1C, lbl_802AC440);
        break;
    default:
        return 2;
    }
    return 1;
}
