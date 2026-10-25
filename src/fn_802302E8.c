// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802302E8-0x80230308 (32B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
void fn_802302E8(void *arg0, void *arg1, s32 arg2) {
    __ps_t *src = (__ps_t *)arg1;
    register s32 acc __asm__("r5");
    __ps_t p0;

    acc = arg2 << 4;
    p0 = src[0];
    acc += (s32)arg0;
    acc += 0x390;
    *(__ps_t *)acc = p0;
    ((__ps_t *)acc)[1] = src[1];
}
