// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B61B0-0x801B62EC (316B). Byte-identical.
#include "types.h"
#include "qb_constants.h"

extern f32 lbl_802AC168;
extern f32 lbl_802AC16C;
extern f32 lbl_802AC170;
extern f64 lbl_802AC178;
extern f32 lbl_802AC180;
extern f32 lbl_802AC184;

f32 cosf(f32);
f32 fn_8012570C(s32, s32);

f32 fn_801B61B0(s32 arg0) {
    struct { char pad[0x30]; union { u32 w[2]; f64 d; } cvt; } fr;
    f32 *var_r31;
    f32 temp_f31;
    f32 temp_f12;
    f32 temp_f13;
    f32 temp_f1;
    f32 angle_base;
    f32 one;
    f32 acc;
    register f32 minus_one __asm__("fr30");
    f64 magic;
    s32 i;

    angle_base = lbl_802AC16C * lbl_802AC170;
    acc = lbl_802AC168;
    magic = lbl_802AC178;
    one = lbl_802AC180;
    i = 0;
    var_r31 = (f32 *)((char *)arg0 + 0x38);
    do {
        *(volatile u32 *)&fr.cvt.w[1] = (u32)i ^ 0x80000000;
        temp_f12 = var_r31[4];
        *(volatile u32 *)&fr.cvt.w[0] = QB_INT_TO_DOUBLE_BIAS;
        temp_f13 = var_r31[0];
        __asm__ volatile("" : "+f"(temp_f12), "+f"(temp_f13));
        temp_f31 = temp_f12 + temp_f13;
        temp_f1 = angle_base * (f32)(fr.cvt.d - magic);
        __asm__ volatile("" : "+f"(temp_f1));
        if (temp_f31 > one) {
            temp_f31 = one;
        }
        minus_one = lbl_802AC184;
        if (temp_f31 < minus_one) {
            temp_f31 = minus_one;
        }
        acc += cosf(temp_f1) * temp_f31;
        if (acc >= one) {
            return one;
        }
        if (acc <= minus_one) {
            return minus_one;
        }
        i += 1;
        var_r31 += 1;
    } while (i <= 3);
    if (__builtin_fabsf(acc) < fn_8012570C(QB_PED_MIN_BIAS, 1)) {
        acc = lbl_802AC168;
    }
    return acc;
}
