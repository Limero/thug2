// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025DA54-0x8025DAD4 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-gcse
// EXI arena-check + init dispatcher. Four distinct base-term symbols
// (CEE8/ADEE0/gap_AD0E0/DF94) force want's per-site lis re-materialization
// (anchor merge keys on base term); -fno-gcse stops the cross-branch
// PRE hoist of the E0 anchor.
#include "types.h"

extern u8 lbl_803ACEE8[];
extern u8 lbl_803ADEE0[];
extern u8 gap_05_803AD0E0_bss[];
extern u8 lbl_803ADF94[];
void fn_8025D988(void *);
void fn_8025DA10(void);

void fn_8025DA54(s32 arg0) {
    u8 *p;
    s32 aligned = (arg0 + 0x1F) & ~0x1F;
    if (aligned == *(s32 *)(lbl_803ACEE8 - 0x160)) {
        s32 acc = *(s32 *)(lbl_803ADEE0 - 0x115C);
        *(s32 *)(gap_05_803AD0E0_bss - 0x360) = 0;
        acc += aligned;
        p = lbl_803ADF94 - 0x1234;
        *(s32 *)(lbl_803ADEE0 - 0x115C) = acc;
        fn_8025D988(p);
    } else {
        *(s32 *)(lbl_803ADEE0 - 0x115C) = -1;
        *(s32 *)(gap_05_803AD0E0_bss - 0x360) = 0x31100;
        fn_8025DA10();
    }
}
