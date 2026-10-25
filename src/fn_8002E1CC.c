// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002E1CC-0x8002E34C (384B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Script/param-driven object setup handler: reads a batch of script params
// into object fields (fn_80128xxx read family), then conditionally drives a
// chain of effect/behaviour calls (fn_8002E174/fn_8002E0F8/fn_8002FC20/
// fn_80030580/fn_80030ADC/fn_80030AE4) keyed on those params. The helper
// callees are declared `extern f32` so ngccc emits no crclr cr1eq before
// their bls (SN float-return convention, §4p item-27).
#include "types.h"
extern f32 lbl_80291970;
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_80128C80(CStruct *, void *, void *, s32);
s32 fn_80128CE0(CStruct *, void *, void *, s32);
s32 fn_80128E34(CStruct *, void *, void *, s32);
extern f32 fn_8002E174(Unk_31DE137E *, s32);
extern f32 fn_8002E0F8(CStruct *);
extern f32 fn_8002FC20(Unk_A9157FE7 *, s32, f32);
extern f32 fn_80030580(Unk_C7387A53 *, s32, s32);
extern f32 fn_80030ADC(Unk_C7387A53 *, s32);
extern f32 fn_80030AE4(Unk_C7387A53 *, s32);
s32 ContainsFlag(CStruct *, s32);
void fn_8002E1CC(CStruct * arg0, CStruct *arg1) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r30;

    fn_80128E34(arg1, QB_SUBSETID, (char *)arg0 + 0x30, 0);
    fn_80128CE0(arg1, QB_BLENDWEIGHT, (char *)arg0 + 0x38, 0);
    sp8 = 0;
    fn_80128C80(arg1, QB_STAGE, &sp8, 0);
    arg0->unk0x34 = sp8;
    fn_80128E34(arg1, QB_ANIMEVENTTABLENAME, (char *)arg0 + 0x68, 0);
    if (GetChecksum_2(arg1, QB_REFERENCECHECKSUM, &spC, 0) == 0) {
        GetChecksum_2(arg1, QB_SKELETONNAME, &spC, 1);
    }
    fn_8002E174(arg0, spC);
    fn_8002E0F8(arg0);
    sp10 = QB_DEFAULT;
    temp_r30 = fn_80128E34(arg1, QB_DEFAULTANIMNAME, &sp10, 0);
    fn_8002FC20(arg0, sp10, lbl_80291970);
    if (temp_r30 != 0) {
        fn_80030580(arg0, 1, 1);
    }
    if (ContainsFlag(arg1, QB_ENABLEBLENDING) != 0) {
        fn_80030ADC(arg0, 1);
    }
    fn_80030AE4(arg0, ContainsFlag(arg1, QB_ENABLEANIMEVENTS));
}
