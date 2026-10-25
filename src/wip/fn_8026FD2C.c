// WIP DRAFT (non-matching) — semantic fdlibm e_sqrt.c reconstruction of sqrt(f64).
// family=m2c range=0x8026FD2C-0x8026FF40 size=532B
// FLAG: -fno-schedule-insns2
// PARKED @86.5% (115/133 words, +7.5 points over 78.95%): netlib signedness restored, q>>1 emits srawi, and the result uses the two-stage ix0 construction.
// The four ix1 += ix1 sites use nonvolatile add asm because ProDG otherwise emits slwi; only 6/133 instructions are emitted asm (2 entry loads + 4 bit ops), with no whole-body transcription.
// SDA-aware verification 2026-09-25: tools/sda_verify.py with -fno-schedule-insns2, and again with -msdata=eabi -G8, both compile 532B and report MISMATCH (18 words).
// Remaining wall: sign is r6 instead of r31; lis/rlwinm are swapped; m<<20 and the final high/low pair use r4/r28/r29 instead of r29/r5/r6, which also forces stmw/lmw r28.
// Semantics retained: f64 NaN/+inf, signed zero, negative sNaN, subnormal normalization, two digit-by-digit loops, and round-to-odd finalization; no helper calls.
// INERT: not registered in splits.txt/configure.py — never compiled, not counted in objdiff progress. activate via tools/wip.py.
#include "qb_constants.h"

f64 fn_8026FD2C(f64 farg0) {
    union { f64 d; u32 w[2]; } u;
    register s32 var_r9 __asm__("r9");
    register u32 var_r8 __asm__("r8");
    register u32 lo_tmp __asm__("r10");
    register s32 var_r11 __asm__("r11");
    register s32 var_r4 __asm__("r4");
    register u32 var_r3 __asm__("r3");
    register s32 var_r12 __asm__("r12");
    register u32 var_r30 __asm__("r30");
    s32 var_r10;
    u32 var_r7;
    s32 temp_r11;
    u32 temp_r10;
    u32 temp_r0;
    s32 sign;
    register s32 ex __asm__("r11");
    register s32 clrtmp __asm__("r0");
    s32 result_hi;

    sign = (s32)0x80000000;
    u.d = farg0;
    __asm__ volatile("lwz %0, 8(1)" : "=r"(var_r9));
    __asm__ volatile("lwz %0, 12(1)" : "=r"(lo_tmp));
    var_r8 = lo_tmp;
    ex = var_r9 & QB_UNKNOWN_0x7FF00000;
    __asm__ volatile("" ::: "memory");
    if (ex == QB_UNKNOWN_0x7FF00000) {
        return (farg0 * farg0) + farg0;
    }
    if ((s32)var_r9 <= 0) {
        if (((var_r9 & ~sign) | var_r8) == 0) {
            return farg0;
        }
        if ((s32)var_r9 < 0) {
            return (farg0 - farg0) / (farg0 - farg0);
        }
    }
    var_r10 = (s32)var_r9 >> 0x14;
    if (var_r10 == 0) {
        if (var_r9 == 0) {
            do {
                temp_r0 = var_r8 >> 0xB;
                var_r10 -= 0x15;
                var_r8 <<= 0x15;
                var_r9 |= temp_r0;
            } while (var_r9 == 0);
        }
        var_r10 += 1;
        var_r11 = 0;
        while (!(var_r9 & 0x100000)) {
            var_r9 = (s32)((u32)var_r9 << 1);
            var_r11 += 1;
        }
        var_r10 -= var_r11;
        var_r9 |= (s32)(var_r8 >> (0x20 - var_r11));
        var_r8 <<= var_r11;
    }
    var_r10 -= 0x3FF;
    clrtmp = var_r9 & 0xFFFFF;
    var_r9 = clrtmp | 0x100000;
    if (var_r10 & 1) {
        temp_r0 = (var_r8 & sign) >> 0x1F;
        __asm__("add %0,%0,%0" : "+r"(var_r8));
        var_r9 = var_r9 + (var_r9 + (s32)temp_r0);
    }
    temp_r0 = (var_r8 & sign) >> 0x1F;
    var_r10 = var_r10 >> 1;
    __asm__("add %0,%0,%0" : "+r"(var_r8));
    var_r9 = var_r9 + (var_r9 + (s32)temp_r0);
    var_r30 = 0;
    var_r4 = 0;
    var_r3 = 0;
    var_r12 = 0;
    var_r7 = 0x200000;
    do {
        temp_r11 = var_r4 + var_r7;
        if ((s32)temp_r11 <= var_r9) {
            var_r4 = temp_r11 + var_r7;
            var_r9 -= temp_r11;
            var_r12 += var_r7;
        }
        temp_r0 = (var_r8 & sign) >> 0x1F;
        var_r7 >>= 1;
        __asm__("add %0,%0,%0" : "+r"(var_r8));
        var_r9 = var_r9 + (var_r9 + (s32)temp_r0);
    } while (var_r7 != 0);
    var_r7 = (s32)sign;
    if (var_r7 != 0) {
        do {
            temp_r11 = var_r4;
            temp_r10 = var_r30 + var_r7;
            if (((s32)temp_r11 < var_r9) || (((s32)temp_r11 == var_r9) && (temp_r10 <= var_r8))) {
                var_r30 = temp_r10 + var_r7;
                if (((temp_r10 & sign) == (u32)sign) && !(var_r30 & (u32)sign)) {
                    var_r4 = temp_r11 + 1;
                }
                var_r9 -= temp_r11;
                if (var_r8 < temp_r10) {
                    var_r9 -= 1;
                }
                var_r8 -= temp_r10;
                var_r3 += var_r7;
            }
            temp_r0 = (var_r8 & sign) >> 0x1F;
            var_r7 >>= 1;
            __asm__("add %0,%0,%0" : "+r"(var_r8));
            var_r9 = var_r9 + (var_r9 + (s32)temp_r0);
        } while (var_r7 != 0);
    }
    if (((u32)var_r9 | var_r8) != 0) {
        if (var_r3 == 0xFFFFFFFFU) {
            var_r3 = 0;
            var_r12 += 1;
        } else {
            var_r3 += var_r3 & 1;
        }
    }
    result_hi = (var_r12 >> 1) + QB_UNKNOWN_0x3FE00000;
    var_r8 = var_r3 >> 1;
    if (var_r12 & 1) {
        var_r8 |= (u32)sign;
    }
    result_hi += var_r10 << 0x14;
    u.w[0] = result_hi;
    u.w[1] = var_r8;
    return u.d;
}
// 2026-10-22: 88.0% (was 86.5%): `ex` computed above the memory barrier.
