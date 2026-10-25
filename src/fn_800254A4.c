// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800254A4-0x800254EC (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

void fn_800254A4(void *arg0, __ps_t *arg1) {
    __ps_t *dst = (__ps_t *)((char *)arg0 + 0x10);
    __ps_t *dst2 = (__ps_t *)((char *)dst + 0x10);

    dst[0] = arg1[0];
    dst[1] = arg1[1];
    dst2[0] = arg1[2];
    dst2[1] = arg1[3];
    dst[4] = arg1[4];
    dst[5] = arg1[5];
    dst[6] = arg1[6];
    dst[7] = arg1[7];
}
