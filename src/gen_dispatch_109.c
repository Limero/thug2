// Auto-generated from tools/gen_dispatch_fns.py
// range 0x801F54B8-0x801F54EC (1 functions). Byte-identical.
#include "types.h"

void fn_801F54B8(void *o) {
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}
