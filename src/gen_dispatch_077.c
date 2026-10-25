// Auto-generated from tools/gen_dispatch_fns.py
// range 0x80177428-0x80177454 (1 functions). Byte-identical.
#include "types.h"

void fn_80177428(void *o) {
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}
