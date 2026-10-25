// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EEC34-0x800EEC7C (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

void fn_800EEC34(void *arg0) {
    char *p = *(char **)((char *)arg0 + 0xc);
    __ps_t *src = (__ps_t *)(p + 0x78);
    __ps_t *dst = (__ps_t *)(p + 0xD0);

    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    dst[4] = src[4];
    dst[5] = src[5];
    dst[6] = src[6];
    dst[7] = *(__ps_t *)(p + 0xB0);
}
