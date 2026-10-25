// Auto-generated from tools/gen_dispatch_fns.py
// range 0x801A386C-0x801A3898 (1 functions). Byte-identical.
#include "types.h"

void fn_801A386C(void *o) {
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x28);
    fp(o);
}
