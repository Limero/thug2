// Auto-generated from tools/gen_dispatch_fns.py
// range 0x8023515C-0x80235188 (1 functions). Byte-identical.
#include "types.h"

void fn_8023515C(void *o) {
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x28);
    fp(o);
}
