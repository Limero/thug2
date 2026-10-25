// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001B7F4-0x8001B838 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80300178[];
// 4 incoming args: want forwards r6 (mr r7,r6) and keeps r3 untouched
// (arg1 is the vcall's FIRST arg), so the callee signature is (a,b,c,d).
void fn_8001B7F4(s32 a, s32 b, s32 c, s32 d) {
    s32 (*temp_r9)();

    temp_r9 = *(s32 (**)())lbl_80300178;
    // call order from want: r3=a, r4=0xA, r5=b, r6=c, r7=d; the old-style
    // (unprototyped) fn-ptr type is what emits want's `crclr cr1eq`.
    temp_r9(a, 0xA, b, c, d);
}
