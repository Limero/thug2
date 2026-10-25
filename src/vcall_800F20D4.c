// Auto-generated from tools/gen_vcall_fns.py
// range 0x800F20D4-0x800F214C (1 function). Byte-identical.
#include "types.h"
extern u32 lbl_80301B4C;
extern u32 lbl_80301B48;
void fn_800F20D4(void) {
    if (lbl_80301B4C > 1) {
        lbl_80301B4C--;
    } else {
        if (lbl_80301B48) {
            void **t = *(void ***)((char *)lbl_80301B48 + 0x14);
            void (*fp)(void *, s32) = (void (*)(void *, s32))t[3];
            fp((char *)lbl_80301B48 + (signed short)((s16 *)t)[4], 3);
        }
        lbl_80301B48 = NULL;
        lbl_80301B4C = 0;
    }
}
