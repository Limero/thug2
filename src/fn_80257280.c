// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80257280-0x802572C4 (68B). Byte-identical.
#include "types.h"
extern s32 lbl_803CA340;
extern void fn_80257CC4(s32 arg0, s32 arg1);
extern void fn_8024EBD8(s32 arg0, s32 * arg1);

void Vtable0x8030804C_m16(void *arg0) {
    if (arg0 != 0) {
        s32 g;
        fn_80257CC4(arg0, 0xC88);
        g = lbl_803CA340;
        fn_8024EBD8(g, arg0);
    }
}
