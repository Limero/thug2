// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8005B488-0x8005B4F0 (2 functions). Byte-identical.
#include "types.h"

void fn_8005B488(void *o) {
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_8005B4BC(void *o) {
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0xd];
    fp((char *)o + (signed short)((s16 *)t)[0x18]);
}
