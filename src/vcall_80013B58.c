// Auto-generated from tools/gen_vcall_fns.py
// range 0x80013B58-0x80013BD0 (1 function). Byte-identical.
#include "types.h"
extern u32 lbl_802FFF28;
extern u32 lbl_802FFF24;
void fn_80013B58(void) {
    if (lbl_802FFF28 > 1) {
        lbl_802FFF28--;
    } else {
        if (lbl_802FFF24) {
            void **t = *(void ***)((char *)lbl_802FFF24 + 0x14);
            void (*fp)(void *, s32) = (void (*)(void *, s32))t[3];
            fp((char *)lbl_802FFF24 + (signed short)((s16 *)t)[4], 3);
        }
        lbl_802FFF24 = NULL;
        lbl_802FFF28 = 0;
    }
}
