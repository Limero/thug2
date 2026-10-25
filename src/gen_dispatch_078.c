// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8018F4E0-0x8018F514 (1 functions). Byte-identical.
#include "types.h"

void fn_8018F4E0(void *o) {
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x9];
    fp((char *)o + (signed short)((s16 *)t)[0x10]);
}
