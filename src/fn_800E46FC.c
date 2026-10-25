// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E46FC-0x800E4750 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern void GetVector(void *arg0, u32 hash, void *out, s32 flag);

void fn_800E46FC(void *arg0, void *arg1) {
    f32 sp8[4];
    char *p;

    GetVector(arg1, QB_VEL, sp8, 1);
    p = *(char **)((char *)arg0 + 0xc);
    ((__ps_t *)(p + 0xB8))[0] = ((__ps_t *)sp8)[0];
    ((__ps_t *)(p + 0xB8))[1] = ((__ps_t *)sp8)[1];
}
