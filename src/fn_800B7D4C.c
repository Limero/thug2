// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B7D4C-0x800B7D94 (72B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
void fn_800B7D4C(void *arg0, void *arg1) {
    __ps_t *mid;
    __ps_t t;
    t = ((__ps_t *)arg1)[0];
    __asm__("" : "=r"(mid) : "r"((__ps_t *)((char *)arg0 + 0x20)));
    ((__ps_t *)((char *)arg0 + 0x20))[0] = t;
    ((__ps_t *)((char *)arg0 + 0x28))[0] = ((__ps_t *)arg1)[1];
    ((__ps_t *)((char *)arg0 + 0x30))[0] = ((__ps_t *)arg1)[2];
    ((__ps_t *)((char *)arg0 + 0x38))[0] = ((__ps_t *)arg1)[3];
    mid[4] = ((__ps_t *)arg1)[4];
    mid[5] = ((__ps_t *)arg1)[5];
    ((__ps_t *)((char *)arg0 + 0x50))[0] = ((__ps_t *)arg1)[6];
    ((__ps_t *)((char *)arg0 + 0x58))[0] = ((__ps_t *)arg1)[7];
}
