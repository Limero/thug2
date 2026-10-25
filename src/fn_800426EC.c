// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800426EC-0x80042768 (124B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetFloat(CStruct *, s32, f32 *, s32);
void CScreenElement_SetMorph(Unk_2B0B333E *, CStruct *);
void CBlurEffect_SetMorph(void *, CStruct *, s32 *);
void fn_80042924(Unk_E80761A5 *, s32, f32);
void fn_800426EC(Unk_C7387A53 *arg0, CStruct *arg1) {
    f32 sp8;

    if ((s32) arg0->unk0x1A8 != 0) {
        CBlurEffect_SetMorph(arg0->unk0x1A8, arg1, 0);
    }
    CScreenElement_SetMorph(arg0, arg1);
    if (GetFloat(arg1, QB_ROT_ANGLE, &sp8, 0) != 0) {
        fn_80042924(arg0, 0, sp8);
    }
}
