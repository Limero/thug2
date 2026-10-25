// range=0x800576C4-0x800576E0 size=28B
// Leaf: fills 4 bytes at arg0 with 0x80, returns arg0.
// Suggested rename: FillFF_4
#include "types.h"

void *fn_800576C4(void *arg0) {
    s8 *p = (s8 *)arg0;
    p[0] = -0x80;
    p[1] = -0x80;
    p[2] = -0x80;
    p[3] = -0x80;
    return arg0;
}
