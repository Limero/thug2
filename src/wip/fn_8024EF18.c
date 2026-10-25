// WIP DRAFT (PARKED, semantic paired-single reconstruction) — hand-written NeGo texture kernel
// family=m2c range=0x8024EF18-0x8024F284 size=876B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled into the DOL.
//
// VERIFIED 2026-09-25: this body compiles with ProDG 3.9.3 -mps-float at
// 880 bytes / 220 instructions, versus retail 876 bytes / 219 instructions.
// tools/ps_diff.py scores 1/219 masked retail instructions (0.5%; 1/220 across
// the full 220-instruction got span); the fixed-position
// score is low because retail's hand-written prologue and PS register schedule
// differ from every C allocation, not because the semantics or opcodes are
// unknown.
//
// arg0 points to 64 signed-16 values (128 bytes). Both passes run four
// iterations with GQR7=7. Pass one applies the eight-coefficient color matrix
// and expands/reorders the block through the 256-byte scratch object
// lbl_803A3378. Pass two applies the matrix again with a different lane
// pairing, adds 0.5/-1.0 and applies ps_sel before storing 64 signed-16 values
// back in place. The scalar table at lbl_8024F284+0x00..+0x24 is
// {0.70710683, 0.49039260, 0.46193981, 0.41573480, 0.35355341,
//  0.27778509, 0.19134170, 0.09754520, 0.5, -1.0}.
//
// Direct __builtin_psq_l/st(..., 7) calls reproduce every quantized I=7 word;
// the former emission-wall claim in this draft was stale. The remaining exact
// blocker is the assembly envelope: retail uses stwu -0x98, individually
// interleaves stfd f14-f31 with constant/GQR setup, and explicitly saves and
// restores CTR. Natural C uses stwu -0x68 and saves f20-f31. Pinning the retail
// constant homes expands the body to 980 bytes; pinning the computed homes
// expands it to 912 bytes; neither improves the 0.5% score. The six asm
// statements below account for only 7/220 emitted instructions and preserve
// the otherwise-unrepresentable CTR/GQR protocol; all conversion and memory
// semantics remain real C.
#include "types.h"

extern f32 lbl_8024F284[];
extern s16 lbl_803A3378[];

#define QLOAD(P) __builtin_psq_l((void *)(P), 0, 7)
#define QSTORE(P, V) __builtin_psq_st((void *)(P), V, 0, 7)

