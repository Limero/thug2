// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8022319C-0x802231C8 (1 functions). Byte-identical.
#include "types.h"

void fn_8022319C(void *o) {
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x28);
    fp(o);
}
