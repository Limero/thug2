// WIP DRAFT (non-matching) — hand edit (u32 switch index recipe 84; r11 pin
// for arg0 homing §74-166; per-arm float LOCAL forces in-arm lfs f1 so
// crossjump merges only [li r5;bl]; fn_8009F054 = (s32,s32,s32,f32) mixed ABI).
// PARKED 83.2%: arms match byte-for-byte except each arm's [lfs f1] lands
// one pair early ([lis9][li][lfs][lis4][lwz3][ori] vs want's
// [lis9][li][lis4][lwz3][lfs][ori]), and old-style proto `void fn();` (which
// gives want's arm order) adds crset cr1eq while full/f32 protos kill the
// crset but reorder lfs early. u32 switch + r11 pin + per-arm float locals +
// case source order are all required; schedule flags resist the rest.
// family=m2c range=0x801C0FF4-0x801C1170 size=380B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8009F054();
extern f32 lbl_802AC700;
s32 fn_801C0FF4(void *arg0, u32 arg1) {
    register s32 o __asm__("r11");
    s32 var_r3;
    s32 var_r0;

    o = (s32)arg0;
    switch (arg1) {
    case QB_INNOLLIE:
        var_r0 = ((Unk_C7387A53 *)o)->unk0x24;
        var_r3 = 0;
        if (var_r0 != 0) {
            var_r3 = 1;
        }
        return var_r3;
    case QB_NOLLIEON:
        if (((Unk_C7387A53 *)o)->unk0x24 == 0) {
            f32 temp_f1 = lbl_802AC700;
            ((Unk_C7387A53 *)o)->unk0x24 = 1;
            fn_8009F054(((Unk_C7387A53 *)o)->unk0xC, QB_SKATERENTERNOLLIE, 0, temp_f1);
        }
        return 1;
    case QB_NOLLIEOFF:
        if (((Unk_C7387A53 *)o)->unk0x24 == 1) {
            f32 temp_f1 = lbl_802AC700;
            ((Unk_C7387A53 *)o)->unk0x24 = 0;
            fn_8009F054(((Unk_C7387A53 *)o)->unk0xC, QB_SKATEREXITNOLLIE, 0, temp_f1);
        }
        return 1;
    case QB_INPRESSURE:
        var_r0 = ((Unk_C7387A53 *)o)->unk0x28;
        var_r3 = 0;
        if (var_r0 != 0) {
            var_r3 = 1;
        }
        return var_r3;
    case 0xA23D710:
        if (((Unk_C7387A53 *)o)->unk0x28 == 0) {
            f32 temp_f1 = lbl_802AC700;
            ((Unk_C7387A53 *)o)->unk0x28 = 1;
            fn_8009F054(((Unk_C7387A53 *)o)->unk0xC, QB_SKATERENTERPRESSURE, 0, temp_f1);
        }
        return 1;
    case QB_PRESSUREOFF:
        if (((Unk_C7387A53 *)o)->unk0x28 == 1) {
            f32 temp_f1 = lbl_802AC700;
            ((Unk_C7387A53 *)o)->unk0x28 = 0;
            fn_8009F054(((Unk_C7387A53 *)o)->unk0xC, QB_SKATEREXITPRESSURE, 0, temp_f1);
        }
        return 1;
    default:
        return 2;
    }
}
