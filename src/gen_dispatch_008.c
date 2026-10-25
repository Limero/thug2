// Auto-generated from tools/gen_dispatch_fns.py
// range 0x80058E40-0x80058EB0 (2 functions). Byte-identical.
#include "types.h"

void fn_80058E40(void *o, u32 v) {
    void **t;
    void (*fp)(void *);
    *(u32 *)((char *)o + 0x3C) = v;
    t = *(void ***)((char *)o + 0x50);
    fp = (void (*)(void *))t[0x9];
    fp((char *)o + (signed short)((s16 *)t)[0x10]);
}

void fn_80058E78(void *o, u32 v) {
    void **t;
    void (*fp)(void *);
    *(u32 *)((char *)o + 0x48) = v;
    t = *(void ***)((char *)o + 0x50);
    fp = (void (*)(void *))t[0xd];
    fp((char *)o + (signed short)((s16 *)t)[0x18]);
}
