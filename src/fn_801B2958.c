// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B2958-0x801B2978 (32B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
bool fn_801B2958(Unk_C7387A53 *arg0) {
    __ps_t *src = (__ps_t *)((char *)*((void * *)&arg0->unk0xC) + 0x58);
    __ps_t *dst = (__ps_t *)((char *)arg0 + 0xC0);

    dst[0] = src[0];
    dst[1] = src[1];
    return true;
}
