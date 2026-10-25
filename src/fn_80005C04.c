// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80005C04-0x80005C28 (36B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80005C04(CStruct *arg0) {
    f32 a = *(f32 *)arg0;
    f32 c = *((f32 *)&arg0->unk0x4);
    f32 b = *((f32 *)&arg0->unk0x8);
    *(f32 *)arg0 = -a;
    *((f32 *)&arg0->unk0x4) = -b;
    *((f32 *)&arg0->unk0x8) = c;
}
