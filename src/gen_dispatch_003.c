// Auto-generated from tools/gen_dispatch_fns.py
// range 0x80035A64-0x80035A98 (1 functions). Byte-identical.
#include "types.h"

void fn_80035A64(void *o) {
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0xb];
    fp((char *)o + (signed short)((s16 *)t)[0x14]);
}
