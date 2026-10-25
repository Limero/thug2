// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800037F8-0x80003830 (56B). Byte-identical.
#include "types.h"
// FRunFilter @ 0x800037F8
f32 FRunFilter(f32 farg0, f32 farg1, f32 farg2) {
    f32 temp_f3;
    f32 temp_f3_2;

    if (farg0 < farg1) {
        temp_f3_2 = fabs(farg2);
        if ((farg1 - farg0) > temp_f3_2) {
            return farg1 - temp_f3_2;
        }
        
        return farg0;
    }
    temp_f3 = fabs(farg2);
    if ((farg0 - farg1) > temp_f3) {
        return farg1 + temp_f3;
    }
    return farg0;
}
