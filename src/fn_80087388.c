// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80087388-0x8008741C (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_80296600;
extern f32 lbl_80296604;
extern s32 lbl_803017CC;
extern char lbl_803017D0[];
extern f32 lbl_803017D4;
extern f32 lbl_803017D8;
void fn_8001F03C(s32, s32 *, f32, f32, f32, f32);
void fn_80087388(void) {
    s32 sp8;

    if (lbl_803017CC != 0) {
        sp8 = *(s32 *)&lbl_803017D0;
        fn_8001F03C(4, &sp8, lbl_803017D4, lbl_803017D8, lbl_80296600, lbl_80296604);
        return;
    }
    sp8 = *(s32 *)&lbl_803017D0;
    fn_8001F03C(0, &sp8, 0.0f, 0.0f, 0.0f, 0.0f);
}
