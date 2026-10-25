// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B7A80-0x800B7BF4 (372B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_80298B68;
extern f32 lbl_80298B6C;
extern f32 lbl_80298B70;
s32 GetFloat(CStruct * arg0, s32 arg1, f32 * arg2, s32 arg3);
s32 GetArray(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
s8 fn_801293FC(CStruct * arg0, s32 arg1);
s32 fn_800B7A80(Unk_31DE137E *arg0, u32 arg1, CStruct *arg2) {
    struct {
        f32 sp8;
        f32 spC;
        s32 sp10;
        u32 sp14;
    } s;
    volatile double _dummy;
    f32 temp_f31;
    f32 temp_f13;
    u32 temp_r0;
    void *temp_r30;
    CScript *temp_r3;
    Unk_C7387A53 *temp_r9;

    temp_r0 = QB_DYNAMICLIGHT_SETINTENSITY;
    if (arg1 == temp_r0) {
        goto case_E;
    }
    if (arg1 > temp_r0) {
        goto block_C;
    }
    if (arg1 == QB_DYNAMICLIGHT_SETRGBA) {
        goto case_D;
    }
    goto block_B;
block_C:
    if (arg1 != QB_DYNAMICLIGHT_SETRADIUS) {
        goto block_B;
    }
case_A:
    temp_f31 = lbl_80298B68;
    s.sp8 = temp_f31;
    GetFloat(arg2, QB_RADIUS, &s.sp8, 1);
    temp_f13 = s.sp8;
    temp_r3 = *((void * *)&arg0->unk0x1C);
    *((f32 *)&temp_r3->unk0x1C) = temp_f13;
    if (temp_f13 != temp_f31) {
        *((f32 *)&temp_r3->unk0x20) = lbl_80298B6C / temp_f13;
    } else {
        *((f32 *)&temp_r3->unk0x20) = lbl_80298B70;
    }
    goto Lr1;
case_E:
    s.spC = lbl_80298B68;
    GetFloat(arg2, QB_INTENSITY, &s.spC, 1);
    temp_r9 = *((void * *)&arg0->unk0x1C);
    *((f32 *)&temp_r9->unk0x24) = s.spC;
    goto Lr1;
case_D:
    s.sp10 = 0;
    temp_r30 = (void *)&s.sp14;
    GetArray(arg2, QB_RGBA, &s.sp10, 1);
    *(u8 *)&s.sp14 = fn_801293FC(s.sp10, 0);
    *((u8 *)&s.sp14 + 1) = fn_801293FC(s.sp10, 1);
    *((u8 *)temp_r30 + 2) = fn_801293FC(s.sp10, 2);
    *((u8 *)temp_r30 + 3) = fn_801293FC(s.sp10, 3);
    temp_r9 = *((void * *)&arg0->unk0x1C);
    temp_r9->unk0x28 = *(s32 *)&s.sp14;
    goto Lr1;
block_B:
    return 2;
Lr1:
    return 1;
}
