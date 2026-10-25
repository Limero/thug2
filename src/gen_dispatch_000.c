// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8000BEB8-0x8000BEE4 (1 functions). Byte-identical.
#include "types.h"

void fn_8000BEB8(void *o) {
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}
