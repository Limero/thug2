// range=0x8002C904-0x8002C914 size=16B
// Leaf: stores f1→arg0+0, f2→arg0+4, f3→arg0+8.
// Suggested rename: Vec3Store3
#include "types.h"
#include "structs.h"

void fn_8002C904(CStruct *arg0, f32 f1, f32 f2, f32 f3) {
    *(f32 *)arg0 = f1;
    *((f32 *)&arg0->unk0x4) = f2;
    *((f32 *)&arg0->unk0x8) = f3;
}
