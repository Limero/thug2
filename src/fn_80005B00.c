// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80005B00-0x80005B74 (116B). Byte-identical.
#include "types.h"

f32 fn_80005B00(f32 *arg0, s32 *arg1) {
    s32 sp8;
    s32 *out;
    f32 ax, ay, az;

    out = arg1;
    if (out == NULL) {
        out = &sp8;
    }
    *out = 0;

    ay = fabs(arg0[1]);
    ax = fabs(arg0[0]);
    if (ay > ax) {
        az = fabs(arg0[2]);
        if (az > ay) {
            *out = 2;
        } else {
            *out = 1;
        }
    } else {
        az = fabs(arg0[2]);
        if (az > ax) {
            *out = 2;
        }
    }

    return arg0[*out];
}
