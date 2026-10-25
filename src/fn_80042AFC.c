// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80042AFC-0x80042C9C (416B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 fn_80128470(CStruct *, s32, f32 *, f32 *, s32);
CStruct *fn_80129528(CStruct *, s32);
void fn_800588A8(s32, s32, s32, s32);
void fn_8005896C(s32, s32, f32, f32);
void fn_80058A70(s32, s32, f32);
void fn_80058BB8(s32, s32);
void fn_80042AFC(Unk_31DE137E *arg0, CStruct *arg1) {
    union { s32 idx; f32 v[12]; } sp;
    f32 temp_f1;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    s32 *temp_r9;
    CStruct *temp_r31;
    u32 var_r29;

    temp_r9 = arg0->unk0x19C;
    var_r29 = 0U;
    fn_80058BB8(*temp_r9, arg0->unk0x190);
    while (var_r29 < (u32) arg1->unk0x4) {
        temp_f31 = 0.0f;
        temp_f29 = 3.1415927410125732f;
        temp_f30 = 180.0f;
        temp_r31 = fn_80129528(arg1, var_r29);
        sp.idx = 0;
        GetInteger(temp_r31, QB_INDEX, &sp.idx, 1);
        sp.v[1] = temp_f31;
        if (GetFloat(temp_r31, QB_ROT_ANGLE, &sp.v[1], 0) != 0) {
            temp_f1 = (sp.v[1] * temp_f29) / temp_f30;
            sp.v[1] = temp_f1;
            fn_80058A70(*arg0->unk0x19C, sp.idx, temp_f1);
        }
        sp.v[2] = temp_f31;
        sp.v[3] = temp_f31;
        if (fn_80128470(temp_r31, QB_OFFSET, &sp.v[2], &sp.v[3], 0) != 0) {
            fn_800588A8(*arg0->unk0x19C, sp.idx, (s32) sp.v[2], (s32) sp.v[3]);
        }
        sp.v[4] = temp_f31;
        sp.v[5] = temp_f31;
        if (fn_80128470(temp_r31, QB_SCALE, &sp.v[4], &sp.v[5], 0) != 0) {
            fn_8005896C(*arg0->unk0x19C, sp.idx, sp.v[4], sp.v[5]);
        }
        var_r29 += 1;
    }
}
