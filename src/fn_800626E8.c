// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800626E8-0x80062774 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"

typedef struct { __ps_t lo; __ps_t hi; } V4;

s32 fn_800626E8(void *arg0, void *arg1) {
    volatile V4 sp;
    __ps_t v;
    __ps_t h;
    if (*(s32 *)((char *)arg1 + 0x48) < 0) {
        v = *(__ps_t *)((char *)arg1 + 0x38);
    } else {
        s32 *vp = *(s32 *)((char *)arg1 + 0x50);
        void *self;
        self = (void *)((char *)arg1 + *(s16 *)((char *)vp + 0x68));
        ((void (*)(V4 *, void *))*(s32 *)((char *)vp + 0x6C))(&sp.lo, self);
        *(__ps_t *)((char *)arg1 + 0x38) = sp.lo;
        h = sp.hi;
        *(volatile u32 *)((char *)arg1 + 0x48) = *(u32 *)((char *)arg1 + 0x48) | 0x80000000;
        *(__ps_t *)((char *)arg1 + 0x40) = h;
        v = sp.lo;
    }
    *(__ps_t *)arg0 = v;
    *(__ps_t *)((char *)arg0 + 8) = *(__ps_t *)((char *)arg1 + 0x40);
    __asm__ __volatile__("" ::: "memory");
    return arg0;
}
