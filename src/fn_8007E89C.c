// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007E89C-0x8007E8F8 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_803017BC;
extern u32 lbl_800000F8;
s32 OSGetTick(void);
void fn_80120B44(void);
void fn_8007E89C(void) {
    s32 temp_r3;

    temp_r3 = OSGetTick();
    if ((temp_r3 < lbl_803017BC) || ((s32) (temp_r3 - lbl_803017BC) > (s32) (lbl_800000F8 / 240))) {
        lbl_803017BC = temp_r3;
        fn_80120B44();
    }
}
