// PARKED 2026-10-06: the worker reconstruction measured
// WORSE than this body and was reverted — worker fdlibm e_fmod rewrite scored 0.9% vs 12.5%.
// This is the current best-scoring body; kept INERT (not promoted).
// WIP DRAFT (non-matching) — fdlibm __ieee754_fmod(x,y) hand-rebuild attempt
// family=m2c range=0x8026E750-0x8026EAAC size=860B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// BEST: 187/215 diffs (13.0%) with floor-entry + 1 dummy vs 190 (11.6%) baseline
// 2026-09-02: tried volatile dummy 0/1/2, schedule flags, bit-pun via *(s32*)&sp8 (worse), union extraction, manual hand-rebuild (worse 212)
// Floor entry: inline asm fmr+stfd+lwz for hx/lx/hy/ly with hi/lo inline, pin x->fr4 not needed (integer)
// Remaining wall is doc44 entry-staging / hot-value-homing allocator wall (see docs/parkings/44)
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
f64 fn_8026E750(f64 farg0, f64 farg1) {
    volatile double _dummy;
    Unk_59AB5482 sp8;
    f64 temp_f1;
    s32 temp_cr0_eq;
    s32 temp_r11;
    s32 temp_r11_2;
    s32 temp_r11_3;
    s32 temp_r11_4;
    s32 temp_r3;
    s32 temp_r5;
    s32 temp_r8;
    s32 var_cr0_lt;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r0_4;
    s32 var_r10;
    s32 var_r11;
    s32 var_r4;
    s32 var_r5;
    s32 var_r6;
    s32 var_r7_2;
    s32 var_r8;
    s32 var_r8_2;
    s32 var_r9;
    s32 var_r9_2;
    u32 temp_r10;
    u32 var_r0;
    u32 var_r7;
    s32 hx;
    s32 hy;
    s32 lx_;
    s32 ly_;
    {
        s32 hi;
        s32 lo;
        __asm__ volatile("fmr 0, %2\n\tstfd 0, 8(1)\n\tlwz %0, 8(1)\n\tlwz %1, 0xc(1)" : "=r"(hi), "=r"(lo) : "f"(farg0) : "fr0", "memory");
        hx = hi; lx_ = lo;
        __asm__ volatile("fmr 0, %2\n\tstfd 0, 8(1)\n\tlwz %0, 8(1)\n\tlwz %1, 0xc(1)" : "=r"(hi), "=r"(lo) : "f"(farg1) : "fr0", "memory");
        hy = hi; ly_ = lo;
    }
    temp_r11 = hx;
    var_r7 = lx_;
    temp_r5 = hy & QB_UNKNOWN_0x7FFFFFFF;
    var_r6 = ly_;
    temp_r3 = hx & 0x80000000;
    temp_r8 = hx & QB_UNKNOWN_0x7FFFFFFF;
    if (((temp_r5 | var_r6) == 0) || (temp_r8 > QB_UNKNOWN_0x7FEFFFFF) || ((u32) (temp_r5 | ((u32) (var_r6 | -var_r6) >> 0x1FU)) > QB_UNKNOWN_0x7FF00000)) {
        temp_f1 = farg0 * farg1;
        return temp_f1 / temp_f1;
    }
    if (temp_r8 <= temp_r5) {
        if ((temp_r8 >= temp_r5) && ((u32)var_r7 >= (u32) var_r6)) {
            if ((s32) var_r7 != (s32)var_r6) {
                goto block_8;
            }
            goto block_58;
        }
        return farg0;
    }
block_8:
    if (temp_r8 <= 0xFFFFF) {
        if (temp_r8 == 0) {
            var_r10 = -0x413;
            var_r0 = var_r7;
            if ((s32) var_r7 > 0) {
                do {
                    var_r10 -= 1;
                    var_r0 *= 2;
                } while ((s32)var_r0 > 0);
            }
        } else {
            var_r10 = -0x3FE;
            var_r0_2 = temp_r8 << 0xB;
            if (var_r0_2 > 0) {
                do {
                    var_r10 -= 1;
                    var_r0_2 *= 2;
                } while (var_r0_2 > 0);
            }
        }
    } else {
        var_r10 = (temp_r8 >> 0x14) - 0x3FF;
    }
    if (temp_r5 <= 0xFFFFF) {
        if (temp_r5 == 0) {
            var_r4 = -0x413;
            var_r0_3 = var_r6;
            if ((s32)var_r6 > 0) {
                do {
                    var_r4 -= 1;
                    var_r0_3 *= 2;
                } while ((s32)var_r0_3 > 0);
            }
        } else {
            var_r4 = -0x3FE;
            var_r0_4 = temp_r5 << 0xB;
            if (var_r0_4 > 0) {
                do {
                    var_r4 -= 1;
                    var_r0_4 *= 2;
                } while (var_r0_4 > 0);
            }
        }
    } else {
        var_r4 = (temp_r5 >> 0x14) - 0x3FF;
    }
    var_cr0_lt = (var_r10 < -0x3FE);
    if (var_cr0_lt == 0) {
        var_r8 = (temp_r8 & 0xFFFFF) | 0x100000;
    } else {
        temp_r11_2 = -0x3FE - var_r10;
        if (temp_r11_2 <= 0x1F) {
            var_r8 = (temp_r8 << temp_r11_2) | (var_r7 >> (0x20 - temp_r11_2));
            var_r7 <<= temp_r11_2;
        } else {
            var_r8 = var_r7 << (temp_r11_2 - 0x20);
            var_r7 = 0;
        }
    }
    if (var_r4 >= -0x3FE) {
        var_r5 = (temp_r5 & 0xFFFFF) | 0x100000;
    } else {
        temp_r11_3 = -0x3FE - var_r4;
        if (temp_r11_3 <= 0x1F) {
            var_r5 = (temp_r5 << temp_r11_3) | ((u32) var_r6 >> (0x20 - temp_r11_3));
            var_r6 <<= temp_r11_3;
        } else {
            var_r5 = var_r6 << (temp_r11_3 - 0x20);
            var_r6 = 0;
        }
    }
    var_r11 = var_r10 - var_r4;
loop_43:
    temp_cr0_eq = var_r11 == 0;
    var_r11 -= 1;
    if (temp_cr0_eq != 0) {
        var_r9 = var_r8 - var_r5;
        if (var_r7 < (u32) var_r6) {
            var_r9 -= 1;
        }
        if (var_r9 >= 0) {
            var_r8 = var_r9;
            var_r7 -= var_r6;
        }
        if ((var_r8 | var_r7) != 0) {
            if (var_r8 <= 0xFFFFF) {
                do {
                    var_r8 = (var_r8 * 2) + (var_r7 >> 0x1FU);
                    var_r7 *= 2;
                    var_r4 -= 1;
                } while (var_r8 <= 0xFFFFF);
            }
            if (var_r4 >= -0x3FE) {
                *((f64 *)&sp8) = 0;
                *(s32 *)&sp8 = (var_r8 + QB_UNKNOWN_0xFFF00000) | ((var_r4 + 0x3FF) << 0x14) | temp_r3;
                sp8.unk0x4 = var_r7;
                return *((f64 *)&sp8);
            }
            temp_r11_4 = -0x3FE - var_r4;
            if (temp_r11_4 <= 0x14) {
                var_r7_2 = (var_r7 >> temp_r11_4) | (var_r8 << (0x20 - temp_r11_4));
                var_r8_2 = var_r8 >> temp_r11_4;
            } else {
                if (temp_r11_4 <= 0x1F) {
                    var_r7_2 = (var_r8 << (0x20 - temp_r11_4)) | (var_r7 >> temp_r11_4);
                } else {
                    var_r7_2 = var_r8 >> (temp_r11_4 - 0x20);
                }
                var_r8_2 = temp_r3;
            }
            *((f64 *)&sp8) = 0;
            *(s32 *)&sp8 = var_r8_2 | temp_r3;
            sp8.unk0x4 = var_r7_2;
            return *((f64 *)&sp8);
        }
        goto block_58;
    }
    var_r9_2 = var_r8 - var_r5;
    temp_r10 = var_r7 - var_r6;
    if (var_r7 < (u32) var_r6) {
        var_r9_2 -= 1;
    }
    if (var_r9_2 < 0) {
        var_r8 = (var_r8 * 2) + (var_r7 >> 0x1FU);
        var_r7 *= 2;
        goto loop_43;
    }
    if ((var_r9_2 | temp_r10) != 0) {
        var_r8 = (var_r9_2 * 2) + (temp_r10 >> 0x1FU);
        var_r7 = temp_r10 * 2;
        goto loop_43;
    }
block_58:
    {
        extern f64 lbl_802B21F0[2];
        u32 idx = ((u32)temp_r3 >> 31);
        return lbl_802B21F0[idx];
    }
}
