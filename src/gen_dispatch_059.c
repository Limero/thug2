// Auto-generated from tools/gen_dispatch_fns.py
// range 0x800E057C-0x800E05A8 (1 functions). Byte-identical.
#include "types.h"

void fn_800E057C(void *o) {
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x28);
    fp(o);
}
