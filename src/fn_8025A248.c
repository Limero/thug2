// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025A248-0x8025A258 (16B). Byte-identical.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
struct NsCtx { char _0[0x6EC]; s32 flag6EC; };
register struct NsCtx *gctx __asm__("r31");

bool fn_8025A248(void) {
    register s32 z __asm__("r6");
    z = 0;
    gctx->flag6EC = z;
    __asm__ volatile("" ::: "memory");
    return false;
}
