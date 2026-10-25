// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025A1D0-0x8025A248 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns -fno-schedule-insns2
#include "types.h"
struct NsCtx { char _0[0x6EC]; s32 flag6EC; };
register struct NsCtx *gctx __asm__("r31");

s32 fn_8025A1D0(s32 arg0, s32 arg1, s32 arg2) {
    register s32 z __asm__("r6");
    register s32 a7 __asm__("r6");
    register s32 a8 __asm__("r6");
    s32 *d;
    s32 *s;

    z = 1;
    gctx->flag6EC = z;
    /* MUST stay a C `if`: it is the only CFG edge keeping the byte-copy block
     * alive (see header). The zero-code barrier right after it makes the
     * masked value live on the fall-through edge, which is what keeps the
     * fused `andi.` destination in the pinned r6 instead of the r0 scratch. */
    z = arg0 & 3;
    if (z != 0) {
        goto bytecopy;
    }
    __asm__ volatile("" : "+r"(z));
    {
        s32 m = arg1;
        __asm__ volatile("andi. %0,%1,3\n\tbne 8f" : "=r"(a7) : "r"(m));
    }
    {
        s32 m = arg2;
        __asm__ volatile("andi. %0,%1,3\n\tbne 8f" : "=r"(a8) : "r"(m));
    }
    d = (s32 *)(arg0 - 4);
    s = (s32 *)(arg1 - 4);
    arg2 = arg2 + (s32)s;
    do {
        z = *++s;
        *++d = z;
    } while ((u32)s < (u32)arg2);
    z = 0;
    gctx->flag6EC = z;
    return 1;
bytecopy:
    __asm__("8:");
    {
        char *bd;
        char *bs;
        bd = (char *)arg0 - 1;
        bs = (char *)arg1 - 1;
        arg2 = (s32)((char *)arg2 + (s32)bs);
        do {
            z = *(u8 *)++bs;
            *(u8 *)++bd = z;
        } while ((u32)(long)bs < (u32)(long)arg2);
        z = 0;
        gctx->flag6EC = z;
        return 1;
    }
}
