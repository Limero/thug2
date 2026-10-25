// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000DB60-0x8000DBC4 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
// FLAG: -fno-schedule-insns
extern u32 lbl_802FFE90;
extern u32 lbl_802FFE8C;
extern void fn_8000D100(Unk_C8FEE62D *, int);
void fn_8000DB60(void) {
    if (lbl_802FFE90 > 1) {
        lbl_802FFE90 = lbl_802FFE90 - 1;
    } else {
        if (lbl_802FFE8C != 0)
            fn_8000D100((void *)lbl_802FFE8C, 3);
        lbl_802FFE90 = 0;
        lbl_802FFE8C = 0;
    }
}