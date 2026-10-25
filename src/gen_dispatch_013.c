// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8005C36C-0x8005C3A0 (1 functions). Byte-identical.
#include "types.h"

void fn_8005C36C(void *o) {
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x2d];
    fp((char *)o + (signed short)((s16 *)t)[0x58]);
}
