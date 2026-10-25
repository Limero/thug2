// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802703EC-0x802704A4 (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G8
// frexp(x, *arg0): splits x into mantissa in [0.5, 1) and exponent (written
// through arg0); the 2^54 fudge (lbl_803CA658) handles denormals.
// Suggested rename: frexp.
#include "types.h"
#include "qb_constants.h"
extern f64 lbl_803CA658;

f64 fn_802703EC(s32 *arg0, f64 x) {
    volatile union { f64 d; u32 w[2]; } t;
    register f64 y __asm__("fr0");
    register f64 r __asm__("fr0");
    register u32 th __asm__("r9");
    register u32 tl __asm__("r10");
    register s32 hi __asm__("r8");
    register s32 lo __asm__("r11");
    register s32 mabs __asm__("r10");
    register s32 e __asm__("r11");
    s32 ex;

    y = x;
    __asm__("" : "+f"(y));
    t.d = y;
    th = t.w[0];
    tl = t.w[1];
    __asm__("" : "+r"(th), "+r"(tl));
    lo = (s32)tl;
    hi = (s32)th;
    mabs = hi & QB_UNKNOWN_0x7FFFFFFF;
    __asm__ __volatile__("");
    *arg0 = (s32)(th = 0u);
    if (mabs > QB_UNKNOWN_0x7FEFFFFF) {
        return x;
    }
    if ((mabs | lo) == 0) {
        return x;
    }
    if (mabs <= 0xFFFFF) {
        x *= lbl_803CA658;
        y = x;
        t.d = y;
        th = t.w[0];
        tl = t.w[1];
        __asm__("" : "+r"(th));
        hi = (s32)th;
        mabs = hi & QB_UNKNOWN_0x7FFFFFFF;
        __asm__ __volatile__("" ::: "memory");
        *arg0 = -0x36;
    }
    e = *arg0;
    __asm__("" : "+r"(mabs));
    ex = mabs >> 0x14;
    __asm__("" :: "r"(mabs));
    hi &= 0x800FFFFF;
    __asm__ __volatile__("");
    e += -0x3FE;
    e += ex;
    *arg0 = e;
    __asm__ __volatile__("" ::: "memory");
    t.d = x;
    th = t.w[0];
    tl = t.w[1];
    th = (u32)hi | 0x3FE00000u;
    t.w[0] = th;
    t.w[1] = tl;
    r = t.d;
    return r;
}
