// Auto-generated from tools/gen_vcall_fns.py
// range 0x8005E700-0x8005E73C (1 function). Byte-identical.
#include "types.h"
void fn_8005E700(void *o, float a0, float a1) {
    void **t;
    void (*fp)(void *);
    *(float *)((char *)o + 0x8) = a0;
    *(float *)((char *)o + 0xC) = a1;
    t = *(void ***)((char *)o + 0x4C);
    fp = (void (*)(void *))t[0x24 / 4];
    fp((char *)o + (signed short)((s16 *)t)[0x20 / 2]);
}
