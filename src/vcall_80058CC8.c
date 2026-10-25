// Auto-generated from tools/gen_vcall_fns.py
// range 0x80058CC8-0x80058D04 (1 function). Byte-identical.
#include "types.h"
void fn_80058CC8(void *o, float a0, float a1) {
    void **t;
    void (*fp)(void *);
    *(float *)((char *)o + 0xC) = a0;
    *(float *)((char *)o + 0x10) = a1;
    t = *(void ***)((char *)o + 0x50);
    fp = (void (*)(void *))t[0x24 / 4];
    fp((char *)o + (signed short)((s16 *)t)[0x20 / 2]);
}
