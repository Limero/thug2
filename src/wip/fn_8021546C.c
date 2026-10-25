// PARKED NEAR 96.3% — REQUIRES FLAG: -mps-float (91.5% flagless): single residual doc-15 emission-order swap
// repeated x3: want [bl 80126eac][mr r30,r3][lfs f0/f1][lis r4,QB_SPEED] vs
// got [bl][lfs][lis][mr r30,r3] — the call-result home copy (temp_r30 pinned
// __asm__("r30")) schedules AFTER the independent lis hash-load where want has
// FLAG: -mps-float
// it before. Tried: "+r" barrier after the assignment (collapses allocation,
// 25%, +12B), -fno-sched-spec/-interblock/-schedule-insns (no-op or worse),
// staged division temps (fixed those loads). Everything else byte-exact.
// family=m2c range=0x8021546C-0x802156FC size=656B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AF734;
extern f32 lbl_802AF738;
extern s32 lbl_80305F9C;
extern void fn_800CC038(void *, s32, s32, s32, f32);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern void fn_8012772C(CStruct *, s32, f32);
extern s32 GetStructure(s32, s32);
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern void CStruct_delete(CStruct *, s32);
extern s32 fn_8009CF2C(CStruct *);
void fn_8021546C(Unk_27E58CF3 *arg0) {
    f32 spC;
    f32 sp8;
    f32 temp_f13;
    f32 var_f31;
    s32 temp_r0;
    register s32 temp_r30 __asm__("r30");
    CScript *temp_r11;
    Unk_E71E4713 *temp_r9;

    temp_r0 = arg0->unk0x7B8;
    switch (temp_r0) {
    case 1:
        temp_f13 = arg0->unk0x187C;
        if (temp_f13 > lbl_802AF734) {
            fn_800CC038(arg0->unk0x1840, 0, 0, 0,
                        (f32) (arg0->unk0x7BC / temp_f13));
            if ((s32) *(s32 *)(arg0->unk0x184C + 0x28) != 0) {
                temp_r30 = CStruct_ctor(CStruct_new(8));
                fn_8012772C(temp_r30, QB_SPEED,
                            (f32) (arg0->unk0x7BC / arg0->unk0x187C));
                temp_r11 = arg0->unk0x1840;
                temp_r9 = *((void * *)&temp_r11->unk0x18);
                ((s32 (*)(void *, s32, void *, s32)) *((void * *)&temp_r9->unk0x64))(
                    (char *)temp_r11 + temp_r9->unk0x60, QB_SETPARTIALANIMSPEED, temp_r30, 0);
                if (temp_r30 != 0) {
                    CStruct_delete(temp_r30, 3);
                }
            }
        }
        return;
    case 2:
        GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_HANG_MOVE_ANIMATION_SPEED, &sp8, 1);
        temp_f13 = sp8;
        var_f31 = (f32) (arg0->unk0x7BC / temp_f13);
        temp_r30 = CStruct_ctor(CStruct_new(8));
        fn_8012772C(temp_r30, QB_SPEED, var_f31);
        temp_r11 = arg0->unk0x1840;
        temp_r9 = *((void * *)&temp_r11->unk0x18);
        ((s32 (*)(void *, s32, void *, s32)) *((void * *)&temp_r9->unk0x64))(
            (char *)temp_r11 + temp_r9->unk0x60, QB_SETPARTIALANIMSPEED, temp_r30, 0);
        if (temp_r30 != 0) {
            CStruct_delete(temp_r30, 3);
        }
        fn_800CC038(arg0->unk0x1840, 0, 0, 0, var_f31);
        return;
    case 3:
        GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_LADDER_MOVE_SPEED, &spC, 1);
        temp_f13 = spC;
        var_f31 = (f32) (arg0->unk0x7BC / temp_f13);
        temp_r30 = CStruct_ctor(CStruct_new(8));
        fn_8012772C(temp_r30, QB_SPEED, var_f31);
        temp_r11 = arg0->unk0x1840;
        temp_r9 = *((void * *)&temp_r11->unk0x18);
        ((s32 (*)(void *, s32, void *, s32)) *((void * *)&temp_r9->unk0x64))(
            (char *)temp_r11 + temp_r9->unk0x60, QB_SETPARTIALANIMSPEED, temp_r30, 0);
        if (temp_r30 != 0) {
            CStruct_delete(temp_r30, 3);
        }
        if ((fn_8009CF2C(lbl_80305F9C) == 0) ||
            (__builtin_fabsf((f32) (var_f31 - arg0->unk0x19CC)) < lbl_802AF738)) {
            fn_800CC038(arg0->unk0x1840, 0, 0, 0, var_f31);
            return;
        }
        arg0->unk0x19CC = var_f31;
        fn_800CC038(arg0->unk0x1840, 1, 0, 0, var_f31);
        return;
    }
}
