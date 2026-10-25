// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80034368-0x80034608 (672B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_8006FB50(s32, s32);
s32 fn_8006FB8C(s32, s32);
void fn_8002DEAC(void *, s32, s32, f32, f32, f32, f32);
extern char lbl_80291C80[];
extern char lbl_80291C7C[];
#include "qb_constants.h"
#include "structs.h"
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_80034368(Unk_DB0E2BAB *arg0, s32 arg1, CStruct *arg2) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    s32 sp14;
    f32 sp10;
    f32 spC;
    s32 sp8;
    u32 swv1;
    f32 minA;
    f32 maxA;
    CScript *scr;
    f32 base;
    f32 span;
    switch (swv1 = arg1) {
    case QB_INVALIDATECACHE:
        arg0->unk0x34 = fn_8006FB50(arg0->unk0x30, 0);
    default:
        return 2;
    case QB_PLAYSEQUENCE:
        GetChecksum_2(arg2, QB_ANIMNAME, &sp8, 1);
        GetFloat(arg2, QB_STARTTIME, &spC, 1);
        GetFloat(arg2, QB_ENDTIME, &sp10, 1);
        GetInteger(arg2, QB_LOOPTYPE, &sp14, 1);
        GetFloat(arg2, QB_BLENDPERIOD, &sp18, 1);
        GetFloat(arg2, QB_SPEED, &sp1C, 1);
        fn_8002DEAC((void *)(arg0->unk0x4 + 4), sp8, sp14, spC, sp10, sp18, sp1C);
        arg0->unk0x34 = fn_8006FB8C(arg0->unk0x30, arg0->unk0x38 + sp8);
        return 1;
    case QB_SETWOBBLETARGET:
        if (GetFloat(arg2, QB_WOBBLETARGETALPHA, &sp20, 0) != 0) {
            minA = *(f32 *)lbl_80291C7C;
            if (sp20 < minA) {
                sp20 = minA;
            }
            maxA = *(f32 *)lbl_80291C80;
            if (sp20 > maxA) {
                sp20 = maxA;
            }
            scr = arg0->unk0x4;
            base = *(f32 *)&scr->unk0x1C;
            span = *(f32 *)&scr->unk0x24;
            *(f32 *)&arg0->unk0x2C = (span - base) * sp20 + base;
        }
        return 1;
    case QB_SETWOBBLEDETAILS:
        if ((GetFloat(arg2, QB_WOBBLEAMPA, &sp24, 0) != 0) && (GetFloat(arg2, QB_WOBBLEAMPB, &sp28, 0) != 0) && (GetFloat(arg2, QB_WOBBLEK1, &sp2C, 0) != 0) && (GetFloat(arg2, QB_WOBBLEK2, &sp30, 0) != 0) && (GetFloat(arg2, QB_SPAZFACTOR, &sp34, 0) != 0)) {
            *(f32 *)&arg0->unk0x18 = sp24;
            *(f32 *)&arg0->unk0x1C = sp28;
            *(f32 *)&arg0->unk0x20 = sp2C;
            *(f32 *)&arg0->unk0x24 = sp30;
            *(f32 *)&arg0->unk0x28 = sp34;
        }
        return 1;
    }
}
