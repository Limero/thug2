// WIP DRAFT (matching) — hand-fixed from tools/fill_wip_drafts.py
// family=m2c range=0x80271444-0x80271538 size=244B
// EXACT @ 0/61 words (LINK-SIM EXACT, tools/sda_verify.py -msdata=eabi -G8).
// Fix: bitcast pair loads via r9/r10 pin + i0/i1 copy-order (floor lever, docs/parkings/44 doc06 2026-09-01),
// per-path tail FPR colors via xy->fr0 + hz->fr1 pins (top/qx plain, order top_first).
// Prologue+poly remain exact (poly C5..C1 -> f13,f0,f10,f12,f11,f13, zp->f11).
// Previous parked walls: bitcast r11/r12 vs r9/r10; tail swap xy/half/hz f0/f1.
// identity: __kernel_cos(x,y) double (fdlibm-style C1..C6 poly, .sdata consts)
// FLAG: -msdata=eabi -G8
#include "types.h"
#include "qb_constants.h"
extern f64 lbl_803CA770; /* one */
extern f64 lbl_803CA778; /* C6 */
extern f64 lbl_803CA780; /* C5 */
extern f64 lbl_803CA788; /* C4 */
extern f64 lbl_803CA790; /* C3 */
extern f64 lbl_803CA798; /* C2 */
extern f64 lbl_803CA7A0; /* C1 */
extern f64 lbl_803CA7A8; /* half */
extern f64 lbl_803CA7B0; /* qx const */

f64 fn_80271444(f64 x, f64 y) {
    union { f64 d; s32 w[2]; } cvt;
    s32 hx;
    f64 z, p, zp;
    f64 qx;
    f64 top;
    register f64 hz __asm__("fr1");
    register f64 xy __asm__("fr0");
    f64 xr;
    register s32 hi __asm__("r9");
    register s32 lo __asm__("r10");
    register s32 i0 __asm__("r10");
    register s32 i1 __asm__("r6");
    xr = x;
    cvt.d = xr;
    __asm__ volatile("lwz %0, 8(1)" : "=r"(hi));
    __asm__ volatile("lwz %0, 12(1)" : "=r"(lo));
    i1 = lo;
    i0 = hi;
    hx = i0 & QB_UNKNOWN_0x7FFFFFFF;
    __asm__ volatile("" : "+r"(hx));
    if (hx <= QB_UNKNOWN_0x3E3FFFFF) {
        if ((s32)xr == 0) {
            return lbl_803CA770;
        }
    }
    z = xr * xr;
    p = lbl_803CA7A0 + z * (lbl_803CA798 + z * (lbl_803CA790 + z * (lbl_803CA788 + z * (lbl_803CA780 + z * lbl_803CA778))));
    zp = z * p;
    if (hx <= QB_UNKNOWN_0x3FD33332) {
        xy = xr * y;
        top = lbl_803CA770;
        hz = z * lbl_803CA7A8 - (z * zp - xy);
    } else {
        if (hx > QB_UNKNOWN_0x3FE90000) {
            qx = lbl_803CA7B0;
        } else {
            cvt.w[0] = hx - QB_UNKNOWN_0x00200000;
            cvt.w[1] = 0;
            qx = cvt.d;
        }
        xy = xr * y;
        top = lbl_803CA770 - qx;
        hz = (z * lbl_803CA7A8 - qx) - (z * zp - xy);
    }
    return top - hz;
}
