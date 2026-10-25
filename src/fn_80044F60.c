// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80044F60-0x80045054 (244B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ContainsFlag(s32, s32);
void fn_80045218(Unk_EE1FD121 *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
void fn_800450B4(Unk_E80761A5 *, s32);
void fn_800414B0(Unk_EE1FD121 *);
void fn_8005EA3C(s32, s32);
void fn_80045170(Unk_EE1FD121 *, s32, f32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_80044F60(Unk_EE1FD121 *arg0, CStruct *arg1) {
    s32 sp10;
    f32 spC;
    s32 sp8;
    s32 temp_r30;

    CScreenElement_SetProperties();
    if (GetChecksum_2(arg1, QB_TEXTURE, &sp8, 0) != 0) {
        fn_800450B4(arg0, sp8);
    }
    if (GetFloat(arg1, QB_ROT_ANGLE, &spC, 0) != 0) {
        fn_80045170(arg0, 1, spC);
    }
    if (GetChecksum_2(arg1, QB_BLEND, &sp10, 0) != 0) {
        fn_80045218(arg0, sp10);
    }
    if (ContainsFlag(arg1, QB_NO_ZWRITE) != 0) {
        arg0->unk0x194 = 0;
    }
    fn_800414B0(arg0);
    temp_r30 = arg0->unk0x198;
    fn_8005EA3C(temp_r30, fn_8004DD70());
}
