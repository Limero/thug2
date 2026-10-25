// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802712CC-0x802712F0 (36B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
u32 fn_802712CC(f64 farg0) {
    union { f64 d; s32 w[2]; } u;

    u.d = farg0;
    return ((u32)(u.w[0] & QB_UNKNOWN_0x7FFFFFFF) + 0x80100000) >> 0x1FU;
}
