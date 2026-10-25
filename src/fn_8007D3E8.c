// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007D3E8-0x8007D410 (40B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8007D3E8(Unk_31DE137E *o, s32 v) {
    if (v)
        *((u32 *)&o->unk0x1C) |= 0x1u;
    else
        *((u32 *)&o->unk0x1C) &= ~0x1u;
}
