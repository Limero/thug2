// WIP DRAFT (non-matching) — hand-tuned from tools/fill_wip_drafts.py
// family=m2c range=0x80271948-0x80271A34 size=236B
// PARKED @ 15/59 words (~74% masked, tools/sda_verify.py -msdata=eabi -G4) — improved from 19/59.
// Baseline 19: zp f8 vs f12, half f13 vs f1, one f1 vs f13, hz f0 vs f1, qx hoist (addis above cmpw).
// Best15 distinct: zp fr0 + hz fr1 + top fr13 + qx fr12 + bhx/bzp barriers (+r hx, +f z/zp) shaves 4.
// Best14 shared (hz+top both fr13) shaves 5 but shares live range — not clean, so kept distinct 15 as best clean.
// Resisted for EXACT: 71444 pins xy fr0/hz fr1 -> 39 on this float; zp fr12 -> 38; half/one vars -> 22;
// qx hoist: +r, volatile, half vars no gain; -fno-* worsen; p*z / y*xv -> 20.
// qx wall: want cmpw/ble/lwz vs got hoisted addis (r9 vs r0) — needs r0 pin or split block.
// Tail FPR wall: same cousin as 71444 but float resists (needs per-path distinct FPRs).
// Next retry: qx inline-asm addis to r0 + explicit b, or per-path separate qx vars.
// identity: __kernel_cosf(x,y) float (fdlibm-style C1..C6 poly, .sdata2 consts)
// FLAG: -msdata=eabi -G4
// RESTORED 2026-09-20 by tools/restore_best_body.py.  The working body
// scored 44.1% while git revision 4e7628f0b scores 57.6%;
// the pool's struct-ification sweep and/or tools/store_order_search.py had
// rewritten this body in place and kept the worse result while the notes
// above stayed put.  Winner picked from 10 distinct committed bodies.
// Re-verify with tools/score_addrs.py before editing again.
#include "types.h"
extern f32 lbl_803CA848; /* one */
extern f32 lbl_803CA84C; /* C6 */
extern f32 lbl_803CA850; /* C5 */
extern f32 lbl_803CA854; /* C4 */
extern f32 lbl_803CA858; /* C3 */
extern f32 lbl_803CA85C; /* C2 */
extern f32 lbl_803CA860; /* C1 */
extern f32 lbl_803CA864; /* half */
extern u32 lbl_803CA868; /* quarter 0.28125f bit pattern */

f32 fn_80271948(f32 x, f32 y) {
    union { f32 f; s32 w; } cvt;
    s32 hx;
    f32 xv = x;
    __asm__("" : "+f"(xv));
    cvt.f = xv;
    hx = cvt.w & 0x7FFFFFFF;
    __asm__ volatile("" : "+r"(hx));
    if (hx <= 0x31FFFFFF) {
        if ((s32)xv == 0) {
            return lbl_803CA848;
        }
    }
    {
        f32 z, p;
        register f32 zp __asm__("fr0");
        register f32 qx __asm__("fr12");
        register f32 top __asm__("fr13");
        register f32 hz __asm__("fr1");
        __asm__ volatile("" : "+r"(hx));
        z = xv * xv;
        p = lbl_803CA860 + z * (lbl_803CA85C + z * (lbl_803CA858 + z * (lbl_803CA854 + z * (lbl_803CA850 + z * lbl_803CA84C))));
        __asm__("" : "+f"(z));
        zp = z * p;
        __asm__("" : "+f"(zp));
        if (hx <= 0x3E999999) {
            top = lbl_803CA848;
            hz = z * lbl_803CA864 - (z * zp - xv * y);
        } else {
            if (hx > 0x3F480000) { cvt.w = lbl_803CA868; } else { cvt.w = hx - 0x01000000; }
            qx = cvt.f;
            top = lbl_803CA848 - qx;
            hz = (z * lbl_803CA864 - qx) - (z * zp - xv * y);
        }
        return top - hz;
    }
}
