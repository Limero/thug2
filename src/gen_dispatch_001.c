// Auto-generated from tools/gen_dispatch_fns.py
// range 0x80013D44-0x80013D70 (1 functions). Byte-identical.
#include "types.h"

void fn_80013D44(void *o) {
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}
