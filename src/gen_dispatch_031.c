// Auto-generated from tools/gen_dispatch_fns.py
// range 0x80070244-0x800702E0 (3 functions). Byte-identical.
#include "types.h"

void fn_80070244(void *o) {
    void **t = *(void ***)((char *)o + 0x5C);
    void (*fp)(void *) = (void (*)(void *))t[0x5];
    fp((char *)o + (signed short)((s16 *)t)[0x8]);
}

void fn_80070278(void *o) {
    void **t = *(void ***)((char *)o + 0x5C);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800702AC(void *o) {
    void **t = *(void ***)((char *)o + 0x5C);
    void (*fp)(void *) = (void (*)(void *))t[0x9];
    fp((char *)o + (signed short)((s16 *)t)[0x10]);
}
