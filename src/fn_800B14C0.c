// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B14C0-0x800B1550 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
s32 fn_800B14C0(s32 arg0) {
    u32 swv1;
    switch (swv1 = arg0) {                                 
    case QB_SPHERE:
        return 0;
    case QB_BOUNDINGBOX:
        return 1;
    case 0x3F1E5A7:
        return 2;
    case QB_CYLINDER:
        return 3;
    case QB_GEOMETRY:
        return 4;
    default:
        return 0;
    }
}
