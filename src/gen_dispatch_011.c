// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8005C070-0x8005C174 (5 functions). Byte-identical.
#include "types.h"

void fn_8005C070(void *o) {
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0xb];
    fp((char *)o + (signed short)((s16 *)t)[0x14]);
}

void fn_8005C0A4(void *o) {
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0xd];
    fp((char *)o + (signed short)((s16 *)t)[0x18]);
}

void fn_8005C0D8(void *o) {
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x13];
    fp((char *)o + (signed short)((s16 *)t)[0x24]);
}

void fn_8005C10C(void *o) {
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x15];
    fp((char *)o + (signed short)((s16 *)t)[0x28]);
}

void fn_8005C140(void *o) {
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x17];
    fp((char *)o + (signed short)((s16 *)t)[0x2c]);
}
