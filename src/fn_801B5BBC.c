// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B5BBC-0x801B5BF8 (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void fn_801B5BBC(Unk_C7387A53 *arg0) {
    __ps_t *src = (__ps_t *)((char *)arg0 + 0x198);
    __ps_t *o;
    s32 i;

    for (i = 0; i < 4; i++) {
        src[-2] = src[0];
        src[-1] = src[1];
        src += 2;
    }
    o = *((__ps_t * *)&arg0->unk0xC);
    ((__ps_t *)((char *)arg0 + 0x1C8))[0] = o[11];
    ((__ps_t *)((char *)arg0 + 0x1D0))[0] = o[12];
}
