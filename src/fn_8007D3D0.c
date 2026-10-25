// range=0x8007D3D0-0x8007D3E8 size=24B
// Leaf: loads *(s32*)(arg1 + arg2*4 + 0x24) into *arg0, returns arg0.
// Suggested rename: GetTableField_0x24
#include "types.h"

void *fn_8007D3D0(void *arg0, void *arg1, s32 arg2) {
    *(s32 *)arg0 = *(s32 *)((char *)arg1 + arg2 * 4 + 0x24);
    return arg0;
}
