// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8019E510-0x8019E53C (1 functions). Byte-identical.
#include "types.h"

void fn_8019E510(void *o) {
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x28);
    fp(o);
}
