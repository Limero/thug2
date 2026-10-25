// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023EF44-0x8023EF88 (68B). Byte-identical.
#include "types.h"
void *fn_8023EF44(void *arg0) {
    volatile s32 *p = (volatile s32 *)(char *)arg0;
    p[2] = 0;
    p[1] = 0;
    p[3] = 0;
    p[0] = (s32)fn_80238964();
    return arg0;
}
