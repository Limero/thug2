// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B1550-0x800B15B0 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
s32 fn_800B1550(s32 arg0) {
    u32 swv1;
    switch (swv1 = arg0) {                                 
    case QB_NONE:
        return 0;
    case QB_CAMERA:
        return 1;
    case QB_OBJECT:
        return 2;
    default:
        return 0;
    }
}
