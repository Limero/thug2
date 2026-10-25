// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800122C4-0x800122FC (56B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
u32 strlen(const char *);                                  

s32 fn_800122C4(s32 arg0) {
    return arg0 + ((strlen((const char *)arg0) + 0x10) & QB_UNKNOWN_0xFFFFFFF0);
}
