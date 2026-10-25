// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8005C5BC-0x8005C6C0 (5 functions). Byte-identical.
#include "types.h"

void fn_8005C5BC(void *o) {
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x45];
    fp((char *)o + (signed short)((s16 *)t)[0x88]);
}

void fn_8005C5F0(void *o) {
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x47];
    fp((char *)o + (signed short)((s16 *)t)[0x8c]);
}

void fn_8005C624(void *o) {
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x4b];
    fp((char *)o + (signed short)((s16 *)t)[0x94]);
}

void fn_8005C658(void *o) {
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x4d];
    fp((char *)o + (signed short)((s16 *)t)[0x98]);
}

void fn_8005C68C(void *o) {
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x4f];
    fp((char *)o + (signed short)((s16 *)t)[0x9c]);
}
