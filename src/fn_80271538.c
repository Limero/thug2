// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80271538-0x802715E4 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G8
// fdlibm __kernel_cos(x, y, iy): cosine of x reduced to [-pi/4, pi/4]
// (Chebyshev coefficients S1-S6). Suggested rename: __kernel_cos.
#include "types.h"
#include "qb_constants.h"
extern f64 lbl_803CA7B8; /* S6 */
extern f64 lbl_803CA7C0; /* S5 */
extern f64 lbl_803CA7C8; /* S4 */
extern f64 lbl_803CA7D0; /* S3 */
extern f64 lbl_803CA7D8; /* S2 */
extern f64 lbl_803CA7E0; /* S1 */
extern f64 lbl_803CA7E8; /* half */

f64 fn_80271538(f64 x, f64 y, s32 iy) {
    union { f64 d; s32 w[2]; } cvt;
    s32 hx;
    register f64 xv __asm__("fr8");

    xv = x;
    cvt.d = xv;
    hx = cvt.w[0] & QB_UNKNOWN_0x7FFFFFFF;
    __asm__ volatile("" : "+r"(hx));
    if (hx <= QB_UNKNOWN_0x3E3FFFFF) {
        if ((s32)xv == 0) {
            return xv;
        }
    }
    {
        f64 z, v, p;
        z = xv * xv;
        v = z * xv;
        p = lbl_803CA7D8 + z * (lbl_803CA7D0 + z * (lbl_803CA7C8 + z * (lbl_803CA7C0 + z * lbl_803CA7B8)));
        if (iy == 0) {
            return xv + v * (lbl_803CA7E0 + z * p);
        }
        return xv - ((z * (y * lbl_803CA7E8 - v * p) - y) - v * lbl_803CA7E0);
    }
}
