// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800455A4-0x8004565C (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetFloat(CStruct *, s32, f32 *, s32);
void fn_8004567C(Unk_31DE137E *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void CScreenElement_SetProperties(void);
void fn_8003FB80(Unk_31DE137E *, s32, f32);
void fn_800456D0(Unk_31DE137E *, s32);
void fn_800455A4(Unk_31DE137E *arg0, CStruct *arg1) {
    s32 sp10;
    f32 spC;
    s32 sp8;

    CScreenElement_SetProperties();
    if (GetChecksum_2(arg1, QB_TEXTURE, &sp8, 0) != 0) {
        fn_8004567C(arg0, sp8);
    }
    if (GetFloat(arg1, QB_ROT_ANGLE, &spC, 0) != 0) {
        fn_8003FB80(arg0, 1, spC);
    }
    if (GetChecksum_2(arg1, QB_BLEND, &sp10, 0) != 0) {
        fn_800456D0(arg0, sp10);
    }
}
