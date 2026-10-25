// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801253EC-0x8012543C (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 Mem_Alloc_3(s32);
extern s32 lbl_80303248;
void fn_801253EC(void) {
    s32 *gp;
    s32 *p;
    s32 i;
    s32 fs_t;
    gp = &lbl_80303248;
    fs_t = Mem_Alloc_3(0x4000);
    *gp = fs_t;
    p = (s32 *)(fs_t + 0x3FFC);
    for (i = 0x1000; i != 0; i--) {
        *p = 0;
        p--;
    }
}
