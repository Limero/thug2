// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009F644-0x8009F66C (40B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8009F644(Unk_9994C3F5 *o, s32 v) {
    if (v)
        *((u32 *)&o->unk0x8) |= 0x1u;
    else
        *((u32 *)&o->unk0x8) &= ~0x1u;
}
