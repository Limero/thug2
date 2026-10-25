// Auto-generated from tools/gen_dispatch_fns.py
// range 0x800EF21C-0x800EF288 (2 functions). Byte-identical.
#include "types.h"

void fn_800EF21C(void *o) {
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800EF250(void *o) {
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *, int) = (void (*)(void *, int))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20], 1);
}
