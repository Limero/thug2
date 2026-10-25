// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8020CA70-0x8020CAA4 (1 functions). Byte-identical.
#include "types.h"

void fn_8020CA70(void *o) {
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}
