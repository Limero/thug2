// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8005EABC-0x8005EAF4 (1 functions). Byte-identical.
#include "types.h"

void fn_8005EABC(void *o, u32 v) {
    void **t;
    void (*fp)(void *);
    *(u32 *)((char *)o + 0x14) = v;
    t = *(void ***)((char *)o + 0x1C);
    fp = (void (*)(void *))t[0xd];
    fp((char *)o + (signed short)((s16 *)t)[0x18]);
}
