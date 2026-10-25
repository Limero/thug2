// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80259D58-0x80259D9C (68B). Byte-identical.
#include "types.h"
extern s32 lbl_803CA340;
extern void fn_80257CC4(void *dst, s32 n);
extern void fn_8024EBD8(void *heap, s32 * ptr);

void Vtable0x803084AC_m2(void *arg0) {
    s32 heap;
    if (arg0 != 0) {
        fn_80257CC4(arg0, 0x448);
        heap = lbl_803CA340;
        fn_8024EBD8(heap, arg0);
    }
}
