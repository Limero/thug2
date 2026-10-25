// Auto-generated from tools/gen_vcall_fns.py
// range 0x80172A18-0x80172A90 (1 function). Byte-identical.
#include "types.h"
extern u32 lbl_80305EB0;
extern u32 lbl_80305EAC;
void fn_80172A18(void) {
    if (lbl_80305EB0 > 1) {
        lbl_80305EB0--;
    } else {
        if (lbl_80305EAC) {
            void **t = *(void ***)((char *)lbl_80305EAC + 0x14);
            void (*fp)(void *, s32) = (void (*)(void *, s32))t[3];
            fp((char *)lbl_80305EAC + (signed short)((s16 *)t)[4], 3);
        }
        lbl_80305EAC = NULL;
        lbl_80305EB0 = 0;
    }
}
