// Auto-generated from tools/gen_dispatch_fns.py
// range 0x800EF030-0x800EF09C (2 functions). Byte-identical.
#include "types.h"

void fn_800EF030(void *o) {
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800EF064(void *o) {
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *, int) = (void (*)(void *, int))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20], 1);
}
