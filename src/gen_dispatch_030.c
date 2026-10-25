// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8005FD34-0x8005FD68 (1 functions). Byte-identical.
#include "types.h"

void fn_8005FD34(void *o) {
    void **t = *(void ***)((char *)o + 0x50);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}
