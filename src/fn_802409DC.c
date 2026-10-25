// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802409DC-0x80240A4C (112B). Byte-identical.
#include "types.h"
extern s32 lbl_803060A8;
extern char lbl_80306098[];
extern char lbl_803060A0[];
extern void fn_80012098(s32, s32);
void fn_802409DC(void) {
    s32 *base = (s32 *)lbl_80306098;
    s32 off = lbl_803060A8 * 4;
    s32 elem = *(s32 *)((char *)base + off);
    if (elem != 0) {
        if (((s32 *)lbl_803060A0)[lbl_803060A8] != 0) {
            fn_80012098(elem, 3);
        }
        ((s32 *)base)[lbl_803060A8] = 0;
    }
}
