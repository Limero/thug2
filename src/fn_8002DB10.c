// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002DB10-0x8002DCCC (444B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    char pad0x0[0x18];
    f32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
    s32 f28;
    s32 f2C;
    s32 f30;
} Rng_t;

extern f32 lbl_802918B0;
f32 fn_800144C8(void);

f32 fn_8002DB10(Rng_t *arg0) {
    f32 var_f1 = 0;
    f32 var_f13 = 0;
    f32 var_f0 = 0;

    arg0->f30 = 0;
    if (arg0->f2C == 3) {
        return 0.0f;
    }
    if (arg0->f28 == 0) {
        var_f1 = arg0->f1C + (arg0->f24 * (fn_800144C8() * lbl_802918B0));
        arg0->f30 = var_f1 > arg0->f20;
        if (arg0->f18 == arg0->f20) {
            var_f0 = arg0->f20;
        } else {
            var_f0 = arg0->f18 + (var_f1 - arg0->f20);
            while (var_f0 > arg0->f20) {
                var_f0 = arg0->f18 + (var_f0 - arg0->f20);
            }
        }
        var_f13 = arg0->f20;
    } else if (arg0->f28 == -1) {
        var_f1 = arg0->f1C - (arg0->f24 * (fn_800144C8() * lbl_802918B0));
        arg0->f30 = var_f1 < arg0->f18;
        if (arg0->f18 == arg0->f20) {
            var_f0 = arg0->f20;
        } else {
            var_f0 = arg0->f20 + (var_f1 - arg0->f18);
            while (var_f0 < arg0->f18) {
                var_f0 = arg0->f20 + (var_f0 - arg0->f18);
            }
        }
        var_f13 = arg0->f18;
    }
    if (arg0->f30) {
        if (arg0->f2C == 0) {
            var_f1 = var_f13;
        } else if (arg0->f2C == 2) {
            arg0->f28 = (arg0->f28 == 0) ? -1 : 0;
            var_f1 = var_f13;
        } else if (arg0->f2C == 1) {
            var_f1 = var_f0;
        }
    }
    if (var_f1 < arg0->f18) {
        var_f1 = arg0->f18;
    }
    if (var_f1 > arg0->f20) {
        var_f1 = arg0->f20;
    }
    return var_f1;
}
