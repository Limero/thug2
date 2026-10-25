// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80045054-0x800450B4 (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetFloat(CStruct *, s32, f32 *, s32);
void CScreenElement_SetMorph(void);
void fn_80045170(Unk_C399A1AE *, s32, f32);
void fn_80045054(Unk_C399A1AE *arg0, CStruct *arg1) {
    f32 sp8;

    CScreenElement_SetMorph();
    if (GetFloat(arg1, QB_ROT_ANGLE, &sp8, 0) != 0) {
        fn_80045170(arg0, 0, sp8);
    }
}
