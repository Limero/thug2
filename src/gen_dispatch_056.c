// Auto-generated from tools/gen_dispatch_fns.py
// range 0x800DEC28-0x800DEC5C (1 functions). Byte-identical.
#include "types.h"

void fn_800DEC28(void *o) {
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}
