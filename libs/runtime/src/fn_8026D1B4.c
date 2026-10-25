// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8026D1B4-0x8026D288 (212B). Byte-identical.
// extra_cflags: -msdata=eabi, -G4
// FLAG: -msdata=eabi -G4
// Debug ring-buffer writer over lbl_803AF240 (.bss[0x80]); count/ptr live
// in .sdata lbl_803CA404/lbl_803CA408 (r13 SDA21 forms, resolved at link
// vs _SDA_BASE_). Promoted via the sda_verify route (AGENTS.md 5q).
#include "types.h"

extern u8 lbl_803AF240[];
extern u32 lbl_803CA404;
extern void *lbl_803CA408;

extern s32 fn_8028DFE8(s32 arg0, s32 buf, s32 count);

s32 fn_8026D1B4(s32 arg0, u8 *arg1, u32 arg2, s32 arg3) {
    s32 temp_r3;
    s32 temp_r5;
    u32 i;

    if (arg3 == 1) {
        temp_r3 = fn_8028DFE8(arg0, lbl_803AF240, lbl_803CA404);
        lbl_803CA404 = 0;
        lbl_803CA408 = lbl_803AF240;
        return temp_r3;
    }
    for (i = 0; i < arg2; i++) {
        *(u8 *)lbl_803CA408 = arg1[i];
        lbl_803CA408 = (u8 *)lbl_803CA408 + 1;
        temp_r5 = lbl_803CA404 + 1;
        lbl_803CA404 = temp_r5;
        if (temp_r5 > 0x7f) {
            temp_r3 = fn_8028DFE8(arg0, lbl_803AF240, temp_r5);
            lbl_803CA408 = lbl_803AF240;
            lbl_803CA404 = 0;
            if (temp_r3 == 0) {
                return 0;
            }
        }
    }
    return i;
}
