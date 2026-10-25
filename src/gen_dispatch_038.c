// Auto-generated from tools/gen_dispatch_fns.py
// range 0x800A3A94-0x800A3AC0 (1 functions). Byte-identical.
#include "types.h"

void fn_800A3A94(void *o) {
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}
