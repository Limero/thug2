// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013AD0C-0x8013ADE8 (220B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8029F480[];
s32 fn_8013E2BC(s32);
void fn_801396A4(s32);
void fn_8013EA38(s32, s32);
void fn_8013AD0C(s32 arg0) {
    s32 sp8[3];
    register s32 b __asm__("r29");
    register s32 q __asm__("r31");
    s32 lblv;
    register s32 x __asm__("r11");
    s32 cur, n, a2;
    register s32 a __asm__("r3");
    b = (s32)&sp8[0];
    lblv = (s32)lbl_8029F480;
    *(s32 *)((char *)b + 8) = lblv;
    *(s32 *)((char *)b + 4) = 0;
    fn_8013E2BC(arg0);
    q = (s32)b;
    fn_801396A4(arg0 + 4);
    cur = arg0 + 0x227C;
    *(s32 *)((char *)b + 4) = cur;
    n = *(s32 *)((char *)cur + 0xC);
    if (*(s32 *)((char *)n + 4) == -1) { n = 0; }
    *(s32 *)((char *)q + 4) = n;
    if (n == 0) { __asm__("" : "+r"(n)); n = 0; } else { n = *(s32 *)((char *)n + 4); }
    a = n;
    if (a == 0) { goto done; }
    do {
        n = *(s32 *)((char *)q + 4);
        x = *(s32 *)((char *)n + 0xC);
        if (*(s32 *)((char *)x + 4) == -1) { x = 0; }
        *(s32 *)((char *)q + 4) = x;
        a2 = x ? *(s32 *)((char *)x + 4) : 0;
        if (a != 0) { fn_8013EA38(a, 3); }
        a = a2;
    } while (a != 0);
    done:
    *(s32 *)((char *)q + 8) = (s32)lbl_8029F480;
}
