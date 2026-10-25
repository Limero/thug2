// range=0x8007D320-0x8007D330 size=16B
// Leaf: copies *(s32*)(arg1 + 0x20) to *arg0, returns arg0.
// Suggested rename: GetField_0x20_Store
#include "types.h"
#include "structs.h"

void *fn_8007D320(void *arg0, Unk_C7387A53 *arg1) {
    *(s32 *)arg0 = arg1->unk0x20;
    return arg0;
}
