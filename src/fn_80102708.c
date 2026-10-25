// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80102708-0x80102724 (28B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void fn_80102708(Unk_C7387A53 *arg0, void *arg1) {
    __ps_t *dst = (__ps_t *)((char *)arg0 + 0x10);
    __ps_t *src = (__ps_t *)arg1;
    dst[0] = src[0];
    dst[1] = src[1];
    arg0->unk0xAC = 1;
}
