// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8027124C-0x802712CC (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G4 -fno-schedule-insns -fno-schedule-insns2
#include "types.h"

extern f32 lbl_803CA74C; /* 0.0f, .sdata 0x803CA74C (small-data) */

s32 fn_80271CF4(f32 x, volatile f32 *y);
f32 fn_80271AE0(f32 x, f32 y, s32 n);

f32 tanf(f32 x) {
    volatile f32 y0, y1;
    f32 z = lbl_803CA74C;
    s32 n, t;
    register s32 w __asm__("r9");
    union { f32 f; s32 i; } u;

    u.f = x;
    w = u.i & 0x7FFFFFFF;
    if (w <= 0x3F490FDA) {
        return fn_80271AE0(x, z, 1);
    }
    if (w > 0x7F7FFFFF) {
        return x - x;
    }
    n = fn_80271CF4(x, &y0);
    t = (n & 1) << 1;
    return fn_80271AE0(y0, y1, 1 - t);
}
