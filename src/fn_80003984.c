// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80003984-0x80003AE8 (356B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_8028FBFC;
extern f32 lbl_8028FC00;
extern f32 lbl_8028FC04;
extern f32 lbl_8028FC08;
extern f32 lbl_8028FC0C;
extern f32 lbl_8028FC10;
extern f32 lbl_8028FC14;
extern f32 lbl_8028FC18;
extern f32 lbl_8028FC1C;
extern f32 lbl_8028FC20;
extern f32 lbl_8028FC24;
extern f32 lbl_8028FC28;
extern f32 lbl_8028FC2C;
extern f32 lbl_8028FC30;
extern f32 lbl_8028FC34;

f32 atan2f(f32, f32);

f32 fn_80003984(f32 y, f32 x) {
    register f32 ratio __asm__("fr1");
    register f32 t __asm__("fr0");
    register f32 t2 __asm__("fr13");
    f32 poly;
    register f32 c20 __asm__("fr6");
    register f32 c18 __asm__("fr12");
    register f32 c14 __asm__("fr11");
    register f32 c10 __asm__("fr10");
    register f32 c0c __asm__("fr9");
    register f32 c08 __asm__("fr7");
    register f32 c04 __asm__("fr5");
    s32 xneg;
    s32 yneg;

    if (__builtin_fabsf(y) > __builtin_fabsf(x)) {
        return atan2f(y, x);
    }

    xneg = 0;
    yneg = 0;
    if (x < lbl_8028FBFC) {
        x = -x;
        xneg = 1;
    }
    if (y <= lbl_8028FC00) {
        y = -y;
        yneg = 1;
    }

    ratio = y / x;
    {
        register f32 k24 __asm__("fr0");
        k24 = lbl_8028FC24;
        t = (ratio - k24) / (ratio + k24);
    }
    {
        register f32 c1c __asm__("fr8");
        c1c = lbl_8028FC1C;
        c20 = lbl_8028FC20;
        c18 = lbl_8028FC18;
        c14 = lbl_8028FC14;
        c10 = lbl_8028FC10;
        c0c = lbl_8028FC0C;
        c08 = lbl_8028FC08;
        c04 = lbl_8028FC04;
        t2 = t * t;
        poly = t * c20;
        poly = poly * t2 + t * c1c;
        poly = poly * t2 + t * c18;
        poly = poly * t2 + t * c14;
        poly = poly * t2 + t * c10;
        poly = poly * t2 + t * c0c;
        poly = poly * t2 + t * c08;
        poly = poly * t2 + t * c04;
    }

    if (xneg != 0) {
        if (yneg != 0) {
            return (poly + lbl_8028FC28) - lbl_8028FC2C;
        }
        return lbl_8028FC30 - poly;
    }
    if (yneg != 0) {
        return lbl_8028FC34 - poly;
    }
    return poly + lbl_8028FC28;
}
