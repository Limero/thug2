// range=0x8002CA4C-0x8002CA64 size=24B
// Leaf: clears upper bits and sets bit 16 of *(arg0+0x1e4), returns arg0.
// Assembly: clrlwi r0,r0,0xf (clear top 15 bits = keep lower 17); oris r0,r0,1 (set bit 16)
// Suggested rename: SetFlag16_0x1E4
#include "types.h"

void *fn_8002CA4C(void *arg0) {
    u32 *p = (u32 *)((char *)arg0 + 0x1e4);
    *p = (*p & 0x1FFFF) | 0x10000;
    return arg0;
}
