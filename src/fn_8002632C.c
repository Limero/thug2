// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002632C-0x80026444 (280B). Byte-identical.
// Validates 4 halfword slots of a buffer via fn_80014904, then byte-swaps
// (endian-flips) all four u16s; returns 1 when the full buffer passed.
// Suggested rename: fn_ValidateAndByteSwapBuffer or fn_ReadSwappedShorts.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 fn_80014904(void *, s32, s32, s32);
bool fn_8002632C(s32 arg0, void *arg1) {
    void *p = arg1;
    s32 cnt = 0;
    do {
        if (fn_80014904(p, 2, 1, arg0) == 0) return false;
        if (fn_80014904(p + 2, 2, 1, arg0) == 0) return false;
        if (fn_80014904(p + 4, 2, 1, arg0) == 0) return false;
        if (fn_80014904(p + 6, 2, 1, arg0) != 0) {
            *(u16 *)p = (u16)((((u16)*(u16 *)p) >> 8) | (((u16)*(u16 *)p) << 8));
            *(u16 *)(p + 2) = (u16)((((u16)*(u16 *)(p + 2)) >> 8) | (((u16)*(u16 *)(p + 2)) << 8));
            *(u16 *)(p + 4) = (u16)((((u16)*(u16 *)(p + 4)) >> 8) | (((u16)*(u16 *)(p + 4)) << 8));
            *(u16 *)(p + 6) = (u16)((((u16)*(u16 *)(p + 6)) >> 8) | (((u16)*(u16 *)(p + 6)) << 8));
            cnt++;
            p += 8;
        } else {
            return false;
        }
    } while (cnt <= 0xFF);
    return true;
}