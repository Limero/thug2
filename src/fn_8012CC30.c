// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012CC30-0x8012CC68 (56B). Byte-identical.
#include "types.h"
extern s32 lbl_803032B0;
void fn_8012E65C(void);
void fn_8012CC30(s32 arg0, s32 arg1) {
    lbl_803032B0 -= 1;
    if (arg1 & 1) {
        fn_8012E65C();
    }
}
