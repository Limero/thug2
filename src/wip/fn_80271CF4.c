// WIP DRAFT (non-matching) — decode notes for hand rebuild (logf reducer).
// family=m2c range=0x80271CF4-0x80272044 size=848B
// IDENTITY: fdlibm-style logf argument reducer: s32 fn(s32 *out2 /*r3*/,
// f32 x /*f1*/). Writes a TWO-FLOAT split through out2 ([0]=hi,[4]=lo) and
// RETURNS the octave k in r3. Body map from want disasm:
//  - |bits| <= 0x3F490FD8 (=pi/4): *out0=x; return 0.  const lbl_803CA8A8.
//  - <= 0x4016CBE3 (~2.36): Cody-Waite +-pi/4 reduction; mantissa-region
//    test (rlwinm r9,r29,0,1,0x1b == 0x3FC90FD0) selects 2-vs-3-term split
//    consts lbl_803CA8B0/B4/B8; k=sign(+1/-1); two stfs through r31.
//  - <= 0x43490F80 (~2^53): fabsf (fn_8027114C), poly fctiwz->n, 0x43300000
//    magic pair at 0x28(r1) (doc-14 dance), int TABLE lookup
//    lwzx lbl_803CBAC8[(n-1)] (.sdata2, size 0xA8) compared vs mantissa
//    mask (rlwinm ,r29,0,1,0x17); two precision-refinement loops re-testing
//    exponent distance >8 / >25 with consts CA8B4/CA8B8 and CA8D0/D4.
//  - else: exponent strip srawi>>23 (-134 scale), builds a 3-FLOAT array at
//    r1+8 via fctiwz-magic loop (pointer walk r10 += 4, cmpw vs r1+0xc),
//    then CALLS fn_8027291C(r1+8, out2, 2) — big poly evaluator (0x884B);
//    cr0 preserved ACROSS that bl via mfcr r30/mtcrf 0x80 (doc-28 shape).
//  - tail: negative-x fixups (fneg both outs, neg k).
// PARKED (not rebuilt): 212 insns; needs the 0x4330 magic dances modeled via
// real rodata2 doubles (lbl_803CA8C8 @-0x79b8 is the subtracted magic),
// the sdata2 tables as sized extern arrays under -msdata=eabi -G256, and
// fn_8027291C prototyped s32(s32,s32,s32)-ish per call site. Same allocator-
// cascade walls as sqrt/tanh/atan2 documented today expected on top.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
static s32 saved_reg_r13;

