// Auto-generated from tools/gen_dispatch_fns.py
// range 0x802231D0-0x802231FC (1 functions). Byte-identical.
#include "types.h"

void fn_802231D0(void *o) {
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}
