// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8009D3A4-0x8009D3D0 (1 functions). Byte-identical.
#include "types.h"

void fn_8009D3A4(void *o) {
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}
