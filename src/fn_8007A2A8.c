// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007A2A8-0x8007A334 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Identification: 2bpp pixel-order mirror — reverses the four 2-bit pixel
// groups inside every byte of two u16 cells (involution). Matching key: the
// eight shifted-mask terms must be emitted low byte first, and the first
// pair of each byte written 0x03<<6 BEFORE 0x0C<<2; that order lets the
// scheduler produce want's asymmetric interleave. Writing 0x0C<<2 first (the
// order want prints for the first cell) scores 88.6%.
#include "types.h"

u32 fn_8007A2A8(u16 *arg0) {
    u32 h1 = arg0[0];
    u32 h2 = arg0[1];

    return ((((h1 & 0x03) << 6) | ((h1 & 0x0C) << 2) | ((h1 & 0x30) >> 2) | ((h1 & 0xC0) >> 6) |
             ((h1 & 0x0300) << 6) | ((h1 & 0x0C00) << 2) | ((h1 & 0x3000) >> 2) | ((h1 & 0xC000) >> 6)) << 16) |
           (((h2 & 0x03) << 6) | ((h2 & 0x0C) << 2) | ((h2 & 0x30) >> 2) | ((h2 & 0xC0) >> 6) |
            ((h2 & 0x0300) << 6) | ((h2 & 0x0C00) << 2) | ((h2 & 0x3000) >> 2) | ((h2 & 0xC000) >> 6));
}
