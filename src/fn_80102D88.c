// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80102D88-0x80102DB0 (40B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80102D88(CStruct *o, s32 v) {
    if (v)
        *((u32 *)&o->unk0x0) |= 0x1u;
    else
        *((u32 *)&o->unk0x0) &= ~0x1u;
}
