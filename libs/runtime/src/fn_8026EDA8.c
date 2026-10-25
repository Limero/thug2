// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8026EDA8-0x8026EEF0 (328B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G8
#include "types.h"
#include "qb_constants.h"
extern f64 lbl_802B2288[2];
extern f64 lbl_802B2290[2];
extern f64 lbl_802B2298[2];
extern char lbl_802B22A0[];
extern f64 lbl_802B22A8[2];
extern f64 lbl_802B22B0[2];
extern f64 lbl_802B22B8[2];
extern f64 fn_8026EAAC(f64);

f64 fn_8026EDA8(f64 farg0) {
    volatile struct { f64 d; u32 cw[2]; } fr;
    f64 xt;
    f64 y;
    f64 z;
    f64 logv;
    register f64 logx __asm__("fr13");
    register f64 ivlnv __asm__("fr12");
    register f64 logterm __asm__("fr1");
    register s32 k __asm__("r8");
    register s32 hx __asm__("r5");
    register u32 lx __asm__("r11");
    register s32 e20 __asm__("r0");
    register s32 hi __asm__("r9");
    register u32 lo __asm__("r10");
    register s32 carry __asm__("r11");
    register s32 kplus __asm__("r0");
    register s32 hout __asm__("r9");
    register s32 magic __asm__("r6");
    register s32 pool_anchor __asm__("r8");
    xt = farg0;
    __asm__ volatile("" : "+f"(xt) :: "memory");
    fr.d = xt;
    __asm__ volatile("lwz %0, 8(1)" : "=r"(hi));
    __asm__ volatile("lwz %0, 12(1)" : "=r"(lo));
    hx = hi;
    lx = lo;
    k = 0;
    __asm__ volatile("" ::: "memory");
    if (hx <= 0xFFFFF) {
        if (((hx & (s32)QB_UNKNOWN_0x7FFFFFFF) | (s32)lx) == 0) {
            return lbl_802B2288[0];
        }
        if (hx < 0) {
            return (farg0 - farg0) / lbl_802B2290[0];
        }
        k = -0x36;
        farg0 = farg0 * lbl_802B2298[0];
        xt = farg0;
        __asm__ volatile("" : "+f"(xt) :: "memory");
        fr.d = xt;
        __asm__ volatile("lwz %0, 8(1)" : "=r"(hi));
        __asm__ volatile("lwz %0, 12(1)" : "=r"(lo));
        hx = hi;
    }
    if (hx > QB_UNKNOWN_0x7FEFFFFF) {
        return farg0 + farg0;
    }
    e20 = hx >> 20;
    __asm__ volatile("" : "+r"(e20));
    {
        register s32 tmp __asm__("r9") = k - 0x3FF;
        k = tmp + e20;
    }
    __asm__ volatile("" ::: "memory");
    fr.d = farg0;
    carry = (s32)(((u32)k) >> 31);
    __asm__ volatile("" ::: "memory");
    kplus = k + carry;
    __asm__ volatile("lwz %0, 8(1)" : "=r"(hi));
    __asm__ volatile("lwz %0, 12(1)" : "=r"(lo));
    carry = 0x3FF - carry;
    __asm__ volatile("" ::: "memory");
    carry = carry << 20;
    fr.cw[1] = ((u32)kplus) ^ 0x80000000;
    __asm__ volatile("" ::: "memory");
    hx = (s32)(((u32)hx & QB_UNKNOWN_0x000FFFFF) | (u32)carry);
    __asm__ volatile("" ::: "memory");
    magic = QB_INT_TO_DOUBLE_BIAS;
    __asm__ volatile("mr %0,%1" : "=r"(hout) : "r"(hx));
    __asm__ volatile("" ::: "memory");
    fr.cw[0] = (u32)magic;
    *(u32 *)&fr.d = (u32)hout;
    ((u32 *)&fr.d)[1] = lo;
    __asm__ volatile("lis %0,%1@ha" : "=r"(pool_anchor) : "s"(lbl_802B22A0));
    y = *(f64 *)&fr.cw[0] - *(f64 *)((char *)pool_anchor + 0x22A0);
    logx = fr.d;
    logv = fn_8026EAAC(logx);
    ivlnv = lbl_802B22B0[0];
    __asm__("fmul %0,%1,%2" : "=f"(logterm) : "f"(logv), "f"(ivlnv));
    z = (y * lbl_802B22A8[0]) + logterm;
    logx = lbl_802B22B8[0];
    return z + y * logx;
}
