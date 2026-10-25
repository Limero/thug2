// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F07CC-0x801F08FC (304B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_80032088(s32);
extern s32 fn_8012ED98(s32 *);
extern s32 GetStructure_2(CStruct *, s32, s32 *, s32);
extern f32 fn_80141570(CScript *, CStruct *);
extern void fn_800CC0F8(s32, void *, s32);
void fn_801F07CC(void *arg0, CStruct *arg1) {
    struct {
        f32 sp8;
        f32 spC;
        f32 sp10;
        f32 sp14;
        f32 sp18;
        char _pad1C[4];
        s32 sp20;
    } fr;
    Unk_C8FEE62D *temp_r30;
    Unk_FCBBC883 *temp_r31;

    temp_r31 = arg0;
    temp_r30 = temp_r31->unk0xC;
    if ((s32)temp_r30->unk0x14 == 0) {
        temp_r30->unk0x14 = fn_8012ED98(fn_80032088(0xF8));
    }
    fr.sp20 = 0;
    GetStructure_2(arg1, QB_WOBBLEAMPA, &fr.sp20, 1);
    fr.sp8 = fn_80141570(temp_r31->unk0xC, fr.sp20);
    GetStructure_2(arg1, QB_WOBBLEAMPB, &fr.sp20, 1);
    fr.spC = fn_80141570(temp_r31->unk0xC, fr.sp20);
    GetStructure_2(arg1, QB_WOBBLEK1, &fr.sp20, 1);
    fr.sp10 = fn_80141570(temp_r31->unk0xC, fr.sp20);
    GetStructure_2(arg1, QB_WOBBLEK2, &fr.sp20, 1);
    fr.sp14 = fn_80141570(temp_r31->unk0xC, fr.sp20);
    GetStructure_2(arg1, QB_SPAZFACTOR, &fr.sp20, 1);
    fr.sp18 = fn_80141570(temp_r31->unk0xC, fr.sp20);
    fn_800CC0F8(temp_r31->unk0x1E8, &fr.sp8, 1);
}
