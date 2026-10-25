// Auto-generated from tools/gen_vcall_fns.py
// range 0x801342D0-0x80134348 (1 function). Byte-identical.
#include "types.h"
extern u32 lbl_80303430;
extern u32 lbl_8030342C;
void fn_801342D0(void) {
    if (lbl_80303430 > 1) {
        lbl_80303430--;
    } else {
        if (lbl_8030342C) {
            void **t = *(void ***)((char *)lbl_8030342C + 0x14);
            void (*fp)(void *, s32) = (void (*)(void *, s32))t[3];
            fp((char *)lbl_8030342C + (signed short)((s16 *)t)[4], 3);
        }
        lbl_8030342C = NULL;
        lbl_80303430 = 0;
    }
}
