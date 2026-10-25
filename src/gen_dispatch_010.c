// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8005B560-0x8005B5FC (3 functions). Byte-identical.
#include "types.h"

void fn_8005B560(void *o) {
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20]);
}

void fn_8005B594(void *o) {
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x15];
    fp((char *)o + (signed short)((s16 *)t)[0x28]);
}

void fn_8005B5C8(void *o) {
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x17];
    fp((char *)o + (signed short)((s16 *)t)[0x2c]);
}
