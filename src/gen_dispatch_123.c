// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8020651C-0x80206554 (1 functions). Byte-identical.
#include "types.h"

void fn_8020651C(void *o) {
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *, int) = (void (*)(void *, int))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20], 1);
}
