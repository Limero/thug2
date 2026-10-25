// Auto-generated from tools/gen_dispatch_fns.py
// range 0x80070C78-0x80070CAC (1 functions). Byte-identical.
#include "types.h"

void fn_80070C78(void *o) {
    void **t = *(void ***)((char *)o + 0x20);
    void (*fp)(void *) = (void (*)(void *))t[0x49];
    fp((char *)o + (signed short)((s16 *)t)[0x90]);
}
