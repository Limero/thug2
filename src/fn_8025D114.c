// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025D114-0x8025D1A0 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern u8 lbl_803ACCC0[];
void fn_8025CDD4(s32);
void fn_8025CF10(void *, s32);

void fn_8025D114(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 buf[0x18];
    u8 *p = buf;
    s32 i;
    s32 sh;
    s32 gv;

    for (i = 0; i < 0x18; i++) {
        *p++ = 0;
    }
    gv = *(s32 *)(lbl_803ACCC0 + 0x54);
    sh = 0x10;
    __asm__("" : "=r" (sh) : "r" (sh));
    *(u16 *)(buf + 2) = sh << 8;
    buf[0] = 9;
    if (gv != 0) {
        buf[8] = 9;
    } else {
        buf[8] = 0xB;
    }
    *(s32 *)(buf + 0xC) = arg0;
    *(s32 *)(buf + 0x10) = arg3;
    *(s32 *)(buf + 0x14) = arg2;
    fn_8025CDD4(0x18);
    fn_8025CF10(buf, 0x18);
}
