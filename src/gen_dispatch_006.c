// Auto-generated from tools/gen_dispatch_fns.py
// range 0x800586CC-0x80058700 (1 functions). Byte-identical.
#include "types.h"

void fn_800586CC(void *o) {
    void **t = *(void ***)((char *)o + 0x4);
    void (*fp)(void *) = (void (*)(void *))t[0x13];
    fp((char *)o + (signed short)((s16 *)t)[0x24]);
}
