// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802704A4-0x8027052C (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G8
// fdlibm scalbn error wrapper: scales x by 2^n via fn_802712F0 and raises
// ERANGE (0x22 through the __getreent error-state ptr) on overflow to
// non-finite or underflow to zero. Suggested rename: scalbn_err.
#include "types.h"

extern f64 lbl_803CA660; /* 0.0 */

s32 fn_802712CC(f64 x);           /* finite-exponent check */
f64 fn_802712F0(f64 x, s32 n);    /* scalbn(x, n) */
struct _reent;
extern struct _reent *__getreent(void); /* error-state ptr getter */

f64 fn_802704A4(s32 n, f64 x) {
    f64 v;
    f64 c;

    v = x;
    if (fn_802712CC(x) != 0) {
        c = lbl_803CA660;
        __asm__("" : : "f"(c));
        if (x != c) {
            v = fn_802712F0(x, n);
            if (fn_802712CC(v) == 0 || v == c) {
                *(s32 *) __getreent() = 0x22;
            }
        }
    }
    return v;
}
