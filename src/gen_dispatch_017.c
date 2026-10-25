// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8005E628-0x8005E660 (1 functions). Byte-identical.
#include "types.h"

void fn_8005E628(void *o, u32 v) {
    void **t;
    void (*fp)(void *);
    *(u32 *)((char *)o + 0x30) = v;
    t = *(void ***)((char *)o + 0x4C);
    fp = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}
