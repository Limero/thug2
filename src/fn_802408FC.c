// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802408FC-0x8024096C (112B). Byte-identical.
#include "types.h"
extern s32 lbl_803060D4;
extern char lbl_803060C4[];
extern char lbl_803060CC[];
extern void fn_80012098(s32, s32);
void fn_802408FC(void) {
    s32 *base = (s32 *)lbl_803060C4;
    s32 off = lbl_803060D4 * 4;
    s32 elem = *(s32 *)((char *)base + off);
    if (elem != 0) {
        if (((s32 *)lbl_803060CC)[lbl_803060D4] != 0) {
            fn_80012098(elem, 3);
        }
        ((s32 *)base)[lbl_803060D4] = 0;
    }
}
