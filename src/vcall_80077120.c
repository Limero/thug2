// Auto-generated from tools/gen_vcall_fns.py
// range 0x80077120-0x80077164 (1 function). Byte-identical.
#include "types.h"
bool fn_80077120(void *o) {
    if (o) {
        void **t = *(void ***)((char *)o + 0x50);
        void (*fp)(void *, s32) = (void (*)(void *, s32))t[3];
        fp((char *)o + (signed short)((s16 *)t)[4], 3);
    }
    return true;
}