void fn_8024EF18(s16 *arg0) {
    __ps_t k24, k25, k26, k27, k28, k29, k30, k31, k7, k6;
    __ps_t a, b, c, d, e, f, g, h;
    __ps_t p00, p01, p10, p11, q00, q01, q10, q11;
    __ps_t t8, t9, t10, t11, t12, t13, t14, t15;
    __ps_t t16, t17, t18, t19, t20, t21, t22, t23;
    s16 *src;
    s16 *tmp_base;
    s16 *tmp;
    s32 count;
    u32 saved_ctr;
    u32 saved_gqr;
    u32 gqr;

    __asm__ volatile("mfctr %0" : "=r"(saved_ctr));
    __asm__ volatile("mfspr %0,919" : "=r"(saved_gqr));
    __asm__ volatile("lis %0,7\n\tmtspr 919,%0" : "=r"(gqr));

    k24 = (__ps_t)lbl_8024F284[0];
    k25 = (__ps_t)lbl_8024F284[1];
    k26 = (__ps_t)lbl_8024F284[2];
    k27 = (__ps_t)lbl_8024F284[3];
    k28 = (__ps_t)lbl_8024F284[4];
    k29 = (__ps_t)lbl_8024F284[5];
    k30 = (__ps_t)lbl_8024F284[6];
    k31 = (__ps_t)lbl_8024F284[7];
    k7 = (__ps_t)lbl_8024F284[8];
    k6 = (__ps_t)lbl_8024F284[9];

    tmp_base = lbl_803A3378;
    src = arg0;
    tmp = tmp_base;
    count = 4;
    do {
        a = QLOAD(src + 0);
        e = QLOAD(src + 8);
        b = QLOAD(src + 2);
        f = QLOAD(src + 10);
        p00 = __builtin_ps_merge00(a, e);
        p01 = __builtin_ps_merge11(a, e);
        c = QLOAD(src + 4);
        g = QLOAD(src + 12);
        p10 = __builtin_ps_merge00(b, f);
        p11 = __builtin_ps_merge11(b, f);
        d = QLOAD(src + 6);
        h = QLOAD(src + 14);
        src += 16;
        q11 = __builtin_ps_merge11(d, h);
        q01 = __builtin_ps_merge11(c, g);
        q00 = __builtin_ps_merge00(c, g);
        q10 = __builtin_ps_merge00(d, h);

        t20 = __builtin_ps_mul(p01, k25);
        t23 = __builtin_ps_mul(p01, k31);
        t21 = __builtin_ps_mul(p11, k29);
        t16 = __builtin_ps_add(p00, q00);
        t20 = __builtin_ps_msub(p01, t20, k31);
        t23 = __builtin_ps_madd(p01, t23, k31);
        t21 = __builtin_ps_msub(q01, t21, k27);
        t16 = __builtin_ps_mul(t16, k28);
        t22 = __builtin_ps_mul(q01, k29);
        t19 = __builtin_ps_mul(p10, k26);
        t17 = __builtin_ps_sub(p00, q00);
        t18 = __builtin_ps_mul(q10, k26);
        t22 = __builtin_ps_madd(p11, t22, k27);
        t19 = __builtin_ps_madd(q10, t19, k30);
        t17 = __builtin_ps_mul(t17, k28);
        t18 = __builtin_ps_msub(p10, t18, k30);

        t15 = __builtin_ps_add(t23, t22);
        t12 = __builtin_ps_add(t20, t21);
        t8 = __builtin_ps_add(t16, t19);
        t11 = __builtin_ps_sub(t16, t19);
        t9 = __builtin_ps_add(t17, t18);
        t10 = __builtin_ps_sub(t17, t18);
        t16 = __builtin_ps_sub(t20, t21);
        t17 = __builtin_ps_sub(t23, t22);
        t18 = __builtin_ps_add(t8, t15);
        t22 = __builtin_ps_add(t11, t12);
        t19 = __builtin_ps_sub(t11, t12);
        t13 = __builtin_ps_sub(t17, t16);
        t14 = __builtin_ps_add(t17, t16);
        t16 = __builtin_ps_sub(t8, t15);
        t13 = __builtin_ps_mul(t13, k24);
        t14 = __builtin_ps_mul(t14, k24);
        t21 = __builtin_ps_add(t10, t13);
        t23 = __builtin_ps_add(t9, t14);
        t17 = __builtin_ps_sub(t10, t13);
        t20 = __builtin_ps_sub(t9, t14);

        QSTORE(tmp + 4, __builtin_ps_merge00(t21, t22));
        QSTORE(tmp + 20, __builtin_ps_merge11(t21, t22));
        QSTORE(tmp + 0, __builtin_ps_merge00(t18, t23));
        QSTORE(tmp + 16, __builtin_ps_merge11(t18, t23));
        QSTORE(tmp + 8, __builtin_ps_merge00(t19, t17));
        QSTORE(tmp + 24, __builtin_ps_merge11(t19, t17));
        QSTORE(tmp + 12, __builtin_ps_merge00(t20, t16));
        QSTORE(tmp + 28, __builtin_ps_merge11(t20, t16));
        tmp += 32;
        count--;
    } while (count != 0);

    __asm__ volatile("li %0,7\n\tmtspr 919,%0" : "=r"(gqr));
    src = arg0;
    tmp = tmp_base;
    count = 4;
    do {
        t15 = QLOAD(tmp + 112);
        t13 = QLOAD(tmp + 80);
        t8 = QLOAD(tmp + 0);
        t9 = QLOAD(tmp + 16);
        t10 = QLOAD(tmp + 32);
        t11 = QLOAD(tmp + 48);
        t12 = QLOAD(tmp + 64);
        t14 = QLOAD(tmp + 96);
        tmp += 4;

        t20 = __builtin_ps_mul(t15, k25);
        t23 = __builtin_ps_mul(t9, k25);
        t21 = __builtin_ps_mul(t11, k29);
        t22 = __builtin_ps_mul(t13, k29);
        t20 = __builtin_ps_msub(t9, t20, k31);
        t23 = __builtin_ps_madd(t15, t23, k31);
        t21 = __builtin_ps_msub(t13, t21, k27);
        t22 = __builtin_ps_madd(t11, t22, k27);
        t16 = __builtin_ps_add(t8, t12);
        t17 = __builtin_ps_sub(t8, t12);
        t18 = __builtin_ps_mul(t14, k26);
        t19 = __builtin_ps_mul(t10, k26);
        t16 = __builtin_ps_mul(t16, k28);
        t17 = __builtin_ps_mul(t17, k28);
        t18 = __builtin_ps_msub(t10, t18, k30);
        t19 = __builtin_ps_madd(t14, t19, k30);

        t12 = __builtin_ps_add(t20, t21);
        t11 = __builtin_ps_sub(t16, t19);
        t15 = __builtin_ps_add(t23, t22);
        t8 = __builtin_ps_add(t16, t19);
        t9 = __builtin_ps_add(t17, t18);
        t10 = __builtin_ps_sub(t17, t18);
        t16 = __builtin_ps_sub(t20, t21);
        t17 = __builtin_ps_sub(t23, t22);
        t18 = __builtin_ps_add(t8, t15);
        t19 = __builtin_ps_add(t11, t12);
        t20 = __builtin_ps_sub(t11, t12);
        t13 = __builtin_ps_sub(t17, t16);
        t14 = __builtin_ps_add(t17, t16);
        t21 = __builtin_ps_sub(t8, t15);
        t18 = __builtin_ps_add(t18, k7);
        t19 = __builtin_ps_add(t19, k7);
        t16 = __builtin_ps_add(t18, k6);
        t17 = __builtin_ps_add(t19, k6);
        t18 = __builtin_ps_sel(t18, t18, t16);
        t19 = __builtin_ps_sel(t19, t19, t17);
        QSTORE(src + 0, t18);
        QSTORE(src + 24, t19);

        t13 = __builtin_ps_mul(t13, k24);
        t14 = __builtin_ps_mul(t14, k24);
        t20 = __builtin_ps_add(t20, k7);
        t21 = __builtin_ps_add(t21, k7);
        t16 = __builtin_ps_add(t20, k6);
        t17 = __builtin_ps_add(t21, k6);
        t20 = __builtin_ps_sel(t20, t20, t16);
        t21 = __builtin_ps_sel(t21, t21, t17);
        QSTORE(src + 32, t20);
        QSTORE(src + 56, t21);

        t17 = __builtin_ps_add(t10, t13);
        t16 = __builtin_ps_add(t9, t14);
        t18 = __builtin_ps_sub(t10, t13);
        t19 = __builtin_ps_sub(t9, t14);
        t17 = __builtin_ps_add(t17, k7);
        t16 = __builtin_ps_add(t16, k7);
        t18 = __builtin_ps_add(t18, k7);
        t19 = __builtin_ps_add(t19, k7);
        t20 = __builtin_ps_add(t17, k6);
        t21 = __builtin_ps_add(t16, k6);
        t22 = __builtin_ps_add(t18, k6);
        t23 = __builtin_ps_add(t19, k6);
        t17 = __builtin_ps_sel(t17, t17, t20);
        t16 = __builtin_ps_sel(t16, t16, t21);
        t18 = __builtin_ps_sel(t18, t18, t22);
        t19 = __builtin_ps_sel(t19, t19, t23);
        QSTORE(src + 16, t17);
        QSTORE(src + 8, t16);
        QSTORE(src + 40, t18);
        QSTORE(src + 48, t19);
        src += 2;
        count--;
    } while (count != 0);

    __asm__ volatile("mtctr %0" : : "r"(saved_ctr));
    __asm__ volatile("mtspr 919,%0" : : "r"(saved_gqr));
}
