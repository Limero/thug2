// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8005C6E8-0x8005C71C (1 functions). Byte-identical.
#include "types.h"

void fn_8005C6E8(void *o) {
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x55];
    fp((char *)o + (signed short)((s16 *)t)[0xa8]);
}
