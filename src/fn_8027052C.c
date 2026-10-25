// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8027052C-0x8027060C (224B). Byte-identical.
// extra_cflags: -msdata=eabi, -G8, -fno-schedule-insns2
// FLAG: -msdata=eabi -G8 -fno-schedule-insns2
// fdlibm/newlib sin(): kernel_sin=fn_80271538, kernel_cos=fn_80271444,
// rem_pio2=fn_802715E4; z=0.0 in .sdata lbl_803CA668 (r13 SDA21 form,
// resolved at link vs _SDA_BASE_). Promoted via the sda_verify route
// (AGENTS.md 5q): promote_wip cannot resolve standalone SDA21 relocs.
// The two empty volatile barriers are required codegen pins (no code).
#include "types.h"
#include "qb_constants.h"
extern const f64 lbl_803CA668;
f64 fn_80271538(f64, f64, s32);
f64 fn_80271444(f64, f64);
s32 fn_802715E4(f64, void *);
f64 fn_8027052C(f64 x) {
    f64 y[2];
    union {
        f64 d;
        struct { s32 hi, lo; } w;
    } u;
    f64 z;
    s32 n;
    s32 ix;

    z = lbl_803CA668;
    __asm__ volatile("" : "+f"(z));
    u.d = x;
    ix = (u.w.hi & QB_UNKNOWN_0x7FFFFFFF) | (u.w.lo * 0);
    __asm__ volatile("" : "+r"(ix));
    if (ix <= QB_UNKNOWN_0x3FE921FB) {
        return fn_80271538(x, z, 0);
    }
    if (ix >= QB_UNKNOWN_0x7FF00000) {
        return x - x;
    }
    n = fn_802715E4(x, y);
    switch (n & 3) {
    case 0:
        return fn_80271538(y[0], y[1], 1);
    case 1:
        return fn_80271444(y[0], y[1]);
    case 2:
        return -fn_80271538(y[0], y[1], 1);
    default:
        return -fn_80271444(y[0], y[1]);
    }
}
