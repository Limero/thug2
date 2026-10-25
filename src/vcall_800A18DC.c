// Auto-generated from tools/gen_vcall_fns.py
// range 0x800A18DC-0x800A1954 (1 function). Byte-identical.
#include "types.h"
extern u32 lbl_80301A3C;
extern u32 lbl_80301A38;
void fn_800A18DC(void) {
    if (lbl_80301A3C > 1) {
        lbl_80301A3C--;
    } else {
        if (lbl_80301A38) {
            void **t = *(void ***)((char *)lbl_80301A38 + 0x2C);
            void (*fp)(void *, s32) = (void (*)(void *, s32))t[3];
            fp((char *)lbl_80301A38 + (signed short)((s16 *)t)[4], 3);
        }
        lbl_80301A38 = NULL;
        lbl_80301A3C = 0;
    }
}
