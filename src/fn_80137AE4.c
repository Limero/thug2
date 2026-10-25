// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80137AE4-0x80137B30 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 strncpy(char *, s32, s32);
void fn_80137AE4(s32 arg0, s32 arg1, s32 arg2) {
    s32 off;
    char *p;

    off = arg1 << 5;
    strncpy((char *)arg0 + (off + 0x34), arg2, 0x1F);
    p = (char *)arg0 + 0x53;
    *(u8 *)(p + off) = 0;
}
