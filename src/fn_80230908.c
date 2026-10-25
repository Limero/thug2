// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80230908-0x80230990 (136B). Byte-identical.
#include "types.h"
void fn_802309C8(s32, s32, s32 *, s32 *);
s32 fn_80230908(s32 arg0, s32 arg1) {
    s32 sp8;
    s32 spC;
    s32 hi;
    register s32 cnt __asm__("r10");
    s32 i;
    register s32 hb __asm__("r8");
    s32 off;
    char *p;
    s32 val;

    sp8 = 0;
    spC = 0;
    fn_802309C8(arg0, arg1, &sp8, &spC);
    hi = spC;
    cnt = 0;
    i = sp8;
    if (i <= hi) {
        __asm__("" : "+r"(hi));
        hb = hi;
        off = i * 0x28 + 0xBC;
        p = (char *)(off + (s32)arg0);
        do {
            val = *(s32 *)p;
            p += 0x28;
            if (val != 0) {
                cnt++;
            }
            i++;
        } while (i <= hb);

    }
    return cnt;
}
