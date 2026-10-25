// Auto-generated from tools/gen_vcall_fns.py
// range 0x8005E898-0x8005E8D4 (1 function). Byte-identical.
#include "types.h"
void fn_8005E898(void *o, s32 a0, s32 a1) {
    void **t;
    void (*fp)(void *);
    *(s32 *)((char *)o + 0x3C) = a0;
    *(s32 *)((char *)o + 0x40) = a1;
    t = *(void ***)((char *)o + 0x4C);
    fp = (void (*)(void *))t[0x24 / 4];
    fp((char *)o + (signed short)((s16 *)t)[0x20 / 2]);
}
