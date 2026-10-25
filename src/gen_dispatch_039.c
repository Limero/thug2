// Auto-generated from tools/gen_dispatch_fns.py
// range 0x800A3D34-0x800A3D68 (1 functions). Byte-identical.
#include "types.h"

void fn_800A3D34(void *o) {
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x5];
    fp((char *)o + (signed short)((s16 *)t)[0x8]);
}
