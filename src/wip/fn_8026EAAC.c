// PARKED 2026-09-25 — semantic Sun fdlibm __ieee754_log reconstruction.
// family=m2c range=0x8026EAAC-0x8026EDA8 size=764B
// FLAG: -msdata=eabi -G8
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// Correct verification: tools/venv/bin/python tools/sda_verify.py 0x8026EAAC
//   src/wip/fn_8026EAAC.c -msdata=eabi -G8
// Result: MISMATCH (108 words): 83/191 compared words exact; generated .text
// is 780B versus 764B retail (+16B). The prologue, all special cases, subnormal
// reduction, normalization, and near-one test are exact through +0x120
// (0x8026EBCC). First divergence is +0x124 (0x8026EBD0), where the exact-one
// dk conversion hoists lbl_802B2220 before the high-word store; the remaining
// fast-R/general blocks then differ in FPR anchor recycling and tail staging.
// All arithmetic is f64 and references the game's .rodata2 constants, including
// 2.0/0.5; dk uses the retail signed-s32 bit construction and real magic double.
// Inline asm is limited to GET_HIGH/GET_LOW, xoris, and srawi; no body assembly.
#include "types.h"
#include "qb_constants.h"

extern f64 lbl_802B2200[2];
extern f64 lbl_802B2208[2];
extern f64 lbl_802B2210[2];
extern f64 lbl_802B2218[2];
extern f64 lbl_802B2220[2];
extern f64 lbl_802B2228[2];
extern f64 lbl_802B2230[2];
extern f64 lbl_802B2238[2];
extern f64 lbl_802B2240[2];
extern f64 lbl_802B2248[2];
extern f64 lbl_802B2250[2];
extern f64 lbl_802B2258[2];
extern f64 lbl_802B2260[2];
extern f64 lbl_802B2268[2];
extern f64 lbl_802B2270[2];
extern f64 lbl_802B2278[2];
extern f64 lbl_802B2280[2];

typedef union {
    f64 d;
    struct {
        s32 hi;
        s32 lo;
    } w;
} DoubleBits;

f64 fn_8026EAAC(f64 x)
{
    volatile DoubleBits xbits;
    volatile DoubleBits cvt;
    register f64 xt __asm__("fr0");
    register s32 hx __asm__("r5");
    register s32 k __asm__("r4");
    register s32 i __asm__("r11");
    register f64 dk __asm__("fr4");
    s32 j;
    s32 cond;
    s32 kbits;
    register f64 f __asm__("fr3");
    f64 R;
    f64 tlo;
    f64 corr;
    f64 s;
    f64 z;
    f64 w;
    f64 t1;
    f64 t2;
    f64 hfsq;

    xt = x;
    xbits.d = xt;
    {
        register s32 hi __asm__("r9");
        register s32 lo __asm__("r10");
        __asm__ volatile("lwz %0, 8(1)" : "=r"(hi));
        __asm__ volatile("lwz %0, 12(1)" : "=r"(lo));
        hx = hi;
        i = lo;
    }
    __asm__ volatile("li %0, 0" : "=r"(k));

    if (hx <= 0x000FFFFF) {
        if (((hx & 0x7FFFFFFF) | i) == 0) {
            return lbl_802B2200[0];
        }
        if (hx < 0) {
            return (x - x) / lbl_802B2208[0];
        }
        k = -54;
        x *= lbl_802B2210[0];
        xt = x;
        xbits.d = xt;
        {
            register s32 hi __asm__("r9");
            register s32 lo __asm__("r10");
            __asm__ volatile("lwz %0, 8(1)" : "=r"(hi));
            __asm__ volatile("lwz %0, 12(1)" : "=r"(lo));
            hx = hi;
        }
    }

    if (hx > 0x7FEFFFFF) {
        return x + x;
    }

    {
        register s32 exponent __asm__("r9");
        register s32 base __asm__("r0");
        exponent = hx >> 20;
        base = k - 0x3FF;
        k = base + exponent;
    }
    hx &= 0x000FFFFF;
    i = (hx + 0x95F64) & 0x100000;
    __asm__ volatile("" : "+r"(i) : : "memory");
    {
        register s32 hi __asm__("r9");
        register s32 lo __asm__("r10");
        __asm__ volatile("stfd %2, 8(1)\n\tlwz %0, 8(1)\n\tlwz %1, 12(1)"
                         : "=r"(hi), "=r"(lo) : "f"(x) : "memory");
        __asm__ volatile("xoris %0, %1, 0x3ff0" : "=r"(j) : "r"(i));
        hi = hx | j;
        xbits.w.hi = hi;
        xbits.w.lo = lo;
    }
    xt = xbits.d;
    x = xt;
    __asm__ volatile("" : "+f"(x) : : "memory");
    __asm__ volatile("srawi %0, %0, 20" : "+r"(i));
    {
        register f64 one __asm__("fr0");
        one = lbl_802B2218[0];
        f = x - one;
    }
    k += i;

    if (((hx + 2) & 0x000FFFFF) <= 2) {
        if (f == lbl_802B2208[0]) {
            if (k == 0) {
                return lbl_802B2208[0];
            }
            __asm__ volatile("xoris %0, %1, 0x8000" : "=r"(kbits) : "r"(k));
            cvt.w.lo = kbits;
            cvt.w.hi = 0x43300000;
            dk = cvt.d - lbl_802B2220[0];
            tlo = dk * lbl_802B2230[0];
            return tlo + dk * lbl_802B2228[0];
        }
        {
            register f64 rfast __asm__("fr12");
            rfast = f * f;
            rfast = rfast * (lbl_802B2240[0] - lbl_802B2238[0] * f);
            if (k == 0) {
                return f - rfast;
            }
            __asm__ volatile("xoris %0, %1, 0x8000" : "=r"(kbits) : "r"(k));
            cvt.w.lo = kbits;
            cvt.w.hi = 0x43300000;
            dk = cvt.d - lbl_802B2220[0];
            corr = dk * lbl_802B2230[0];
            corr = rfast - corr;
            corr = corr - f;
            return dk * lbl_802B2228[0] + corr;
        }
    }

    s = f / (lbl_802B2248[0] + f);
    __asm__ volatile("xoris %0, %1, 0x8000" : "=r"(kbits) : "r"(k));
    cvt.w.lo = kbits;
    cvt.w.hi = 0x43300000;
    dk = cvt.d - lbl_802B2220[0];
    z = s * s;
    cond = hx - 0x6147A;
    w = z * z;
    j = 0x6B851 - hx;
    t1 = w * (lbl_802B2260[0] + w * (lbl_802B2258[0] + w * lbl_802B2250[0]));
    t2 = z * (lbl_802B2280[0] + w * (lbl_802B2278[0] + w * (lbl_802B2270[0] + w * lbl_802B2268[0])));
    cond |= j;
    R = t2 + t1;

    if (cond > 0) {
        hfsq = f * lbl_802B2240[0] * f;
        if (k == 0) {
            return f - (hfsq - s * (hfsq + R));
        }
        return dk * lbl_802B2228[0] - ((hfsq - (s * (hfsq + R) + dk * lbl_802B2230[0])) - f);
    }

    if (k == 0) {
        return f - s * (f - R);
    }
    return dk * lbl_802B2228[0] - ((s * (f - R) - dk * lbl_802B2230[0]) - f);
}
