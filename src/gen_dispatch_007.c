// Auto-generated from tools/gen_dispatch_fns.py
// range 0x80058B48-0x80058BB8 (2 functions). Byte-identical.
#include "types.h"

void fn_80058B48(void *o, u32 v) {
    void **t;
    void (*fp)(void *);
    *(u32 *)((char *)o + 0x40) = v;
    t = *(void ***)((char *)o + 0x50);
    fp = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_80058B80(void *o, u32 v) {
    void **t;
    void (*fp)(void *);
    *(u32 *)((char *)o + 0x0) = v;
    t = *(void ***)((char *)o + 0x50);
    fp = (void (*)(void *))t[0x9];
    fp((char *)o + (signed short)((s16 *)t)[0x10]);
}
