// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8019E544-0x8019E570 (1 functions). Byte-identical.
#include "types.h"

void fn_8019E544(void *o) {
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}
