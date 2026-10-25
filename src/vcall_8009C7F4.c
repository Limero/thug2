// Auto-generated from tools/gen_vcall_fns.py
// range 0x8009C7F4-0x8009C838 (1 function). Byte-identical.
#include "types.h"
void fn_8009C7F4(void *o, s32 a0, s32 a1, s32 a2, s32 a3) {
    void **t;
    void (*fp)(void *);
    *(s32 *)((char *)o + 0x28) = a0;
    *(s32 *)((char *)o + 0x30) = a1;
    *(s32 *)((char *)o + 0x34) = a2;
    *(s32 *)((char *)o + 0x2C) = a3;
    t = *(void ***)((char *)o + 0x20);
    fp = (void (*)(void *))t[0x34 / 4];
    fp((char *)o + (signed short)((s16 *)t)[0x30 / 2]);
}
