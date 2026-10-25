// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8005EBE4-0x8005EC1C (1 functions). Byte-identical.
#include "types.h"

void fn_8005EBE4(void *o, u32 v) {
    void **t;
    void (*fp)(void *);
    *(u32 *)((char *)o + 0x4) = v;
    t = *(void ***)((char *)o + 0x1C);
    fp = (void (*)(void *))t[0xd];
    fp((char *)o + (signed short)((s16 *)t)[0x18]);
}
