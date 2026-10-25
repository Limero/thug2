// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802157D0-0x802157E8 (24B). Byte-identical.
// extra_cflags: -mps-float
// UNPARKED: r3-clobber asm between pairs reproduces the game's
// "mr r9, r3" dst-pointer copy (game compiler modeled PS ops as
// clobbering r3). Verified EXACT (one-off script, since removed)
#include "types.h"
void fn_802157D0(__ps_t *arg1, __ps_t *arg2) {
    arg1[0] = arg2[10];
    __asm__("" ::: "r3");
    arg1[1] = arg2[11];
}
