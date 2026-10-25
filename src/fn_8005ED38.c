// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005ED38-0x8005ED88 (80B). Byte-identical.
#include "types.h"
extern bool lbl_803664E0;
extern char lbl_803664C0[];
void fn_800071D4(s32);
s32 fn_8005ED38(void) {
    if (lbl_803664E0 == 0) {
        fn_800071D4((s32)lbl_803664C0);
        lbl_803664E0 = 1;
    }
    return (s32)lbl_803664C0;
}
