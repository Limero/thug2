// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8005C1B4-0x8005C2B8 (5 functions). Byte-identical.
#include "types.h"

void fn_8005C1B4(void *o) {
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x1d];
    fp((char *)o + (signed short)((s16 *)t)[0x38]);
}

void fn_8005C1E8(void *o) {
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x1f];
    fp((char *)o + (signed short)((s16 *)t)[0x3c]);
}

void fn_8005C21C(void *o) {
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x21];
    fp((char *)o + (signed short)((s16 *)t)[0x40]);
}

void fn_8005C250(void *o) {
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x23];
    fp((char *)o + (signed short)((s16 *)t)[0x44]);
}

void fn_8005C284(void *o) {
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x25];
    fp((char *)o + (signed short)((s16 *)t)[0x48]);
}
