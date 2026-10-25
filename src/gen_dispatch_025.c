// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8005F188-0x8005F28C (5 functions). Byte-identical.
#include "types.h"

void fn_8005F188(void *o) {
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x19];
    fp((char *)o + (signed short)((s16 *)t)[0x30]);
}

void fn_8005F1BC(void *o) {
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x1b];
    fp((char *)o + (signed short)((s16 *)t)[0x34]);
}

void fn_8005F1F0(void *o) {
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x1d];
    fp((char *)o + (signed short)((s16 *)t)[0x38]);
}

void fn_8005F224(void *o) {
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x1f];
    fp((char *)o + (signed short)((s16 *)t)[0x3c]);
}

void fn_8005F258(void *o) {
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x21];
    fp((char *)o + (signed short)((s16 *)t)[0x40]);
}
