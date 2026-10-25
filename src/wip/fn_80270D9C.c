// PARKED 2026-10-03 — 2.9% (528 B).  This is libm `atanf`; the m2c draft
// guesses every constant through `saved_reg_r13 - 0x6E00`-style offsets that
// were never resolved, so essentially the whole rodata pool is wrong.  Not a
// codegen problem — the constants must come from the real pool first.
//
// family=m2c range=0x80270D9C-0x80270FAC size=528B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 2.9% ([2]rev->2.9%).
#include "types.h"
#include "qb_constants.h"
static s32 saved_reg_r13;

f32 atanf(f32 farg0) {
    f32 sp8;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f12;
    f32 temp_f1;
    f32 temp_f5;
    f32 temp_f6;
    f32 var_f1;
    f32 var_f5;
    s32 temp_r0;
    s32 temp_r31;
    s32 var_r0;

    var_f5 = farg0;
    sp8 = var_f5;
    temp_r31 = (s32) sp8 & QB_UNKNOWN_0x7FFFFFFF;
    if (temp_r31 > QB_UNKNOWN_0x507FFFFF) {
        if (temp_r31 > QB_UNKNOWN_0x7F800000) {
            return 2.0f * var_f5;
        }
        if ((s32) sp8 > 0) {
            return *(s32 *)((char *)saved_reg_r13 - 0x6E00) + *(s32 *)((char *)saved_reg_r13 - 0x6DF0);
        }
        return -*(s32 *)((char *)saved_reg_r13 - 0x6E00) - *(s32 *)((char *)saved_reg_r13 - 0x6DF0);
    }
    if (temp_r31 <= QB_UNKNOWN_0x3EDFFFFF) {
        if ((temp_r31 <= QB_UNKNOWN_0x30FFFFFF) && ((var_f5 + *(s32 *)((char *)saved_reg_r13 - 0x7B58)) > *(s32 *)((char *)saved_reg_r13 - 0x7B54))) {
            return var_f5;
        }
        var_r0 = -1;
        goto block_18;
    }
    temp_f5 = fn_8027114C(var_f5);
    if (temp_r31 <= QB_UNKNOWN_0x3F97FFFF) {
        if (temp_r31 <= QB_UNKNOWN_0x3F2FFFFF) {
            var_r0 = 0;
            var_f5 = ((2.0f * temp_f5) - *(s32 *)((char *)saved_reg_r13 - 0x7B54)) / (temp_f5 + *(s32 *)((char *)saved_reg_r13 - 0x7B50));
        } else {
            var_f5 = (temp_f5 - temp_f0_2) / (temp_f5 + temp_f0_2);
            var_r0 = 1;
            temp_f0_2 = *(s32 *)((char *)saved_reg_r13 - 0x7B54);
        }
    } else if (temp_r31 <= QB_UNKNOWN_0x401BFFFF) {
        temp_f0_3 = *(s32 *)((char *)saved_reg_r13 - 0x7B4C);
        var_r0 = 2;
        var_f5 = (temp_f5 - temp_f0_3) / ((temp_f5 * temp_f0_3) + *(s32 *)((char *)saved_reg_r13 - 0x7B54));
    } else {
        var_r0 = 3;
        var_f5 = *(s32 *)((char *)saved_reg_r13 - 0x7B48) / temp_f5;
    }
block_18:
    temp_f6 = var_f5 * var_f5;
    temp_f12 = temp_f6 * temp_f6;
    temp_f1 = temp_f6 * ((temp_f12 * ((temp_f12 * ((temp_f12 * ((temp_f12 * ((temp_f12 * *(s32 *)((char *)saved_reg_r13 - 0x6DC4)) + *(s32 *)((char *)saved_reg_r13 - 0x6DCC))) + *(s32 *)((char *)saved_reg_r13 - 0x6DD4))) + *(s32 *)((char *)saved_reg_r13 - 0x6DDC))) + *(s32 *)((char *)saved_reg_r13 - 0x6DE4))) + *(s32 *)((char *)saved_reg_r13 - 0x6DEC));
    temp_f0 = temp_f12 * ((temp_f12 * ((temp_f12 * ((temp_f12 * ((temp_f12 * *(s32 *)((char *)saved_reg_r13 - 0x6DC8)) + *(s32 *)((char *)saved_reg_r13 - 0x6DD0))) + *(s32 *)((char *)saved_reg_r13 - 0x6DD8))) + *(s32 *)((char *)saved_reg_r13 - 0x6DE0))) + *(s32 *)((char *)saved_reg_r13 - 0x6DE8));
    if (var_r0 < 0) {
        return var_f5 - (var_f5 * (temp_f1 + temp_f0));
    }
    temp_r0 = var_r0 * 4;
    var_f1 = *((s32 *)saved_reg_r13 - 0x6E0C + temp_r0) - (((var_f5 * (temp_f1 + temp_f0)) - *((s32 *)saved_reg_r13 - 0x6DFC + temp_r0)) - var_f5);
    if ((s32) sp8 < 0) {
        var_f1 = -var_f1;
    }
    return var_f1;
}
