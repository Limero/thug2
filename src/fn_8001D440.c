// range=0x8001D440-0x8001D454 size=20B
// Leaf: stores 3 floats (f1,f2,f3) to arg0+0, arg0+4, arg0+8. Returns arg0.
// Suggested rename: Vec3Store
#include "types.h"
#include "structs.h"

void *fn_8001D440(CStruct *arg0, f32 f1, f32 f2, f32 f3) {
    *(f32 *)arg0 = f1;
    *((f32 *)&arg0->unk0x4) = f2;
    *((f32 *)&arg0->unk0x8) = f3;
    return arg0;
}
