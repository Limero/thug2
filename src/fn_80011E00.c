// range=0x80011E00-0x80011E14 size=20B
// Leaf: *(arg0+4) -= arg1, returns arg0.
// Suggested rename: SubField_4
#include "types.h"
#include "structs.h"

void *fn_80011E00(CStruct *arg0, s32 arg1) {
    arg0->unk0x4 -= arg1;
    return arg0;
}
