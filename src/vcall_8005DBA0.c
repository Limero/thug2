// Auto-generated from tools/gen_vcall_fns.py
// range 0x8005DBA0-0x8005DBDC (1 function). Byte-identical.
#include "types.h"
void fn_8005DBA0(void *o, s32 a0, s32 a1) {
    void **t;
    void (*fp)(void *);
    *(s32 *)((char *)o + 0x8) = a0;
    *(s32 *)((char *)o + 0xC) = a1;
    t = *(void ***)((char *)o + 0x14);
    fp = (void (*)(void *))t[0x14 / 4];
    fp((char *)o + (signed short)((s16 *)t)[0x10 / 2]);
}
