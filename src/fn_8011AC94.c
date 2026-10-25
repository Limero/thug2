// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011AC94-0x8011ADD4 (320B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8029D52C[];
extern char lbl_8029D530[];
extern char lbl_8029D534[];
extern char lbl_8029D538[];
extern char lbl_8029D53C[];
extern char lbl_80302C58[];
extern f32 sinf(f32);

typedef struct {
    f32 f0;
    f32 f1;
    f32 f2;
} T3;

void fn_8011AC94(f32 *unused, f32 farg0, f32 *arg1) {
    volatile double _dummy;
    volatile double _d1;
    volatile double _d2;
    volatile double _d3;
    volatile double _d4;
    f32 v = farg0;
    f32 one;
    f32 period;
    f32 pi;
    f32 half;
    T3 *t;
    s32 p;
    s32 pe;
    f32 a;
    f32 b;
    f32 c;
    f32 r;

    if (v < *(f32 *)lbl_8029D52C) {
        v += *(f32 *)lbl_8029D530;
    }
    one = *(f32 *)lbl_8029D534;
    period = *(f32 *)lbl_8029D530;
    pi = *(f32 *)lbl_8029D538;
    half = *(f32 *)lbl_8029D53C;
    t = (T3 *)lbl_80302C58;
    p = (s32)arg1;
    pe = (s32)arg1 + 0x10;
    do {
        b = t->f1;
        a = t->f0;
        c = t->f2;
        r = *(f32 *)lbl_8029D52C;
        if (b < a) {
            if (v > b) {
                if (v <= a) {
                    r = (v - b) / (a - b);
                    goto out;
                }
            }
            if (v > a) {
                if (v < c) {
                    r = one - (v - a) / (c - a);
                }
            }
        } else {
            if (v > b) {
                r = (v - b) / (period - b);
            } else if (v < c) {
                r = (c - v) / c;
            }
        }
    out:
        t += 1;
        *(f32 *)p = sinf(r * pi * half);
        p += 4;
    } while (p <= pe);
}
