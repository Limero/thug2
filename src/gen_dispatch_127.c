// Auto-generated from tools/gen_dispatch_fns.py
// range 0x80223204-0x80223230 (1 functions). Byte-identical.
#include "types.h"

void fn_80223204(void *o) {
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}
