// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80126310-0x801263A0 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern s32 lbl_802FFE54;
extern void *lbl_80303258;
extern s8 *lbl_8030325C;
extern void *lbl_80303260;

void *Mem_Alloc_3(s32);

void AllocateChecksumNameLookupTables(void) {
    s32 *p;
    u32 i;

    if (lbl_802FFE54 == 0) {
        return;
    }
    lbl_80303258 = Mem_Alloc_3(0x500000);
    lbl_8030325C = Mem_Alloc_3(5000000);
    lbl_80303260 = lbl_8030325C;
    p = lbl_80303258;
    for (i = 0xA0000; i != 0; i--) {
        p[0] = 0;
        p[1] = 0;
        p += 2;
    }
    *lbl_8030325C = 0;
}
