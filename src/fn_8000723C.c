// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000723C-0x80007264 (40B). Byte-identical.
// extra_cflags: -mps-float
// UNPARKED: r3-clobber asm between pairs reproduces the game's
// "mr r9, r3" dst-pointer copy (game compiler modeled PS ops as
// clobbering r3). Verified EXACT (one-off script, since removed)
#include "types.h"
void fn_8000723C(__ps_t *arg1, __ps_t *arg2) {
    arg1[0] = arg2[0];
    __asm__("" ::: "r3");
    arg1[1] = arg2[1];
    arg1[2] = arg2[0];
    arg1[3] = arg2[1];
}
