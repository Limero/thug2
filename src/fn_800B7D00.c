// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B7D00-0x800B7D4C (76B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void fn_800B7D00(Unk_C7387A53 *arg0) {
    __ps_t *dst;
    __ps_t *mid;
    __ps_t t;
    t = ((__ps_t *)((char *)arg0 + 0x20))[0];
    __asm__("" : "=r"(mid) : "r"((__ps_t *)((char *)arg0 + 0x20)));
    dst = (__ps_t *)arg0->unk0xC;
    dst[26] = t;
    dst[27] = ((__ps_t *)((char *)arg0 + 0x28))[0];
    dst[28] = ((__ps_t *)((char *)arg0 + 0x30))[0];
    dst[29] = ((__ps_t *)((char *)arg0 + 0x38))[0];
    dst[30] = mid[4];
    dst[31] = mid[5];
    dst[32] = ((__ps_t *)((char *)arg0 + 0x50))[0];
    dst[33] = ((__ps_t *)((char *)arg0 + 0x58))[0];
}
