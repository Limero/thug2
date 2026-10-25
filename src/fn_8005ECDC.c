// range=0x8005ECDC-0x8005ECF8 size=28B
// Leaf: zeroes 4 bytes at arg0 using individual byte stores, returns arg0.
// Suggested rename: ZeroInit_4
#include "types.h"

void *fn_8005ECDC(void *arg0) {
    s8 *p = (s8 *)arg0;
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    return arg0;
}
