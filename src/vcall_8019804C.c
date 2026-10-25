// Auto-generated from tools/gen_vcall_fns.py
// range 0x8019804C-0x801980C4 (1 function). Byte-identical.
#include "types.h"
extern u32 lbl_80305EC4;
extern u32 lbl_80305EC0;
void fn_8019804C(void) {
    if (lbl_80305EC4 > 1) {
        lbl_80305EC4--;
    } else {
        if (lbl_80305EC0) {
            void **t = *(void ***)((char *)lbl_80305EC0 + 0x24);
            void (*fp)(void *, s32) = (void (*)(void *, s32))t[3];
            fp((char *)lbl_80305EC0 + (signed short)((s16 *)t)[4], 3);
        }
        lbl_80305EC0 = NULL;
        lbl_80305EC4 = 0;
    }
}
