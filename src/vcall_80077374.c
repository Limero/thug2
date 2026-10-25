// Auto-generated from tools/gen_vcall_fns.py
// range 0x80077374-0x800773B8 (1 function). Byte-identical.
#include "types.h"
bool fn_80077374(void *o) {
    if (o) {
        void **t = *(void ***)((char *)o + 0x4C);
        void (*fp)(void *, s32) = (void (*)(void *, s32))t[3];
        fp((char *)o + (signed short)((s16 *)t)[4], 3);
    }
    return true;
}
