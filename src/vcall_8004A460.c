// Auto-generated from tools/gen_vcall_fns.py
// range 0x8004A460-0x8004A4D8 (1 function). Byte-identical.
#include "types.h"
extern u32 lbl_80300438;
extern u32 lbl_80300434;
void fn_8004A460(void) {
    if (lbl_80300438 > 1) {
        lbl_80300438--;
    } else {
        if (lbl_80300434) {
            void **t = *(void ***)((char *)lbl_80300434 + 0x2C);
            void (*fp)(void *, s32) = (void (*)(void *, s32))t[3];
            fp((char *)lbl_80300434 + (signed short)((s16 *)t)[4], 3);
        }
        lbl_80300434 = NULL;
        lbl_80300438 = 0;
    }
}
