// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025CFB4-0x8025CFFC (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// ID: compiler runtime helper __cvt_fp2unsigned(f32) -> s32 (float->unsigned
//     conversion via 2^31 bias trick: subtract 2^31 then flip sign bit).
#include "types.h"
extern u8 lbl_802B1CD8[];
s32 __cvt_fp2unsigned(f32 farg0) {
    register char *k9 __asm__("r9");
    register f64 kk __asm__("fr0");
    __asm__ volatile("lis %0, lbl_802B1CD8@ha" : "=r"(k9));
    __asm__ volatile("addi %0, %0, lbl_802B1CD8@l" : "+r"(k9));
    __asm__ volatile("lfd %0, 0(%1)" : "=f"(kk) : "r"(k9));
    if (farg0 >= kk) {
        return ((s32) (farg0 - kk)) ^ 0x80000000;
    }
    return (s32) farg0;
}
