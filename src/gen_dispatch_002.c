// Auto-generated from tools/gen_dispatch_fns.py
// range 0x80024344-0x80024378 (1 functions). Byte-identical.
#include "types.h"

void fn_80024344(void *o) {
    void **t = *(void ***)((char *)o + 0x24);
    void (*fp)(void *) = (void (*)(void *))t[0x5];
    fp((char *)o + (signed short)((s16 *)t)[0x8]);
}
