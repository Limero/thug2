// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012516C-0x801251B4 (72B). Byte-identical.
#include "types.h"
extern bool lbl_80303184;
extern s32 lbl_80303194;
void Mem_Free_3(s32);
// UseRegularStringHeap @ 0x8012516C
void UseRegularStringHeap(void) {
    lbl_80303184 = 0;
    if (lbl_80303194 != 0) {
        Mem_Free_3(lbl_80303194);
        lbl_80303194 = 0;
    }
}
