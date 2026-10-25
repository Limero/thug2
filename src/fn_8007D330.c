// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007D330-0x8007D354 (36B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

bool fn_8007D330(void *arg0, s32 arg1, __ps_t *arg2) {
    register s32 q __asm__("r4");
    s32 off = arg1 << 4;

    q = (s32)(char *)(off + (s32)arg0);
    q = q + 0xa0;
    ((__ps_t *)q)[0] = arg2[0];
    ((__ps_t *)q)[1] = arg2[1];
    return true;
}
