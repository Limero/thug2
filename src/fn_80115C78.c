// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80115C78-0x80115E3C (452B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(s32, s32, s32, s32);
s32 ContainsFlag(CStruct *, void *);
s32 GetFloat(CStruct *, void *, f32 *, void *);
s32 AddInteger(CStruct *, void *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
extern f32 lbl_8029D1D0;
s32 Mth_Rnd(s32 scale);
void fn_8012772C(CStruct *arg0, s32 arg1, f32 farg0);
bool ScriptGetRandomValue(CStruct *pParams, CScript *pScript) {
    f32 sp1C;
    f32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    f32 temp_f0;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r9;

    sp8 = 0;
    GetChecksum_2(pParams, QB_NAME, &sp8, 0);
    if (ContainsFlag(pParams, QB_INTEGER) != 0) {
        spC = 0;
        sp10 = 0;
        GetInteger(pParams, QB_A, &spC, 0);
        GetInteger(pParams, QB_B, &sp10, 0);
        temp_r9 = spC;
        if (temp_r9 > sp10) {
            spC = sp10;
            sp10 = temp_r9;
        }
        temp_r29 = pScript->unk0x18;
        AddInteger(temp_r29, sp8, spC + Mth_Rnd((sp10 - spC) + 1));
    } else {
        sp14 = 0x3E8;
        GetInteger(pParams, QB_RESOLUTION, &sp14, 0);
        temp_f0 = lbl_8029D1D0;
        sp18 = temp_f0;
        sp1C = temp_f0;
        GetFloat(pParams, QB_A, &sp18, 0);
        GetFloat(pParams, QB_B, &sp1C, 0);
        temp_r30 = pScript->unk0x18;
        fn_8012772C(temp_r30, sp8, sp18 + (((f32) (f64) Mth_Rnd(sp14) * (sp1C - sp18)) / (f32) (f64) (sp14 - 1)));
    }
    return true;
}