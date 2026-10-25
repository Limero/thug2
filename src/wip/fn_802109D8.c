// WIP DRAFT — decode-documented park (groupB PS zone, 2026-08-25)
// PARKED (m2c husk retained; partial analysis done).
// 824B, frame 0xF0, saves f28-f31 + r22-r31 — TEN callee-saved GPRs
// (big-function allocator wall class per §6y signature).
// Structure: entry guard *(arg0+0x1978) vs const@lbl_802AF5BC(-0xa44):
//   != path clamps 0x1978 toward 0x88-field and returns.
// == path: r9=arg0+0x1968, r11=arg0+0x1970 walkers; ps dot products;
//   derived ptrs r24/r23/r28(+0x1960)/r27(+0x1958)/r26/r25/r22(&sp8)/r30.
//   Hash chains GetStructure(0x6775E538,0)->GetFloat(chained,
//   0x896B8888[-0x7694|8888], &sp48, 1) x3 (+ 0xF008443B[-0xf7b|443b]).
//   fn_80107B20(&sp8,1,0) probe; float min/max ladder w/ cror+bns
//   NaN-guard compares; PS block: ps_sub/add pairs, ps_merge00, sum0,
//   muls0-normalize + vsel-labeled words (all standard emittable,
//   hand-decoded: 0x118c0372=muls0, 0x1000627a=add etc.).
//   fn_8009F010(*(arg0+0xC), 0x6E84ACF3, 0) before tail cleanup.
// Walls: 10-GPR saved span resists reconstruction (class);
// pointer web r22-r28 needs full-web pins that historically collapse.
// family=m2c range=0x802109D8-0x80210D10 size=824B
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AF5BC[];
static s32 sp58;
static s32 sp60;
static s32 sp68;
static s32 sp70;

void fn_802109D8(Unk_519C2007 *arg0) {
    f32 sp80;
    f32 sp78;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    Unk_59AB5482 sp8;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f11;
    f32 temp_f13;
    f32 temp_f28;
    f32 temp_f30;
    f32 var_f13;
    f32 var_f29;
    f32 var_f30;
    f32 var_f31;
    s32 temp_r0;
    s32 var_cr0_lt;

    temp_f28 = *(f32 *)0x802AF5BC;
    temp_f13 = arg0->unk0x1978;
    if (temp_f13 != temp_f28) {
        temp_f0 = temp_f13 - arg0->unk0x88;
        var_f13 = temp_f0;
        if (temp_f0 < temp_f28) {
            var_f13 = temp_f28;
        }
        arg0->unk0x1978 = var_f13;
        return;
    }
    0;
    temp_f11 = arg0->unk0x1958;
    0;
    *((f32 *)&sp8) = -arg0->unk0x1960;
    0;
    sp8.unk0x8 = temp_f11;
    temp_f30 = arg0->unk0xA0;
    ((Unk_E266FB50 *)&sp8)->unk0xC = (f32) *(f32 *)0x802AF5C0;
    sp8.unk0x4 = temp_f28;
    GetStructure(QB_WALK_PARAMETERS, 0, 0x802B0000, temp_f11, 0);
    GetFloat(QB_JUMP_ADJUST_SPEED, &sp48, 1);
    0;
    0;
    0;
    GetStructure(QB_WALK_PARAMETERS, 0);
    GetFloat(QB_JUMP_ACCEL_FACTOR, &sp4C, 1);
    var_f29 = (((sp48 * temp_f30 * sp58) - sp60) * (sp4C * arg0->unk0x88)) + sp60;
    GetStructure(QB_WALK_PARAMETERS, 0);
    GetFloat(QB_JUMP_ADJUST_SPEED, &sp50, 1);
    0;
    temp_r0 = arg0->unk0x1A3C;
    var_cr0_lt = temp_r0 < 0;
    0;
    0;
    var_f30 = sp50 * temp_f30 * sp68;
    var_f31 = sp70;
    if (temp_r0 == 0) {
        temp_f0_2 = arg0->unk0xA0;
        var_cr0_lt = temp_f0_2 < temp_f28;
        if (temp_f0_2 == temp_f28) {
            var_f31 = temp_f28;
            var_f30 = var_f31;
        }
    } else {
        var_f29 = temp_f28;
    }
    0;
    0;
    if ((0 == 0) || (var_cr0_lt = var_f31 < var_f30, ((var_f31 > var_f30) == 0))) {
        if ((var_cr0_lt != 0) && (var_f31 > *(s32 *)lbl_802AF5BC)) {
            var_f30 += var_f31;
        }
        GetStructure(QB_WALK_PARAMETERS, 0);
        GetFloat(QB_JUMP_ACCEL_FACTOR, &sp54, 1);
        var_f31 += (var_f30 - var_f31) * (sp54 * arg0->unk0x88);
    }
    sp78 = var_f31;
    sp80 = var_f29;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
}
