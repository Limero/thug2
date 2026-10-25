// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012CBD4-0x8012CBE8 (20B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// WriteBE16: writes u16 arg1 big-endian (hi byte first) to *arg0 and returns
// arg0 + 2 (the pre-increment store form reproduces the stbu + addi).
// Suggested rename: WriteBE16
#include "types.h"
void *fn_8012CBD4(u8 *arg0, u32 arg1) {
    *arg0 = arg1;
    *++arg0 = arg1 >> 8;
    return ++arg0;
}