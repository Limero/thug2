// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CE380-0x801CE3E4 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern s32 fn_801D60F4(void *, Unk_5EF41E38 *);
bool fn_801CE380(void *arg0) {
    __ps_t sp8[2];
    __ps_t *src;
    __ps_t *dst;
    __ps_t *out;

    dst = (__ps_t *)arg0;
    out = sp8;
    src = *((__ps_t * *)&((Unk_C7387A53 *)dst)->unk0xC);
    dst[12] = src[17];
    dst[13] = src[18];
    dst[14] = src[17];
    dst[15] = src[18];
    out[0] = dst[41];
    out[1] = dst[42];
    fn_801D60F4(arg0, out);
    return true;
}
