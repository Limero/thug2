// Auto-generated from tools/gen_dispatch_fns.py
// range 0x800F3564-0x800F3590 (1 functions). Byte-identical.
#include "types.h"

void fn_800F3564(void *o) {
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}
