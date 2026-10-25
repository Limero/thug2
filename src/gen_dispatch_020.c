// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8005EA3C-0x8005EA74 (1 functions). Byte-identical.
#include "types.h"

void fn_8005EA3C(void *o, u32 v) {
    void **t;
    void (*fp)(void *);
    *(u32 *)((char *)o + 0x48) = v;
    t = *(void ***)((char *)o + 0x4C);
    fp = (void (*)(void *))t[0xd];
    fp((char *)o + (signed short)((s16 *)t)[0x18]);
}
