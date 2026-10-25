// Auto-generated from tools/gen_dispatch_fns.py
// range 0x801A0CF0-0x801A0D1C (1 functions). Byte-identical.
#include "types.h"

void fn_801A0CF0(void *o) {
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x28);
    fp(o);
}
