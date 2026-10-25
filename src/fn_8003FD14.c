// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003FD14-0x8003FDDC (200B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

// CScreenElement_SetRGBA @ 0x8003FD14
void CScreenElement_SetRGBA(void *arg0, s32 *arg1, s32 arg2) {
    u32 cur;
    u32 want;
    want = *arg1;
    cur = *(u32 *)((char *)arg0 + 0x110);
    if (((cur >> 24) != (want >> 24)) ||
        ((((u8 *)&cur)[1] != (((want >> 16) & 0xff)))) ||
        ((((u8 *)&cur)[2] != (((want >> 8) & 0xff)))) ||
        ((((u8 *)&cur)[3] != (((u8 *)&want)[3])))) {
           u32 w = want;
           u32 b0 = w >> 24;
           u32 b1 = (w >> 16) & 0xff;
           u32 b2 = (w >> 8) & 0xff;
           u8 *d = (u8 *)((char *)arg0 + 0xD0);
           d[0x40] = b0;
           d[0x41] = b1;
           d[0x42] = b2;
           d[0x43] = w;
           *(u32 *)((char *)arg0 + 0xC) |= 0x400;
    }
    if (arg2 != 0) {
           u32 w = want;
           u32 b0 = w >> 24;
           u32 b1 = (w >> 16) & 0xff;
           u32 b2 = (w >> 8) & 0xff;
           u8 *d = (u8 *)((char *)arg0 + 0x88);
           d[0x40] = b0;
           d[0x41] = b1;
           d[0x42] = b2;
           d[0x43] = w;
           *(u32 *)((char *)arg0 + 0xC) |= 0x400;
    }
}
