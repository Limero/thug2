// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002B920-0x8002BA5C (316B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_8002B920(s32 *arg0, f32 farg0, f32 farg1, s32 arg3) {
    s32 result;
    f32 v;

    if (arg3 != 0) {
        if (farg0 < farg1) {
            result = 0;
            v = (f32)*(s32 *)arg0;
            if (v >= farg0) {
                if (v <= farg1) {
                    result = 1;
                }
            }
        } else {
            result = 0;
            v = (f32)*(s32 *)arg0;
            if (v <= farg0) {
                if (v >= farg1) {
                    result = 1;
                }
            }
        }
    } else {
        if (farg0 < farg1) {
            result = 0;
            v = (f32)*(s32 *)arg0;
            if (v >= farg0) {
                if (v < farg1) {
                    result = 1;
                }
            }
        } else {
            result = 0;
            v = (f32)*(s32 *)arg0;
            if (v <= farg0) {
                if (v > farg1) {
                    result = 1;
                }
            }
        }
    }
    return result;
}
