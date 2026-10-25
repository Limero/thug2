// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DED38-0x800DED50 (24B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

void fn_800DED38(void *arg0) {
    __ps_t *src = (__ps_t *)(*(char **)((char *)arg0 + 0xc) + 88);
    __ps_t *dst = (__ps_t *)((char *)arg0 + 32);

    dst[0] = src[0];
    dst[1] = src[1];
}
