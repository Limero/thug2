// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8005F8E8-0x8005F984 (3 functions). Byte-identical.
#include "types.h"

void fn_8005F8E8(void *o) {
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x63];
    fp((char *)o + (signed short)((s16 *)t)[0xc4]);
}

void fn_8005F91C(void *o) {
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x65];
    fp((char *)o + (signed short)((s16 *)t)[0xc8]);
}

void fn_8005F950(void *o) {
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x67];
    fp((char *)o + (signed short)((s16 *)t)[0xcc]);
}
