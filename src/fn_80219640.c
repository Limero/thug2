// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80219640-0x80219668 (40B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80219640(CStruct *o, s32 v) {
    if (v)
        *((u32 *)&o->unk0x4) |= 0x1u;
    else
        *((u32 *)&o->unk0x4) &= ~0x1u;
}
