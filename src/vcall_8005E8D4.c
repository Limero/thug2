// Auto-generated from tools/gen_vcall_fns.py
// range 0x8005E8D4-0x8005E910 (1 function). Byte-identical.
#include "types.h"
void fn_8005E8D4(void *o, float a0, float a1) {
    void **t;
    void (*fp)(void *);
    *(float *)((char *)o + 0x18) = a0;
    *(float *)((char *)o + 0x1C) = a1;
    t = *(void ***)((char *)o + 0x4C);
    fp = (void (*)(void *))t[0x24 / 4];
    fp((char *)o + (signed short)((s16 *)t)[0x20 / 2]);
}
