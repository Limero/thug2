// Auto-generated from tools/gen_dispatch_fns.py
// range 0x80138DF0-0x80138E1C (1 functions). Byte-identical.
#include "types.h"

void fn_80138DF0(void *o) {
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}
