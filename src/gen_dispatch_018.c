// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8005E6C8-0x8005E700 (1 functions). Byte-identical.
#include "types.h"

void fn_8005E6C8(void *o, u32 v) {
    void **t;
    void (*fp)(void *);
    *(u32 *)((char *)o + 0x4) = v;
    t = *(void ***)((char *)o + 0x4C);
    fp = (void (*)(void *))t[0x9];
    fp((char *)o + (signed short)((s16 *)t)[0x10]);
}
