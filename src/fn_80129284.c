// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80129284-0x801292A8 (36B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80129284(CStruct *arg0, s32 arg1, f32 farg0) {
    if (*((u32 *)&arg0->unk0x4) == 1) {
        *((f32 *)&arg0->unk0x8) = farg0;
    } else {
        ((f32 *) * (u32 *)((char *)arg0 + 8))[arg1] = farg0;
    }
}