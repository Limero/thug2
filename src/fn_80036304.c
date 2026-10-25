// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80036304-0x80036328 (36B). Byte-identical.
#include "types.h"
#include "structs.h"
f32 fn_80036304(CStruct *arg0) {
    f32 x = *(f32 *)arg0;
    f32 y = *((f32 *)&arg0->unk0x4);
    f32 z = *((f32 *)&arg0->unk0x8);
    f32 w = *((f32 *)&arg0->unk0xC);
    return x*x + y*y + z*z + w*w;
}
