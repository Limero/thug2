// range=0x800A7C88-0x800A7C9C size=20B
// Leaf: zeroes two s32 fields at arg0+0 and arg0+4, returns arg0.
// Suggested rename: ZeroInit_8
#include "types.h"
#include "structs.h"

void *fn_800A7C88(CStruct *arg0) {
    *(s32 *)arg0 = 0;
    arg0->unk0x4 = 0;
    return arg0;
}
