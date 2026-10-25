// Auto-generated from tools/gen_dispatch_fns.py
// range 0x800DCFF0-0x800DD024 (1 functions). Byte-identical.
#include "types.h"

void fn_800DCFF0(void *o) {
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x5];
    fp((char *)o + (signed short)((s16 *)t)[0x8]);
}
