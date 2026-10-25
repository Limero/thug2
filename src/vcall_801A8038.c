// Auto-generated from tools/gen_vcall_fns.py
// range 0x801A8038-0x801A80B0 (1 function). Byte-identical.
#include "types.h"
extern u32 lbl_80305F20;
extern u32 lbl_80305F1C;
void fn_801A8038(void) {
    if (lbl_80305F20 > 1) {
        lbl_80305F20--;
    } else {
        if (lbl_80305F1C) {
            void **t = *(void ***)((char *)lbl_80305F1C + 0x3C);
            void (*fp)(void *, s32) = (void (*)(void *, s32))t[3];
            fp((char *)lbl_80305F1C + (signed short)((s16 *)t)[4], 3);
        }
        lbl_80305F1C = NULL;
        lbl_80305F20 = 0;
    }
}
