// Auto-generated from tools/gen_dispatch_fns.py
// range 0x800A2184-0x800A21B0 (1 functions). Byte-identical.
#include "types.h"

void fn_800A2184(void *o) {
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}
