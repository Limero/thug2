// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80270174-0x80270254 (224B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G8
// Identity: sin(double) — fdlibm __ieee754_sin family; calls kernel_sin /
// kernel_cos (fn_80271444 / fn_80271538).
// Suggested rename: sin
#include "types.h"
#include "qb_constants.h"

extern f64 lbl_803CA640; /* 0.0 */

f64 fn_80271444(f64 x, f64 y);            /* kernel_sin(x, y) */
f64 fn_80271538(s32 iy, f64 x, f64 y);    /* kernel_cos(iy, x, y) */
s32 fn_802715E4(f64 x, f64 *y);           /* rem_pio2(x, y[]) */

f64 fn_80270174(f64 x) {
    f64 y[2];
    union {
        f64 d;
        u32 w[2];
    } u;
    f64 z;
    s32 n;
    s32 ix;

    z = lbl_803CA640;
    __asm__("" : : "f"(z));
    u.d = x;
    ix = u.w[0];
    __asm__("" : "+r"(ix));
    ix &= QB_UNKNOWN_0x7FFFFFFF;
    __asm__ volatile("");
    if (ix <= QB_UNKNOWN_0x3FE921FB) {
        return fn_80271444(x, z);
    }
    if (ix >= QB_UNKNOWN_0x7FF00000) {
        return x - x;
    }
    n = fn_802715E4(x, y);
    switch (n & 3) {
    case 0:
        return fn_80271444(y[0], y[1]);
    case 1:
        return -fn_80271538(1, y[0], y[1]);
    case 2:
        return -fn_80271444(y[0], y[1]);
    default:
        return fn_80271538(1, y[0], y[1]);
    }
}
