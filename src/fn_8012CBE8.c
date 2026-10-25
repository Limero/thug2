// range 0x8012CBE8-0x8012CC0C (0x24). Byte-identical.
// Identification: token-stream skip — scans a byte buffer forward, skipping
// a 1-byte token (byte==1 → +1) or a 5-byte record (byte==2 → +5),
// returning the pointer at the first non-token byte. Used to walk a
// run-length/packing table.
#include "types.h"
u8 *fn_8012CBE8(u8 *p) {
    for (;;) {
        u8 c = *p;
        if (c == 1) { p += 1; continue; }
        if (c == 2) { p += 5; continue; }
        return p;
    }
}