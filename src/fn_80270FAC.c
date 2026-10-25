// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80270FAC-0x80271070 (196B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G8
// fdlibm float frexp-style helper: exponent extraction/masking with the
// lbl_803CA73C/40 constants. Suggested rename: fn_80270FAC_float_exp_split.
#include "types.h"
#include "qb_constants.h"
extern f32 lbl_803CA73C;
extern f32 lbl_803CA740;

f32 fn_80270FAC(f32 x) {
    volatile f32 t;
    register f32 y __asm__("fr0");
    register f32 r __asm__("fr0");
    register f32 c2 __asm__("fr13");
    register s32 b __asm__("r11");
    register u32 tu __asm__("r0");
    s32 e;
    s32 mask;

    y = x;
    t = y;
    tu = *(u32 *)&t;
    __asm__("mr %0,%1" : "=r"(b) : "r"(tu));
    e = (s32)(((u32)b >> 23) & 0xFFu) - 127;
    if (e > 22) {
        goto big;
    }
    if (e < 0) {
        if (x + lbl_803CA73C > (c2 = lbl_803CA740)) {
            if (b < 0) {
                b = (s32)0x80000000;
            } else if (b != 0) {
                b = QB_UNKNOWN_0x3F800000;
            }
        }
        goto store;
    }
    mask = 0x7FFFFF >> e;
    if ((b & mask) != 0) {
        if (x + lbl_803CA73C > (c2 = lbl_803CA740)) {
            if (b > 0) {
                b += (s32)0x800000 >> e;
            }
            b &= ~mask;
        }
    } else {
        return x;
    }
    goto store;
big:
    if (e == 128) {
        x += x;
    }
    return x;
store:
    *(s32 *)&t = b;
    r = t;
    return r;
}
