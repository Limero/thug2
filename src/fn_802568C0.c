// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802568C0-0x80256904 (68B). Byte-identical.
#include "types.h"
extern s32 lbl_803CA340;

extern void fn_80257CC4(void *dst, s32 n);
extern void fn_8024EBD8(void *heap, s32 * ptr);

// MATCHED @ 0x802568C0 size=0x44 (byte-exact, reloc-masked)
void Vtable0x8030804C_m2(void *arg0) {
    s32 heap;

    if (arg0 != NULL) {
        fn_80257CC4(arg0, 0x714);
        heap = lbl_803CA340;
        fn_8024EBD8((void *)heap, arg0);
    }
}
