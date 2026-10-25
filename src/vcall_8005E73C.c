// Auto-generated from tools/gen_vcall_fns.py
// range 0x8005E73C-0x8005E778 (1 function). Byte-identical.
#include "types.h"
void fn_8005E73C(void *o, s16 a0, s16 a1) {
    void **t;
    void (*fp)(void *);
    *(s16 *)((char *)o + 0x2C) = a0;
    *(s16 *)((char *)o + 0x2E) = a1;
    t = *(void ***)((char *)o + 0x4C);
    fp = (void (*)(void *))t[0x24 / 4];
    fp((char *)o + (signed short)((s16 *)t)[0x20 / 2]);
}
