// range=0x8012CB2C-0x8012CB60 size=52B
// Leaf: reads u32 big-endian from 4 bytes at arg1, stores to *arg0, returns arg0.
// Suggested rename: ReadBE32
#include "types.h"

void *fn_8012CB2C(void *arg0, u8 *arg1) {
    u32 v = arg1[0];
    v |= (u32)arg1[1] << 8;
    v |= (u32)arg1[2] << 16;
    v |= (u32)arg1[3] << 24;
    *(u32 *)arg0 = v;
    return arg0;
}
