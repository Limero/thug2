// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FC2FC-0x800FC374 (120B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
s32 fn_800FC2FC(u32 arg0) {
    switch (arg0) {
    case QB_GEOMETRY:
        return 4;
    case QB_UNKNOWN_0xDD42AA66:
    case QB_BOUNDINGBOX:
    case QB_UNKNOWN_0x2BA71070:
        return 1;
    case QB_NONE:
    default:
        return 0;
    }
}
