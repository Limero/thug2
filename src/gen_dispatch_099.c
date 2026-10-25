// Auto-generated from tools/gen_dispatch_fns.py
// range 0x801EDAD4-0x801EDB08 (1 functions). Byte-identical.
#include "types.h"

void fn_801EDAD4(void *o) {
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}
