// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8005F098-0x8005F100 (2 functions). Byte-identical.
#include "types.h"

void fn_8005F098(void *o) {
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0xb];
    fp((char *)o + (signed short)((s16 *)t)[0x14]);
}

void fn_8005F0CC(void *o) {
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x13];
    fp((char *)o + (signed short)((s16 *)t)[0x24]);
}
