// Auto-generated from tools/gen_vcall_fns.py
// range 0x80058D40-0x80058D80 (1 function). Byte-identical.
#include "types.h"
void fn_80058D40(void *o, float a0, float a1, float a2) {
    void **t;
    void (*fp)(void *);
    *(float *)((char *)o + 0x24) = a0;
    *(float *)((char *)o + 0x14) = a1;
    *(float *)((char *)o + 0x18) = a2;
    t = *(void ***)((char *)o + 0x50);
    fp = (void (*)(void *))t[9];
    fp((char *)o + (signed short)((s16 *)t)[0x10]);
}
