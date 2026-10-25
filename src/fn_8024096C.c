// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024096C-0x802409DC (112B). Byte-identical.
#include "types.h"
extern s32 lbl_803060C0;
extern char lbl_803060B0[];
extern char lbl_803060B8[];
extern void fn_80012098(s32, s32);
void fn_8024096C(void) {
    s32 *base = (s32 *)lbl_803060B0;
    s32 off = lbl_803060C0 * 4;
    s32 elem = *(s32 *)((char *)base + off);
    if (elem != 0) {
        if (((s32 *)lbl_803060B8)[lbl_803060C0] != 0) {
            fn_80012098(elem, 3);
        }
        ((s32 *)base)[lbl_803060C0] = 0;
    }
}
