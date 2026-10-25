// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EE55C-0x800EE7B0 (596B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

typedef struct Unk_EE55C_tire {
    char pad0x0[0x4];
    s32 unk0x4;
    char pad0x8[0x98];
    f32 unk0xA0;
    char pad0xA4[0x38];
    f32 unk0xDC;
} Unk_EE55C_tire;

typedef struct Unk_EE55C_owner {
    char pad0x0[0x2F0];
    void *unk0x2F0;
    char pad0x2F4[0x38];
    s32 unk0x32C;
    s32 unk0x330;
} Unk_EE55C_owner;

typedef struct Unk_EE55C {
    char pad0x0[0xC];
    s32 unk0xC;
    char pad0x10[0x18];
    s32 unk0x28;
    char pad0x2C[0x8];
    s32 unk0x34;
    char pad0x38[0x78];
    f32 unk0xB0;
    char pad0xB4[0x4];
    struct Unk_EE55C_owner *unk0xB8;
} Unk_EE55C;

typedef struct Unk_EE55C_vec {
    f32 unk0x0[5];
    s32 unk0x14;
    char pad0x18[0x10];
} Unk_EE55C_vec;

extern f32 lbl_8029AEB8;
extern f32 lbl_8029AEBC;
extern s32 lbl_80302C34;

f32 fn_800EEAE0(Unk_EE55C *, s32);
f32 fn_800EEB10(Unk_EE55C *, s32);
f32 fn_800144C8(void);
void fn_801195DC(Unk_EE55C_vec *);
void fn_80119640(Unk_EE55C_vec *, s32);
void fn_80119668(Unk_EE55C_vec *, f32);
s32 fn_8011970C(Unk_EE55C_vec *, f32);
s32 fn_8011A56C(s32, s32, Unk_EE55C_vec *, s32, s32, s32, f32);
void fn_8011AACC(s32, s32, Unk_EE55C_vec *, f32);
void fn_8011A6A8(s32, s32);
void fn_8011AA4C(s32, s32);
void fn_8011ADD4(s32, Unk_EE55C_vec *, s32, s32, s32, s32);

void fn_800EE55C(Unk_EE55C *arg0) {
    Unk_EE55C_vec sp8;
    Unk_EE55C_owner *temp_r11;
    Unk_EE55C_tire *var_r11;
    s32 temp_base;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f1;
    f32 temp_f11;
    f32 temp_f12;
    f32 temp_f13;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 temp_f31_3;
    f32 temp_f31_4;
    f32 var_f13;
    f32 var_f13_2;
    f32 var_f30;
    f32 var_f30_2;
    s32 temp_r29;
    s32 temp_c58;
    s32 temp_r9;
    s32 var_ctr;

    temp_r11 = arg0->unk0xB8;
    temp_base = (s32)temp_r11->unk0x2F0;
    var_f30 = lbl_8029AEB8;
    if ((temp_r11->unk0x32C != 0) || (temp_r11->unk0x330 != 0)) {
        var_r11 = (Unk_EE55C_tire *)(temp_base + 0x5A0);
        var_ctr = 4;
        do {
            temp_r9 = var_r11->unk0x4;
            if (((u32)(temp_r9 - 4) <= 1U) || (((u32)(temp_r9 - 6) <= 1U) && (var_r11->unk0xA0 > var_r11->unk0xDC))) {
                temp_f0 = var_r11->unk0xA0;
                if (var_f30 > temp_f0) {
                    var_f13 = var_f30;
                } else {
                    var_f13 = temp_f0;
                }
                var_f30 = var_f13;
            }
            var_r11 = (Unk_EE55C_tire *)((s32)var_r11 - 0x1E0);
            var_ctr -= 1;
        } while (var_ctr != 0);
    }
    temp_f31 = fn_800EEB10(arg0, QB_TIRE_SLIP_LERP_RATE);
    temp_f31 = temp_f31 * fn_800144C8();
    temp_f13 = arg0->unk0xB0;
    arg0->unk0xB0 = (var_f30 - temp_f13) * temp_f31 + temp_f13;
    temp_f0_2 = arg0->unk0xB0 / fn_800EEAE0(arg0, QB_FULLTIRESLIPVELOCITY);
    temp_f12 = lbl_8029AEBC;
    temp_f11 = lbl_8029AEB8;
    if (temp_f0_2 > temp_f12) {
        var_f13_2 = temp_f12;
    } else {
        var_f13_2 = temp_f0_2;
    }
    if (var_f13_2 < temp_f11) {
        var_f30_2 = temp_f11;
    } else {
        var_f30_2 = var_f13_2;
    }
    fn_801195DC(&sp8);
    temp_c58 = arg0->unk0xC + 0x58;
    temp_r29 = lbl_80302C34;
    fn_8011AA4C(temp_r29, arg0->unk0x34);
    fn_8011ADD4(temp_r29, &sp8, temp_c58, 0, 0, 0);
    temp_f31_2 = fn_800EEAE0(arg0, QB_MINTIREVOL);
    fn_80119668(&sp8, ((fn_800EEAE0(arg0, QB_MAXTIREVOL) - temp_f31_2) * var_f30_2) + temp_f31_2);
    temp_f31_3 = fn_800EEAE0(arg0, QB_MINTIREPITCH);
    temp_f1 = fn_800EEAE0(arg0, QB_MAXTIREPITCH) - temp_f31_3;
    temp_f31_4 = (temp_f1 * var_f30_2) + temp_f31_3;
    if (fn_8011970C(&sp8, temp_f1) == 0) {
        if (arg0->unk0x28 == 0) {
            arg0->unk0x28 = fn_8011A56C(lbl_80302C34, arg0->unk0x34, &sp8, 0, 0, 0, temp_f31_4);
        } else {
            fn_8011AACC(lbl_80302C34, arg0->unk0x28, &sp8, temp_f31_4);
        }
    } else if (arg0->unk0x28 != 0) {
        fn_8011A6A8(lbl_80302C34, arg0->unk0x28);
        arg0->unk0x28 = 0;
    }
    fn_80119640(&sp8, 2);
}
