// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80271A34-0x80271AE0 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G4
// fdlibm float __kernel_sin/sincos helper: polynomial sine of x reduced to
// [-pi/4, pi/4] (Chebyshev coefficients S1-S6, iy flag selects cos path).
// Suggested rename: __kernel_sinf.
#include "types.h"
#include "qb_constants.h"
extern f32 lbl_803CA86C; /* S6 */
extern f32 lbl_803CA870; /* S5 */
extern f32 lbl_803CA874; /* S4 */
extern f32 lbl_803CA878; /* S3 */
extern f32 lbl_803CA87C; /* S2 */
extern f32 lbl_803CA880; /* S1 */
extern f32 lbl_803CA884; /* half */

f32 fn_80271A34(s32 flag, f32 x, f32 y) {
    union { f32 f; s32 w; } cvt;
    s32 hx;
    register f32 xv __asm__("fr9");

    xv = x;
    cvt.f = xv;
    hx = cvt.w & QB_UNKNOWN_0x7FFFFFFF;
    __asm__ volatile("" : "+r"(hx));
    if (hx <= QB_UNKNOWN_0x31FFFFFF) {
        if ((s32)xv == 0) {
            return xv;
        }
    }
    {
        f32 z, v, p;
        z = xv * xv;
        v = z * xv;
        p = lbl_803CA87C + z * (lbl_803CA878 + z * (lbl_803CA874 + z * (lbl_803CA870 + z * lbl_803CA86C)));
        if (flag == 0) {
            return xv + v * (lbl_803CA880 + z * p);
        }
        return xv - ((z * (y * lbl_803CA884 - v * p) - y) - v * lbl_803CA880);
    }
}
