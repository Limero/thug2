// range=0x80042F38-0x80042F44 size=12B
// Leaf: stores f1→arg0+0x1b0, f2→arg0+0x1b4.
// Suggested rename: SetPos2D
#include "types.h"
#include "structs.h"

void fn_80042F38(Unk_C7387A53 *arg0, f32 f1, f32 f2) {
    *((f32 *)&arg0->unk0x1B0) = f1;
    *((f32 *)&arg0->unk0x1B4) = f2;
}
