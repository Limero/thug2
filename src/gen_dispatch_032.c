// Auto-generated from tools/gen_dispatch_fns.py
// range 0x80070B40-0x80070BA8 (2 functions). Byte-identical.
#include "types.h"

void fn_80070B40(void *o) {
    void **t = *(void ***)((char *)o + 0x20);
    void (*fp)(void *) = (void (*)(void *))t[0x5];
    fp((char *)o + (signed short)((s16 *)t)[0x8]);
}

void fn_80070B74(void *o) {
    void **t = *(void ***)((char *)o + 0x20);
    void (*fp)(void *) = (void (*)(void *))t[0x9];
    fp((char *)o + (signed short)((s16 *)t)[0x10]);
}
