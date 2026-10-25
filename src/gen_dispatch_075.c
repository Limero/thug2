// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8016D214-0x8016D240 (1 functions). Byte-identical.
#include "types.h"

void fn_8016D214(void *o) {
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x28);
    fp(o);
}
