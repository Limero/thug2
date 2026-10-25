// WIP DRAFT (non-matching) — hand reconstruction decoded from the retail WANT
// (0x800EE0B8-0x800EE55C, 1188B).  Per-vehicle engine-sound update
// (RPM -> volume/pitch), the sibling of the already-matched fn_800EE55C
// (next function, same Script sound-API idiom).  The previous m2c body scored
// ~2% because it manufactured int<->double conversions that the WANT does not
// contain: this engine code is pure single-precision (fmuls/fmadds/fdivs/
// fsubs).  Rebuilt from the disassembly:
//   * the 4-iteration `li r0,4 / mtctr / bdnz` running-min scan over the
//     0x1E0-stride tire entries (base = owner->0x2F0 + 0x5A0) of
//     fabs(entry->0x8) * entry->0xC8, gated on entry->0xBC != 0;
//   * the effective-speed gate (owner->0x328 / 0x334 / 0x32C) and the
//     lerp-then-clamp toward the target (min/max, not the m2c shape);
//   * the gear-ratio interpolation over the 16-byte {a,b,c,d} pair array at
//     self+0x3C (idx = self->0xA0), then the RPM lerp and the 0..1 clamp;
//   * the volume/pitch blend and the fn_8011A56C / fn_8011AACC voice calls,
//     whose trailing f32 (pitch) argument is passed in f1 (that is why the
//     WANT computes the pitch but never moves it again);
//   * the ONLY int->float in the function is (Tmr - self->0xA8) (the
//     0x4330/lfd 2^52 magic) — written here as a plain `(f32)` conversion.
// No inline asm; types are declared rather than cast.
//
// family=m2c range=0x800EE0B8-0x800EE55C size=1188B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"

typedef struct EE0B8_tire {
    char pad0x0[0x8];
    f32 unk0x8;
    char pad0xC[0xB0];
    s32 unk0xBC;
    char pad0xC0[0x8];
    f32 unk0xC8;
} EE0B8_tire;

typedef struct EE0B8_owner {
    char pad0x0[0x120];
    s32 unk0x120;
    char pad0x124[0x1CC];
    void *unk0x2F0;
    char pad0x2F4[0x34];
    s32 unk0x328;
    s32 unk0x32C;
    s32 unk0x330;
    s32 unk0x334;
    char pad0x338[0x1000];
    f32 unk0x1338;
} EE0B8_owner;

typedef struct EE0B8_pair {
    f32 a;
    f32 b;
    f32 c;
    f32 d;
} EE0B8_pair;

typedef struct EE0B8 {
    char pad0x0[0xC];
    s32 unk0xC;
    char pad0x10[0x14];
    s32 unk0x24;
    char pad0x28[0x8];
    s32 unk0x30;
    char pad0x34[0x4];
    s32 unk0x38;
    EE0B8_pair pa[6];
    f32 unk0x9C;
    s32 unk0xA0;
    f32 unk0xA4;
    s32 unk0xA8;
    char pad0xAC[0xC];
    EE0B8_owner *unk0xB8;
} EE0B8;

typedef struct EE0B8_vec {
    f32 unk0x0[5];
    s32 unk0x14;
    char pad0x18[0x10];
} EE0B8_vec;

extern f32 lbl_8029AE98;
extern f32 lbl_8029AE9C;
extern f32 lbl_8029AEA0;
extern f32 lbl_8029AEA4;
extern f32 lbl_8029AEA8;
extern f32 lbl_8029AEAC;
extern s32 lbl_80302C34;
extern s32 lbl_80303150;

f32 fn_800144C8(void);
f32 fn_800EEAE0(EE0B8 *, s32);
f32 fn_800EEB10(EE0B8 *, s32);
s32 Tmr_GetTime(void);
void fn_801195DC(EE0B8_vec *);
void fn_80119640(EE0B8_vec *, s32);
void fn_80119668(EE0B8_vec *, f32);
void fn_8011AA4C(s32, s32);
void fn_8011ADD4(s32, EE0B8_vec *, s32, s32, s32, s32);
s32 fn_8011A56C(s32, s32, EE0B8_vec *, s32, s32, s32, f32);
void fn_8011AACC(s32, s32, EE0B8_vec *, f32);

