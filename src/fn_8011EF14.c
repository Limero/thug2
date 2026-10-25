// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011EF14-0x8011EF98 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8029D6B0[];
extern char lbl_80302D0B[];
extern unsigned int strlen(const char *);
extern char *strcpy(char *, const char *);
s32 fn_8011E9A0(s32, s32, s32, s32);
bool fn_8011EF14(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 n = strlen((char *)arg0);
    u8 *q;
    strcpy(lbl_80302D0B, arg0);
    q = (u8 *)((char *)n + (s32)lbl_80302D0B);
    *(s32 *)q = *(s32 *)lbl_8029D6B0;
    q[4] = *(u8 *)((u8 *)lbl_8029D6B0 + 4);
    fn_8011E9A0(arg2, (s32)lbl_80302D0B - 0xB, (arg3 == 0), arg2 + 0xC);
    return true;
}
