// Auto-generated from tools/gen_dispatch_fns.py
// range 0x800585B4-0x80058684 (4 functions). Byte-identical.
#include "types.h"

void fn_800585B4(void *o) {
    void **t = *(void ***)((char *)o + 0x4);
    void (*fp)(void *) = (void (*)(void *))t[0x5];
    fp((char *)o + (signed short)((s16 *)t)[0x8]);
}

void fn_800585E8(void *o) {
    void **t = *(void ***)((char *)o + 0x4);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_8005861C(void *o) {
    void **t = *(void ***)((char *)o + 0x4);
    void (*fp)(void *) = (void (*)(void *))t[0x9];
    fp((char *)o + (signed short)((s16 *)t)[0x10]);
}

void fn_80058650(void *o) {
    void **t = *(void ***)((char *)o + 0x4);
    void (*fp)(void *) = (void (*)(void *))t[0xb];
    fp((char *)o + (signed short)((s16 *)t)[0x14]);
}
