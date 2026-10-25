// Auto-generated from tools/gen_vcall_fns.py
// range 0x80069F1C-0x80069F54 (1 function). Byte-identical.
#include "types.h"
void fn_80069F1C(void *o, float a0) {
    void **t;
    void (*fp)(void *);
    *(float *)((char *)o + 0x138) = a0;
    t = *(void ***)((char *)o + 0x1B8);
    fp = (void (*)(void *))t[0x3C / 4];
    fp((char *)o + (signed short)((s16 *)t)[0x38 / 2]);
}
