// Auto-generated from tools/gen_dispatch_fns.py
// range 0x800DB978-0x800DB9A4 (1 functions). Byte-identical.
#include "types.h"

void fn_800DB978(void *o) {
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}