void fn_800EE0B8(EE0B8 *arg0) {
    EE0B8_vec sp8;
    EE0B8_owner *temp_r11;
    EE0B8_pair *var_r28;
    EE0B8_tire *var_r11;
    s32 temp_base;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f11;
    f32 temp_f13;
    f32 temp_f13_2;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 temp_f31_3;
    f32 temp_f31_4;
    f32 temp_f31_5;
    f32 var_f11;
    f32 var_f12;
    f32 var_f13;
    f32 var_f28;
    f32 var_f30;
    s32 temp_r0;
    s32 temp_r9;
    s32 temp_r11_2;
    s32 temp_r29;
    s32 temp_r30;
    s32 var_ctr;
    s32 var_sel;

    temp_f29 = fn_800144C8();
    temp_r11 = arg0->unk0xB8;
    temp_base = (s32)temp_r11->unk0x2F0;
    var_f11 = lbl_8029AE98;
    var_r11 = (EE0B8_tire *)(temp_base + 0x5A0);
    var_ctr = 4;
    do {
        temp_r9 = var_r11->unk0xBC;
        if (temp_r9 != 0) {
            temp_f0 = __builtin_fabsf(var_r11->unk0x8) * var_r11->unk0xC8;
            if (var_f11 < temp_f0) {
                var_f13 = var_f11;
            } else {
                var_f13 = temp_f0;
            }
            var_f11 = var_f13;
        }
        var_r11 = (EE0B8_tire *)((s32)var_r11 - 0x1E0);
        var_ctr -= 1;
    } while (var_ctr != 0);

    temp_f11 = ((var_f11 / lbl_8029AE9C) / lbl_8029AEA0) * lbl_8029AEA4;
    temp_f31 = temp_f11 * lbl_8029AEA4;
    var_sel = 0;
    temp_r11 = arg0->unk0xB8;
    if ((temp_r11->unk0x328 != 0) || (temp_r11->unk0x334 != 0)) {
        if (temp_r11->unk0x32C == 0) {
            var_sel = 1;
        }
    }
    if (var_sel == 0) {
        temp_f31 = temp_f31 * fn_800EEB10(arg0, QB_IDLE_ENGINE_EFFECTIVE_SPEED_FACTOR);
    }

    temp_f0 = ((arg0->unk0x9C - temp_f31) *
               (fn_800EEB10(arg0, QB_EFFECTIVE_SPEED_LERP_RATE) * temp_f29)) +
              temp_f31;
    arg0->unk0x9C = temp_f0;
    if (temp_f0 < temp_f31) {
        temp_f0_3 = arg0->unk0x9C;
        temp_f1 = (fn_800EEB10(arg0, QB_EFFECTIVE_SPEED_ADJUST_UP_RATE) * temp_f29) +
                  temp_f0_3;
        if (temp_f1 <= temp_f0_3) {
            var_f13 = temp_f1;
        } else {
            var_f13 = temp_f0_3;
        }
    } else {
        temp_f0_4 = arg0->unk0x9C;
        temp_f1_2 = temp_f0_4 -
                    (fn_800EEB10(arg0, QB_EFFECTIVE_SPEED_ADJUST_DOWN_RATE) * temp_f29);
        if (temp_f1_2 >= temp_f0_4) {
            var_f13 = temp_f1_2;
        } else {
            var_f13 = temp_f0_4;
        }
    }
    arg0->unk0x9C = var_f13;

    temp_r30 = (s32)arg0->unk0xB8;
    temp_r29 = ((EE0B8_owner *)temp_r30)->unk0x120;
    if (temp_r29 != 0) {
        var_r28 = arg0->pa;
        temp_r11_2 = arg0->unk0xA0;
        if ((temp_r11_2 < arg0->unk0x38 - 1) &&
            (arg0->unk0x9C > var_r28[temp_r11_2].a)) {
            temp_r0 = temp_r11_2 + 1;
            goto set_index;
        }
        temp_r11_2 = arg0->unk0xA0;
        if ((temp_r11_2 > 0) && (arg0->unk0x9C < var_r28[temp_r11_2].b)) {
            temp_r0 = temp_r11_2 - 1;
set_index:
            arg0->unk0xA0 = temp_r0;
            arg0->unk0xA8 = lbl_80303150 + Tmr_GetTime();
        }
    } else {
        var_r28 = arg0->pa;
        if (((EE0B8_owner *)temp_r30)->unk0x1338 >
            fn_800EEB10(arg0, QB_ENGINE_AIRBORNE_DELAY)) {
            arg0->unk0xA0 = temp_r29;
        }
    }

    temp_f30 = fn_800EEB10(arg0, QB_GEAR_SHIFT_MIN_VOL_FACTOR);
    temp_r30 = arg0->unk0xA8;
    temp_f31 = (f32)((lbl_80303150 + Tmr_GetTime()) - temp_r30);
    var_f12 = lbl_8029AEA8;
    temp_f13 = lbl_8029AEAC;
    temp_f0_5 = ((temp_f13 - temp_f30) *
                 ((temp_f31 - var_f12) /
                  (fn_800EEB10(arg0, QB_GEAR_SHIFT_VOL_ADJUSTMENT_DURATION) - var_f12))) +
                temp_f30;
    if (temp_f0_5 > temp_f13) {
        var_f28 = temp_f13;
    } else {
        var_f28 = temp_f0_5;
    }

    temp_r0 = arg0->unk0xA0;
    if (temp_r0 != 0) {
        var_f12 = var_r28[temp_r0 - 1].a;
    }
    temp_f0_2 = (var_r28[temp_r0].d - var_r28[temp_r0].c) *
                ((arg0->unk0x9C - var_f12) / (var_r28[temp_r0].a - var_f12)) +
                var_r28[temp_r0].c;
    temp_f0_3 = arg0->unk0xA4;
    temp_f1 = fn_800EEB10(arg0, QB_ENGINE_RPM_LERP_RATE) * temp_f29;
    arg0->unk0xA4 = (temp_f0_2 - temp_f0_3) * temp_f1 + temp_f0_3;

    temp_f31_2 = fn_800EEAE0(arg0, QB_MINENGINERPM);
    temp_f31_3 = (arg0->unk0xA4 - temp_f31_2) /
                 (fn_800EEAE0(arg0, QB_MAXENGINERPM) - temp_f31_2);
    temp_f0_6 = temp_f31_3 + lbl_8029AEA8;
    temp_f13_2 = temp_f0_6;
    if (temp_f0_6 > lbl_8029AEAC) {
        temp_f13_2 = lbl_8029AEAC;
    }
    var_f30 = temp_f13_2;
    if (temp_f13_2 < lbl_8029AEA8) {
        var_f30 = lbl_8029AEA8;
    }

    fn_801195DC(&sp8);
    temp_r30 = arg0->unk0xC + 0x58;
    temp_r29 = lbl_80302C34;
    fn_8011AA4C(temp_r29, arg0->unk0x30);
    fn_8011ADD4(temp_r29, &sp8, temp_r30, 0, 0, 0);
    temp_f31_4 = fn_800EEAE0(arg0, QB_MINENGINEVOL);
    fn_80119668(&sp8,
                var_f28 * (((fn_800EEAE0(arg0, QB_MAXENGINEVOL) - temp_f31_4) * var_f30) +
                           temp_f31_4));
    temp_f31_5 = fn_800EEAE0(arg0, QB_MINENGINEPITCH);
    temp_f1_3 = (fn_800EEAE0(arg0, QB_MAXENGINEPITCH) - temp_f31_5) * var_f30 + temp_f31_5;
    if (arg0->unk0x24 == 0) {
        arg0->unk0x24 = fn_8011A56C(lbl_80302C34, arg0->unk0x30, &sp8, 0, 0, 0, temp_f1_3);
    } else {
        fn_8011AACC(lbl_80302C34, arg0->unk0x24, &sp8, temp_f1_3);
    }
    fn_80119640(&sp8, 2);
}

// NOTE: hand reconstruction from the WANT (no compiler here, so the masked
// score is unmeasured).  Modelled on the byte-identical sibling fn_800EE55C:
// same owner/vec shapes, same sound-API prototypes, and the trailing f32
// pitch argument that fn_8011A56C / fn_8011AACC take in f1 (confirmed by that
// matched sibling and by src/fn_8011AACC.c's
// `s32 fn_8011AACC(s32, s32, void *, f32)`).
//
// PARKED 2026-10-06: best effort, unverified.  Residual risk is regalloc /
// scheduling only — the semantics now follow the WANT: the loop runs an
// unconditional 4 iterations (no owner->0x32C/0x330 gate, unlike the
// sibling), the effective-speed gate is the three-field 0x328/0x334/0x32C
// expression, and the index/timestamp block shares one store block reached
// from two conditions (goto set_index).  Two details to re-check first when a
// compiler is available: (a) whether the up/down clamp really is min/max this
// way round (0x800EE1FC `ble` keeps f1 when f1 <= v, else f0; 0x800EE228
// `bge` keeps f1 when f1 >= v, else f0), and (b) whether the FPR frame (0x88,
// stfd f28..f31) needs the issue-01 `volatile double` dummy — the sweep's
// dual-test will decide.
