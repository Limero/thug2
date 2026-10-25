// range=0x8012CB60-0x8012CB7C size=28B
// Leaf: reads u16 big-endian from 2 bytes at arg1, stores to *arg0, returns arg0.
// Suggested rename: ReadBE16
#include "types.h"

void *fn_8012CB60(void *arg0, u8 *arg1) {
    *(u16 *)arg0 = arg1[0] | (arg1[1] << 8);
    return arg0;
}
