// Auto-generated from tools/gen_vcall_fns.py
// range 0x80230C54-0x80230CCC (1 function). Byte-identical.
#include "types.h"
extern u32 lbl_80305FFC;
extern u32 lbl_80305FF8;
void fn_80230C54(void) {
    if (lbl_80305FFC > 1) {
        lbl_80305FFC--;
    } else {
        if (lbl_80305FF8) {
            void **t = *(void ***)((char *)lbl_80305FF8 + 0x14);
            void (*fp)(void *, s32) = (void (*)(void *, s32))t[3];
            fp((char *)lbl_80305FF8 + (signed short)((s16 *)t)[4], 3);
        }
        lbl_80305FF8 = NULL;
        lbl_80305FFC = 0;
    }
}