s32 fn_80271CF4(CStruct *arg0, f32 farg0) {
s32 fs_t;
    f32 sp18;                                       
    f32 sp10;
    s32 spC;
    Unk_59AB5482 sp8;
    f32 *var_r10;
    f32 *var_r9;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f13;
    f32 temp_f13_2;
    f32 temp_f13_3;
    f32 temp_f13_4;
    f32 temp_f13_5;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f8;
    f32 temp_f9;
    f32 temp_f9_2;
    f32 temp_r29;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f11;
    f32 var_f12;
    f32 var_f12_2;
    f32 var_f13;
    f32 var_f1;
    f32 var_f1_2;
    f32 var_f1_3;
    f32 var_f1_4;
    s32 temp_r30;
    s32 temp_r9;
    s32 var_r3;

    sp18 = farg0;
    temp_r29 = sp18;
    temp_r30 = (s32) temp_r29 & QB_UNKNOWN_0x7FFFFFFF;
    if (temp_r30 <= QB_UNKNOWN_0x3F490FD8) {
        var_f0 = *(s32 *)((char *)saved_reg_r13 - 0x79D8);
        var_r3 = 0;
        arg0->unk0x0 = farg0;
        goto block_31;
    }
    if (temp_r30 <= QB_UNKNOWN_0x4016CBE3) {
        if ((s32) temp_r29 > 0) {
            var_f1 = farg0 - *(s32 *)((char *)saved_reg_r13 - 0x79D4);
            if ((s32) ((s32) temp_r29 & QB_UNKNOWN_0x7FFFFFF0) != QB_UNKNOWN_0x3FC90FD0) {
                var_f12 = *(s32 *)((char *)saved_reg_r13 - 0x79D0);
            } else {
                var_f12 = *(s32 *)((char *)saved_reg_r13 - 0x79C8);
                var_f1 -= *(s32 *)((char *)saved_reg_r13 - 0x79CC);
            }
            temp_f13 = var_f1 - var_f12;
            arg0->unk0x0 = temp_f13;
            *((f32 *)&arg0->unk0x4) = (f32) ((var_f1 - temp_f13) - var_f12);
            return 1;
        }
        var_f1_2 = farg0 + *(s32 *)((char *)saved_reg_r13 - 0x79D4);
        if ((s32) ((s32) temp_r29 & QB_UNKNOWN_0x7FFFFFF0) != QB_UNKNOWN_0x3FC90FD0) {
            var_f12_2 = *(s32 *)((char *)saved_reg_r13 - 0x79D0);
        } else {
            var_f12_2 = *(s32 *)((char *)saved_reg_r13 - 0x79C8);
            var_f1_2 += *(s32 *)((char *)saved_reg_r13 - 0x79CC);
        }
        temp_f13_2 = var_f1_2 + var_f12_2;
        arg0->unk0x0 = temp_f13_2;
        *((f32 *)&arg0->unk0x4) = (f32) ((var_f1_2 - temp_f13_2) + var_f12_2);
        return -1;
    }
    if (temp_r30 <= QB_UNKNOWN_0x43490F80) {
        fs_t = fn_8027114C();
        var_r3 = (s32) ((temp_f1 * *(s32 *)((char *)saved_reg_r13 - 0x79C4)) + *(s32 *)((char *)saved_reg_r13 - 0x79C0));
        temp_f1 = fs_t;
        temp_f8 = (f32) (f64) var_r3;
        var_f11 = temp_f1 - (temp_f8 * *(s32 *)((char *)saved_reg_r13 - 0x79D4));
        var_f1_3 = temp_f8 * *(s32 *)((char *)saved_reg_r13 - 0x79D0);
        if ((var_r3 <= 0x1F) && ((s32) ((s32) temp_r29 & QB_UNKNOWN_0x7FFFFF00) != (s32) *((s32 *)saved_reg_r13 - 0x67B8 + ((var_r3 - 1) * 4)))) {
            arg0->unk0x0 = (f32) (var_f11 - var_f1_3);
        } else {
            temp_f0 = var_f11 - var_f1_3;
            temp_r9 = temp_r30 >> 0x17;
            arg0->unk0x0 = temp_f0;
            sp18 = temp_f0;
            if ((s32) (temp_r9 - (u8) ((u32) sp18 >> 0x17U)) > 8) {
                temp_f9 = var_f11;
                temp_f1_2 = temp_f8 * *(s32 *)((char *)saved_reg_r13 - 0x79CC);
                var_f11 -= temp_f1_2;
                var_f1_3 = (temp_f8 * *(s32 *)((char *)saved_reg_r13 - 0x79C8)) - ((temp_f9 - var_f11) - temp_f1_2);
                temp_f13_3 = var_f11 - var_f1_3;
                arg0->unk0x0 = temp_f13_3;
                sp18 = temp_f13_3;
                if ((s32) (temp_r9 - (u8) ((u32) sp18 >> 0x17U)) > 0x19) {
                    temp_f9_2 = var_f11;
                    temp_f1_3 = temp_f8 * *(s32 *)((char *)saved_reg_r13 - 0x79B0);
                    var_f11 -= temp_f1_3;
                    var_f1_3 = (temp_f8 * *(s32 *)((char *)saved_reg_r13 - 0x79AC)) - ((temp_f9_2 - var_f11) - temp_f1_3);
                    arg0->unk0x0 = (f32) (var_f11 - var_f1_3);
                }
            }
        }
        temp_f13_4 = arg0->unk0x0;
        var_f0_2 = (var_f11 - temp_f13_4) - var_f1_3;
        *((f32 *)&arg0->unk0x4) = var_f0_2;
        if ((s32) temp_r29 < 0) {
            var_f13 = -temp_f13_4;
            var_r3 = -var_r3;
            goto block_30;
        }
    } else {
        if (temp_r30 > QB_UNKNOWN_0x7F7FFFFF) {
            var_f0 = farg0 - farg0;
            var_r3 = 0;
            arg0->unk0x0 = var_f0;
            goto block_31;
        }
        sp18 = temp_r30 - (((temp_r30 >> 0x17) - 0x86) << 0x17);
        var_f1_4 = (f32) sp18;
        0;
        var_r10 = &sp8;
        do {
            temp_f0_2 = (f32) (f64) (s32) var_f1_4;
            *((s32 *)var_r10) = temp_f0_2;
            var_r10 += 4;
            var_f1_4 = (var_f1_4 - temp_f0_2) * *(s32 *)((char *)saved_reg_r13 - 0x79A8);
        } while (var_r10 <= &spC);
        sp10 = var_f1_4;
        temp_f13_5 = *(s32 *)((char *)saved_reg_r13 - 0x79D8);
        if (sp8.unk0x8 == temp_f13_5) {
            var_r9 = &sp8 + 8;
            do {
                temp_f0_3 = *(s32 *)((char *)var_r9 - 0x4);
                var_r9 -= 4;
            } while (temp_f0_3 == temp_f13_5);
        }
        var_r3 = fn_8027291C(&sp8, arg0, 2, saved_reg_r13 - 0x6AD0, *(s32 *)((char *)saved_reg_r13 - 0x79B8));
        0;
        if (0) {
            var_r3 = -var_r3;
            var_f0_2 = *((f32 *)&arg0->unk0x4);
            var_f13 = -arg0->unk0x0;
block_30:
            var_f0 = -var_f0_2;
            arg0->unk0x0 = var_f13;
block_31:
            *((f32 *)&arg0->unk0x4) = var_f0;
        }
    }
    return var_r3;
}
