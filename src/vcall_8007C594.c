// Auto-generated from tools/gen_vcall_fns.py
// range 0x8007C594-0x8007C5D8 (1 function). Byte-identical.
#include "types.h"
bool fn_8007C594(void *o) {
    if (o) {
        void **t = *(void ***)((char *)o + 0x18);
        void (*fp)(void *, s32) = (void (*)(void *, s32))t[3];
        fp((char *)o + (signed short)((s16 *)t)[4], 3);
    }
    return true;
}
