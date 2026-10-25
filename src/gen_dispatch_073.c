// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8013E27C-0x8013E2B0 (1 functions). Byte-identical.
#include "types.h"

void fn_8013E27C(void *o) {
    void **t = *(void ***)((char *)o + 0x2300);
    void (*fp)(void *) = (void (*)(void *))t[0xd];
    fp((char *)o + (signed short)((s16 *)t)[0x18]);
}
