// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8005EB6C-0x8005EBA4 (1 functions). Byte-identical.
#include "types.h"

void fn_8005EB6C(void *o, u32 v) {
    void **t;
    void (*fp)(void *);
    *(u32 *)((char *)o + 0x8) = v;
    t = *(void ***)((char *)o + 0x1C);
    fp = (void (*)(void *))t[0xb];
    fp((char *)o + (signed short)((s16 *)t)[0x14]);
}
