// Auto-generated from tools/gen_vcall_fns.py
// range 0x8019CF94-0x8019D00C (1 function). Byte-identical.
#include "types.h"
extern u32 lbl_80305EE8;
extern u32 lbl_80305EE4;
void fn_8019CF94(void) {
    if (lbl_80305EE8 > 1) {
        lbl_80305EE8--;
    } else {
        if (lbl_80305EE4) {
            void **t = *(void ***)((char *)lbl_80305EE4 + 0x14);
            void (*fp)(void *, s32) = (void (*)(void *, s32))t[3];
            fp((char *)lbl_80305EE4 + (signed short)((s16 *)t)[4], 3);
        }
        lbl_80305EE4 = NULL;
        lbl_80305EE8 = 0;
    }
}
