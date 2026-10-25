// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80119498-0x80119510 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
s32 fn_80119498(s32 arg0) {
    u32 swv1;
    switch (swv1 = arg0) {                                 
    case QB_STANDARD:
        return 0;
    case QB_LINEAR:
        return 1;
    case QB_EXPONENTIAL:
        return 2;
    case 0xCA64C41:
        return 3;
    default:
        return 0;
    }
}
