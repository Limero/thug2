// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80036108-0x80036128 (32B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
void fn_80036108(void *arg0, void *arg1, s32 arg2) {
    __ps_t *src = (__ps_t *)arg1;
    register s32 acc __asm__("r5");
    __ps_t p0;

    acc = arg2 * 0x78;
    p0 = src[0];
    acc += (s32)arg0;
    acc += 0x40;
    *(__ps_t *)acc = p0;
    ((__ps_t *)acc)[1] = src[1];
}
