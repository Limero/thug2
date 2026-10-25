// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80037BF0-0x80037C40 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"

s32 fn_80036328(void *arg0, s32 arg1);

s32 fn_80037BF0(void *arg2, s32 arg0, void *arg1) {
    s32 r = fn_80036328(arg2, arg0);

    if (r != 0) {
        *(__ps_t *)((char *)arg1 + 0) = *(__ps_t *)((char *)r + 16);
        *(__ps_t *)((char *)arg1 + 8) = *(__ps_t *)((char *)r + 24);
    }
    return r != 0;
}
