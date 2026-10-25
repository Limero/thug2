// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80014534-0x800145AC (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern u64 lbl_80314328;

u64 fn_800144B4(void);
void *fn_800559A0(void);

void fn_80014534(void) {
    void (*fp)(void);

    lbl_80314328 = fn_800144B4();
    while (lbl_80314328 == fn_800144B4()) {
        fp = (void (*)(void))fn_800559A0();
        if (fp == NULL) {
            continue;
        }
        fp = (void (*)(void))fn_800559A0();
        fp();
    }
}
