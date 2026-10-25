// fn_8026BBC4 — SN ProDG newlib runtime (byte-exact, ngccc -O2 -G0).
// range 0x8026BBC4-0x8026BC98 (212B). Byte-identical.
// extra_cflags: -msdata=eabi -G4
// FLAG: -msdata=eabi -G4
// Buffered byte-writer twin of fn_8026D1B4: appends arg1[0..arg2) into the
// 128B .bss buffer lbl_803AF1C0; count/ptr live in .sdata lbl_803CA3FC/
// lbl_803CA400 (r13 SDA21 forms, resolved at link vs _SDA_BASE_).
// Ported verbatim from libs/runtime/src/fn_8026D1B4.c (same temps, order,
// SDA route) — LINK-SIM EXACT on the first attempt. Promoted via the
// sda_verify route (AGENTS.md §5q).
#include "types.h"

extern u8 lbl_803AF1C0[];
extern u32 lbl_803CA3FC;
extern void *lbl_803CA400;

extern s32 fn_8028DFE8(s32 arg0, s32 buf, s32 count);

s32 fn_8026BBC4(s32 arg0, u8 *arg1, u32 arg2, s32 arg3) {
    s32 temp_r3;
    s32 temp_r5;
    u32 i;

    if (arg3 == 1) {
        temp_r3 = fn_8028DFE8(arg0, lbl_803AF1C0, lbl_803CA3FC);
        lbl_803CA3FC = 0;
        lbl_803CA400 = lbl_803AF1C0;
        return temp_r3;
    }
    for (i = 0; i < arg2; i++) {
        *(u8 *)lbl_803CA400 = arg1[i];
        lbl_803CA400 = (u8 *)lbl_803CA400 + 1;
        temp_r5 = lbl_803CA3FC + 1;
        lbl_803CA3FC = temp_r5;
        if (temp_r5 > 0x7f) {
            temp_r3 = fn_8028DFE8(arg0, lbl_803AF1C0, temp_r5);
            lbl_803CA400 = lbl_803AF1C0;
            lbl_803CA3FC = 0;
            if (temp_r3 == 0) {
                return 0;
            }
        }
    }
    return i;
}
