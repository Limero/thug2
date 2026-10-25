// Auto-generated from tools/gen_vcall_fns.py
// range 0x80069D68-0x80069DA0 (1 function). Byte-identical.
#include "types.h"
void fn_80069D68(void *o, float a0) {
    void **t;
    void (*fp)(void *);
    *(float *)((char *)o + 0x40) = a0;
    t = *(void ***)((char *)o + 0x1B8);
    fp = (void (*)(void *))t[0x3C / 4];
    fp((char *)o + (signed short)((s16 *)t)[0x38 / 2]);
}
